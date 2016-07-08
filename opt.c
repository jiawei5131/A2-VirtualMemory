//opt.c
#include <stdio.h>
#include <assert.h>
#include <unistd.h>
#include <getopt.h>
#include <stdlib.h>
#include <string.h>
#include "pagetable.h"

extern pgdir_entry_t init_second_level();

extern int memsize;

extern int debug;

extern struct frame *coremap;

extern char *tracefile;

extern pgdir_entry_t pgdir[PTRS_PER_PGDIR];

typedef struct linked_vad linked_vad;

// struct used to store sequence of the tracefile
struct linked_vad {
	long long vaddr;
	linked_vad* next;
};

// head of the entire linked list of virtural address
linked_vad *head;

/* Page to evict is chosen using the optimal (aka MIN) algorithm. 
 * Returns the page frame number (which is also the index in the coremap)
 * for the page that is to be evicted.
 *
 * Main idea: Read through the entire linked_vad to find the frame number 
 * that appears the last.
 */
 

int opt_evict() {
	linked_vad *current;
	long long cur_vad;
	int last_appear = 0;
	int counter = 0;	// counter to keep track if the frame is the last

	current = head;

	// an array to keep a record wether certain frame has appeared in the
	// linked_vad sequence.
	int *records = malloc(memsize * sizeof(int));
	// Zero the array
	memset(records, 0, memsize * sizeof(int));


	while(current){
		cur_vad = current->vaddr;

		pgtbl_entry_t *p=NULL; // pointer to the full page table entry for vaddr
		unsigned idx = PGDIR_INDEX(cur_vad); // get index into page directory

		// Use top-level page directory to get pointer to 2nd-level page table

		if (!(pgdir[idx].pde & PG_VALID)){	// 2nd-level pt not initialized
			pgdir[idx] = init_second_level();
		}

		// Get a pointer to the 2nd-level page table
		pgtbl_entry_t *pgtbl = (pgtbl_entry_t *)((pgdir[idx].pde) & PAGE_MASK);
		// Get the index of the page table entry and initialize 'p'
		p = &pgtbl[PGTBL_INDEX(cur_vad)];

		if (p->frame & PG_VALID){ // case: the frame pointed by vaddr is in memory
			int frame_num = p->frame >> PAGE_SHIFT;
			// check if this frame has appeared
			if (records[frame_num] == 0){	// case: not appeared
				// check if this frame is the last
				if (counter == memsize - 1){	// case: last appear
					// this frame will be evicted
					last_appear = frame_num;
					free(records);

					return last_appear;

				}else{	// not the last
					records[frame_num] = 1;
					counter ++;
				}
			}else{	// case: appeared before
				// do nothing
			}
		}

		// keep reading
		current = current->next;
	}

	// last appearing page not found
	int i;

	for (i = 0; i < memsize; i ++){
		// find the first not appeared frame to evict
		if (records[i] == 0){
			last_appear = i;
		}
	}

	free(records);

	return last_appear;
}

/* This function is called on each access to a page to update any information
 * needed by the opt algorithm.
 * Input: The page table entry for the page that is being accessed.
 */
void opt_ref(pgtbl_entry_t *p) {
	// Keep a temperory reference to the current head for free().
	linked_vad *tmp = head;

	// As the program keeps references, the sequence of vaddr keeps moving.
	head = head->next;

	// The program just accessed head, hence move forward.
	free(tmp);
	return;
}

/* Initializes any data structures needed for this
 * replacement algorithm.
 */
void opt_init() {
	FILE *fd;
	long long vaddr;
	linked_vad *list_vaddr_cur_e = NULL;
	linked_vad *list_vaddr_last_e = NULL;


	if ((fd = fopen(tracefile, "r")) == NULL){
		perror("Error opening tracefile:");
		exit(1);
	}

	// read the first line and set head
	if ((fscanf(fd, "%*c %llx\n", &vaddr)) != -1) {
		head = malloc(sizeof(linked_vad));

		if (head == NULL){
			perror("malloc");
			exit(1);
		}

		head->vaddr = vaddr;
		list_vaddr_last_e = head;
	}else{
		perror("fscanf");
		exit(1);
	}

	// keep reading the rest of the file.
	while ((fscanf(fd, "%*c %llx\n", &vaddr)) != -1) {
        list_vaddr_cur_e = malloc(sizeof(linked_vad));

        if (list_vaddr_cur_e == NULL){
        	perror("malloc");
        	exit(1);
        }

        list_vaddr_cur_e->vaddr = vaddr;

        // link the last struct with current.
        list_vaddr_last_e->next = list_vaddr_cur_e;

        // prepare for the next loop
        list_vaddr_last_e = list_vaddr_cur_e;
    }

    return;

}


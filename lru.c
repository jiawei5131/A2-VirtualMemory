//lru.c
#include <stdio.h>
#include <assert.h>
#include <unistd.h>
#include <getopt.h>
#include <stdlib.h>
#include "pagetable.h"


extern int memsize;

extern int debug;

extern struct frame *coremap;

struct QNode{
	int frameNum;
	struct QNode *next;
};

struct node *rm_frame;
struct node *tail;
bool *r_bit;
/* Page to evict is chosen using the accurate LRU algorithm.
 * Returns the page frame number (which is also the index in the coremap)
 * for the page that is to be evicted.
 */

int lru_evict() {
	int frameNum = rm_frame -> frame;
	if (rm_frame=tail){
		tail = NULL;
	}
	struct node *new_rm_frame = rm_frame -> next;
	free (rm_frame);
	rm_frame = new_rm_frame;
	return frameNum;
}

/* This function is called on each access to a page to update any information
 * needed by the lru algorithm.
 * Input: The page table entry for the page that is being accessed.
 */
void lru_ref(pgtbl_entry_t *p) {
	int frame = p->frame >> PAGE_SHIFT;
	if (r_bit[frame] == 0){
		r_bit[frame] == 1;
		QNode *new = malloc(sizeof(QNode));
		new -> frame = frame;
		new -> next = NULL;
		
		
	}	
	return;
}


/* Initialize any data structures needed for this 
 * replacement algorithm 
 */
void lru_init() {
	rm_frame = 0;
}


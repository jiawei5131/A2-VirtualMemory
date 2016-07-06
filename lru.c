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

// struct QNode{
	// int frameNum;
	// struct QNode *next;
// };

// struct node *head;
// struct node *tail;
// bool *r_bit;
/* Page to evict is chosen using the accurate LRU algorithm.
 * Returns the page frame number (which is also the index in the coremap)
 * for the page that is to be evicted.
 */

int lru_evict() {
	// int frame = head -> frame;
	// if (head = tail){
		// tail = NULL;
	// }
	// struct node *new_head = head -> next;
	// free (head);
	// head = new_head;
	// return frame;
}

/* This function is called on each access to a page to update any information
 * needed by the lru algorithm.
 * Input: The page table entry for the page that is being accessed.
 */
void lru_ref(pgtbl_entry_t *p) {
	// int frame = p->frame >> PAGE_SHIFT;
	// if (r_bit[frame] == 0){
		// r_bit[frame] == 1;
		// QNode *new = malloc(sizeof(QNode)); //create a space to hold the frame
		// new -> frame = frame;
		// new -> next = NULL;
		
		// if (tail == NULL){ // if list is empty
			// tail = new;
			// head = tail
		// }else{
			// tail -> next = new;
			// tail = new;
		// }
	// }else{
		// QNode *new = malloc(sizeof(QNode)); //put the new node at the end of the list
		// new -> frame = frame;
		// new -> next = null;
		// tail -> next = new;
		// tail = new;
		
		// struct node *temp = head;
		// struct node *temp2 = NULL;
		// while (temp -> frame != frame){
			// if (temp->next != NULL){
				// temp = temp -> next;
			// }else{
				// break;
			// }
		// }
		
		// if (temp -> frame == frame);{
			case: frame found
			// temp2 = temp -> next;
			// temp -> next = temp2 -> next;
			// free(temp2);
		// }else(temp->next == NULL ){
			case: frame not found
		// }
		// }
		
		
	// }	
	// return;
}


/* Initialize any data structures needed for this 
 * replacement algorithm 
 */
void lru_init() {
	// rm_frame = 0;
}


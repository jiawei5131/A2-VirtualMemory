//lru.c
#include <stdio.h>
#include <assert.h>
#include <unistd.h>
#include <getopt.h>
#include <stdlib.h>
#include "pagetable.h"

#include <stdbool.h>


extern int memsize;

extern int debug;

extern struct frame *coremap;

// struct QNode{
	// int frame;
	// struct QNode *next;
// };

// struct node *head;
// struct node *tail;

/* Page to evict is chosen using the accurate LRU algorithm.
 * Returns the page frame number (which is also the index in the coremap)
 * for the page that is to be evicted.
 */

int counter;
int lru_evict() {
	int oldest;
	int i = 0;
	int compare = 0; 
	 while(i < memsize){
		if (coremap[i].pte -> stamp < compare){
			oldest = i;
			compare = coremap[i].pte -> stamp;
		}
		i++;
	}
	return oldest;
}

/* This function is called on each access to a page to update any information
 * needed by the lru algorithm.
 * Input: The page table entry for the page that is being accessed.
 */
void lru_ref(pgtbl_entry_t *p) {
	int i;
	for (i = 0; i < memsize; i++){
	counter = coremap[i].pte -> stamp;
	}
	// int frame = p->frame >> PAGE_SHIFT;
	// if (head = NULL){
		// QNode *head = malloc(sizeof(QNode)); //create a space to hold the frame
		// head -> frame = frame;
		// head -> next = NULL;
		// }else{
			// tail -> next = temp;
			// tail = temp;
		// }
	// }else{
		// QNode *new = (QNode*)malloc(sizeof(QNode)); //put the new node at the end of the list
		// new -> frame = frame;
		// new -> next = null;
		// tail -> next = temp;
		// tail = temp;
		
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
			//case: frame found
			// temp2 = temp -> next;
			// temp -> next = temp2 -> next;
			// free(temp2);
		// }else(temp->next == NULL ){
			//case: frame not found
		// }
		// }
		
		
	// }	
	// return;
}


/* Initialize any data structures needed for this 
 * replacement algorithm 
 */
void lru_init() {
	counter = 0;
	return;
}


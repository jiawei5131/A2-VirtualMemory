//lru.c
#include <stdio.h>
#include <assert.h>
#include <unistd.h>
#include <getopt.h>
#include <stdlib.h>
#include <string.h>
#include "pagetable.h"

#include <stdbool.h>


extern int memsize;

extern int debug;

extern struct frame *coremap;

/* Page to evict is chosen using the accurate LRU algorithm.
 * Returns the page frame number (which is also the index in the coremap)
 * for the page that is to be evicted.
 */

int timeline;	// Timeline that moves forward once any frame is referenced.
int* records;	// Record the last time when the frame is accessed.

int lru_evict(){
	// variable define
	int minimum = records[0];
	int frame = 0;	// frame number of the least used frame
	int i;

	// Loop the whole array to find out the least used frame
	for(i = 1; i < memsize; i ++){
		if (records[i] < minimum){
			frame = i;
		}
	}
	return frame;
}

/* This function is called on each access to a page to update any information
 * needed by the lru algorithm.
 * Input: The page table entry for the page that is being accessed.
 */
void lru_ref(pgtbl_entry_t *p) {
	// Move the timeline forward
	timeline ++;

	// Record the time as p is being referenced
	records[p->frame] = timeline;

	return;
}


/* Initialize any data structures needed for this 
 * replacement algorithm 
 */
void lru_init() {
	// Allocate space for records
	records = malloc(memsize * sizeof(int));

	// Zero the array
	memset(records, 0, sizeof records);

	timeline = 0;
	return;
}


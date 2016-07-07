//fifo.c
#include <stdio.h>
#include <assert.h>
#include <unistd.h>
#include <getopt.h>
#include <stdlib.h>
#include "pagetable.h"


extern int memsize;

extern int debug;

extern struct frame *coremap;

/* Page to evict is chosen using the fifo algorithm.
 * Returns the page frame number (which is also the index in the coremap)
 * for the page that is to be evicted.
 */
int fifo_start;
int fifo_evict() {
	int frame = fifo_start;
	fifo_start++;
	return frame;
}

/* This function is called on each access to a page to update any information
 * needed by the fifo algorithm.
 * Input: The page table entry for the page that is being accessed.
 */
void fifo_ref(pgtbl_entry_t *p) {
	if(fifo_start >= memsize){
		fifo_start = 0;
	}
	return;
}

/* Initialize any data structures needed for this 
 * replacement algorithm 
 */
void fifo_init() {
	fifo_start = 0;
}


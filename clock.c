//clock.c
#include <stdio.h>
#include <assert.h>
#include <unistd.h>
#include <getopt.h>
#include <stdlib.h>
#include "pagetable.h"


extern int memsize;

extern int debug;

extern struct frame *coremap;

int hand;




/* Page to evict is chosen using the clock algorithm.
 * Returns the page frame number (which is also the index in the coremap)
 * for the page that is to be evicted.
 */

int clock_evict() {
	
	while(1){
		if( !(coremap[hand].pte->frame & PG_REF)){ // reference bit not set(0)
			// increment the hand
			hand = (hand + 1) % memsize;

			// make sure the hand is a positive number
			return (hand - 1 + memsize) % memsize;
		}else if(coremap[hand].pte->frame & PG_REF){ // reference bit set(1)
			coremap[hand].pte -> frame &= ~PG_REF ;
			
			// increment the hand
			hand = (hand + 1) % memsize;
		}
	}
}

/* This function is called on each access to a page to update any information
 * needed by the clock algorithm.
 * Input: The page table entry for the page that is being accessed.
 */
void clock_ref(pgtbl_entry_t *p) {
	coremap[hand].pte -> frame |= PG_REF;
	return;
}

/* Initialize any data structures needed for this replacement
 * algorithm. 
 */
void clock_init(){ 
	hand = 0;
}

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

int hand = 0;

bool *r_bit;

/* Page to evict is chosen using the clock algorithm.
 * Returns the page frame number (which is also the index in the coremap)
 * for the page that is to be evicted.
 */

int clock_evict() {
	while (hand < memsize){
		if (coremap[hand].pte -> frame & PG_REF == 1){
			coremap[hand].pte -> frame & PG_REF == 0;
		}else{
			coremap[hand].pte -> frame & PG_REF == 1;
			return hand;
		}
		hand++;
	}
}

/* This function is called on each access to a page to update any information
 * needed by the clock algorithm.
 * Input: The page table entry for the page that is being accessed.
 */
void clock_ref(pgtbl_entry_t *p) {
	int frame = p -> frame >> PAGE_SHIFT;
	coremap[frame].pte -> frame & PG_REF == 1;
	return;
}

/* Initialize any data structures needed for this replacement
 * algorithm. 
 */
void clock_init() 
	hand = 0;
	memset()
}

#include <stdio.h>
#include <stdlib.h>
#include "gc.h"
#include "list.h"
#include "gc_list.h"


/* This function itereates over the directory system rooted at 'obj'
 * and for each node (and its memory address marks the corresponsing
 * node in the garbage collector as in use.
 */

int ds_count;

void mark_list(void *obj) {
	ds_count = 0;
    List *current = obj;
    while (current){
        mark_one(current);
        ds_count++;
        current = current->next;
	}
}

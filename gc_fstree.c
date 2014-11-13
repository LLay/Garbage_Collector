#include <stdio.h>
#include <stdlib.h>
#include "gc.h"
#include "fstree.h"


int ds_count;

/* Traverse the given Fstree 'obj' and mark the corresponding node address
 * in the garbage collector as USED
 */
void mark_fstree(void *obj) {
    if (!obj) {
        fprintf(stderr, "Error: cannot mark, obj is NULL.\n");
    } else {
        Fstree *tree = obj;
        if (!mark_one(tree)) { //check obj already marked, proceed if not.
            ds_count ++;
    	   mark_one(tree->name);
            ds_count ++;
            // iterate over the links to other directories/fstrees
            Link *curr_link = tree->links;
            while(curr_link){
                mark_one(curr_link); //Mark link as used
                ds_count ++;
                mark_fstree(curr_link->fptr); //recurse on content of link
                curr_link = curr_link->next;
            }
        }
    }
}

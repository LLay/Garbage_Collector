
/* This function itereates over the linked list rooted at 'obj'
 * and for each node (and its memory address marks the corresponsing
 * node in the garbage collector as in use.
 */
void mark_list(void *obj);

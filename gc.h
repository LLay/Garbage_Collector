/* External functions that are the interface to the garbage collector */
#ifndef LOGFILE
#define LOGFILE "gc.log"
#endif


extern int ds_count;

struct mem_chunk * MEMORY_LIST_PTR;

struct mem_chunk {
    int in_use;
    void * address;
    struct mem_chunk *next;
};

// Following convention and sytle in list.h I shall leave out func descriptions
void update_num_in_ds(int count);
void push(struct mem_chunk * head, void * address);
void delete_head(struct mem_chunk * head);
void rmv_unused(struct mem_chunk * head);
void set_all_unused(struct mem_chunk * head);
void gc_string(struct mem_chunk * head);
void signal_mark_and_sweep(int sig);
int delete(struct mem_chunk * head, void * address);
int count_allocations(struct mem_chunk * head);

/* A wrapper around malloc to keep track of dynamically allocated memory
 */
void *gc_malloc(int nbytes);

/* Executes the garbage collector.
 * mark_obj will traverse the data structure rooted at obj, calling
 * mark_one for each dynamically allocated chunk of memory to mark
 * that it is still in use.
 */
void mark_and_sweep(void *obj, void (*mark_obj)(void *));

// how do function pointers work?
// obj points to root of data structure?
// mark obj is the appropriate mark function


/* Mark vptr as still in use
 * Return code:
 *   0 on success
 *   1 if memory chunk pointed to by vptr was already marked as in use
 */
int mark_one(void *vptr);

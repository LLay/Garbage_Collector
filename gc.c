/* Garbage collector and all its functionality are implemented in this file.
*/
#include <stdio.h>
#include <stdlib.h>
#include "gc.h"
#include <time.h>
#include <sys/time.h>
#include <signal.h>
#include <unistd.h>

/* PLEASE READ MY README BEFORE YOU BEGIN. */

int NOT_USED = 0;
int USED = 1;
size_t INT_SIZE = sizeof(int);
size_t CHAR_SIZE = sizeof(char *);
size_t POINTER_SIZE = sizeof(void *);
size_t NODE_SIZE = sizeof(struct mem_chunk);

// Declare count of number of elements in a data structure. Set by mark functions
int ds_count;

/* Enables signals. TURN ON SIGNALS HERE.
 * 1 = ON,
 * 0 = OFF.
 */
static int signals_on = 0;
static sigset_t old_sigs;

// Declare log number. Incremented by mark and sweep
static int log_count = 1;
//Declare variables to be written to the log at the end of mark_and_sweep
static int num_allo_before = 0; // the number of chunks of memory allocated before sweep
static int num_freed = 0;       // the number of chunks that were freed during sweep.
static int num_allo_after = 0;  // the number of chunks of memory allocated after sweep


/* This funciton pushes a new node with the address 'address'
 * onto the given mem_chunk list. The node is flagged as in use.
 */
void push(struct mem_chunk * head, void * address) {

    struct mem_chunk * new_node;
    // Create new mem_chunk node
    if (!(new_node = malloc(NODE_SIZE))) {
            perror("malloc");
            exit(1);
        }
    // Set address
    new_node->address = address;
    // Flag as in use
    new_node->in_use = USED;
    // Set this new node as the new head
    if (!head){ // if the gc is empty, set next to null
        new_node->next = NULL;
    } else { // else set next to what head was
        new_node->next = head;
    }
    MEMORY_LIST_PTR = new_node;
}

/* This function removes all nodes that are flagged as unused.
 * It also has linear runing time! :)
 * Counts the number of freed nodes. num_freed
 * Count the number of node left in gc. Info stored in num_allo_after
 */
void rmv_unused(struct mem_chunk * head) {
    if (!head) {
        fprintf(stderr, "Error: nothing to rmv, gc empty.\n");
    }

    struct mem_chunk * del_node;
    struct mem_chunk * current = head;
    struct mem_chunk * prev = head;

    while (current) {
        if (!current->in_use){ // ie. current not used
            if (current == MEMORY_LIST_PTR) { // case for head node
                MEMORY_LIST_PTR = current->next;
                // free space allocated to desired node
                del_node = current;
                // printf("Freeing %p \n", del_node->address);
                free(del_node->address);
                del_node->address = NULL;
                free(del_node);
                num_freed ++; //increment the count of freed nodes in gc
                current = MEMORY_LIST_PTR;
                prev = MEMORY_LIST_PTR;
            } else { //case for all other nodes
                // remove node from list
                prev->next = prev->next->next;
                // free space allocated to desired node
                del_node = current;
                free(del_node->address);
                del_node->address = NULL;
                free(del_node);
                num_freed ++; //increment the count of freed nodes in gc
                current = prev->next;
            }
        } else { // current not to be deleted, iterate.
            num_allo_after ++; //increment the count of undeleted nodes in gc
            prev = current;
            current = current->next;
        }
    }
}

/* This function sets all node in_use attributes to NOT_USED
 * in the given mem_chunk list.
 */
void set_all_unused(struct mem_chunk * head) {
    if (!head) {
        fprintf(stderr, "Error: nothing to set, gc empty.\n");
    }
    struct mem_chunk *current = head;
    while (current){
        current->in_use = NOT_USED;
        num_allo_before ++;
        current = current->next;
    }
}

/* Prints the contents of the garbage collector */
void gc_string(struct mem_chunk * head) {
    int count = 0;
    struct mem_chunk *current = head;
    while (current){
        //printf("gc node points to%p\n", current->address);
        current = current->next;
        count++;
    }
    printf("gc has %d nodes\n", count);
}

/* A wrapper around malloc to keep track of dynamically allocated memory
 * Signaling: This function contains a signal handler that prevents
 * interuption from a SIGUSR1 signal.
 */
void *gc_malloc(int nbytes) {

    if (signals_on) {
        // Set up signal handler/blocker
        sigset_t sigs;
        sigemptyset(&sigs);
        /* Add SIGINT to the set */
        sigaddset(&sigs, SIGINT);
        /* Add signals to blocked set (save old mask) */
        sigset_t old_sigs;

        //Block signals
        if (sigprocmask(SIG_BLOCK, &sigs, &old_sigs) != 0) {
            exit(1);
        }
        printf("Mallocing with signal blocker. Try to stop me! Sleeping for 20s\n");
        sleep(15);
    }

    //printf("Mallocing, try to mark mark_and_sweep again, you cant!\n");
    //sleep(20);
    void *target = malloc(nbytes);
    if (!target) {
        fprintf(stderr, "failed to allocate memory.\n");
        exit(1);
    }


    // Add target to garbage collector list
    push(MEMORY_LIST_PTR, target);

    if (signals_on) {
        // Unblock signals
        if(sigprocmask(SIG_SETMASK, &old_sigs, NULL) != 0) {
            exit(1);
        }
    }
    return target;

}

/* Mark vptr as still in use
 * Return code:
 *   0 on success
 *   1 if memory chunk pointed to by vptr was already marked as in use
 */
int mark_one(void *vptr) {
    struct mem_chunk * current = MEMORY_LIST_PTR;
    while (current) {
        if (current->address == vptr) {
            if (current->in_use == USED) {
                return 1;
            } else {
                current->in_use = USED;
                return 0;
            }
        }
        current = current->next;
    }
    return 1;
}

void signal_mark_and_sweep(int sig) {
}

/* Executes the garbage collector.
 * mark_obj will traverse the data structure rooted at obj, calling
 * mark_one for each dynamically allocated chunk of memory to mark
 * that it is still in use.
 * Logging: This function writes to LOGFILE the number of chunks of memory
 * allocated before sweep,
 * freed during sweep,
 * and allocated after sweep.
 * As well as the time and date of the function execution
 * Signaling: This function contains a signal handler that prevents
 * interuption from a SIGUSR1 signal.
 */
void mark_and_sweep(void *obj, void (*mark_obj)(void *)) {
    if (signals_on) {
        /* Initialize signal set */
        sigset_t sigs;
        sigemptyset(&sigs);
        /* Add SIGINT to the set */
        sigaddset(&sigs, SIGINT);
        /* Add signals to blocked set (save old mask) */
        sigset_t old_sigs;

        //Block signals
        if(sigprocmask(SIG_BLOCK, &sigs, &old_sigs) != 0) {
            fprintf(stderr, "Failed to block SIGUSR1\n");
            exit(1);
        }
        printf("Mark and sweeping, try to malloc again, you cant! Sleeping for 20s\n");
        sleep(20);
    }

    //open log file for appending
    FILE *logfile;
    logfile = fopen(LOGFILE, "a+" );
    // Set the current system time.
    time_t rawtime;
    struct tm * timeinfo;
    time ( &rawtime );
    timeinfo = localtime ( &rawtime );

    //reset count of # of elements in the data structure. Updated by mark_obj
    ds_count = 0;

    //Mark and Sweep:
    // Step 1: Reset all flags to NOT_USED
    //printf("Setting unused\n");
    set_all_unused(MEMORY_LIST_PTR);
    //printf("Done setting unused\n");

    // Step 2: Mark. Traverse data structure 'obj', change each element's
    // corresponsing node in the garbage collector list to USED. Use the mark
    // function 'mark_obj'.
    // Set sftree_count to number of elemts in the sata structure
    //
    //printf("marking\n");
    mark_obj(obj);
    //printf("Done marking\n");

    // Step 3: Sweep. Iterate over garbage collector list and remove all
    // nodes still flagged as NOT_USED
    //printf("Sweeping\n");
    rmv_unused(MEMORY_LIST_PTR);
    //printf("Done sweeping\n");

    // Write to log file
    fprintf(logfile,"\nGarbage collections report #%d\n%s", log_count, asctime (timeinfo) );
    fprintf(logfile, "Number of elements in data structure:%d\n", ds_count);
    fprintf(logfile, "Number of elements in gc before sweep:%d\n", num_allo_before);
    fprintf(logfile, "Number of elements freed:%d\n", num_freed);
    fprintf(logfile, "Number of elements in gc after sweep:%d\n", num_allo_after);
    fprintf(logfile,"Log end.\n\n");

    log_count++;

    fclose(logfile);

    // Reset
    num_allo_before = 0;
    num_freed = 0;
    num_allo_after = 0;

    if (signals_on) {
        // Unblock signals
        if(sigprocmask(SIG_SETMASK, &old_sigs, NULL) != 0) {
            fprintf(stderr, "Failed to unblock SIGUSR1\n");
            exit(1);
        }
    }
}

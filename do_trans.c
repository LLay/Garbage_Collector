/* Read and execute a list of operations on a linked list.
 * Periodically call the garbage collector.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>
#include "list.h"
#include "gc.h"
#include "gc_list.h"

#define MAX_LINE 128
#define ADD_NODE 1
#define DEL_NODE 2
#define PRINT_LIST 3

List *ll = NULL;

// Define a sig handler that calls mark and sweep if SIGUSR1 recieved
void sig_handler_list(int signum) {
    if (signum == SIGUSR1) {
        printf("Received SIGUSR1! Calling mark_and_sweep\n");
        sleep(3);
        mark_and_sweep(ll, mark_list);
    }
}

int main(int argc, char **argv) {

    // Install signal handler.
    signal(SIGUSR1, sig_handler_list);

    //clear log file
    FILE *logfile;
    logfile = fopen(LOGFILE, "w");
    fclose(logfile);

    char line[MAX_LINE];
    char *str;

    if(argc != 2) {
        fprintf(stderr, "Usage: do_trans filename. Provide a file to read from\n");
        exit(1);
    }

    FILE *fp;
    if((fp = fopen(argv[1], "r")) == NULL) {
        perror("fopen");
        exit(1);
    }

    int count = 1;

    while(fgets(line, MAX_LINE, fp) != NULL) {

        char *next;
        int value;
        int type = strtol(line, &next, 0);
        //printf("case: %d, for node %d\n", type, value);

        //printf("Try sending a SIGUSR1\n");
        //sleep(15);
        switch(type) {
            case ADD_NODE :
                value = strtol(next, NULL, 0);
                // printf("about to add %d\n", value);
                ll = add_node(ll, value);
                break;
            case DEL_NODE :
                value = strtol(next, NULL, 0);
                // printf("about to add %d\n", value);
                ll = remove_node(ll, value);
                break;
            case PRINT_LIST :
                str = tostring(ll);
                printf("List is %s\n", str);
                free(str);
                break;
            default :
                fprintf(stderr, "Error: bad transaction type\n");
        }

        if(count % 10 == 0) {
            printf("Mark and sweep on operation #%d\n", count);
            mark_and_sweep(ll, mark_list);

            /* Write the number of nodes in linked list to log.
             * Since we were not allowed to change the functions definition of
             * mark and sweep I am using this method to add the number of nodes
             * in the linked list.
             * My origional idea was to print this info to the log inside mark
             * and sweep and get that information by passing in a function
             * pointer to a generalized 'count_ds' function. or by returning a
             * count from the mark_obj functions. But this will have to do.

            FILE *logfile;
            logfile = fopen(LOGFILE, "a+" );
            int num_in_ll = length(ll);
            fprintf(logfile, "Number of elements in linked list:%d\n", num_in_ll);
            fclose(logfile);
    */
            //gc_string(MEMORY_LIST_PTR);
            //tostring(ll);

            // You might want to add something here to
            // make your program sleep long enough to see what it
            // is doing. In the commented out code, we wait for
            // any user input before continuing.

            // char check[MAX_LINE];
            // fgets(check, MAX_LINE, stdin);
        }
        count++;

    }
    // final garbage collection
    mark_and_sweep(ll, mark_list);
    printf("Done!\n");
    return 0;
}

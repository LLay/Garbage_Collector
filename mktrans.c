/*
 * Generate a random series of add, delete, and print operations on a
 * linked list.
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "list.h"

#define MAX_VAL 10000

/* The probability of generating print and add operations
 * The probability of generating a delete operation is
 * 1 - (PROB_PRINT + PROB_ADD)
 */
#define PROB_PRINT 0.05
#define PROB_ADD 0.55

int extraArgs = 0; //is there a reason all the other definitions are in main?
char *newline = "\n";
size_t long_size = sizeof(long);
FILE *fp;

int main(int argc, char **argv) {
    long type;
    long value;
    int length = 0;
    List *ll;

    int i;

    // Sets extraArgs to 1 if extra arguments were given on the command line
    if (argc > 1) {
        extraArgs = 1;
        // Create file to write transactions to.
        fp = fopen(argv[1], "w+");
    }

    for(i = 0; i < MAX_VAL; i++) {
        double prob = (double)random() / RAND_MAX;
        if(prob < PROB_PRINT) {
            type = 3;
            if (extraArgs) {     // make this a helper func?
                fprintf(fp, "%ld\n", type);
            } else {
                printf("%ld\n", type);
            }
        }
        if(prob < PROB_PRINT + PROB_ADD) {
            type = 1;
            value = random() % MAX_VAL;
            ll = add_node(ll, value);
            length++;
            if (extraArgs) {
                    fprintf(fp, "%ld %ld\n", type, value);
                } else {
                    printf("%ld %ld\n", type, value);
                }
        } else {
            type = 2;
            if(length > 0) {
                // choose a node that is in the list to delete
                int index = random() % length;
                value = find_nth(ll, index);
                ll = remove_node(ll, value);
                length--;
                if (extraArgs) {
                    fprintf(fp, "%ld %ld\n", type, value);
                } else {
                    printf("%ld %ld\n", type, value);
                }

            }
        }
    }
    fclose(fp);
    return 0;
}

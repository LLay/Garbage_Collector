/* Read and execute a list of operations on a linked list.
 * Periodically call the garbage collector.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "list.h"
#include "gc.h"
#include "gc_list.h"

    static List *ll = NULL;

int main(int argc, char **argv) {

    //clear log file
FILE *logfile2;
    logfile2 = fopen(LOGFILE, "w");
    fclose(logfile2);

    //add 10 nodes
    ll = add_node(ll, 1);
    ll = add_node(ll, 2);
    ll = add_node(ll, 3);
    ll = add_node(ll, 4);
    ll = add_node(ll, 5);
    ll = add_node(ll, 6);
    ll = add_node(ll, 7);
    ll = add_node(ll, 8);
    ll = add_node(ll, 9);
    ll = add_node(ll, 10);

    //clear log file
    FILE *logfile;
    logfile = fopen(LOGFILE, "w");
    fclose(logfile);

    // #1 1st Call. 10 elements in both lists before and after sweep. See log #1
    mark_and_sweep(ll, mark_list);

    // #2 Delete the head node
    ll = remove_node(ll, 10);
    // Both data structures should have 9 elements after mark and sweep

    mark_and_sweep(ll, mark_list);

    // #3 Delete internal node
    ll = remove_node(ll, 5);
    // Both data structures should have 8 elements after mark and sweep
    mark_and_sweep(ll, mark_list);

    // #4 Delete tail node
    ll = remove_node(ll, 1);
    // Both data structures should have 7 elements after mark and sweep
    mark_and_sweep(ll, mark_list);

    // #5 Add and Delete same node
    ll = add_node(ll, 99);
    ll = remove_node(ll, 99);
    // Both data structures should have 7 elements after mark and sweep
    mark_and_sweep(ll, mark_list);

    // #6 Remove all nodes from ll
    ll = remove_node(ll, 2);
    ll = remove_node(ll, 3);
    ll = remove_node(ll, 4);
    ll = remove_node(ll, 6);
    ll = remove_node(ll, 7);
    ll = remove_node(ll, 8);
    ll = remove_node(ll, 9);
    // Both data structures should have 0 elements after mark and sweep
    mark_and_sweep(ll, mark_list);

    // Enough nuance! Let try to break this baby!

    ll = add_node(ll, 1);
    ll = add_node(ll, 2);
    ll = add_node(ll, 3);
    ll = remove_node(ll, 1);
    ll = remove_node(ll, 2);
    ll = remove_node(ll, 3);
    ll = add_node(ll, 4);
    ll = add_node(ll, 5);
    ll = add_node(ll, 6);
    ll = remove_node(ll, 6);
    ll = add_node(ll, 7);
    ll = remove_node(ll, 7);
    ll = remove_node(ll, 4);
    ll = add_node(ll, 8);
    ll = add_node(ll, 9);
    ll = remove_node(ll, 9);
    ll = add_node(ll, 10);
    ll = remove_node(ll, 8);
    ll = remove_node(ll, 5);
    ll = remove_node(ll, 10);
    mark_and_sweep(ll, mark_list);
    ll = add_node(ll, 12);
    ll = add_node(ll, 22);
    ll = add_node(ll, 32);
    ll = add_node(ll, 42);
    ll = add_node(ll, 52);
    ll = add_node(ll, 62);
    ll = add_node(ll, 72);
    ll = add_node(ll, 82);
    ll = add_node(ll, 92);
    ll = add_node(ll, 120);
    ll = add_node(ll, 14);
    ll = add_node(ll, 24);
    ll = add_node(ll, 34);
    ll = add_node(ll, 44);
    ll = add_node(ll, 54);
    ll = add_node(ll, 64);
    ll = add_node(ll, 74);
    ll = add_node(ll, 84);
    ll = add_node(ll, 94);
    ll = add_node(ll, 140);
    ll = add_node(ll, 541);
    ll = add_node(ll, 542);
    ll = add_node(ll, 543);
    ll = add_node(ll, 544);
    ll = add_node(ll, 545);
    ll = add_node(ll, 546);
    ll = add_node(ll, 547);
    ll = add_node(ll, 548);
    ll = add_node(ll, 549);
    ll = add_node(ll, 5410);
    ll = add_node(ll, 61);
    ll = add_node(ll, 62);
    ll = add_node(ll, 63);
    ll = add_node(ll, 64);
    ll = add_node(ll, 65);
    ll = add_node(ll, 66);
    ll = add_node(ll, 67);
    ll = add_node(ll, 68);
    ll = add_node(ll, 69);
    ll = add_node(ll, 1140);
    ll = add_node(ll, 1541);
    ll = add_node(ll, 1542);
    ll = add_node(ll, 1543);
    ll = add_node(ll, 1544);
    ll = add_node(ll, 1545);
    ll = add_node(ll, 1546);
    ll = add_node(ll, 1547);
    ll = add_node(ll, 1548);
    ll = add_node(ll, 1549);
    ll = add_node(ll, 15410);
    ll = add_node(ll, 161);
    ll = add_node(ll, 162);
    ll = add_node(ll, 163);
    ll = add_node(ll, 164);
    ll = add_node(ll, 165);
    ll = add_node(ll, 166);
    mark_and_sweep(ll, mark_list);
    ll = remove_node(ll, 12);
    ll = remove_node(ll, 22);
    ll = remove_node(ll, 32);
    ll = remove_node(ll, 42);
    ll = remove_node(ll, 52);
    ll = remove_node(ll, 62);
    ll = remove_node(ll, 72);
    ll = remove_node(ll, 82);
    ll = remove_node(ll, 92);
    ll = remove_node(ll, 120);
    ll = remove_node(ll, 14);
    ll = remove_node(ll, 24);
    ll = remove_node(ll, 34);
    ll = remove_node(ll, 44);
    ll = remove_node(ll, 54);
    ll = remove_node(ll, 64);
    ll = remove_node(ll, 74);
    ll = remove_node(ll, 84);
    ll = remove_node(ll, 94);
    ll = remove_node(ll, 140);
    ll = remove_node(ll, 541);
    ll = remove_node(ll, 542);
    ll = remove_node(ll, 543);
    ll = remove_node(ll, 544);
    ll = remove_node(ll, 545);
    ll = remove_node(ll, 546);
    ll = remove_node(ll, 547);
    ll = remove_node(ll, 548);
    ll = remove_node(ll, 549);
    ll = remove_node(ll, 5410);
    ll = remove_node(ll, 61);
    ll = remove_node(ll, 62);
    ll = remove_node(ll, 63);
    ll = remove_node(ll, 64);
    ll = remove_node(ll, 65);
    ll = remove_node(ll, 66);
    ll = remove_node(ll, 67);
    ll = remove_node(ll, 68);
    ll = remove_node(ll, 69);
    ll = add_node(ll, 610);
    ll = add_node(ll, 112);
    ll = add_node(ll, 122);
    ll = add_node(ll, 132);
    ll = add_node(ll, 142);
    ll = add_node(ll, 152);
    ll = add_node(ll, 162);
    ll = add_node(ll, 172);
    ll = add_node(ll, 182);
    ll = add_node(ll, 192);
    ll = add_node(ll, 1120);
    ll = add_node(ll, 114);
    ll = add_node(ll, 124);
    ll = add_node(ll, 134);
    ll = add_node(ll, 144);
    ll = add_node(ll, 154);
    ll = add_node(ll, 164);
    ll = add_node(ll, 174);
    ll = add_node(ll, 184);
    ll = add_node(ll, 194);
    mark_and_sweep(ll, mark_list);
    ll = remove_node(ll, 610);
    ll = remove_node(ll, 112);
    ll = remove_node(ll, 122);
    ll = remove_node(ll, 132);
    ll = remove_node(ll, 142);
    ll = remove_node(ll, 152);
    ll = remove_node(ll, 162);
    ll = remove_node(ll, 172);
    ll = remove_node(ll, 182);
    ll = remove_node(ll, 192);
    ll = remove_node(ll, 1120);
    ll = remove_node(ll, 114);
    ll = remove_node(ll, 124);
    ll = remove_node(ll, 134);
    ll = remove_node(ll, 144);
    ll = remove_node(ll, 154);
    ll = remove_node(ll, 164);
    ll = remove_node(ll, 174);
    ll = remove_node(ll, 184);
    ll = remove_node(ll, 194);
    ll = remove_node(ll, 1140);
    ll = remove_node(ll, 1541);
    ll = remove_node(ll, 1542);
    ll = remove_node(ll, 1543);
    ll = remove_node(ll, 1544);
    ll = remove_node(ll, 1545);
    ll = remove_node(ll, 1546);
    ll = remove_node(ll, 1547);
    ll = remove_node(ll, 1548);
    ll = remove_node(ll, 1549);
    ll = remove_node(ll, 15410);
    ll = remove_node(ll, 161);
    ll = remove_node(ll, 162);
    ll = remove_node(ll, 163);
    ll = remove_node(ll, 164);
    ll = remove_node(ll, 165);
    ll = remove_node(ll, 166);
    ll = add_node(ll, 167);
    ll = add_node(ll, 168);
    ll = add_node(ll, 169);
    ll = add_node(ll, 1610);
    ll = add_node(ll, 112);
    ll = add_node(ll, 4122);
    ll = add_node(ll, 4132);
    ll = add_node(ll, 4142);
    ll = add_node(ll, 4152);
    ll = add_node(ll, 4162);
    ll = add_node(ll, 4172);
    ll = add_node(ll, 4182);
    ll = add_node(ll, 4192);
    ll = add_node(ll, 41120);
    ll = add_node(ll, 4114);
    ll = remove_node(ll, 167);
    ll = remove_node(ll, 168);
    ll = remove_node(ll, 169);
    ll = remove_node(ll, 1610);
    ll = remove_node(ll, 112);
    ll = remove_node(ll, 4122);
    ll = remove_node(ll, 4132);
    ll = remove_node(ll, 4142);
    ll = remove_node(ll, 4152);
    ll = remove_node(ll, 4162);
    ll = remove_node(ll, 4172);
    ll = remove_node(ll, 4182);
    ll = remove_node(ll, 4192);
    ll = remove_node(ll, 41120);
    ll = remove_node(ll, 4114);
    mark_and_sweep(ll, mark_list);
    printf("Test complete. See gc.log for details.\n");
    return 0;
}

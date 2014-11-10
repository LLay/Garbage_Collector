Garbage_Collector
=================
Written in C, this is a demo garbage collector that will track and reclaim memory from two different data structures, a linked list and a file system tree. Allocated space is tracked when the user calls the wrapper function 'gc_malloc' and removed when the user calls 'mark_and_sweep' on their data structure.

Files
----------
- gc.c - Contains the garbage collector
- mktrans.c - randomly generate a series of linked list operations (add, remove, print).
- do_trans.c - Takes a file produced by mktrans as a command line argument and executes the operations on a linked list. Ready-made argument files are transactions1, short_trans, trans_del_all.
- do_fstree.c - Performs a series of operations on the fstree data structure (input file hard coded as argument to do_transactions. See Testing for more details
- test_list.c - Tests various functionality of garbage collection on a linked list (see Testing)

Testing
-------------------------
I have provided a very basic test program 'test_list'. It can be compiled and run by
calling make and then calling test_list. The program adds and deletes a number
of nodes in various sequences to demonstrate garbage collection (and mark_list)
performance on a number of different cases.
Calling valgrind on this program shows that there are 0 bytes lost and no
leak possible.
valgrind --tool=memcheck --leak-check=yes ./test_list

Furthermore, if you call valgrind on transactions 1 or on fs_tree (with "fs_trans1", 
"fs_trans2", or "fs_trans_loop" as the argument for do_transactions()) you will 
see that there are no bytes lost.
valgrind --tool=memcheck --leak-check=yes ./do_trans transactions1
valgrind --tool=memcheck --leak-check=yes ./do_fstree

LOGGING
----------------
gc.log
The log resets on each execution of do_trans, do_fstree, and test_list.
Log contains the follosing info:
 - The log number (the nth log since program start)
 - Time of mark and sweep
 - Number of elements in data structure
 - Number of elements in gc before sweep
 - Number of elements freed
 - Number of elements in gc after sweep
'element' referes to anything that was malloced. Attributes of structs included.
You can use this information to see that after a mark and sweep
the number of elements in the data structure is equal to the number of elements
in the garbage collector.

SIGNALING
--------------
A user can call mark and sweep at any point during the execution of the program by sending a SIGUSR1 to the process. This is a handy feature but dangerous if it is called during the execution of a gc_malloc or a mark_and_sweep. The user can enable signal blocking (in gc.c by setting signals_on to 1) to prevent just this. 

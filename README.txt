TESTING:
test_list
I have provided a very basic test program. It can be compiled and run by
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

LOGS - gc.log
The log resets on each execution of do_trans, do_fstree, and test_list.
Log contains the follosing info:
 - The log number (the nth log since program start)
 - Time of mark and sweep
 - Number of elements in data structure
 - Number of elements in gc before sweep
 - Number of elements freed
 - Number of elements in gc after sweep
'element' referes to anything that was malloced. attributes of structs included.
You can use this information to see that after a mark and sweep
the number of elements in the data structure is equal to the number of elements
in the garbage collector.

SIGNAL BLOCKING
Enable signal blocking by setting the variable 'signals_on' to 0 in gc.c.
When you enable signals mark_and_sweep will block SIGUSR1 commands.
However, regardless of the signal state I have made it possible to
signal a mark and sweep. See do_trans for more info and to see the
sgnal handler.

ADDITIONAL TESTING
do_trans trans_del_all:
In addition to test_list I wrote a transaciton file that can be used
as an argument for do_trans. There are 1200 transactions.
Nodes are added and deleted in sequence. All nodes are
eventually removed from the linked list.
You will see that:
	0 bytes of memory are lost
	and all memory in use at exit is still reachable:
valgrind --tool=memcheck --leak-check=yes ./do_trans trans_del_all


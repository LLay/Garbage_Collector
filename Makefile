LOGFILE='"gc.log"'
FLAGS = -DLOGFILE=${LOGFILE} -Wall -g

all : mktrans do_trans do_fstree test_list

do_trans : do_trans.o list.o gc.o gc_list.o
	gcc ${FLAGS} -o $@ $^

mktrans : mktrans.o list.o gc.o
	gcc ${FLAGS} -o $@ $^

do_fstree : do_fstree.o fstree.o gc.o gc_fstree.o
	gcc ${FLAGS} -o $@ $^

test_list : test_list.o list.o gc.o gc_list.o
	gcc ${FLAGS} -o $@ $^

%.o : %.c
	gcc ${FLAGS} -c $<

do_trans.o : list.h
mktrans.o : list.h
list.o : list.h
gc.o : gc.h
gc_fstree.o : gc_fstree.h fstree.o
gc_list.o : gc_list.h list.o
fstree.o : fstree.h
do_fstree.o : fstree.h

clean :
	rm *.o mktrans do_trans do_fstree test_list

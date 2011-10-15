#
# Makefile for visualize the c function calls
#

CC = gcc 
CFLAGS+=-g -finstrument-functions

OBJS = ls.o instrument.o
all: ls
	@echo making pvtrace
	@make -C pvtrace
	@make -C pvtrace install
	@echo making ls util for test
	@./ls 2>&1 >/dev/null
	@echo generating dot file
	@./pvtrace.out ls
	@echo generating function calls\'s picture 
	@dot graph.dot -Tpng -o graph.png

ls: $(OBJS)
	@gcc -o $@ $(OBJS)

.c.o:
	@$(CC) $(CFLAGS) -Wall -c $<

clean:
	rm -f ls *.o graph* trace.txt pvtrace.out
	make -C pvtrace clean

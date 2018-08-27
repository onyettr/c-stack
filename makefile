# Simple makefile
#
# 1) If you want gcov coverage enable the PLFAGS option and rebuild all
# 2) Added 'check' support
#

#
# Tools
#
#CC    		     = g++
#LINK  		     = g++
CC    		     = gcc
LINK  		     = gcc
DEBUG 		     = -g
AR    		     = ar
CHK   		     = checkmk

#
# Build options
#

# gcov and gprof build options
COVPFLAGS		 = -fprofile-arcs -ftest-coverage
PROFLAGS         = -pg
#PFLAGS           = $(COVFLAGS)

# Main CC and Link build strings
CFLAGS		     = -c -std=c99 -Wall -pedantic $(PFLAGS)
LFLAGS		     = $(PFLAGS) -static -L.

# -DDEBUG_TRACE	Will turn on deep trace per function
# -DEXCEPTION	Will use the real exceptions with the 'try' that's in the test harness

#
# Code checking with splint
#
CODE_CHECK       = splint
CODE_CHECK_ARGS	 = -showfunc -mustfreefresh -nullpass

#
# Libs, objs targets
# libstack library is built from trap handling and the stack implementation. 
#
OBJS  		     = main.o test01.o
LIBS  		     = libstack.a
TEST_STACK 	     = stack_test.ts

#all:	stack.exe libstack.a splint-it
all:	stack.exe libstack.a test_harness

stack.exe:	$(OBJS) $(LIBS)
	$(LINK) $(OBJS) $(LFLAGS) -lstack -o stack.exe

libstack.a:	stack.o trap.o
	$(AR) rcs libstack.a stack.o trap.o

main.o:		main.c
	$(CC) $(CFLAGS) $(DEBUG) main.c -o main.o
stack.o:	stack.c
	$(CC) $(CFLAGS) $(DEBUG) stack.c -o stack.o
trap.o:		trap.c
	$(CC) $(CFLAGS) $(DEBUG) trap.c -o trap.o
test01.o:	test01.c
	$(CC) $(CFLAGS) $(DEBUG) test01.c -o test01.o

#
# This is the "check" target: Test harness is in stack_check.ts file and 
# this is converted by "check" into a C file which is linked to give another
# executable. 
# 
# NOTE: This will not build if you have the Profiling enabled as the libstack.a 
# contains gcov 
#
test_harness: libstack.a stack_check.ts
	$(CHK) stack_check.ts > stack_check.c
	$(CC) -o stack_check.exe stack_check.c -static -L. -lcheck -lstack 

#
# Code checking target
#
splint-it:
	$(CODE_CHECK) $(CODE_CHECK_ARGS) main.c  
	$(CODE_CHECK) $(CODE_CHECK_ARGS) trap.c   
	$(CODE_CHECK) $(CODE_CHECK_ARGS) test01.c
	$(CODE_CHECK) $(CODE_CHECK_ARGS) stack.c     

clean:
	rm -f stack.exe
	rm -f stack_check.exe
	rm -f stack.o
	rm -f libstack.a
	rm -f test01.o
	rm -f main.o
	rm -f trap.o
	rm -f *.gcno
	rm -f *.gcda
	rm -f gmon.out
	rm -f core

#
# Fin
#


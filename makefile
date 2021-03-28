#*******************************************************************************
# File name        : makefile
# File description : C Stack implementation
# Author           : ronyett
#*******************************************************************************

SRC_DIR				= 	.
OBJECT_DIR		= 	$(SRC_DIR)/object
MAKE_DIR_CMD	= 	mkdir $(OBJECT_DIR)

#CC  					= 	clang
#LINK  				= 	clang
CC  					= 	gcc
LINK  				= 	gcc
AR						= 	ar
CHK   				= 	checkmk
CHECK_FOR_CHK	:= 	$(shell command -v $(CHK) 2> /dev/null)

#*******************************************************************************
# Build options
#*******************************************************************************

# gcov and gprof build options
COVPFLAGS			= 	-fprofile-arcs -ftest-coverage
PROFLAGS			= 	-pg
#PFLAGS				= 	$(COVFLAGS)

# Main CC and Link build strings
DEBUG					= 	-g
CFLAGS				= 	-c -std=c99 -Wall -pedantic $(PFLAGS)
LFLAGS				= 	$(PFLAGS) -static -L.

# -DDEBUG_TRACE	Will turn on deep trace per function
# -DEXCEPTION	Will use the real exceptions with the 'try' that's in the test harness

#
# Code checking with splint
#
CODE_CHECK       	= 	splint
CODE_CHECK_ARGS	 	= 	-showfunc -mustfreefresh -nullpass -nullret -noeffect

#
# codespell
CODE_SPELL		= 	codespell
CODE_SPELL_ARGS		= 	\
	--skip "*.pdf,*.png,*.obj,./latex,./Debug,./.vs,./html,*.a,*.o,*.exe,./.git"
CHECK_FOR_CODESPELL	:=	$(shell command -v $(CODE_SPELL) 2> /dev/null)

#
# Libs, objs targets
# libstack library is built from trap handling and the stack implementation. 
#
OBJS  =		\
			$(OBJECT_DIR)/main.o 					\
		  $(OBJECT_DIR)/test_create.o		\
			$(OBJECT_DIR)/test_pop_char.o	\
			$(OBJECT_DIR)/test_pop_int.o	\
		 	$(OBJECT_DIR)/test_empty.o		\
		 	$(OBJECT_DIR)/test_push.o			\
		 	$(OBJECT_DIR)/test_size.o			\
		 	$(OBJECT_DIR)/test_swap.o			\
		 	$(OBJECT_DIR)/test_pop.o			\
		 	$(OBJECT_DIR)/test_top.o

LIBS 		 		     	= 	libstack.a

TEST_STACK 	     	= 	stack_test.ts

#*******************************************************************************
# Build targets:
# all		Creates object directory, builds executable and runs checker
# lib		Build only the list library, no test harness
# splint-it	run the Syntax checker
# clean		Delete object and library files
#*******************************************************************************

all:	$(OBJECT_DIR) stack.exe libstack.a test_harness unity_test_harness spelling-bee

lib:	$(LIBS)

stack.exe:	$(OBJS) $(LIBS)
	$(LINK) $(OBJS) $(LFLAGS) -lstack -o stack.exe

libstack.a:	$(OBJECT_DIR)/stack.o $(OBJECT_DIR)/trap.o
	$(AR) rcs libstack.a $(OBJECT_DIR)/stack.o $(OBJECT_DIR)/trap.o

$(OBJECT_DIR):
	-$(MAKE_DIR_CMD)

$(OBJECT_DIR)/main.o:		main.c
	$(CC) $(CFLAGS) $(DEBUG) main.c -o $(OBJECT_DIR)/main.o
$(OBJECT_DIR)/stack.o:	stack.c
	$(CC) $(CFLAGS) $(DEBUG) stack.c -o $(OBJECT_DIR)/stack.o
$(OBJECT_DIR)/trap.o:		trap.c
	$(CC) $(CFLAGS) $(DEBUG) trap.c -o $(OBJECT_DIR)/trap.o
$(OBJECT_DIR)/test_create.o:	test_create.c
	$(CC) $(CFLAGS) $(DEBUG) test_create.c -o $(OBJECT_DIR)/test_create.o
$(OBJECT_DIR)/test_empty.o:	test_empty.c
	$(CC) $(CFLAGS) $(DEBUG) test_empty.c -o $(OBJECT_DIR)/test_empty.o
$(OBJECT_DIR)/test_push.o:	test_push.c
	$(CC) $(CFLAGS) $(DEBUG) test_push.c -o $(OBJECT_DIR)/test_push.o
$(OBJECT_DIR)/test_swap.o:	test_swap.c
	$(CC) $(CFLAGS) $(DEBUG) test_swap.c -o $(OBJECT_DIR)/test_swap.o
$(OBJECT_DIR)/test_size.o:	test_size.c
	$(CC) $(CFLAGS) $(DEBUG) test_size.c -o $(OBJECT_DIR)/test_size.o
$(OBJECT_DIR)/test_top.o:	test_top.c
	$(CC) $(CFLAGS) $(DEBUG) test_top.c -o $(OBJECT_DIR)/test_top.o
$(OBJECT_DIR)/test_pop.o:	test_pop.c
	$(CC) $(CFLAGS) $(DEBUG) test_pop.c -o $(OBJECT_DIR)/test_pop.o
$(OBJECT_DIR)/test_pop_char.o:	test_pop_char.c
	$(CC) $(CFLAGS) $(DEBUG) test_pop_char.c -o $(OBJECT_DIR)/test_pop_char.o
$(OBJECT_DIR)/test_pop_int.o:	test_pop_int.c
	$(CC) $(CFLAGS) $(DEBUG) test_pop_int.c -o $(OBJECT_DIR)/test_pop_int.o
$(OBJECT_DIR)/test01.o:	test01.c
	$(CC) $(CFLAGS) $(DEBUG) test01.c -o $(OBJECT_DIR)/test01.o

#
# Unity test harness
#
unity_test_harness: unitytest.exe

unitytest.exe:	libstack.a $(OBJECT_DIR)/unity.o $(OBJECT_DIR)/unitytest.o
	$(CC) -o unitytest.exe $(OBJECT_DIR)/unity.o $(OBJECT_DIR)/unitytest.o -static -L. -lstack  -lpthread
$(OBJECT_DIR)/unity.o:	unity/unity.c
	$(CC) $(CFLAGS) -I unity/ unity/unity.c -o $(OBJECT_DIR)/unity.o
$(OBJECT_DIR)/unitytest.o:	unitytest.c
	$(CC) $(CFLAGS) -I unity/ unitytest.c -o $(OBJECT_DIR)/unitytest.o

#
# This is the "check" target: Test harness is in stack_check.ts file and 
# this is converted by "check" into a C file which is linked to give another
# executable. 
# 
# NOTE: This will not build if you have the Profiling enabled as the libstack.a 
# contains gcov 
#
test_harness: libstack.a stack_check.ts
ifndef CHECK_FOR_CHK
	@echo "** checkmk command not found"
else
	$(CHK) stack_check.ts > stack_check.c
	$(CC) -o stack_check.exe stack_check.c -static -L. -lcheck -lstack 
endif

#
# Code checking target
#
splint-it:
	$(CODE_CHECK) $(CODE_CHECK_ARGS) main.c
	$(CODE_CHECK) $(CODE_CHECK_ARGS) trap.c   
	$(CODE_CHECK) $(CODE_CHECK_ARGS) test01.c
	$(CODE_CHECK) $(CODE_CHECK_ARGS) stack.c     

spelling-bee:
ifndef CHECK_FOR_CODESPELL
	@echo "** codespell was not found"
else
	$(CODE_SPELL) $(CODE_SPELL_ARGS)
endif

clean:
	rm -f stack.exe
	rm -f stack_check.exe
	rm -f unitytest.exe
	rm -f libstack.a
	rm -f $(OBJECT_DIR)/test_create.o
	rm -f $(OBJECT_DIR)/test_empty.o
	rm -f $(OBJECT_DIR)/unitytest.o
	rm -f $(OBJECT_DIR)/test_push.o
	rm -f $(OBJECT_DIR)/test_size.o
	rm -f $(OBJECT_DIR)/test_swap.o
	rm -f $(OBJECT_DIR)/test_top.o
	rm -f $(OBJECT_DIR)/test_pop.o
	rm -f $(OBJECT_DIR)/test01.o
	rm -f $(OBJECT_DIR)/unity.o
	rm -f $(OBJECT_DIR)/stack.o
	rm -f $(OBJECT_DIR)/main.o
	rm -f $(OBJECT_DIR)/trap.o
	rm -f *.gcno
	rm -f *.gcda
	rm -f gmon.out
	rm -f core

#
# Fin
#


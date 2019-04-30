C Programming Exercises  - Stack

Introduction
	Simple stack implementation. It uses dynamic memory allocation
	for the Stack_t type called from an exposed StackCreate() function call.
	
Files
  main.c		launches the test harness to execute the stack
  makefil1e             builds everything
  stack.c               stack implementation 
  stack.h               stack header file
  test_empty.c          test harness for empty
  test_pop.c            test harness for pop
  test_push.c           test harness for push
  test_swap.c           test harness for swap
  test_top.c            test harness for top
  test_size.c           test harness for size
  stack_check.ts        check testing tool script  
  test.h                test harness header
  trap.c                error trap handler
  trap.h                error trap handler header file

Build
  make

Tests
  All functions are tested through test_xxxxx.c test harness
  'check' test harness is used
  Unity test harness
  
ToDo
  1) Convert to a standalone library - DONE
  2) Provide ability to have fixed size Stack as a build option.


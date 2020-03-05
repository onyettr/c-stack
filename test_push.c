/**
 *	@file    test_push.c
 *	@brief   simple c stack test harness
 *	@author
 *	@note
 */

/*
******************************************************************************
Includes
******************************************************************************
*/
#include <stdio.h>
#include "stack.h"
#include "test.h"

/*
******************************************************************************
Private Constants
******************************************************************************
*/

/*
******************************************************************************
Private Types
******************************************************************************
*/

/*
******************************************************************************
Private variables (static)
******************************************************************************
*/

/*
******************************************************************************
Private Macros
******************************************************************************
*/

/*
******************************************************************************
Global variables
******************************************************************************
*/

/*
******************************************************************************
Exported Global variables
******************************************************************************
*/

/*
******************************************************************************
Prototypes of all functions contained in this file (in order of occurance)
******************************************************************************
*/

int test_push ( void )
{
  Stack_t *sp = NULL;  
  Stack_t *sp1= NULL;
  
  printf("test_push - create <int> stack\n");

  sp = StackCreate(4, stack_int);

  printf("\tTest01 - creation good\n");
  (void)push(sp, 100);
  (void)push(sp, 200);
  (void)push(sp, 300);
  (void)push(sp, 700);

  StackDump(sp, 0);

  printf("\tTest02 - push beyond size\n");
  printf("\tTest02 return -1 %d\n", push(sp,800));

  printf("\tTest03 - creation with null stack\n");
  printf("\tTest03 return -1 %d\n", push(sp1,800));

  (void)StackDestroy(sp);

  printf("test_push - create <char> stack\n");

  sp1 = StackCreate(4, stack_char);

  printf("\tTest04 - creation good\n");
  (void)push(sp1, 'A');
  (void)push(sp1, 'B');
  (void)push(sp1, 'C');
  (void)push(sp1, 'D');

  StackDump(sp1, 0);
  (void)StackDestroy(sp1);
  
  printf("test_push - Ends\n");

  return 0;
}

//
// Fin
//
  

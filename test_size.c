/**
 *	@file    test_size.c
 *	@brief   simple c stack test harness - size
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

int test_size ( void )
{
  Stack_t *sp = NULL;
  Stack_t *sp0= NULL;    
  Stack_t *sp1= NULL;  
  Stack_t *sp2= NULL;
  
  printf("*** test_size\n");

  sp = StackCreate(5, stack_int);

  (void)push(sp,400);
  (void)push(sp,500);
  (void)push(sp,600);
  (void)push(sp,700);

  StackDump(sp, 0);

  printf("\ttest_size   %d = 4\n", size(sp));

  printf("\ttest_size:  %d after pop #1 %d\n", pop(sp), size(sp));
  printf("\ttest_size:  %d after pop #2 %d\n", pop(sp), size(sp));
  printf("\ttest_size:  %d after pop #3 %d\n", pop(sp), size(sp));
  printf("\ttest_size:  %d after pop #4 %d\n", pop(sp), size(sp));

  printf("\ttest_size:  %d after pop #5 %d StackUnderFlowExcep\n", pop(sp), size(sp));

  sp0 = StackCreate(5, stack_int);
  printf("\ttest_size   %d = 0 No Elements\n", size(sp0));
  
  sp1 = StackCreate(5, stack_int);
  (void)push(sp1,800);
  printf("\ttest_size   %d = 1 One Element\n", size(sp1));
  
  printf("\ttest_size:  %d = -1 null stack\n",size(sp2));
  
  (void)StackDestroy(sp);
  (void)StackDestroy(sp0);  
  (void)StackDestroy(sp1);
  (void)StackDestroy(sp2);
  
  printf("test_size - Ends\n");

  return 0;
}

//
// Fin
//
  

/**
 *	@file    test_pop.c
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
Prototypes of all functions contained in this file (in order of occurrence)
******************************************************************************
*/

int test_pop_int ( void )
{
  Stack_t *sp = NULL;
  Stack_t *sp0= NULL;
  int retvalue;
  
  printf("*** test_pop - stack\n");

  sp = StackCreate(5, stack_int);

  (void)push(sp,400);
  (void)push(sp,500);
  (void)push(sp,600);
  (void)push(sp,700);
  StackDump(sp, 0);

  pop(sp, &retvalue);
  printf("\ttest_pop - <int> stack 700 = %d\n",retvalue);

  pop(sp, &retvalue);
  printf("\ttest_pop - <int> stack 600 = %d\n",retvalue);

  pop(sp, &retvalue);
  printf("\ttest_pop - <int> stack 500 = %d\n",retvalue);

  pop(sp, &retvalue);
  printf("\ttest_pop - <int> stack 400 = %d\n",retvalue);
  
  printf("\tTest02 creation with null stack\n");
  printf("\tTest02 return -1 %d\n", pop(sp0,&retvalue));

  sp0 = StackCreate(5, stack_int);  
  printf("\tTest03 creation with empty stack\n");
  printf("\tTest03 return -1 %d\n", pop(sp0,&retvalue));
  
  (void)StackDestroy(sp);
 
  return 0;
}

//
// Fin
//
  

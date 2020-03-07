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

int test_pop_char( void )
{
  Stack_t *sp = NULL;
  Stack_t *sp0= NULL;
  char retvalue;
  
  printf("*** test_pop_char - stack\n");

  sp = StackCreate(5, stack_char);

  (void)push(sp,'A');
  (void)push(sp,'B');
  (void)push(sp,'C');
  (void)push(sp,'D');
  StackDump(sp, 0);

  pop(sp, &retvalue);
  printf("\ttest_pop - <char> stack A = %c\n",retvalue);

  pop(sp, &retvalue);
  printf("\ttest_pop - <char> stack B = %c\n",retvalue);

  pop(sp, &retvalue);
  printf("\ttest_pop - <char> stack C = %c\n",retvalue);

  pop(sp, &retvalue);
  printf("\ttest_pop - <char> stack D = %c\n",retvalue);
  
  printf("\tTest02 creation with null stack\n");
  printf("\tTest02 return -1 %d\n", pop(sp0,&retvalue));

  sp0 = StackCreate(5, stack_char);  
  printf("\tTest03 creation with empty stack\n");
  printf("\tTest03 return -1 %d\n", pop(sp0,&retvalue));
  
  (void)StackDestroy(sp);
  (void)StackDestroy(sp0);
  
  return 0;
}

//
// Fin
//
  

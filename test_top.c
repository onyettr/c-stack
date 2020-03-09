/**
 *	@file    test_top.c
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

int test_top ( void )
{
  Stack_t *sp = NULL;  
  Stack_t *sp1 = NULL;
  Stack_t *sp2 = NULL;  
  int retvalue;
  int Error;
  
  printf("*** test_top\n");

  sp = StackCreate(4, stack_int);

  (void)push(sp,100);
  (void)push(sp,200);
  (void)push(sp,300);
  (void)push(sp,700);
  StackDump(sp, 0);

  top(sp, &retvalue);  
  printf("\tTest01 return 700 %d\n", retvalue);

  printf("\tTest02 return  -1 %d  NULL stack\n", top(NULL, &retvalue));  

  sp1 = StackCreate(4, stack_int);  
  printf("\tTest02 return  -1 %d  Empty Stack\n", top(sp1, &retvalue));  

  sp2 = StackCreate(4, stack_int);
  push(sp2, 101);
  Error = top(sp2, &retvalue);
  
  printf ("\tTest03 return %d, Value = %d\n", Error, retvalue);
  
  (void)StackDestroy(sp);
  (void)StackDestroy(sp1);
  (void)StackDestroy(sp2);    

  printf("test_top - Ends\n");

  return 0;
}

//
// Fin
//
  

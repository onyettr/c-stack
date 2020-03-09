/**
 *	@file    test_swap.c
 *	@brief   simple c stack test harness - swap
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

int test_swap ( void )
{
  Stack_t *sp  = NULL;  
  Stack_t *sp1 = NULL;
  Stack_t *sp2 = NULL;
  Stack_t *sp3 = NULL;
  Stack_t *sp4 = NULL;
  Stack_t *sp5 = NULL;
  Stack_t *sp6 = NULL;
  Stack_t *sp7 = NULL;
  Stack_t *sp8 = NULL;  
  Stack_t *sp9 = NULL;
  
  printf("test_swap - create <int> stack\n");

  sp = StackCreate(4, stack_int);
  sp1= StackCreate(4, stack_int);
  
  (void)push(sp,100);
  (void)push(sp,200);
  (void)push(sp,300);
  (void)push(sp,700);

  (void)push(sp1,101);
  (void)push(sp1,201);
  (void)push(sp1,301);
  (void)push(sp1,701);

  //(void)StackDestroy(sp);
  printf("\tTest01 swap - same size, but stack freed -1 = %d\n", swap(sp,sp1));

  /*
   * Test02 positive swap - same size
   */
  sp2 = StackCreate(4, stack_int);
  sp3 = StackCreate(4, stack_int);

  (void)push(sp2,1);
  (void)push(sp2,2);
  (void)push(sp2,3);
  (void)push(sp2,4);
  printf("\tTest02 - before sp2\n");
  StackDump(sp2,0);

  (void)push(sp3,5);
  (void)push(sp3,6);
  (void)push(sp3,7);
  (void)push(sp3,8);
  printf("\tTest02 - before sp3\n");
  StackDump(sp3,0);

  printf("Test02 swap same size, but ok 0 = %d\n", swap(sp2,sp3));
  printf("\tTest02 - after sp2\n");
  StackDump(sp2,0);
  printf("\tTest02 - after sp3\n");
  StackDump(sp3,0);

   /*
    * Test04 positive swap - src size is less than dst, will need to increase src
    */
   sp6 = StackCreate(2, stack_int);  /* src */
   sp7 = StackCreate(4, stack_int);  /* dst */

   (void)push(sp6,1);
   (void)push(sp6,2);
   printf("\tTest04 - before sp6, size %d\n", size(sp6));
   StackDump(sp6,0);

   (void)push(sp7,3);
   (void)push(sp7,4);
   (void)push(sp7,5);
   (void)push(sp7,4);
   printf("\tTest04 - before sp7, size %d\n", size(sp7));
   StackDump(sp7,0);

   printf("Test04 swap dst size less than src size, but ok 0 = %d\n", swap(sp6,sp7));
   printf("\tTest04 - after sp6, size %d\n", size(sp6));
   StackDump(sp6,0);
   printf("\tTest04 - after sp7, size %d\n", size(sp7));
   StackDump(sp7,0);


   /*
    * Test05 positive swap - dst size is less than src, will need to increase dst
    */
   sp8 = StackCreate(2, stack_int);  /* dst */
   sp9 = StackCreate(4, stack_int);  /* src */

   (void)push(sp8,101);
   (void)push(sp8,201);
   printf("\tTest05 - before dst sp8, size %d\n", size(sp8));
   StackDump(sp8,0);

   (void)push(sp9,301);
   (void)push(sp9,401);
   (void)push(sp9,501);
   (void)push(sp9,401);
   printf("\tTest05 - before src sp9, size %d\n", size(sp9));
   StackDump(sp9,0);
   
   printf("Test05 swap dst size less than src size, but ok 0 = %d\n", swap(sp9,sp8));
   printf("\tTest05 - after dst sp8, size %d\n", size(sp8));
   StackDump(sp8,0);
   printf("\tTest05 - after src sp9, size %d\n", size(sp9));
   StackDump(sp9,0);

   printf("test_swap - Ends\n");

   StackDestroy(sp );
   StackDestroy(sp1);
   //   StackDestroy(sp2);
   //   StackDestroy(sp3);
   //StackDestroy(sp4);
   //StackDestroy(sp5);
   //StackDestroy(sp6);
   //StackDestroy(sp7);
   //   StackDestroy(sp8);
   //   StackDestroy(sp9);

   return 0;
}

//
// Fin
//
  

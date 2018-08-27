/**
 *****************************************************************************
 * \file stack.c
 * \brief MODULE: C Programming Examples
 *
 * \author Onyettr
 *
 * NAME: Richard Onyett 
 * EMAIL: 
 *
 * PURPOSE: Simple Stack implementation
 * \bug no known bugs
 *
 ***************************************************************************** 
 */

/*
******************************************************************************
Includes
******************************************************************************
*/
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "stack.h"
#include "trap.h"

static bool isFull (stack_t *pStack);
static bool isEmpty(stack_t *pStack);

/**
 *
 * @fn         static int isEmpty(stack_t *pStack)
 * @param[in]  stack_t *pStack stack to test
 * @brief      tests if stack is empty.
 * @return     bool True or False
 */
static bool isEmpty(stack_t *pStack) {
  return pStack->StackTop == -1 ? true : false;
}

/**
 *
 * @fn         static int isFull(stack_t *pStack)
 * @param[in]  stack_t *pStack stack to test
 * @brief      tests if stack is full.
 * @return     bool True or False
 */
static bool isFull(stack_t *pStack) {
  return pStack->StackTop == (pStack->StackMax - 1) ? true : false;
}

/**
 * @fn         int pop(stack_t *pStack)
 * @brief      "pop" off the top of the stack. If the stack is empty then we throw an exception and return negative value 
 * @param[in]  stack_t *pStack - Stack to pop from
 * @return     int stack value
 * @note       Will throw an exception if no stack is created.
 */
int pop(stack_t *pStack) {

  if ( pStack == (stack_t *)NULL ) {
    Thrower(e_stacknotcreated);

    return -1;      
  }

  if (isEmpty(pStack)) {
    printf ("Stack empty - Cannot pop\n");
    Thrower(e_stackunderflow);
    
    return -1;
  }

  return pStack->pStack[pStack->StackTop--];
}

/**
 *
 * @fn            int peek(stack_t *pStack) 
 * @brief         "peek" the top of the stack, does not move the
 *                StackPointer
 * @param[in]     stack_t *pStack - Stack to peek from
 * @return        int stack_value
 */
int peek(stack_t *pStack) {
  if ( pStack == NULL ) {
    Thrower(e_stacknotcreated);

    return -1;      
  }
  
  if (isEmpty(pStack)) {
    printf ("Stack empty - Cannot peek\n");
    Thrower(e_stackunderflow);
    
    return -1;
  }

  return pStack->pStack[pStack->StackTop];  
}

/**
 * 
 * @fn         int push(stack_t *pStack, int element)
 * @brief      Push element onto the provided Stack
 * @param[in]  stack_t *pStack stack to push into
 * @param[in]  int element item to push onto the stack
 * @return     -1 if error, 0 otherwise.
 */
int push(stack_t *pStack, int element) {
  if ( pStack == NULL ) {
    Thrower(e_stacknotcreated);

    return -1;      
  }
  
  if (isFull(pStack)) {
    Thrower(e_stackoverflow);
    
    return -1;
  }

  pStack->pStack[++pStack->StackTop] = element;

  return 0;
}

/**
 * 
 * @fn         void StackDump (stack_t *pStack, int num) {
 * @brief      print out stack contents to console. 
 * @param[in]  stack_t *pStack stack to test
 * @param[in]  int num allows number of elements to be printed. 
 * @return     None
 */
void StackDump (stack_t *pStack, int num) {
  int i;
  int numtoShow = 0;

  if ( pStack == NULL ) {
    Thrower(e_stacknotcreated);

    return;      
  }
  
  if (isEmpty(pStack)) {
    printf ("Stack empty - nothing to display\n");

    return;
  }

  if ( num == 0) {
    numtoShow = pStack->StackMax;
  } else {
    numtoShow = num;
  }
  
  for (i=0; i < numtoShow; i++) {
    printf("Stack[%4d] = %d", i, pStack->pStack[i] );
    if ( i == pStack->StackTop ) {
      printf("  <--- Stacktop");
    }
    printf("\n");  
  }
}

/**
 *
 * @fn         stack_t *StackCreate(int maxStack)
 * @brief      creates a stack of the size specified in maxStack 
 *             using malloc().
 * @param[in]  int maxStack - Maximum size of the Stack to create
 * @return     stack_t pointer to the stack_t structure
 */
stack_t *StackCreate(int maxStack) {

  /* 
   * Cannot allocate negative size stacks
   */
  if ( maxStack < 0) {
    return (stack_t *)NULL;
  }
  
  /*
   * create a stack "head"
   */
  stack_t *pStackHead = (stack_t *)malloc(sizeof(stack_t));
  if ( pStackHead == NULL )
    return (stack_t *)NULL;

  pStackHead->StackMax = maxStack; /* High water mark for the stack */
  pStackHead->StackTop = -1;       /* Ready for push                */

  /*
   * create the actual stack to push and pull from 
   */
  pStackHead->pStack   = (int *)malloc(sizeof(int) * maxStack);

  return pStackHead;
}

/**
 * @fn         int StackDestroy(stack_t *sp)
 * @brief      Destroy the created stack 
 * @param[in]  stack_t *sp object to be destroyed
 * @return     -1 if Error, else 0
 */
int StackDestroy(stack_t *pStack) {

  if ( pStack == (stack_t *)NULL) {
    Thrower(e_stacknotcreated);    

    return -1;
  }

  /*
   * destroy the actual stack to push and pull from 
   */
  free (pStack->pStack); 

  return 0;
}

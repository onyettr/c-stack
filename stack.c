/**
 *****************************************************************************
 * @file   stack.c
 * @brief  C Programming Examples -  Simple Stack implementation
 * @author onyettr
 * @bug    no known bugs
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
 * @fn         static int isEmpty(stack_t *pStack)
 *
 * @param[in]  *pStack stack to test
 *
 * @brief      tests if stack is empty.
 *
 * @return     bool True or False
 *
 * @note       none
 */
static bool isEmpty(stack_t *pStack) {
  return pStack->StackTop == -1 ? true : false;
}

/**
 * @fn         static int isFull(stack_t *pStack)
 *
 * @param[in]  *pStack stack to test
 *
 * @brief      tests if stack is full.
 *
 * @return     bool True or False
 *
 * @note       none
 */
static bool isFull(stack_t *pStack) {
  return pStack->StackTop == (pStack->StackMax - 1) ? true : false;
}

/**
 * @fn         int pop(stack_t *pStack)
 *
 * @brief      "pop" off the top of the stack. If the stack is empty then we throw an exception and return negative value 
 *
 * @param[in]  *pStack - Stack to pop from
 *
 * @return     int stack value
 *
 * @note       Will throw an exception if no stack is created.
 */
int pop(stack_t *pStack) {

  if ( pStack == (stack_t *)NULL ) {
    Thrower(e_stacknotcreated);

    return -1;      
  }

  if (isEmpty(pStack)) {
    Thrower(e_stackunderflow);
    
    return -1;
  }

  return pStack->pStack[pStack->StackTop--];
}


/**
 * @fn            int top(stack_t *pStack) 
 *
 * @brief         Returns the top of the stack, does not move the
 *                StackPointer
 *
 * @param[in]     *pStack - Stack to peek from
 *
 * @return        int stack_value
 * 
 * @note
 */
int top(stack_t *pStack) {
  if ( pStack == NULL ) {
    Thrower(e_stacknotcreated);

    return -1;      
  }
  
  if (isEmpty(pStack)) {
    Thrower(e_stackunderflow);
    
    return -1;
  }

  return pStack->pStack[pStack->StackTop];  
}

/**
 * @fn         int push(stack_t *pStack, int element)
 *
 * @brief      Push element onto the provided Stack
 *
 * @param[in]  *pStack stack to push into
 * @param[in]  element item to push onto the stack
 *
 * @return     -1 if error, 0 otherwise.
 *
 * @note
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
 * @fn         void swap(stack_t *srcStack, stack_t *dstStack)
 *
 * @brief      Swap stacks from src -> dst
 *
 * @param[in]  *srcStack source stack
 * @param[in]  *dstStack destination stack
 *
 * @return     -1 if error, 0 otherwise.
 *
 * @note
 */
int swap(stack_t *srcStack, stack_t *dstStack) {
  int i;

  if ( srcStack == NULL || dstStack == NULL) {
    Thrower(e_stacknotcreated);

    return -1;      
  }

  /*
   * Do we need to allocate more stack space?
   */
  if (srcStack->StackMax <= dstStack->StackMax) {
    for (i=0; i < srcStack->StackMax; i++) {
      int tmp;
      tmp = srcStack->pStack[i];
      printf("Before %d src %d, dst %d\n", i, tmp, dstStack->pStack[i]);
      srcStack->pStack[i] = dstStack->pStack[i];
      dstStack->pStack[i] = tmp;
      printf("after  %d src %d, dst %d\n", i, tmp, dstStack->pStack[i]);      
    }
  }

  return 0;
}

/**
 * @fn         bool empty(stack_t *pStack) 
 *
 * @brief      is the stack empty?
 *
 * @param[in]  *pStack - Stack to pop from
 *
 * @return     bool TRUE, if empty, false otherwise
 *
 * @note       Will throw an exception if no stack is created.
 */
bool empty(stack_t *pStack) {

  if ( pStack == (stack_t *)NULL ) {
    Thrower(e_stacknotcreated);

    return -1;      
  }

  if (isEmpty(pStack)) {
    return true;
  }

  return false;
}

/**
 * @fn         int size(stack_t *pStack)
 *
 * @brief      return the number of elements on the stack
 *
 * @param[in]  *pStack stack
 *
 * @return     size
 *
 * @note
 */
int size(stack_t *pStack) {
  if ( pStack == NULL ) {
    Thrower(e_stacknotcreated);

    return -1;      
  }
  
  return pStack->StackTop+1;
}

/**
 * @fn         void StackDump (stack_t *pStack, int num) {
 *
 * @brief      print out stack contents to console. 
 *
 * @param[in]  *pStack stack to test
 * @param[in]  num allows number of elements to be printed. 
 *
 * @return     None
 *
 * @note
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
 * @param[in]  maxStack - Maximum size of the Stack to create
 * @return     stack_t pointer to the stack_t structure or NULL
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
  if ( pStackHead == NULL ) {
    return (stack_t *)NULL;
  }

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
 * 
 * @brief      Destroy the created stack 
 *
 * @param[in]  *pStack object to be destroyed
 *
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

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

static bool isFull (Stack_t *pStack);
static bool isEmpty(Stack_t *pStack);

/**
 * @fn         static int isEmpty(Stack_t *pStack)
 *
 * @param[in]  *pStack stack to test
 *
 * @brief      tests if stack is empty.
 *
 * @return     bool True or False
 *
 * @note       none
 */
static bool isEmpty(Stack_t *pStack) {
  return pStack->StackTop == -1 ? true : false;
}

/**
 * @fn         static int isFull(Stack_t *pStack)
 * @param[in]  *pStack stack to test
 * @brief      tests if stack is full.
 * @return     bool True or False
 * @note       none
 */
static bool isFull(Stack_t *pStack) {
  return pStack->StackTop == (pStack->StackMax - 1) ? true : false;
}

/**
 * @fn         int pop(Stack_t *pStack)
 * @brief      "pop" off the top of the stack. If the stack is empty then we throw an exception and return negative value 
 * @param[in]  *pStack - Stack to pop from
 * @return     int stack value
 * @note       Will throw an exception if no stack is created.
 */
int pop(Stack_t *pStack) {

  if ( pStack == (Stack_t *)NULL ) {
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
 * @fn            int top(Stack_t *pStack) 
 * @brief         Returns the top of the stack, does not move the
 *                StackPointer
 * @param[in]     *pStack - Stack to peek from
 * @return        int stack_value
 * @note
 */
int top(Stack_t *pStack) {
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
 * @fn         int push(Stack_t *pStack, int element)
 * @brief      Push element onto the provided Stack
 * @param[in]  *pStack stack to push into
 * @param[in]  element item to push onto the stack
 * @return     -1 if error, 0 otherwise.
 * @note
 */
int push(Stack_t *pStack, int element) {
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
 * @fn         void swap(Stack_t *srcStack, Stack_t *dstStack)
 * @brief      Swap stacks from src -> dst
 * @param[in]  *srcStack source stack
 * @param[in]  *dstStack destination stack
 * @return     -1 if error, 0 otherwise.
 * @note        If the src < dst || dst < src we can simply copy, if not we
 *              need to reallocated more memory.
 */
int swap(Stack_t *srcStack, Stack_t *dstStack) {
  int i;
  int counter;

  /*
   * TODO: If one is NULL we should simply allocate a new stack
   */
  if ( srcStack == NULL || dstStack == NULL) {
	  Thrower(e_stacknotcreated);

	  return -1;
  }

  if (srcStack->pStack == NULL || dstStack->pStack == NULL) {
	  Thrower(e_stacknotcreated);
printf("swap - stacked has been freed already!\n");
	  return -1;
  }

  /*
   * Do we need to allocate more stack space?
   * If not we can simply copy from one to the other
   */
  if (srcStack->StackMax == dstStack->StackMax) {
	  if (srcStack->StackMax <= dstStack->StackMax ) {
		  counter = srcStack->StackMax;
	  }
	  if (dstStack->StackMax <= srcStack->StackMax ) {
	  		  counter = dstStack->StackMax;
	  }

	  for (i=0; i < counter; i++) {
		  int tmp;
		  tmp = srcStack->pStack[i];
		  srcStack->pStack[i] = dstStack->pStack[i];
		  dstStack->pStack[i] = tmp;
	  }
  }

  if (srcStack->StackMax < dstStack->StackMax) {                    /* We need to reallocate more memory for the source */
	  int *newStack;
          int StackTop;
	  
	  newStack = realloc(srcStack->pStack, dstStack->StackMax); /* Add more memory                                  */
	  srcStack->pStack = newStack;                              /* update to the new stack                          */
	  srcStack->StackMax = dstStack->StackMax;                  /* update the stack size                            */
printf("realloc src\n");

	  counter = dstStack->StackMax;
	  for (i=0; i < counter; i++) {
		  int tmp;
		  tmp = srcStack->pStack[i];
		  srcStack->pStack[i] = dstStack->pStack[i];
		  dstStack->pStack[i] = tmp;
	  }
	  StackTop = dstStack->StackTop;
	  dstStack->StackTop = srcStack->StackTop;
	  srcStack->StackTop = StackTop;
  }

  if (dstStack->StackMax < srcStack->StackMax) {                    /* We need to reallocate more memory for the source */
	  int *newStack;
          int StackTop;
	  
	  newStack = realloc(dstStack->pStack, srcStack->StackMax); /* Add more memory                                  */
	  dstStack->pStack = newStack;                              /* update to the new stack                          */
	  dstStack->StackMax = srcStack->StackMax;                  /* update the stack size                            */
printf("realloc dst\n");

	  counter = srcStack->StackMax;
	  for (i=0; i < counter; i++) {
		  int tmp;
		  tmp = srcStack->pStack[i];
		  srcStack->pStack[i] = dstStack->pStack[i];
		  dstStack->pStack[i] = tmp;
	  }
	  StackTop = dstStack->StackTop;
	  dstStack->StackTop = srcStack->StackTop;
	  srcStack->StackTop = StackTop;
  }

  return 0;
}

/**
 * @fn         bool empty(Stack_t *pStack) 
 * @brief      is the stack empty?
 * @param[in]  *pStack - Stack to pop from
 * @return     bool TRUE, if empty, false otherwise
 * @note       Will throw an exception if no stack is created.
 */
bool empty(Stack_t *pStack) {

  if ( pStack == (Stack_t *)NULL ) {
    Thrower(e_stacknotcreated);

    return -1;      
  }

  if (isEmpty(pStack)) {
    return true;
  }

  return false;
}

/**
 * @fn         int size(Stack_t *pStack)
 * @brief      return the number of elements on the stack
 * @param[in]  *pStack stack
 * @return     size
 * @note
 */
int size(Stack_t *pStack) {
  if ( pStack == NULL ) {
    Thrower(e_stacknotcreated);

    return -1;      
  }
  
  return pStack->StackTop+1;
}

/**
 * @fn         void StackDump (Stack_t *pStack, int num) {
 * @brief      print out stack contents to console. 
 * @param[in]  *pStack stack to test
 * @param[in]  num allows number of elements to be printed. 
 * @return     None
 * @note
 */
void StackDump (Stack_t *pStack, int num) {
  int i;
  int numtoShow = 0;

  if ( pStack == NULL || pStack->pStack == NULL) {
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
 * @fn         Stack_t *StackCreate(int maxStack)
 * @brief      creates a stack of the size specified in maxStack 
 *             using malloc().
 * @param[in]  maxStack - Maximum size of the Stack to create
 * @return     Stack_t pointer to the Stack_t structure or NULL
 */
Stack_t *StackCreate(int maxStack) {

  /* 
   * Cannot allocate negative size stacks
   */
  if ( maxStack < 0) {
    return (Stack_t *)NULL;
  }
  
  /*
   * create a stack "head"
   */
  Stack_t *pStackHead = (Stack_t *)malloc(sizeof(Stack_t));
  if ( pStackHead == NULL ) {
    return (Stack_t *)NULL;
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
 * @fn         int StackDestroy(Stack_t *sp)
 * @brief      Destroy the created stack 
 * @param[in]  *pStack object to be destroyed
 * @return     -1 if Error, else 0
 */
int StackDestroy(Stack_t *pStack) {

  if ( pStack == (Stack_t *)NULL) {
    Thrower(e_stacknotcreated);    

    return -1;
  }

  /*
   * destroy the actual stack to push and pull from 
   */
  free (pStack->pStack); 
  pStack->pStack = NULL;

  return 0;
}

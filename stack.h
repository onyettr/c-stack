/**
 *****************************************************************************
 * @file stack.h
 *
 * MODULE: C Programming Examples
 *
 * $Header: $
 * $Archive:$
 * 
 * $Workfile: $
 *
 * @author Onyettr
 *
 * NAME: Richard Onyett 
 * EMAIL: 
 *
 * PURPOSE: 
 * Header file for simple stack
 * 
 * $Revision:$
 * $History: $
 *
 ***************************************************************************** 
 */

/*
******************************************************************************
Includes
******************************************************************************
*/
#ifndef __STACK_H__
#define __STACK_H__

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

/**
 * @struct stack
 * @brief  Data structure to hold the details about the stack.
 * TODO Make stack object other than Integer.
 */
typedef struct stack { /*! stack type                     */
  int StackMax;        /*!< Max size of the created stack */
  int StackTop;        /*!< point at the top of the stack */
  int *pStack;         /*!< actual stack                  */
} stack_t;

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

/** 
 *  @fn         int pop  (stack_t *pStack)
 *  @brief      pop an element from the stack pointed to
 *  @param[in]  stack_t *pStack - Pointer to the stack
 *  @return     returns (int) element
 */
int pop  (stack_t *pStack);

/**
 *  @fn         int peek  (stack_t *pStack)
 *  @brief      peeks at the top of the stack but doesn't pop
 *  @param[in]  stack_t *pStack - Pointer to the stack
 *  @return     returns (int) element
 */
int peek (stack_t *pStack);

/**
 *  @fn         int push  (stack_t *pStack)
 *  @brief      pushes an element onto the stack pointed to
 *  @param[in]  stack_t *pStack - Pointer to the stack
 *  @param[in]  int to be pushed
 *  @return     -1 if error, 0 otherwise
 */
int push(stack_t *pStack, int element);

stack_t *StackCreate(int maxStack);
int  StackDestroy( stack_t *sp );
void StackDump (stack_t *pStack, int num);

#endif // __STACK_H__


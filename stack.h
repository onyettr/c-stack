/**
 *****************************************************************************
 * @file stack.h
 *
 * MODULE: C Programming Examples
 *
 * @author Onyettr
 *
 * PURPOSE: Header file for simple stack
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
 *  @param[in]  *pStack - Pointer to the stack
 *  @return     returns (int) element
 */
int pop  (stack_t *pStack);

/**
 *  @fn         int peek  (stack_t *pStack)
 *  @brief      peeks at the top of the stack but doesn't pop
 *  @param[in]  *pStack - Pointer to the stack
 *  @return     returns (int) element
 */
int peek (stack_t *pStack);

/**
 *  @fn         int push  (stack_t *pStack)
 *  @brief      pushes an element onto the stack pointed to
 *  @param[in]  *pStack - Pointer to the stack
 *  @param[in]  element to be pushed
 *  @return     -1 if error, 0 otherwise
 */
int push(stack_t *pStack, int element);

/**
 * @fn         stack_t *StackCreate(int maxStack)
 * @brief      creates a stack of the size specified in maxStack 
 *             using malloc().
 * @param[in]  maxStack - Maximum size of the Stack to create
 * @return     stack_t pointer to the stack_t structure or NULL
 */
stack_t *StackCreate(int maxStack);

/**
 * @fn         int StackDestroy(stack_t *pStack)
 * @brief      Destroy the created stack 
 * @param[in]  *pStack object to be destroyed
 * @return     -1 if Error, else 0
 */
int  StackDestroy( stack_t *pStack );

/**
 * @fn         void StackDump (stack_t *pStack, int num) {
 * @brief      print out stack contents to console. 
 * @param[in]  *pStack stack to test
 * @param[in]  num allows number of elements to be printed. 
 * @return     None
 * @note
 */
void StackDump (stack_t *pStack, int num);

#endif // __STACK_H__


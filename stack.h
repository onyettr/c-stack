/**
 *****************************************************************************
 * @file   stack.h
 * @brief  Programming Examples
 * @author Onyettr
 * PURPOSE: Header file for simple stack
 ***************************************************************************** 
 */
#ifndef __STACK_H__
#define __STACK_H__

/*
******************************************************************************
Includes
******************************************************************************
*/
#include <stdbool.h>

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
 * @enum  StackType_t
 * @brief Various types allowed for the stack 
 */
typedef enum StackType {
  stack_char,
  stack_int,
  stack_long,
  stack_float,
  stack_double,
  stack_string,
  stack_pointer
} StackType_t;

/**
 * @struct stackElement_t
 * @brief  Element for the stack
 */
typedef struct StackElement {

  union {
    char   char_value;
    int    int_value;
    long   long_value;
    float  float_value;
    double double_value;
    void   *ptr_value;
  } stackdata;
} StackElement_t;
  
/**
 * @struct stack
 * @brief  Data structure to hold the details about the stack.
 * @note   Stack is of one type only
 */
typedef struct stack { /*! stack type                     */
  size_t StackMax;     /*!< Max size of the created stack */
  size_t StackTop;     /*!< point at the top of the stack */
  StackType_t Type;    /*!< Variable type for stack       */    
  StackElement_t *pElement; /*!< Actual stack             */
  int *pStack;         /*!< actual stack                  */
} Stack_t;

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
 *  @fn         int pop  (Stack_t *pStack)
 *  @brief      pop an element from the stack pointed to
 *  @param[in]  *pStack - Pointer to the stack
 *  @return     returns (int) element
 */
int pop  (Stack_t *pStack);

/**
 *  @fn         int top  (Stack_t *pStack)
 *  @brief      returns the top of the stack but doesn't pop
 *  @param[in]  *pStack - Pointer to the stack
 *  @return     returns (int) element
 */
int top  (Stack_t *pStack);

/**
 *  @fn         int push  (Stack_t *pStack)
 *  @brief      pushes an element onto the stack pointed to
 *  @param[in]  *pStack - Pointer to the stack
 *  @return     -1 if error, 0 otherwise
 */
int push(Stack_t *pStack, ...);

/**
 * @fn         bool empty(Stack_t *pStack) 
 * @brief      is the stack empty?
 * @param[in]  *pStack - Stack to pop from
 * @return     bool TRUE, if empty, false otherwise
 * @note       Will throw an exception if no stack is created.
 */
bool empty(Stack_t *pStack);

/**
 * @fn         int size(Stack_t *pStack)
 * @brief      return the number of elements on the stack
 * @param[in]  *pStack stack
 * @return     size
 * @note
 */
int size(Stack_t *pStack);

/**
 * @fn         int swap(Stack_t *srcStack, Stack_t *dstStack)
 * @brief      Swap stacks from src -> dst
 * @param[in]  *srcStack source stack
 * @param[in]  *dstStack destination stack
 * @return     -1 if error, 0 otherwise.
 * @note
 */
int swap(Stack_t *srcStack, Stack_t *dstStack);

/**
 * @fn         Stack_t *StackCreate(int maxStack)
 * @brief      creates a stack of the size specified in maxStack 
 *             using malloc().
 * @param[in]  maxStack - Maximum size of the Stack to create
 * @param[in]  type - what object type is stored in the Stack
 * @return     Stack_t pointer to the Stack_t structure or NULL
 */
Stack_t *StackCreate(size_t maxStack, const StackType_t type);

/**
 * @fn         int StackDestroy(Stack_t *pStack)
 * @brief      Destroy the created stack 
 * @param[in]  *pStack object to be destroyed
 * @return     -1 if Error, else 0
 */
int  StackDestroy( Stack_t *pStack );

/**
 * @fn         void StackDump (Stack_t *pStack, int num) {
 * @brief      print out stack contents to console. 
 * @param[in]  *pStack stack to test
 * @param[in]  num allows number of elements to be printed. 
 * @return     None
 * @note
 */
void StackDump (Stack_t *pStack, int num);

#endif // __STACK_H__


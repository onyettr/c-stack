/**
 *****************************************************************************
 * MODULE: C Programming Examples
 *
`* @author   Onyettr
 *
 * PURPOSE: Simple Stack implementation
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
#include "stack.h"
#include "trap.h"

/**
 * @brief     Exception Handler
 * @fn        void Thrower(stack_exception_t exp)
 * @param[in] exp  - Execption to "throw"
 * @return    none
 * @note      none
 */
void Thrower(stack_exception_t exp) {
  printf( ">> ouch something bad went on = ");
  if (exp == e_stackoverflow ) {
    printf ("StackOverFlowExcep");
  } else if (exp == e_stackunderflow) {
    printf ("StackUnderFlowExcep");
  } else if (exp == e_stackoutofmemory) {
    printf ("StackOutofMemoryExcep()");
  } else if (exp == e_stacknotcreated) {
    printf ("StackNotCreatedExcep()");
  }    
  
  printf("\n");
}


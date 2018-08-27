/*
 *****************************************************************************
 * 
 * MODULE: C Programming Examples
 *
 * $Header: $
 * $Archive:$
 * 
 * $Workfile: $
 *
 * $Author: Onyettr $
 *
 * NAME: Richard Onyett 
 * EMAIL: 
 *
 * PURPOSE: Simple Stack implementation
 *
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
#include <stdio.h>
#include <stdlib.h>
#include "stack.h"
#include "trap.h"

/*
 -- --------------------------------------------------------------
 -- void Thrower(stack_exception_t exp) - excep handler
 --    stack_exception_t exp  - Execption to "throw"
 -- 
 -- returns: none
 -- --------------------------------------------------------------
*/
void Thrower(stack_exception_t exp) {
  printf( "ouch something bad went on = ");
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


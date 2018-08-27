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
 * NAME: Richard Onyett (STMicroelectronics,San Jose)
 * EMAIL: richard.onyett@st.com
 *
 * PURPOSE: Test harness for Stack.
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
Prototypes of all functions contained in this file (in order of occurance)
******************************************************************************
*/

static int test01 ( void ) {
  stack_t *sp = NULL;

  printf("\ntest01 - create stack and push some values\n" );

  sp = StackCreate(5);

  StackDump(sp,0);  /* Should be empty */

  push( sp, 100 );
  push( sp, 200 );
  push( sp, 300);
  push( sp, 700);

  StackDump(sp, 0);

  StackDestroy(sp);
  
  return 0;
}

static int test02 ( void ) {
  stack_t *sp = NULL;

  printf("\ntest02 - create stack and push some values\n" );

  sp = StackCreate(3);

  push( sp, 100 );
  push( sp, 200 );
  push( sp, 300);
  StackDump(sp, 0);

  printf("pop %d\n", pop(sp));
  printf("pop %d\n", pop(sp));
  printf("pop %d\n", pop(sp));
  StackDump(sp, 0);
  
  return 0;
}

static int test03 ( void ) {
  stack_t *sp = NULL;

  printf("\ntest03 - destroy stack tests\n" );

  printf("test03-01: destroy stack not created\n");
  StackDestroy(sp);
  
  printf("test03-02: destroy stack that is created\n");
  sp = StackCreate(3);
  StackDestroy(sp);
  
  StackDump(sp, 0);
  
  return 0;
}

static int test04 ( void ) {
  stack_t *sp = NULL;
  int value = 0;
  
  printf("\ntest04 - stack tests with no stack\n" );
  printf("test04.1 - push, no stack");
  push ( sp, 100);     

  printf("test04.2 - pop , no stack");
  value = pop( sp );     

  printf("test04.3 - peek, no stack");
  value = peek ( sp );     

  printf("test04.4 - dump, no stack");
  StackDump( sp, 10);

  printf("test04.5 - destroy, no stack");
  StackDestroy(sp);

  value = value;
  
  return 0;
}

int test_run ( void ) {
  int error_code = 0;

  error_code  = test01();    /* Run one of the tests */
  error_code |= test02();    /* Run one of the tests */
  error_code |= test03();    /* Run one of the tests */
  error_code |= test04();    /* Run one of the tests */
  
  return error_code;
}

//
// Fin
//
  

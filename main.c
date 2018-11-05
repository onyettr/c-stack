/**
 *****************************************************************************
 * MODULE: C Programming Examples
 *
 * @author onyettr
 * PURPOSE: Simple Stack implementation
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
#include "test.h"

int main ( void ) {
  int result = 0;
  
  if ((result = test_push()) == 0) printf ("test_run - ok\n");

  return 0;
}

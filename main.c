/*
 *****************************************************************************
 * MODULE: C Programming Examples
 *
 * NAME: Richard Onyett 
 * EMAIL: 
 *
 * PURPOSE: Simple Stack implementation
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
#include "test.h"

int main ( void ) {
  int result = 0;
  
  result = test_run();
  if (result == 0) printf ("test_run - ok\n");

  return 0;
}

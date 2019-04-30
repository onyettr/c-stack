/**
 *****************************************************************************
 * MODULE: C Programming Examples
 *
 * @author onyettr
 * PURPOSE: unity test harness for Simple Stack 
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
#include "unity.h"

void stack_create_invalid_size(void) {
  Stack_t *sp;

  sp = StackCreate(-1);
  TEST_ASSERT_MESSAGE(sp == NULL, "Stack rturned NULL");
}

void stack_create_valid_size(void) {
  Stack_t *sp;

  sp = StackCreate(10);
  TEST_ASSERT_MESSAGE(sp != NULL, "Stack created ok");
}

void runTest(UnityTestFunction test) {
  if(TEST_PROTECT()) {
    test();
  }
}

#if 1
void setUp(void) {
}

void tearDown(void) {
}
#endif

int main ( void ) {
  UNITY_BEGIN();

  RUN_TEST(stack_create_invalid_size, __LINE__);
  RUN_TEST(stack_create_valid_size,   __LINE__);

  return UNITY_END();
}

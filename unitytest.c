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

/** 
 * test stack creation
 */
void stack_create_invalid_size(void) {
  Stack_t *sp;

  sp = StackCreate(-1);
  TEST_ASSERT_MESSAGE(sp == NULL, "Stack returned NULL");
}

void stack_create_valid_size(void) {
  Stack_t *sp;

  sp = StackCreate(10);
  TEST_ASSERT_MESSAGE(sp != NULL, "Stack created ok");
}

void stack_push_no_stack(void) {
   Stack_t *sp = (Stack_t*)NULL;

   TEST_ASSERT_MESSAGE(push(sp,101) == -1, "push no stack");
}

void stack_push_stack(void) {
   Stack_t *sp = (Stack_t*)NULL;
   sp = StackCreate(4);

   TEST_ASSERT_MESSAGE(push(sp,101) == 0, "push with stack");
}

void stack_push_stack_beyond_limit(void) {
   Stack_t *sp = (Stack_t*)NULL;

   sp = StackCreate(2);

   TEST_ASSERT_MESSAGE(push(sp,101) ==  0, "push fail");   
   TEST_ASSERT_MESSAGE(push(sp,102) ==  0, "push fail");
   TEST_ASSERT_MESSAGE(push(sp,103) == -1, "push beyond limit");   
}

void stack_pop_no_stack(void) {
   Stack_t *sp = (Stack_t*)NULL;

   TEST_ASSERT_MESSAGE(pop(sp) == -1, "pop with no stack");
}

void stack_pop_stack(void) {
   Stack_t *sp = (Stack_t*)NULL;

   sp = StackCreate(5);
   
   push(sp, 101);

   TEST_ASSERT_MESSAGE(pop(sp) == 101, "pop");
}

void stack_top_with_stack(void) {
   Stack_t *sp;
   sp = StackCreate(5);
   push(sp, 101);

   TEST_ASSERT_MESSAGE(top(sp) != -1, "top with stack failed");   
}

void stack_top_null_stack(void) {
   Stack_t *sp = NULL;
   sp = StackCreate(5);

   TEST_ASSERT_MESSAGE(top(sp) == -1, "top with empty stack failed");   
}

void stack_top_empty_stack(void) {
   Stack_t *sp = NULL;

   TEST_ASSERT_MESSAGE(top(sp) == -1, "top with no stack failed");   
}

void stack_empty_not_empty_stack(void) {
   Stack_t *sp = NULL;
   sp = StackCreate(5);

   (void)push(sp,400);
   (void)push(sp,500);
   (void)push(sp,600);
   (void)push(sp,700);

   TEST_ASSERT_MESSAGE(empty(sp) == 0, "empty with not empty stack");   
}

void stack_empty_empty_stack(void) {
   Stack_t *sp = NULL;

   sp = StackCreate(5);
   TEST_ASSERT_MESSAGE(empty(sp) == 1, "empty with empty stack");   
}

void stack_destroy_no_stack(void) {
   Stack_t *sp = NULL;

   TEST_ASSERT_MESSAGE(StackDestroy(sp) == -1, "Destroy failed, no stack created");   
}

void runTest(UnityTestFunction test) {
  if(TEST_PROTECT()) {
    test();
  }
}

void setUp(void) {
}

void tearDown(void) {
}

int main ( void ) {
  UnityBegin("stack.c");

  RUN_TEST(stack_create_invalid_size, __LINE__);
  RUN_TEST(stack_create_valid_size,   __LINE__);
  RUN_TEST(stack_push_no_stack,       __LINE__);
  RUN_TEST(stack_push_stack,          __LINE__);
  RUN_TEST(stack_push_stack_beyond_limit, __LINE__);
  RUN_TEST(stack_pop_no_stack,        __LINE__);
  RUN_TEST(stack_pop_stack,           __LINE__);
  RUN_TEST(stack_top_with_stack,      __LINE__);
  RUN_TEST(stack_top_null_stack,      __LINE__);
  RUN_TEST(stack_top_empty_stack,     __LINE__);
  RUN_TEST(stack_empty_not_empty_stack, __LINE__);
  RUN_TEST(stack_empty_empty_stack,   __LINE__);        

  UnityEnd();

  return 0;
}

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
  Stack_t *sp = (Stack_t *)NULL;

  sp = StackCreate(0, stack_int);
  TEST_ASSERT_MESSAGE(sp == NULL, "Stack returned NULL");
}

void stack_create_valid_size(void) {
  Stack_t *sp;

  sp = StackCreate(10, stack_int);
  TEST_ASSERT_MESSAGE(sp != NULL, "Stack created ok");
}

void stack_create_object_int(void) {
  Stack_t *sp;
  int ret;
   
  sp = StackCreate(2, stack_char);
  push(sp, 101);
  push(sp, 102);
  top(sp, &ret);
   
  TEST_ASSERT_MESSAGE(ret == 102, "Stack <int> created ok");
}

void stack_create_object_char(void) {
   Stack_t *sp = (Stack_t*)NULL;
   char ret;
   
   sp = StackCreate(2, stack_char);
   push(sp, 'A');
   push(sp, 'B');
   top(sp, &ret);
   
   TEST_ASSERT_MESSAGE(ret == 'B', "Stack <char> created ok");
}

void stack_create_object_float(void) {
   Stack_t *sp = (Stack_t*)NULL;
   char ret;
   
   sp = StackCreate(2, stack_float);
   push(sp, 1.2);
   push(sp, 1.3);
   top(sp, &ret);
   
   TEST_ASSERT_MESSAGE(ret == 1.3, "Stack <float> created ok");
}

void stack_push_no_stack(void) {
   Stack_t *sp = (Stack_t*)NULL;

   TEST_ASSERT_MESSAGE(push(sp,101) == -1, "push no stack");
}

void stack_push_stack(void) {
   Stack_t *sp = (Stack_t*)NULL;
   sp = StackCreate(4, stack_int);

   TEST_ASSERT_MESSAGE(push(sp,101) == 0, "push with stack");
}

void stack_push_stack_beyond_limit(void) {
   Stack_t *sp = (Stack_t*)NULL;

   sp = StackCreate(2, stack_int);

   TEST_ASSERT_MESSAGE(push(sp,101) ==  0, "push fail");   
   TEST_ASSERT_MESSAGE(push(sp,102) ==  0, "push fail");
   TEST_ASSERT_MESSAGE(push(sp,103) == -1, "push beyond limit");   
}

void stack_pop_no_stack(void) {
   Stack_t *sp = (Stack_t*)NULL;
   int ret;
   
   TEST_ASSERT_MESSAGE(pop(sp, &ret) == -1, "pop with no stack");
}

void stack_pop_stack(void) {
   Stack_t *sp = (Stack_t*)NULL;
   int ret;
   
   sp = StackCreate(5, stack_int);
   
   push(sp, 101);
   pop(sp, &ret);
   TEST_ASSERT_MESSAGE(ret == 101, "pop");
}

void stack_top_with_stack(void) {
   Stack_t *sp;
   int ret;
   int Error;
   
   sp = StackCreate(5, stack_int);

   push(sp, 101);

   Error = top(sp, &ret);
   TEST_ASSERT_MESSAGE(Error != -1 , "top with stack failed");
   TEST_ASSERT_MESSAGE(ret   == 101, "top with stack failed wrong value");      
}

void stack_top_null_stack(void) {
   Stack_t *sp = NULL;
   int ret;
   int Error;

   sp = StackCreate(5, stack_int);
   Error = top(sp, &ret);

   TEST_ASSERT_MESSAGE(Error == -1, "top with empty stack failed");   
}

void stack_top_empty_stack(void) {
   Stack_t *sp = NULL;
   int ret;
   int Error;

   Error = top(sp, &ret);
   TEST_ASSERT_MESSAGE(Error == -1, "top with no stack failed");   
}

void stack_empty_not_empty_stack(void) {
   Stack_t *sp = NULL;

   sp = StackCreate(5, stack_int);

   (void)push(sp,400);
   (void)push(sp,500);
   (void)push(sp,600);
   (void)push(sp,700);

   TEST_ASSERT_MESSAGE(empty(sp) == 0, "empty with not empty stack");   
}

void stack_empty_empty_stack(void) {
   Stack_t *sp = NULL;

   sp = StackCreate(5, stack_int);
   TEST_ASSERT_MESSAGE(empty(sp) == 1, "empty with empty stack");   
}

void stack_destroy_no_stack(void) {
   Stack_t *sp = NULL;

   TEST_ASSERT_MESSAGE(StackDestroy(sp) == -1, "Destroy failed, no stack created");   
}

void stack_swap_src_size(void) {
   Stack_t *sp;
   Stack_t *sp1;
   int ret;
   
   sp  = StackCreate(2, stack_int);
   sp1 = StackCreate(3, stack_int);
   
   (void)push(sp,400);
   (void)push(sp,500);

   (void)push(sp1,402);
   (void)push(sp1,502);
   (void)push(sp1,602);

   //   StackDump(sp,0);
   swap(sp, sp1);
   //   StackDump(sp,0);
   
   TEST_ASSERT_MESSAGE(size(sp) == 3, "Src size did not change!");   
   top(sp, &ret);
   TEST_ASSERT_MESSAGE(ret == 602, "swap did not work!");      
   
   top(sp1, &ret);
   TEST_ASSERT_MESSAGE(ret == 500, "swap did not work!");         
}

void stack_swap_same_size(void) {
   Stack_t *sp;
   Stack_t *sp1;
   int ret;
   
   sp  = StackCreate(4, stack_int);
   sp1 = StackCreate(4, stack_int);
   
   (void)push(sp,400);
   (void)push(sp,500);
   (void)push(sp,600);
   (void)push(sp,700);

   (void)push(sp1,402);
   (void)push(sp1,502);
   (void)push(sp1,602);
   (void)push(sp1,702);

   //   StackDump(sp,0);
   swap(sp, sp1);
   //   StackDump(sp,0);
   
   top(sp, &ret);
   TEST_ASSERT_MESSAGE(ret == 702, "swap did not work!");
   
   top(sp1, &ret);
   TEST_ASSERT_MESSAGE(ret == 700, "swap did not work!");   
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
  RUN_TEST(stack_create_object_int,   __LINE__);
  RUN_TEST(stack_create_object_char,  __LINE__);  
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
  RUN_TEST(stack_destroy_no_stack,    __LINE__);
  RUN_TEST(stack_swap_same_size,      __LINE__);
  RUN_TEST(stack_swap_src_size,       __LINE__);
  
  UnityEnd();

  return 0;
}

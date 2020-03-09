#include <stdio.h>
#include "stack.h"

#test stack_create_bad_size
   Stack_t *sp;

   printf("stack_create_bad_size\n");
   
   sp = StackCreate(0, stack_int);
   fail_unless(sp == NULL, "bad size create failed");   

#test stack_create_int_positive
   Stack_t *sp;

   printf("stack_create_positive\n");

   sp = StackCreate(5, stack_int);
   fail_unless(sp != NULL, "positive create failed");   

#test stack_create_double_positive
   Stack_t *sp;

   printf("stack_create_double_positive\n");

   sp = StackCreate(5, stack_double);
   fail_unless(sp != NULL, "positive create failed");   

#test push_negative_no_stack
   Stack_t *sp = (Stack_t*)NULL;

   printf("push_negative_no_stack\n");
   
   fail_unless(push(sp,101) == -1, "push no stack failed");   

#test push_positive_with_stack
   Stack_t *sp = (Stack_t*)NULL;

   printf("push_positive_no_stack\n");
   
   sp = StackCreate(4, stack_int);
   fail_unless(push(sp,101) ==  0, "push with stack failed");   

#test push_object_type_char
   Stack_t *sp = (Stack_t*)NULL;
   char ret;
   int error;
   
   sp = StackCreate(2, stack_char);
   push(sp, 'A');
   push(sp, 'B');
   StackDump(sp, 0);
   error = top(sp, &ret);
   
   fail_unless(ret == 'B', "push char failed!");

#test push_object_type_float
   Stack_t *sp = (Stack_t*)NULL;
   float ret;
   int error;
   
   sp = StackCreate(2, stack_char);
   push(sp, 1.2);
   push(sp, 1.3);

   error = top(sp, &ret);
   
   fail_unless(ret != 1.3, "push char failed!");

#test push_positive_with_stack_beyond_limit
   Stack_t *sp = (Stack_t*)NULL;

   printf("push_positive_with_stack_beyond_limit\n");
   
   sp = StackCreate(2, stack_int);
   fail_unless(push(sp,101) == 0, "push fail");
   fail_unless(push(sp,102) == 0, "push fail");      
   fail_unless(push(sp,103) == -1, "push beyond limit");


#test pop_negative_no_stack
   Stack_t *sp = (Stack_t*)NULL;
   int ret;
   int error;
//   push(sp, 101);

   error = pop(sp,&ret);
   fail_unless(error == -1, "pop no stack failed");   

#test pop_negative_with_stack_no_push
   Stack_t *sp = (Stack_t*)NULL;
   int ret;
   int error;

   error = pop(sp,&ret);
   fail_unless(error == -1, "pop no pushes failed");   

#test pop_positive_with_stack
   Stack_t *sp;
   int ret;
   int error;

   sp = StackCreate(5, stack_int);
   
   push(sp, 101);
   
   error = pop(sp,&ret);
   fail_unless(ret == 101, "pop failed");   

#test top_positive_with_stack
   Stack_t *sp;
   int ret;
   int error;
   
   sp = StackCreate(5, stack_int);
   push(sp, 101);

   error = top(sp, &ret);
   fail_unless(error != -1, "top with stack failed");   

#test top_negative_null_stack
   int ret;
   int error;
   Stack_t *sp = NULL;
   sp = StackCreate(5, stack_int);

   error = top(sp,&ret);
   fail_unless(error == -1, "top with empty stack failed");   

#test top_negative_empty_stack
   Stack_t *sp = NULL;
   int ret;
   int error;

   error = top(sp, &ret);
   fail_unless(error == -1, "top with no stack failed");   

#test empty_postive__not_empty_stack
   Stack_t *sp = NULL;
   sp = StackCreate(5, stack_int);

   (void)push(sp,400);
   (void)push(sp,500);
   (void)push(sp,600);
   (void)push(sp,700);

   fail_unless(empty(sp) == 0, "empty with not empty stack");   

#test empty_negatve_empty_stack
   Stack_t *sp = NULL;

   sp = StackCreate(5, stack_int);
   fail_unless(empty(sp) == 1, "empty with empty stack");   

#test destroy_stack_no_stack
   Stack_t *sp = NULL;

   fail_unless(StackDestroy(sp) == -1, "Destroy failed, no stack created");


#test stack_swap_same_size
   Stack_t *sp;
   Stack_t *sp1;
   int error;
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

   StackDump(sp,0);
   swap(sp, sp1);
   StackDump(sp,0);
   
   error = top(sp, &ret);
   fail_unless(ret == 702, "swap did not work!");
   
   error = top(sp1, &ret);
   fail_unless(ret == 700, "swap did not work!");

#test stack_swap_src_size_delta
   Stack_t *sp;
   Stack_t *sp1;
   int error;
   int ret;
   
   sp  = StackCreate(2, stack_int);
   sp1 = StackCreate(3, stack_int);
   
   (void)push(sp,400);
   (void)push(sp,500);

   (void)push(sp1,402);
   (void)push(sp1,502);
   (void)push(sp1,602);

   StackDump(sp,0);
   swap(sp, sp1);
   StackDump(sp,0);
   
   fail_unless(size(sp) == 3, "Src size didnt change");
   error = top(sp, &ret);
   fail_unless(ret == 602, "swap did not work!");
   
   error = top(sp1, &ret);
   fail_unless(ret == 500, "swap did not work!");

#test stack_swap_dst_size_delta
   Stack_t *sp;
   Stack_t *sp1;
   int error;
   int ret;
   
   sp  = StackCreate(3, stack_int);
   sp1 = StackCreate(2, stack_int);
   
   (void)push(sp,400);
   (void)push(sp,500);
   (void)push(sp,600);   

   (void)push(sp1,402);
   (void)push(sp1,502);

   StackDump(sp,0);
   swap(sp, sp1);
   StackDump(sp,0);
   
   fail_unless(size(sp1) == 3, "dst size did not change");
   error = top(sp, &ret);
   fail_unless(ret == 502, "swap did not work!");
   
   error = top(sp1, &ret);
   StackDump(sp1,0);   
   fail_unless(ret == 600, "swap did not work!");

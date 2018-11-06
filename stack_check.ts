#include "stack.h"

#test create_negative
   stack_t *sp;
   sp = StackCreate(-1);
   fail_unless(sp == NULL, "negative create failed");   

#test create_positive
   stack_t *sp;
   sp = StackCreate(5);
   fail_unless(sp != NULL, "positive create failed");   

#test push_negative_no_stack
   stack_t *sp = (stack_t*)NULL;

   fail_unless(push(sp,101) == -1, "push no stack failed");   

#test push_positive_with_stack
   stack_t *sp = (stack_t*)NULL;
   sp = StackCreate(4);
   fail_unless(push(sp,101) ==  0, "push with stack failed");   

#test push_positive_with_stack_beyond_limit
   stack_t *sp = (stack_t*)NULL;
   sp = StackCreate(2);
   fail_unless(push(sp,101) == 0, "push fail");
   fail_unless(push(sp,102) == 0, "push fail");      
   fail_unless(push(sp,103) == -1, "push beyond limit");
   
#test pop_negative_no_stack
   stack_t *sp = (stack_t*)NULL;
   push(sp, 101);

   fail_unless(pop(sp) == -1, "pop no stack failed");   

#test pop_negative_with_stack_no_push
   stack_t *sp = (stack_t*)NULL;

   fail_unless(pop(sp) == -1, "pop no pushes failed");   

#test pop_positive_with_stack
   stack_t *sp;
   sp = StackCreate(5);
   push(sp, 101);

   fail_unless(pop(sp) == 101, "pop failed");   

#test top_positive_with_stack
   stack_t *sp;
   sp = StackCreate(5);
   push(sp, 101);

   fail_unless(top(sp) != -1, "top with stack failed");   

#test top_negative_null_stack
   stack_t *sp = NULL;
   sp = StackCreate(5);

   fail_unless(top(sp) == -1, "top with empty stack failed");   

#test top_negative_empty_stack
   stack_t *sp = NULL;

   fail_unless(top(sp) == -1, "top with no stack failed");   

#test destroy_stack_no_stack
   stack_t *sp = NULL;

   fail_unless(StackDestroy(sp) == -1, "Destroy failed, no stack created");   

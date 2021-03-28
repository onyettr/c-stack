/**
 *****************************************************************************
 * @file   stack.c
 * @brief  C Programming Examples -  Simple Stack implementation
 * @author onyettr
 ***************************************************************************** 
 */

/*
******************************************************************************
Includes
******************************************************************************
*/
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdarg.h>
#include "stack.h"
#include "trap.h"

static bool isFull (Stack_t *pStack);
static bool isEmpty(Stack_t *pStack);

/**
 * @fn         static int isEmpty(Stack_t *pStack)
 * @param[in]  *pStack stack to test
 * @brief      tests if stack is empty.
 * @return     bool True or False
 * @note       none
 */
static bool isEmpty(Stack_t *pStack) {
  return pStack->StackTop == -1 ? true : false;
}

/**
 * @fn         static int isFull(Stack_t *pStack)
 * @param[in]  *pStack stack to test
 * @brief      tests if stack is full.
 * @return     bool True or False
 * @note       none
 */
static bool isFull(Stack_t *pStack) {
  return pStack->StackTop == (pStack->StackMax - 1) ? true : false;
}

/**
 * @fn         int pop(Stack_t *pStack)
 * @brief      "pop" off the top of the stack. If the stack is empty then we throw an 
 *             exception and return negative value 
 * @param[in]  *pStack - Stack to pop from
 * @param[out] *retvalue - data object 
 * @return     int 
 * @note       Will throw an exception if no stack is created.
 */
int pop(Stack_t *pStack, void *retvalue) {

  if ( pStack == (Stack_t *)NULL ) {
    Thrower(e_stacknotcreated);

    return -1;      
  }

  if (isEmpty(pStack)) {
    Thrower(e_stackunderflow);
    
    return -1;
  }

  switch (pStack->Type) {
     case stack_int:
       *((int *) retvalue) = pStack->pElement[pStack->StackTop--].stackdata.int_value;
       break;
     case stack_long:
       *((long *) retvalue) = pStack->pElement[pStack->StackTop--].stackdata.long_value;
       break;
     case stack_char:
       *((char *) retvalue) = pStack->pElement[pStack->StackTop--].stackdata.char_value;
       break;
     case stack_float:
       *((float *) retvalue) = pStack->pElement[pStack->StackTop--].stackdata.float_value;
       break;
     case stack_double:
	 *((double *) retvalue) = pStack->pElement[pStack->StackTop--].stackdata.double_value;
	 break;
     case stack_pointer:
	 *((void**) retvalue) = pStack->pElement[pStack->StackTop--].stackdata.ptr_value;
	 break;
     default:
          printf("pop - unknown object type %d\n", pStack->Type);
	 break;
  }

  return 0;
}

/**
 * @fn            int top(Stack_t *pStack) 
 * @brief         Returns the top of the stack, does not move the
 *                StackPointer
 * @param[in]     *pStack - Stack to peek from
 * @param[out]    *retvalue - data object from stack
 * @return        int stack_value
 * @note
 */
int top(Stack_t *pStack, void *retvalue) {
  if ( pStack == NULL ) {
    Thrower(e_stacknotcreated);

    return -1;      
  }
  
  if (isEmpty(pStack)) {
    Thrower(e_stackunderflow);
    
    return -1;
  }
  
  switch (pStack->Type) {
     case stack_int:
       *((int *) retvalue) = pStack->pElement[pStack->StackTop].stackdata.int_value;
       break;
     case stack_long:
       *((long *) retvalue) = pStack->pElement[pStack->StackTop].stackdata.long_value;
       break;
     case stack_char:
       *((char *) retvalue) = pStack->pElement[pStack->StackTop].stackdata.char_value;
       break;
     case stack_float:
       *((float *) retvalue) = pStack->pElement[pStack->StackTop].stackdata.float_value;
       break;
     case stack_double:
	 *((double *) retvalue) = pStack->pElement[pStack->StackTop].stackdata.double_value;
	 break;
     case stack_pointer:
	 *((void**) retvalue) = pStack->pElement[pStack->StackTop].stackdata.ptr_value;
	 break;
     default:
         printf("top - unknown object type %d\n", pStack->Type);
	 break;
  }

  return 0;
}

/**
 * @fn         int push(Stack_t *pStack, int element)
 * @brief      Push element onto the provided Stack
 * @param[in]  *pStack stack to push into
 * @return     -1 if error, 0 otherwise.
 * @note
 */
int push(Stack_t *pStack, ...) {

  //  printf("push pStack %p\n", (void*)pStack);

  if (pStack == NULL) {
    //    printf("push - stack is NULL\n");    
    Thrower(e_stacknotcreated);
    
    return -1;      
  }
  
  if (isFull(pStack)) {
    //    printf("push - stack is full\n");
    Thrower(e_stackoverflow);
    
    return -1;
  }

  va_list vargs;
  va_start(vargs, (Stack_t*)pStack);

  //  printf("push: type %d\n", pStack->Type);
  switch (pStack->Type) {
     case stack_int:
       pStack->pElement[++pStack->StackTop].stackdata.int_value  = va_arg(vargs, int);
       break;
     case stack_long:
       pStack->pElement[++pStack->StackTop].stackdata.long_value = va_arg(vargs, long);
       break;
     case stack_char:
       pStack->pElement[++pStack->StackTop].stackdata.char_value = (char) va_arg(vargs, int);
       break;
     case stack_float:
       pStack->pElement[++pStack->StackTop].stackdata.float_value= (float) va_arg(vargs, double);
       break;
     case stack_double:
       pStack->pElement[++pStack->StackTop].stackdata.double_value = va_arg(vargs, double);
       break;
     case stack_pointer:
       pStack->pElement[++pStack->StackTop].stackdata.ptr_value = va_arg(vargs, void *);
       break;
     default:
       break;
  }
  
  va_end(vargs);
  
  return 0;
}

/**
 * @fn         void swap (Stack_t *srcStack, Stack_t *dstStack)
 * @brief      Swap stacks from src -> dst
 * @param[in]  *srcStack source stack
 * @param[in]  *dstStack destination stack
 * @return     -1 if error, 0 otherwise.
 * @note       If the src < dst || dst < src we can simply copy, if not we
 *             need to reallocated more memory.
 */
int swap (Stack_t *srcStack, Stack_t *dstStack) {
  int i;
  int counter;
  Stack_t *pStack;

  pStack = srcStack;
  
  /*
   * TODO: If one is NULL we should simply allocate a new stack
   */
  if (srcStack == NULL || dstStack == NULL) {
	  Thrower(e_stacknotcreated);

	  return -1;
  }

  if (srcStack->pElement == NULL || dstStack->pElement == NULL) {
	  Thrower(e_stacknotcreated);
	  printf("swap - stacked has been freed already!\n");
	  return -1;
  }

  /*
   * Do we need to allocate more stack space?
   * If not we can simply copy from one to the other
   */
  //  printf("swap: src %d dst %d\n", srcStack->StackMax, dstStack->StackMax);
  
  if (srcStack->StackMax == dstStack->StackMax) {
    if (srcStack->StackMax <= dstStack->StackMax ) {
      counter = srcStack->StackMax;
    }
    if (dstStack->StackMax <= srcStack->StackMax ) {
      counter = dstStack->StackMax;
    }

    // printf("swap: stack size are the same\n");
    
    for (i=0; i < counter; i++) {
      int i_tmp;
      char c_tmp;
      long l_tmp;
      float f_tmp;
      double d_tmp;
      //      void *p_tmp;
      
      switch (pStack->Type) {
         case stack_int:

	   i_tmp = pStack->pElement[i].stackdata.int_value;
	   srcStack->pElement[i].stackdata.int_value = dstStack->pElement[i].stackdata.int_value;
	   dstStack->pElement[i].stackdata.int_value = i_tmp;
	   break;
         case stack_char:

	   c_tmp = pStack->pElement[i].stackdata.char_value;
	   srcStack->pElement[i].stackdata.char_value = dstStack->pElement[i].stackdata.char_value;
	   dstStack->pElement[i].stackdata.char_value = c_tmp;
	   break;
         case stack_long:

	   l_tmp = pStack->pElement[i].stackdata.long_value;
	   srcStack->pElement[i].stackdata.long_value = dstStack->pElement[i].stackdata.long_value;
	   dstStack->pElement[i].stackdata.long_value = l_tmp;
	   break;
         case stack_float:

	   f_tmp = pStack->pElement[i].stackdata.float_value;
	   srcStack->pElement[i].stackdata.float_value = dstStack->pElement[i].stackdata.float_value;
	   dstStack->pElement[i].stackdata.float_value = f_tmp;

	   break;
         case stack_double:

	   d_tmp = pStack->pElement[i].stackdata.double_value;
	   srcStack->pElement[i].stackdata.double_value = dstStack->pElement[i].stackdata.double_value;
	   dstStack->pElement[i].stackdata.double_value = d_tmp;
	   
	   break;
         case stack_pointer:
#if 0
	   *p_tmp = pStack->pElement[i].stackdata.ptr_value;
	   srcStack->pElement[i].stackdata.ptr_value = dstStack->pElement[i].stackdata.ptr_value;
	   dstStack->pElement[i].stackdata.ptr_value = *p_tmp;
#endif
	   break;
         default:
           printf("unknown object type %d\n", pStack->Type);
	   break;
       }
    }
  }

  if (srcStack->StackMax < dstStack->StackMax) {   /* We need to reallocate more memory for the source */
    int    *i_newStack;
    char   *c_newStack;
    long   *l_newStack;
    float  *f_newStack;
    double *d_newStack;
    int StackTop;

      switch (pStack->Type) {
         case stack_int:
	   i_newStack = realloc(srcStack->pElement, dstStack->StackMax); /* Add more memory                                  */
           srcStack->pElement = i_newStack;                              /* update to the new stack                          */
	   break;
         case stack_char:
	   c_newStack = realloc(srcStack->pElement, dstStack->StackMax); /* Add more memory                                  */
           srcStack->pElement = c_newStack;                              /* update to the new stack                          */
           break;
         case stack_long:
	   l_newStack = realloc(srcStack->pElement, dstStack->StackMax); /* Add more memory                                  */
           srcStack->pElement = l_newStack;                              /* update to the new stack                          */
           break;
         case stack_float:
	   f_newStack = realloc(srcStack->pElement, dstStack->StackMax); /* Add more memory                                  */
           srcStack->pElement = f_newStack;                              /* update to the new stack                          */
           break;
        case stack_double:
	   d_newStack = realloc(srcStack->pElement, dstStack->StackMax); /* Add more memory                                  */
           srcStack->pElement = d_newStack;                              /* update to the new stack                          */
           break;
        default:
           printf("unknown object type %d\n", pStack->Type);
	   break;
      }
      srcStack->StackMax = dstStack->StackMax;                      /* update the stack size                            */      
    // printf("swap: realloc src to size %ld\n", dstStack->StackMax);

    counter = dstStack->StackMax;
    for (i=0; i < counter; i++) {
      int i_tmp;
      char c_tmp;
      long l_tmp;
      float f_tmp;
      double d_tmp;
      //      void *p_tmp;
      
      switch (pStack->Type) {
         case stack_int:
	   i_tmp = pStack->pElement[i].stackdata.int_value;
	   srcStack->pElement[i].stackdata.int_value = dstStack->pElement[i].stackdata.int_value;
	   dstStack->pElement[i].stackdata.int_value = i_tmp;
	   break;
         case stack_char:
	   c_tmp = pStack->pElement[i].stackdata.char_value;
	   srcStack->pElement[i].stackdata.char_value = dstStack->pElement[i].stackdata.char_value;
	   dstStack->pElement[i].stackdata.char_value = c_tmp;
	   break;
         case stack_long:
	   l_tmp = pStack->pElement[i].stackdata.long_value;
	   srcStack->pElement[i].stackdata.long_value = dstStack->pElement[i].stackdata.long_value;
	   dstStack->pElement[i].stackdata.long_value = l_tmp;
	   break;
         case stack_float:
	   f_tmp = pStack->pElement[i].stackdata.float_value;
	   srcStack->pElement[i].stackdata.float_value = dstStack->pElement[i].stackdata.float_value;
	   dstStack->pElement[i].stackdata.float_value = f_tmp;
	   break;
         case stack_double:
	   d_tmp = pStack->pElement[i].stackdata.double_value;
	   srcStack->pElement[i].stackdata.double_value = dstStack->pElement[i].stackdata.double_value;
	   dstStack->pElement[i].stackdata.double_value = d_tmp;
	   break;
         case stack_pointer:
#if 0
	   *p_tmp = pStack->pElement[i].stackdata.ptr_value;
	   srcStack->pElement[i].stackdata.ptr_value = dstStack->pElement[i].stackdata.ptr_value;
	   dstStack->pElement[i].stackdata.ptr_value = *p_tmp;
#endif
	   break;
         default:
           printf("unknown object type %d\n", pStack->Type);
	   break;
       }
    }
    StackTop = dstStack->StackTop;
    dstStack->StackTop = srcStack->StackTop;
    srcStack->StackTop = StackTop;
  }

  if (dstStack->StackMax < srcStack->StackMax) {                    /* We need to reallocate more memory for the source */
    int    *i_newStack;
    char   *c_newStack;
    long   *l_newStack;
    float  *f_newStack;
    double *d_newStack;
    int StackTop;

    switch (pStack->Type) {
         case stack_int:
	   i_newStack = realloc(srcStack->pElement, dstStack->StackMax); /* Add more memory                                  */
           srcStack->pElement = i_newStack;                              /* update to the new stack                          */
	   break;
         case stack_char:
	   c_newStack = realloc(srcStack->pElement, dstStack->StackMax); /* Add more memory                                  */
           srcStack->pElement = c_newStack;                              /* update to the new stack                          */
           break;
         case stack_long:
	   l_newStack = realloc(srcStack->pElement, dstStack->StackMax); /* Add more memory                                  */
           srcStack->pElement = l_newStack;                              /* update to the new stack                          */
           break;
         case stack_float:
	   f_newStack = realloc(srcStack->pElement, dstStack->StackMax); /* Add more memory                                  */
           srcStack->pElement = f_newStack;                              /* update to the new stack                          */
           break;
        case stack_double:
	   d_newStack = realloc(srcStack->pElement, dstStack->StackMax); /* Add more memory                                  */
           srcStack->pElement = d_newStack;                              /* update to the new stack                          */
           break;
        default:
           printf("unknown object type %d\n", pStack->Type);
	   break;
      }
      srcStack->StackMax = dstStack->StackMax;                      /* update the stack size                            */      

	  // printf("swap: realloc src to size %ld\n", srcStack->StackMax);

	  counter = srcStack->StackMax;
	  for (i=0; i < counter; i++) {
	    int i_tmp;
	    char c_tmp;
	    long l_tmp;
	    float f_tmp;
	    double d_tmp;
	    //	    void *p_tmp;

	    switch (pStack->Type) {
	       case stack_int:
		 i_tmp = pStack->pElement[i].stackdata.int_value;
		 srcStack->pElement[i].stackdata.int_value = dstStack->pElement[i].stackdata.int_value;
		 dstStack->pElement[i].stackdata.int_value = i_tmp;
		 break;
	       case stack_char:
	         c_tmp = pStack->pElement[i].stackdata.char_value;
		 srcStack->pElement[i].stackdata.char_value = dstStack->pElement[i].stackdata.char_value;
		 dstStack->pElement[i].stackdata.char_value = c_tmp;
		 break;
	       case stack_long:
		 l_tmp = pStack->pElement[i].stackdata.long_value;
		 srcStack->pElement[i].stackdata.long_value = dstStack->pElement[i].stackdata.long_value;
		 dstStack->pElement[i].stackdata.long_value = l_tmp;
		 break;
               case stack_float:
		 f_tmp = pStack->pElement[i].stackdata.float_value;
		 srcStack->pElement[i].stackdata.float_value = dstStack->pElement[i].stackdata.float_value;
		 dstStack->pElement[i].stackdata.float_value = f_tmp;
		 break;
	       case stack_double:
		 d_tmp = pStack->pElement[i].stackdata.double_value;
		 srcStack->pElement[i].stackdata.double_value = dstStack->pElement[i].stackdata.double_value;
		 dstStack->pElement[i].stackdata.double_value = d_tmp;
		 break;
	       case stack_pointer:
#if 0
          	   *p_tmp = pStack->pElement[i].stackdata.ptr_value;
		   srcStack->pElement[i].stackdata.ptr_value = dstStack->pElement[i].stackdata.ptr_value;
		   dstStack->pElement[i].stackdata.ptr_value = *p_tmp;
#endif
		   break;
	    default:
	      printf("unknown object type %d\n", pStack->Type);
	      break;
	    }
	  }
	  StackTop = dstStack->StackTop;
	  dstStack->StackTop = srcStack->StackTop;
	  srcStack->StackTop = StackTop;
  }

  return 0;
}

/**
 * @fn         bool empty(Stack_t *pStack) 
 * @brief      is the stack empty?
 * @param[in]  *pStack - Stack to pop from
 * @return     bool TRUE, if empty, false otherwise
 * @note       Will throw an exception if no stack is created.
 */
bool empty(Stack_t *pStack) {

  if ( pStack == (Stack_t *)NULL ) {
    Thrower(e_stacknotcreated);

    return false;
  }

  if (isEmpty(pStack)) {
    return true;
  }

  return false;
}

/**
 * @fn         int size(Stack_t *pStack)
 * @brief      return the number of elements on the stack
 * @param[in]  *pStack stack
 * @return     size
 * @note
 */
int size(Stack_t *pStack) {
  if ( pStack == NULL ) {
    Thrower(e_stacknotcreated);

    return -1;      
  }
  
  return pStack->StackTop+1;
}

/**
 * @fn         void StackDump (Stack_t *pStack, int num) {
 * @brief      print out stack contents to console. 
 * @param[in]  *pStack stack to test
 * @param[in]  num allows number of elements to be printed. 
 * @return     None
 * @note
 */
void StackDump (Stack_t *pStack, int num) {
  int i;
  int numtoShow = 0;
  char *TypeStr[] = {
     "<char>  ",
     "<int>   ",
     "<long>  ",
     "<float> ",
     "<double>",
     "<string>",
     "<pointer>"
  };
  
  if (pStack == NULL || pStack->pElement == NULL) {
    Thrower(e_stacknotcreated);

    return;      
  }
  
  if (isEmpty(pStack)) {
    printf ("Stack empty - nothing to display\n");

    return;
  }

  if (num == 0) {
    numtoShow = pStack->StackMax;
  } else {
    numtoShow = num;
  }

  printf("******** Stack Type %s, Size = %ld *********\n", TypeStr[pStack->Type], (long int)pStack->StackMax);
  for (i=0; i < numtoShow; i++) {
    switch(pStack->Type) {
        case stack_char:
          printf("Stack[%4d] = %c", i, pStack->pElement[i].stackdata.char_value);
	  break;
        case stack_int:
          printf("Stack[%4d] = %d", i, pStack->pElement[i].stackdata.int_value);
          break;
        case stack_long:
          printf("Stack[%4d] = %ld", i, pStack->pElement[i].stackdata.long_value);
          break;
        case stack_float:
          printf("Stack[%4d] = %f", i, pStack->pElement[i].stackdata.float_value);
	  break;
        case stack_pointer:
          printf("Stack[%4d] = %p", i, pStack->pElement[i].stackdata.ptr_value);
	  break;
        default:
	  printf("StackDump - Unknown object type %d\n", pStack->Type);
          break;
    }
      
    if (i == pStack->StackTop) {
      printf("  <--- Stacktop");
    }
    printf("\n");  
  }
}

/**
 * @fn         Stack_t *StackCreate(int maxStack)
 * @brief      creates a stack of the size specified in maxStack 
 *             using malloc().
 * @param[in]  maxStack - Maximum size of the Stack to create
 * @param[in]  type - what object type is stored in the Stack
 * @return     Stack_t pointer to the Stack_t structure or NULL
 */
Stack_t *StackCreate(size_t maxStack, const StackType_t Type) {

  /* 
   * Cannot allocate negative size stacks
   */
  if (maxStack == (size_t)0) {
    return (Stack_t *)NULL;
  }

  /*
   * create a stack "head"
   */
  Stack_t *pStackHead = (Stack_t *)malloc(sizeof(Stack_t));
  if (pStackHead == NULL) {
    return (Stack_t *)NULL;
  }
  //  printf("StackCreate: StackHead %p\n", (void*)pStackHead);
  
  pStackHead->StackMax = maxStack; /* High water mark for the stack */
  pStackHead->StackTop = -1;       /* Ready for push                */
  pStackHead->Type     = Type;     /* What object is in the stack   */
  pStackHead->pStack   = NULL;
  
  /*
   * create the actual stack to push and pull from 
   */
  /*  pStackHead->pStack   = (int *)malloc(sizeof(int) * maxStack); */
  // printf("StackCreate: size request = %ld, actual size = %ld\n", maxStack, sizeof(pStackHead->pElement) * maxStack);
  
  //  pStackHead->pStack = malloc(sizeof(*pStackHead->pElement) * maxStack);
  pStackHead->pElement = malloc(sizeof(*pStackHead->pElement) * maxStack);  
  // printf("StackCreate: pElement %p\n", (void*)pStackHead->pElement);
  
  return pStackHead;
}

/**
 * @fn         int StackDestroy(Stack_t *sp)
 * @brief      Destroy the created stack 
 * @param[in]  *pStack object to be destroyed
 * @return     -1 if Error, else 0
 */
int StackDestroy(Stack_t *pStack) {

  if ( pStack == (Stack_t *)NULL) {
    Thrower(e_stacknotcreated);    

    return -1;
  }

  /*
   * destroy the actual stack to push and pull from 
   */
  free (pStack->pElement);
  //  printf("StackDestroy: %p\n", (void*)pStack->pElement);    
  free (pStack);
  // printf("StackDestroy: %p\n", (void*)pStack);  
  
  return 0;
}

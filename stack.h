#ifndef STACK_H
#define STACK_h

#include "std_types.h"
#define STACK_DEBUG ;

// The struct of Stack

typedef struct
{
    void **stackArray;
    sint32 stackTop;
    uint32 elementCount;
    uint32 stackMaxSize;
} Stack_t;

// all status which will happen

typedef enum
{
    STACK_EMPTY,
    STACK_FULL,
    STACK_OK,
    STACK_NOK,
    STACK_NULL_POINTER,
} StackStatus_t;

Stack_t *CreatStack(uint32 maxSize, StackStatus_t *ret_status);
Stack_t *DestroyStack(Stack_t *stack_obj, StackStatus_t *ret_status);
StackStatus_t PushStack(Stack_t *stack_obj, void *itemptr);
void *PopStack(Stack_t *stack_obj, StackStatus_t *ret_status);
void *StackTop(Stack_t *stack_obj, StackStatus_t *ret_status);
StackStatus_t StackConut(Stack_t *stack_obj, uint32 *stack_count);

#endif

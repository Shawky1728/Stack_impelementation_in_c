#include "stack.h"

/*
 * @brief      check status is Empty
 * @parameter  stack_obj pointer to stack
 * @return     status of stack
 */

static uint8 StackIsEmpty(Stack_t *stack_obj)
{

    return (stack_obj->elementCount == 0);
}

/*
 * @brief     check status is full
 * @parameter stack_obj pointer to stack
 * @return    status of stack
 */

static uint8 StackIsFull(Stack_t *stack_obj)
{

    return (stack_obj->elementCount == stack_obj->stackMaxSize);
}

/*
 * @brief     creat the stack
 * @parameter maxSize uint32 for  stack
 * @parameter ret_status pointer to status of stack
 * @return    return a pointer to the stack
 */

Stack_t *CreatStack(uint32 maxSize, StackStatus_t *ret_status)
{

    Stack_t *my_stack = NULL;
    if (NULL == ret_status)
    {

        *ret_status = STACK_NULL_POINTER;
        my_stack = NULL;
    }
    else
    {
        my_stack = (Stack_t *)malloc(sizeof(Stack_t));
        if (!my_stack)
        {
            *ret_status = STACK_NULL_POINTER;
            my_stack = NULL;
        }
        else
        {
            my_stack->elementCount = 0;
            my_stack->stackMaxSize = maxSize;
            my_stack->stackTop = -1;
            my_stack->stackArray = (void **)calloc(maxSize, sizeof(void *));

            if (NULL == my_stack->stackArray)
            {
                *ret_status = STACK_NULL_POINTER;
                free(my_stack);
            }
            else
            {
                *ret_status = STACK_OK;
#ifdef STACK_DEBUG
                printf("Stack with size %d is created\n", maxSize);
#endif
            }
        }
    }
    return my_stack;
}

/*
 * @brief     destroy the stack
 * @parameter stack_obj pointer to  stack
 * @parameter ret_status pointer to status of stack
 * @return    return a pointer to the stack
 */

Stack_t *DestroyStack(Stack_t *stack_obj, StackStatus_t *ret_status)
{

    Stack_t *my_stack = NULL;

    if (NULL == ret_status || NULL == stack_obj)
    {

        *ret_status = STACK_NULL_POINTER;
    }
    else
    {
        if (NULL == stack_obj->stackArray)
        {
            *ret_status = STACK_NULL_POINTER;
        }
        else
        {
            free(stack_obj->stackArray);
            free(stack_obj);
            *ret_status = STACK_OK;
#ifdef STACK_DEBUG
            printf("Stack with size %d is destroyed\n", stack_obj->stackMaxSize);
#endif
        }
    }
    return my_stack;
}

/*
 * @brief     push elements to the stack
 * @parameter stack_obj pointer to  stack
 * @parameter itemptr pointer to data
 * @return    return the status of stack
 */

StackStatus_t PushStack(Stack_t *stack_obj, void *itemptr)
{

    StackStatus_t ret_status = STACK_NOK;

    if (NULL == itemptr || NULL == stack_obj)
    {

        ret_status = STACK_NULL_POINTER;
    }
    else
    {
        if (StackIsFull(stack_obj))
        {
            ret_status = STACK_FULL;
        }
        else
        {
            (stack_obj->stackTop)++;
            stack_obj->stackArray[stack_obj->stackTop] = itemptr;
            (stack_obj->elementCount)++;
            ret_status = STACK_OK;
#ifdef STACK_DEBUG
            printf("the element %d is added \n", *((int *)itemptr));
#endif
        }
    }

    return ret_status;
}

/*
 * @brief     remove elements from the stack
 * @parameter stack_obj pointer to  stack
 * @parameter ret_status pointer to status of stack
 * @return    return a void pointer to element that removed
 */

void *PopStack(Stack_t *stack_obj, StackStatus_t *ret_status)
{

    void *returnElement = NULL;
    if (NULL == ret_status || NULL == stack_obj)
    {

        *ret_status = STACK_NULL_POINTER;
    }
    else
    {
        if (StackIsEmpty(stack_obj))
        {
            *ret_status = STACK_EMPTY;
        }
        else
        {
            returnElement = stack_obj->stackArray[stack_obj->stackTop];
            (stack_obj->stackTop)--;
            (stack_obj->elementCount)--;
            *ret_status = STACK_OK;
#ifdef STACK_DEBUG
            printf("the element %d is removed \n", *((int *)returnElement));
#endif
        }
    }

    return returnElement;
}

/*
 * @brief     return the element on the top of stack
 * @parameter stack_obj pointer to  stack
 * @parameter ret_status pointer to status of stack
 * @return    return a void pointer to element that on top
 */

void *StackTop(Stack_t *stack_obj, StackStatus_t *ret_status)
{

    void *returnElement = NULL;
    if (NULL == ret_status || NULL == stack_obj)
    {

        *ret_status = STACK_NULL_POINTER;
    }
    else
    {
        if (StackIsEmpty(stack_obj))
        {

            *ret_status = STACK_EMPTY;
            returnElement = NULL;
        }
        else
        {
            returnElement = stack_obj->stackArray[stack_obj->stackTop];
            *ret_status = STACK_OK;
        }
    }

    return returnElement;
}

/*
 * @brief     count the elements in stack
 * @parameter stack_obj pointer to  stack
 * @parameter stack_count pointer to number of elements
 * @return    return a status of stack
 */

StackStatus_t StackConut(Stack_t *stack_obj, uint32 *stack_count)
{

    StackStatus_t ret_status = STACK_NOK;

    if (NULL == stack_count || NULL == stack_obj)
    {

        ret_status = STACK_NULL_POINTER;
    }
    else
    {
        *stack_count = stack_obj->elementCount;
        ret_status = STACK_OK;
    }

    return ret_status;
}

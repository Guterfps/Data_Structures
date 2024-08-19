/****************************
*	developer : Itay Guter	*
*							*
*	WS : stack				*
*							*	
*	reviewer : 	Noy Cohen	*
*****************************/

#include <assert.h>	/*assert()*/
#include <stdlib.h>	/*calloc(), free()*/

#include "stack.h" /*header of this file*/


struct stack
{
	int top;
	size_t capacity;
	void **arr;
};

stack_t *StackCreate(size_t capacity)
{
	stack_t *stack = NULL;
	
	stack = (stack_t *)malloc(sizeof(stack_t));
	if (NULL == stack)
	{
		return NULL;
	}
	
	stack->capacity = capacity;
	stack->top = -1;
	stack->arr = NULL;
	
	stack->arr = calloc(capacity, sizeof(void *));
	if (NULL == stack->arr)
	{
		free(stack);
		stack = NULL;
		return NULL;
	}
	
	return (stack);
}

void StackDestroy(stack_t *stack)
{
	assert(NULL != stack);
	
	free(stack->arr);
	stack->arr = NULL;
	free(stack);
	stack = NULL;
}

void StackPush(stack_t *stack, void *data)
{
	assert(NULL != stack);
	assert(NULL != data);
	
	++(stack->top);
	*(stack->arr + stack->top) = data;
}

void *StackPop(stack_t *stack)
{
	void *data = NULL;
	assert(NULL != stack);
	
	data = *(stack->arr + stack->top);
	*(stack->arr + stack->top) = NULL;
	--(stack->top);
	
	return data;
}

void *StackPeek(const stack_t *stack)
{
	assert(NULL != stack);
	
	return *(stack->arr + stack->top);
}

size_t StackSize(const stack_t *stack)
{
	assert(NULL != stack);
	
	return (stack->top + 1);
}

size_t StackCapacity(const stack_t *stack)
{
	assert(NULL != stack);
	
	return (stack->capacity);
}

int StackIsEmpty(const stack_t *stack)
{
	assert(NULL != stack);
	
	return (-1 == stack->top);
}



/****************************
*	developer : Itay Guter	*
*							*
*	WS : stack				*
*							*	
*	reviewer : 	Noy Cohen	*
*****************************/

/********************************Documantation*********************************
*	stack_t type to use stack.
*	
*	to create a stack use StackCreate(size_t capacity)
*	the function returns a pointer of type stack_t to the stack,
*	if it fails it returns NULL.
*	resources complexity: time: o(1) , space: o(n).
*
*	to destroy a stack use StackDestroy(stack_t *stack).
*	resources complexity: time: o(1) , space: o(1).
*
*	to add items to the stack use StackPush(stack_t *stack, void *data).
*	resources complexity: time: o(1) , space: o(1).
*
*	to remove items from the stack use StackPop(stack_t *stack).
*	returns the address of the item.
*	resources complexity: time: o(1) , space: o(1).
*
*	to "see" the item in the top of the stack 
*	use StackPeek(const stack_t *stack).
*	returns the address of the item.
*	resources complexity: time: o(1) , space: o(1).
*
*	to get the number of items in the stack use StackSize(const stack_t *stack),
*	it returns a size_t number.
*	resources complexity: time: o(1) , space: o(1).	
*
*
*	to get the maximum capacity of the stack 
*	use StackCapacity(const stack_t *stack),
*	it returns a size_t number.
*	resources complexity: time: o(1) , space: o(1).
*
*	to check if the stack is empty use StackIsEmpty(const stack_t *stack),
*	it returns 1 if the stack is empty and 0 otherwise.
*	resources complexity: time: o(1) , space: o(1).
*
******************************************************************************/

#ifndef STACK_H
#define STACK_H

#include <stddef.h>	/*size_t*/

/************************struct*****************************/
typedef struct stack stack_t;



/******************Function Declarations********************/


stack_t *StackCreate(size_t capacity);
	 

void StackDestroy(stack_t *stack);

 	
void StackPush(stack_t *stack, void *data);

	
void *StackPop(stack_t *stack);	

	
void *StackPeek(const stack_t *stack);	

	
size_t StackSize(const stack_t *stack);	

	
size_t StackCapacity(const stack_t *stack);

	
int StackIsEmpty(const stack_t *stack);		

#endif




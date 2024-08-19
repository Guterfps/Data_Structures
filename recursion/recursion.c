/*-------------------------------------------*/
/* DEVELOPER: Itay Guter                    */
/* LAST MODIFIED: 26/1/2023	               */
/* WORKSHEET NAME: Recursion		      */
/* REVIEWER: Noy Elankry		         */
/*--------------------------------------*/

#include <assert.h>	/* assert() */
#include <string.h>	/* strncmp() */

#include "recursion.h"	/* functions declerations and typedefs */

static void SaveCurrentTop(int **top, stack_t *stack);
static int *FindElementToInsert(stack_t *stack, int *data);

int IterFibonacci(int element_index)
{
	int result = element_index;
	int fib1 = 0;
	int fib2 = 1;
	
	if (0 == element_index || 1 == element_index)
	{
		return result;
	}
	
	for (;1 < element_index; --element_index)
	{
		result = fib1 + fib2;
		fib1 = fib2;
		fib2 = result; 
	}
	
	return result;
}

int RecFibonacci(int element_index)
{
	if (0 == element_index || 1 == element_index)
	{
		return element_index;
	}
	
	return (RecFibonacci(element_index - 1) + RecFibonacci(element_index - 2));
}

node_t *RecFlipList(node_t *node)
{
	node_t *rest_of_list = NULL;
	
	assert(NULL != node);
	
	if (NULL == node->next)
	{
		return node;
	}
	
	rest_of_list = RecFlipList(node->next);
	node->next->next = node;
	node->next = NULL;
	
	return rest_of_list;
}

void RecStackSort(stack_t *stack)
{	
	int *top = NULL;
	
	assert(NULL != stack);
	
	if (StackIsEmpty(stack))
	{
		return;
	}
	
	SaveCurrentTop(&top, stack);
	RecStackSort(stack);
	RecStackSortInsert(stack, top);
}

void RecStackSortInsert(stack_t *stack, int *data)
{
	int *element = NULL;
	
	assert(NULL != stack);
	assert(NULL != data);
	
	if (StackIsEmpty(stack) || (*data >= *(int *)StackPeek(stack)))
	{
		StackPush(stack, data);
		return;
	}
	
	element = FindElementToInsert(stack, data);
	StackPush(stack, element);
}

size_t RecStrLen(const char *str)
{
	assert(NULL != str);
	
	if ('\0' == *str)
	{
		return 0;
	}	
	
	return (1 + RecStrLen(str + 1));
}

int RecStrCmp(const char *str1, const char *str2)
{
	assert(NULL != str1);
	assert(NULL != str2);
	
	if ((*str1 != *str2) || ('\0' == *str2))
	{
		return (*str1 - *str2);
	}
	
	return (RecStrCmp(str1 + 1, str2 + 1));
}

char *RecStrCpy(char *dst, const char *src)
{
	assert(NULL != dst);
	assert(NULL != src);
	
	*dst = *src;
	
	if ('\0' == *src)
	{
		return dst;
	}
	
	return (RecStrCpy(dst + 1, src + 1) - 1);
}

char *RecStrCat(char *dst, const char *src)
{
	assert(NULL != dst);
	assert(NULL != src);
	
	if ('\0' == *dst)
	{
		return RecStrCpy(dst, src);
	}
	
	return (RecStrCat(dst + 1, src) - 1);
}

char *RecStrStr(const char *haystack, const char *needle)
{
	assert(NULL != haystack);
	assert(NULL != needle);
	
	if ('\0' == *haystack)
	{
		return NULL;
	}
	else if (0 == strncmp(haystack, needle, RecStrLen(needle)))
	{
		return (char *)haystack;
	}
	
	return (RecStrStr(haystack + 1, needle));
}

static void SaveCurrentTop(int **top, stack_t *stack)
{
	assert(NULL != top);
	
	*top = (int *)StackPop(stack);
}

static int *FindElementToInsert(stack_t *stack, int *data)
{
	int *temp = NULL;
	
	assert(NULL != stack);
	assert(NULL != data);
	
	temp = (int *)StackPop(stack);
	RecStackSortInsert(stack, data);
	
	return temp;
}


/*-------------------------------------------*/
/* DEVELOPER: Itay Guter                    */
/* LAST MODIFIED: 26/1/2023	               */
/* WORKSHEET NAME: Recursion		      */
/* REVIEWER: Noy Elankry		         */
/*--------------------------------------*/

#ifndef __RECURSION_H__
#define __RECURSION_H__

#include <stddef.h>		/* size_t */

#include "stack.h"		/* stack API */

/*-----------------------------------------------------------------------------
Recursion: The process in which a function calls itself directly or indirectly 
is called recursion and the corresponding function is called a recursive 
function. A recursive function solves a particular problem by calling a copy of 
itself and solving smaller subproblems of the original problems. Many more 
recursive calls can be generated as and when required. It is essential to know 
that we should provide a certain case in order to terminate this recursion 
process.
------------------------------------------------------------------------------*/

/* simple single linke list node */
typedef struct node
{
	void *data;
	struct node *next;
}node_t;

/*-----------------------------------------------------------------------------
Description: calculate the nth element of a fibonacci sequnce iterativly.

parameters: element_index - nth element of a fibonacci sequnce.

return value: the value of the nth element.

complexity:
	time: O(n) / space: O(1).
------------------------------------------------------------------------------*/
int IterFibonacci(int element_index);

/*-----------------------------------------------------------------------------
Description: calculate the nth element of a fibonacci sequnce recursivly.

parameters: element_index - nth element of a fibonacci sequnce.

return value: the value of the nth element.

complexity:
	time: O(n) / space: O(n).
------------------------------------------------------------------------------*/
int RecFibonacci(int element_index);

/*-----------------------------------------------------------------------------
Description: reverse the order of nodes in a single linke list.

parameters: node - the head of the list.

return value: the new head of the list(the old tail).

complexity:
	time: O(n) / space: O(n).
------------------------------------------------------------------------------*/
node_t *RecFlipList(node_t *node);

/*-----------------------------------------------------------------------------
Description: sorts a stack of integers from small to large(large at the top).

parameters: stack - pointer to a stack.

return value: none.

complexity:
	time: O(n^2) / space: O(n).
------------------------------------------------------------------------------*/
void RecStackSort(stack_t *stack);

/*-----------------------------------------------------------------------------
Description: inserting an element into the stack in the correct order(small
			 to big).

parameters: stack - pointer to a stack.
			data - pointer to the element to insert

return value: none.

complexity:
	time: O(n) / space: O(n).
------------------------------------------------------------------------------*/
void RecStackSortInsert(stack_t *stack, int *data);

/*-----------------------------------------------------------------------------
Description: calculate the length of a string recursivly.

parameters: str - pointer to null terminated string.

return value: the length of the string.

complexity:
	time: O(n) / space: O(n).
------------------------------------------------------------------------------*/
size_t RecStrLen(const char *str);

/*-----------------------------------------------------------------------------
Description: compers two strings recursivly.

parameters: str1 - pointer to null terminated string.
			str2 - pointer to null terminated string.

return value: negtive if a character in str1 has smaller ascii value then the
			  one in str2, otherwise positive, if they are the same returns 0.

complexity:
	time: O(n) / space: O(n).
------------------------------------------------------------------------------*/
int RecStrCmp(const char *str1, const char *str2);

/*-----------------------------------------------------------------------------
Description: copys one string to a given buffer(including null terminator).

parameters: dst - pointer to a buffer to copy to.
			src - pointer to null terminated string.

return value: pointer top dst.

note: if the buffer is not big enough the behivior is undefined.

complexity:
	time: O(n) / space: O(n).
------------------------------------------------------------------------------*/
char *RecStrCpy(char *dst, const char *src);

/*-----------------------------------------------------------------------------
Description: copys src to the end of dst.

parameters: dst - pointer to null terminated string.
			src - pointer to null terminated string.

return value: pointer to dst.

complexity:
	time: O(n) / space: O(n).
------------------------------------------------------------------------------*/
char *RecStrCat(char *dst, const char *src);

/*-----------------------------------------------------------------------------
Description: finds the first occurrence of the substring needle in the string 
			haystack. The terminating null bytes ('\0') are not compared.

parameters: haystack - pointer to null terminated string to search in.
			needle - pointer to null terminated string to search for.
			
return value: pointer to the first occurrence of the substring needle in the
			  string haystack.

complexity:
	time: O(n) / space: O(n).
------------------------------------------------------------------------------*/
char *RecStrStr(const char *haystack, const char *needle);

#endif /* __RECURSION_H__ */


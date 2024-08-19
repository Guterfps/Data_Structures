/*-------------------------------------------*/
/* DEVELOPER: Itay Guter                    */
/* LAST MODIFIED: 26/1/2023	               */
/* WORKSHEET NAME: Recursion		      */
/* REVIEWER: Noy Elankry		         */
/*--------------------------------------*/

#include <stdio.h>	/* printf() */
#include <string.h>	/* tests */

#include "recursion.h"	/* functions declerations and typedefs */

void FibTest(void);
void FlipListTest(void);
void StrTest(void);
void SortStack(void);

int main(void)
{
	FibTest();
	FlipListTest();
	StrTest();
	SortStack();
	
	return 0;
}

void FibTest(void)
{
	int results[] = {0,1,1,2,3,5,8,13,21,34,55,89,144,233,377,610};
	size_t len = sizeof(results) / sizeof(*results);
	int status = 1;
	size_t i = 0;
	
	for (i = 0; (i < len) && status; ++i)	
	{
		status = (results[i] == IterFibonacci(i));
	}
	printf("iter fib test:	");
	status ? printf("SUCCESS ✅️\n") : printf("FAIL ❌️\n");

	for (i = 0; (i < len) && status; ++i)	
	{
		status = (results[i] == RecFibonacci(i));
	}
	printf("recursive fib test:	");
	status ? printf("SUCCESS ✅️\n") : printf("FAIL ❌️\n");
}

void FlipListTest(void)
{
	node_t head = {NULL};
	node_t node1 = {NULL}, node2 = {NULL}, node3 = {NULL};
	
	head.next = &node1;
	node1.next = &node2;
	node2.next = &node3;
	node3.next = NULL;
	
	printf("Flip list test1:	");
	(&node3 == RecFlipList(&node3)) ? 
	printf("SUCCESS ✅️\n") : printf("FAIL ❌️\n");
	
	printf("Flip list test2:	");
	(&node3 == RecFlipList(&head)) ? 
	printf("SUCCESS ✅️,") : printf("FAIL ❌️,");
	(NULL == head.next) ? printf("SUCCESS ✅️,") : printf("FAIL ❌️,");
	(&node1 == node2.next) ? printf("SUCCESS ✅️\n") : printf("FAIL ❌️\n");
	
	printf("Flip list test3:	");
	(&head == RecFlipList(&node3)) ? 
	printf("SUCCESS ✅️,") : printf("FAIL ❌️,");
	(NULL == node3.next) ? printf("SUCCESS ✅️,") : printf("FAIL ❌️,");
	(&node2 == node1.next) ? printf("SUCCESS ✅️\n") : printf("FAIL ❌️\n");
	
}

void StrTest(void)
{
	const char *test1 = "";
	const char *test2 = "ahi";
	const char *test3 = "ah yakar";
	const char *test4 = "ahi";
	char copy[20] = {0};
	const char *test_cat = "ahiah yakar";
	const char *test_strstr = "ya";
	const char *test_strstr2 = "ay";
	
	printf("strlen test:	");
	(strlen(test1) == RecStrLen(test1)) ? 
	printf("SUCCESS ✅️,") : printf("FAIL ❌️,");
	(strlen(test2) == RecStrLen(test2)) ?
	printf("SUCCESS ✅️,") : printf("FAIL ❌️,");
	(strlen(test3) == RecStrLen(test3)) 
	? printf("SUCCESS ✅️,") : printf("FAIL ❌️,");
	printf("\n");
	
	printf("strcmp test:	");
	(0 < RecStrCmp(test2, test1)) ? 
	printf("SUCCESS ✅️,") : printf("FAIL ❌️,");
	(0 == RecStrCmp(test2, test4)) ? 
	printf("SUCCESS ✅️,") : printf("FAIL ❌️,");
	(0 > RecStrCmp(test3, test4)) ? 
	printf("SUCCESS ✅️,") : printf("FAIL ❌️,");
	printf("\n");
	
	printf("strcpy test:	");
	(copy == RecStrCpy(copy, test4)) ? 
	printf("SUCCESS ✅️,") : printf("FAIL ❌️,");
	(0 == RecStrCmp(copy, test4)) ? 
	printf("SUCCESS ✅️,") : printf("FAIL ❌️,");
	printf("\n");
	
	printf("strcat test:	");
	(copy == RecStrCat(copy, test3)) ? 
	printf("SUCCESS ✅️,") : printf("FAIL ❌️,");
	(0 == RecStrCmp(copy, test_cat)) ? 
	printf("SUCCESS ✅️,") : printf("FAIL ❌️,");
	printf("\n");
	
	printf("strstr test:	");
	((test_cat + 6) == RecStrStr(test_cat, test_strstr)) ? 
	printf("SUCCESS ✅️,") : printf("FAIL ❌️,");
	(NULL == RecStrStr(test_cat, test_strstr2)) ? 
	printf("SUCCESS ✅️,") : printf("FAIL ❌️,");
	printf("\n");
	
}

void SortStack(void)
{
	stack_t *stack = NULL;
	int arr[] = {1, 0 ,-1, 3, 7, 25, 420, 3, 123, 0};
	size_t len = sizeof(arr) / sizeof(*arr);
	size_t i = 0;
	int status = 1;
	
	stack = StackCreate(len);
	
	for (i = 0; i < len; ++i)
	{
		StackPush(stack, arr + i);
	}
	
	RecStackSort(stack);
	
	for(i = 0; (i < len - 1) && status; ++i)
	{
		status = (*(int *)StackPop(stack) >= *(int *)StackPeek(stack));
	}
	
	printf("sort stack test:	");
	status ? printf("SUCCESS ✅️\n") : printf("FAIL ❌️\n");
	
	StackDestroy(stack);
	stack = NULL;
}



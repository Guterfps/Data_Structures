/*-------------------------------------------*/
/* DEVELOPER: Itay Guter                    */
/* LAST MODIFIED: 07/12/2022               */
/* WORKSHEET NAME: Singly linked list     */
/* REVIEWER: Noy Elankry                 */
/*--------------------------------------*/

#include <stdio.h>	/*printf()*/

#include "slist.h"	/*function declerations and typedefs*/

#define CHECK_MARK ("\t\033[0;32m\xE2\x9C\x93\033[0m\n")
#define FAIL_MARK ("\t\033[0;31m\xE2\x9C\x97\033[0m\n")

void TestList(void);
void TestListForEach(void);
int PrintIntValues(void *data, void *param);
int IsInt(const void *data, void *param);

int main(void)
{
	TestList();
	TestListForEach();
	
	return 0;
}

void TestList(void)
{
	int num = 7;
	char *str = "ahi";
	double d = 2.71;
	slist_iter_t iter_start = NULL;
	slist_iter_t iter_end = NULL;
	slist_iter_t iter_runer = NULL;
	slist_t *list = SlistCreate();
	
	SlistIsEmpty(list) ? printf("list empty	%s\n", CHECK_MARK) :
	 					 printf("list not empty %s\n", FAIL_MARK);
	printf("size is: %ld", SlistCount(list));
	(SlistCount(list) == 0) ? printf("	%s\n", CHECK_MARK) :
	 					 		printf("	%s\n", FAIL_MARK);
	 					 		
	iter_start = SlistBegin(list);
	iter_end = SlistEnd(list);
	iter_runer = SlistInsertBefore(iter_start, &num);
	printf("value at start is: %d\n", *(int *)SlistGetVal(iter_runer));
	SlistInsertBefore(iter_start, str);
	printf("value at start is: %s\n", (char *)SlistGetVal(iter_start));
	iter_runer = SlistInsertBefore(iter_end, &d);
	printf("value at end is: %.2f\n", *(double *)SlistGetVal(iter_runer));
	printf("size is: %ld\n", SlistCount(list));
	(SlistCount(list) == 3) ? printf("	%s\n", CHECK_MARK) :
	 					 		printf("	%s\n", FAIL_MARK);
	
	SlistIsEmpty(list) ? printf("list empty	%s\n", FAIL_MARK) :
	 					 printf("list not empty	%s\n", CHECK_MARK);
	iter_runer = SlistRemove(iter_start);
	printf("value at start is: %s\n", (char *)SlistGetVal(iter_start));
	SlistRemove(iter_start);
	printf("value at start is: %d\n", *(int *)SlistGetVal(iter_runer));
	printf("size is: %ld", SlistCount(list));
	(SlistCount(list) == 1) ? printf("		%s\n", CHECK_MARK) :
	 					 		printf("	 %s\n", FAIL_MARK);
	
	
	SlistIsEmpty(list) ? printf("list empty	%s\n", FAIL_MARK) :
	 					 printf("list not empty	%s\n", CHECK_MARK);
	iter_runer = SlistRemove(iter_start);
	SlistIsEmpty(list) ? printf("list empty	%s\n", CHECK_MARK) :
	 					 printf("list not empty %s\n", FAIL_MARK);
	SlistDestroy(list);	
	
}

void TestListForEach(void)
{
	int num1 = 0;
	int num2 = 20;
	int num3 = 300;
	int num4 = 4;
	int num_set = 123;
	int counter = 1;
	slist_t *list = SlistCreate();
	slist_iter_t iter_start = NULL;
	slist_iter_t iter_end = NULL;
	slist_iter_t iter_runer = NULL;
	slist_do_action_t print = &PrintIntValues;
	
	iter_start = SlistBegin(list);

	iter_runer = SlistInsertBefore(iter_start, &num1);
	iter_runer = SlistInsertBefore(iter_start, &num2);
	iter_end = SlistEnd(list);
	SlistForEach(iter_start, iter_end, print, &counter);
	counter = 1;
	
	SlistIterIsEqual(iter_end, iter_start) ? 
	printf("iterators are same	%s\n", FAIL_MARK) :
	printf("iterators are not same	%s\n", CHECK_MARK);
											 
	SlistIterIsEqual(iter_runer, iter_start) ? 
	printf("iterators are same	%s\n", CHECK_MARK) : 
	printf("iterators are not same	%s\n", FAIL_MARK);
											 
	SlistInsertBefore(iter_end, &num3);
	iter_end = SlistEnd(list);
	SlistForEach(iter_start, iter_end, print, &counter);
	counter = 1;
											 
	iter_end = SlistEnd(list);
	iter_runer = SlistFind(iter_start, iter_end, IsInt, &num1);
	printf("value at middle is: %d\n", *(int *)SlistGetVal(iter_runer));
	iter_runer = SlistInsertBefore(iter_runer, &num4);
	
	iter_runer = SlistFind(iter_start, iter_end, IsInt, &num1);
	SlistSetVal(iter_runer, &num_set);
	printf("value after set is: %d\n", *(int *)SlistGetVal(iter_runer));
	
	iter_end = SlistEnd(list);
	printf("size is: %ld", SlistCount(list));
	(SlistCount(list) == 4) ? printf("		%s\n", CHECK_MARK) :
	 					 		printf("	 %s\n", FAIL_MARK);
	SlistForEach(iter_start, iter_end, print, &counter);
	counter = 1;
	
	iter_runer = SlistFind(iter_start, iter_end, IsInt, &num4);
	SlistRemove(iter_runer);
	iter_end = SlistEnd(list);
	printf("size is: %ld", SlistCount(list));
	(SlistCount(list) == 3) ? printf("		%s\n", CHECK_MARK) :
	 					 		printf("	 %s\n", FAIL_MARK);
	SlistForEach(iter_start, iter_end, print, &counter); 
	counter = 1;
	
	iter_runer = SlistFind(iter_start, iter_end, IsInt, &num3);
	SlistRemove(iter_runer);
	iter_end = SlistEnd(list);
	printf("size is: %ld", SlistCount(list));
	(SlistCount(list) == 2) ? printf("		%s\n", CHECK_MARK) :
	 					 		printf("	 %s\n", FAIL_MARK);
	SlistForEach(iter_start, iter_end, print, &counter);
	counter = 1;
	
	SlistRemove(iter_start);
	iter_end = SlistEnd(list);
	printf("size is: %ld", SlistCount(list));
	(SlistCount(list) == 1) ? printf("		%s\n", CHECK_MARK) :
	 					 		printf("	 %s\n", FAIL_MARK);
	SlistForEach(iter_start, iter_end, print, &counter); 

	SlistDestroy(list);
}

int PrintIntValues(void *data, void *param)
{
	printf("value at place %d is: %d\n", *(int *)param ,*(int *)data);
	++*(int *)param;
	
	return 0;
}

int IsInt(const void *data, void *param)
{
	return (*(int *)data == *(int *)param);
}


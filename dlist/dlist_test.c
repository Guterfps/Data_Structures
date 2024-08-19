/*-------------------------------------------*/
/* DEVELOPER: Itay Guter                    */
/* LAST MODIFIED: 18/12/2022               */
/* WORKSHEET NAME: Doubly linked list     */
/* REVIEWER: Or Abadi	                 */
/*--------------------------------------*/

#include <stdio.h>		/*printf()*/
#include <assert.h>		/*assert()*/

#include "dlist.h"		/*function declerations and typedefs*/

void Test1(void);
void Test2(void);
int IsMatch(const void *data, void *param);
int PrintList(void *data, void *param);

int main(void)
{
	Test1();
	Test2();
	
	return 0;
}

void Test1(void)
{
	int arr[] = {1,2,3,4,5,6,7,8,9,10};
	size_t len = sizeof(arr) / sizeof(*arr);
	dlist_t *list = DlistCreate();
	dlist_iter_t iter = NULL;
	size_t i = 0;
	int status = 1;
	int insert_test = -123;
	int set_val_test = 25;
	int push_back = 0;
	int push_front = 42;
	
	printf("is empty test:  ");
	DlistIsEmpty(list) ? printf("SUCCESS ✅️\n") : printf("FAIL ❌️\n");
	
	printf("count test:  ");
	(0 == DlistCount(list)) ? printf("SUCCESS ✅️\n") : printf("FAIL ❌️\n");
	
	for (; i < len; ++i)
	{
		DlistPushFront(list, arr + i);
	}
	
	iter = DlistEnd(list);
	printf("DlistEnd test:  ");
	(*arr == *(int *)DlistGetVal(DlistPrev(iter))) ? printf("SUCCESS ✅️\n") :
														printf("FAIL ❌️\n");
	iter = DlistBegin(list);
	printf("DlistBegin test:  ");
	(arr[9] == *(int *)DlistGetVal(iter)) ? printf("SUCCESS ✅️\n") :
										printf("FAIL ❌️\n");
	
	for (; i > 0; --i)
	{
		status *= (arr[i - 1] == *(int *)DlistGetVal(iter));
		iter = DlistNext(iter);
	}
	
	printf("pushFront + getval test:  ");
	status ? printf("SUCCESS ✅️\n") : printf("FAIL ❌️\n");
	printf("is empty test:  ");
	DlistIsEmpty(list) ? printf("FAIL ❌️\n") : printf("SUCCESS ✅️\n");
	printf("count test:  ");
	(len == DlistCount(list)) ? printf("SUCCESS ✅️\n") : printf("FAIL ❌️\n");
	
	printf("insert before test:  ");
	iter = DlistPrev(iter);
	iter = DlistPrev(iter);
	iter = DlistInsertBefore(iter, &insert_test);
	(insert_test == *(int *)DlistGetVal(iter)) ? printf("SUCCESS ✅️\n") :
													printf("FAIL ❌️\n");
	printf("iter prev/next test:  ");
	iter = DlistNext(iter);
	iter = DlistNext(iter);
	(*arr == *(int *)DlistGetVal(iter)) ? printf("SUCCESS ✅️\n") :
													printf("FAIL ❌️\n");
	printf("setval + find test:  ");
	iter = DlistPrev(iter);
	DlistSetVal(iter, &set_val_test);
	iter = DlistFind(DlistBegin(list), DlistEnd(list), &IsMatch, &set_val_test);
	(set_val_test == *(int *)DlistGetVal(iter)) ? printf("SUCCESS ✅️\n") :
													printf("FAIL ❌️\n");
	
	printf("remove + find test:  ");
	iter = DlistPrev(iter);
	iter = DlistPrev(iter);
	DlistRemove(iter);
	iter = DlistFind(DlistBegin(list), DlistEnd(list), &IsMatch, arr + 2);
	DlistIterIsEqual(iter, DlistEnd(list)) ? printf("SUCCESS ✅️\n") :
													printf("FAIL ❌️\n");
	printf("pushback test:  ");
	iter = DlistPushBack(list, &push_back);
	(push_back == *(int *)DlistGetVal(DlistPrev(DlistEnd(list)))) ? 
	printf("SUCCESS ✅️\n") : printf("FAIL ❌️\n");
	
	printf("test forEach:  ");
	DlistPushFront(list, &push_front);
	DlistForEach(DlistBegin(list), DlistEnd(list), &PrintList, 0) ? 
	printf("FAIL ❌️\n") : printf("SUCCESS ✅️\n");
	printf("\n");
	
	printf("popfront test:  ");
	(*(int *)DlistPopFront(list) == push_front) ? printf("SUCCESS ✅️\n") :
													printf("FAIL ❌️\n");
	printf("popback test:  ");
	(*(int *)DlistPopBack(list) == push_back) ? printf("SUCCESS ✅️\n") :
													printf("FAIL ❌️\n");
	
	
	
	DlistDestroy(list);
}

int IsMatch(const void *data, void *param)
{
	assert(NULL != data);
	assert(NULL != param);
	
	return (*(int *)data == *(int *)param);
}

int PrintList(void *data, void *param)
{
	printf(" %d ,", *(int *)data);
	(void)param;
	
	return 0;
}

void Test2(void)
{
	int arr1[] = {0,1,2,3,4,5,6,7,8,9,10};
	int arr2[] = {-1,-2,-3,-4,-5};
	size_t len1 = sizeof(arr1) / sizeof(*arr1);
	size_t len2 = sizeof(arr2) / sizeof(*arr2);
	dlist_t *list1 = DlistCreate();
	dlist_t *list2 = DlistCreate();
	dlist_iter_t iter_test = NULL;
	dlist_iter_t iter_to = NULL;
	dlist_iter_t iter_from = NULL;
	int find_test = 5;
	int find_test2 = 25;
	size_t i = 0;
	
	for (; i < len1; ++i)
	{
		DlistPushBack(list1, arr1 + i);
	}
	
	for (i = 0; i < len2; ++i)
	{
		DlistPushFront(list2, arr2 + i);
	}
	
	printf("splice one list: \n");
	iter_to = DlistFind(DlistBegin(list1), DlistEnd(list1), &IsMatch, arr1 + 4);
	iter_from = DlistBegin(list1);
	iter_test = DlistSplice(iter_from, iter_to, DlistEnd(list1));
	printf("new begin test:  ");
	(*(arr1 + 4) == *(int *)DlistGetVal(DlistBegin(list1))) ?
	printf("SUCCESS ✅️\n") : printf("FAIL ❌️\n");
	printf("new end test:  ");
	(*(arr1 + 3) == *(int *)DlistGetVal(DlistPrev(DlistEnd(list1)))) ?
	printf("SUCCESS ✅️\n") : printf("FAIL ❌️\n");
	printf("size test:  ");
	(len1 == DlistCount(list1)) ? printf("SUCCESS ✅️\n") : printf("FAIL ❌️\n");
	printf("iter return after splice test :  ");
	(*(arr1 + 3) == *(int *)DlistGetVal(iter_test)) ?
	printf("SUCCESS ✅️\n") : printf("FAIL ❌️\n");
	
	printf("splice two list test:  \n");
	iter_test = DlistSplice(DlistNext(DlistBegin(list2)), 
							DlistPrev(DlistEnd(list2)),	
							DlistNext(DlistNext(DlistBegin(list1))));
	printf("iter return after splice test :  ");
	(*(arr2 + 1) == *(int *)DlistGetVal(iter_test)) ?
	printf("SUCCESS ✅️\n") : printf("FAIL ❌️\n");
	printf("size after splice(2 lists):  ");
	printf("list1: ");
	((len1 + len2 - 2) == DlistCount(list1)) ? 
	printf("SUCCESS ✅️") : printf("FAIL ❌️");
	printf(",list2: ");
	(2 == DlistCount(list2)) ? printf("SUCCESS ✅️\n") : printf("FAIL ❌️\n");
	
	iter_test = DlistSplice(DlistBegin(list2), DlistEnd(list2), 
												DlistBegin(list1));
	printf("iter return after splice test :  ");
	(*arr2 == *(int *)DlistGetVal(iter_test)) ?
	printf("SUCCESS ✅️\n") : printf("FAIL ❌️\n");
	
	printf("size after splice(2 lists):  ");
	printf("list1: ");
	((len1 + len2) == DlistCount(list1)) ? 
	printf("SUCCESS ✅️") : printf("FAIL ❌️");
	printf(",list2: ");
	(0 == DlistCount(list2)) ? printf("SUCCESS ✅️\n") : printf("FAIL ❌️\n");
	printf("new begin test:  ");
	(*(arr2 + len2 - 1) == *(int *)DlistGetVal(DlistBegin(list1))) ?
	printf("SUCCESS ✅️\n") : printf("FAIL ❌️\n");
	printf("is list1 empty test:  ");
	DlistIsEmpty(list1) ? printf("FAIL ❌️\n") : printf("SUCCESS ✅️\n");
	printf("is list2 empty test:  ");
	DlistIsEmpty(list2) ? printf("SUCCESS ✅️\n") : printf("FAIL ❌️\n");

	printf("multifind test:  ");
	DlistPushFront(list1, &find_test);
	DlistInsertBefore(iter_test, &find_test);
	DlistPushBack(list1, &find_test);
	DlistMultiFind(list2, DlistBegin(list1), DlistEnd(list1), 
											&IsMatch, &find_test2);
	(0 == DlistCount(list2)) ? printf("SUCCESS ✅️ , ") : printf("FAIL ❌️ , ");
	DlistMultiFind(list2, DlistBegin(list1), DlistEnd(list1), 
											&IsMatch, &find_test);
	(4 == DlistCount(list2)) ? printf("SUCCESS ✅️ , ") : printf("FAIL ❌️ , ");
	
	(find_test == *(int *)DlistGetVal(DlistPrev(DlistEnd(list2)))) ?
	printf("SUCCESS ✅️\n") : printf("FAIL ❌️\n");
	
	DlistForEach(DlistBegin(list1), DlistEnd(list1), &PrintList, 0);
	printf("\n");
	DlistForEach(DlistBegin(list2), DlistEnd(list2), &PrintList, 0);
	printf("\n");
	
	DlistDestroy(list1);
	DlistDestroy(list2);
}



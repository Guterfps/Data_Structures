/*-------------------------------------------*/
/* DEVELOPER: Itay Guter                    */
/* LAST MODIFIED: 19/1/2023	               */
/* WORKSHEET NAME: Binary Tree Iterative  */
/* REVIEWER: Matan				         */
/*--------------------------------------*/

#include <stdio.h>	/* printf() */
#include <stdlib.h>	/*srand(), rand()*/
#include <time.h>	/*time(), clock()*/

#include "ilrd_bst.h"	/* function declerations and typedefs */

#define ARR_LEN 5000

void InitArr(int *arr, size_t len);

void Test1(void);

int CmpFunc(const void *data1, const void *data2);
int CallBack(void *data, void *param);

int main(void)
{
	Test1();
	
	return 0;
}

void Test1(void)
{
	bst_t *bst = BSTCreate(&CmpFunc);
	int data[ARR_LEN] = {0};
	size_t len = sizeof(data) / sizeof(*data);
	size_t i = 0;
	int test1 = 25;
	bst_iter_t iter1 = NULL;
	bst_iter_t iter2 = NULL;
	bst_iter_t iter_smallest = NULL;
	bst_iter_t runner = NULL;
	int status = 1;
	clock_t start_time = 0; 
	clock_t end_time = 0;
	
	srand(time(NULL));
	
	InitArr(data, ARR_LEN);
	printf("is empty test:	");
	BSTIsEmpty(bst) ? printf("SUCCESS ✅️\n") : printf("FAIL ❌️\n");
	printf("count test:	");
	(0 == BSTCount(bst)) ?
	printf("SUCCESS ✅️\n") : printf("FAIL ❌️\n");
	
	
	for (i = 0; i < len; ++i)
	{
		BSTInsert(bst, data + i);
	}
	
	for (i = 0; (i < len) && status; ++i)
	{
		status = (data[i] == *(int *)BSTGetVal(BSTFind(bst, data + i)));
	}
	
	printf("insert test:	");
	status ? printf("SUCCESS ✅️\n") : printf("FAIL ❌️\n");
	
	printf("is empty test:	");
	!BSTIsEmpty(bst) ? printf("SUCCESS ✅️\n") : printf("FAIL ❌️\n");
	
	iter_smallest = BSTBegin(bst);
	
	for (i = 0; (i < len) && status; ++i)
	{
		status = (*(int *)BSTGetVal(iter_smallest) <= 
				 *(int *)BSTGetVal(BSTFind(bst, data + i)));
	}
	
	printf("begin test:	");
	printf("%d ", *(int *)BSTGetVal(iter_smallest));
	status ? printf("SUCCESS ✅️\n") : printf("FAIL ❌️\n");
	
	runner = iter_smallest;
	for (i = 0; (i < len - 1) && status; ++i)
	{
		status = (*(int *)BSTGetVal(runner) < 
				*(int *)BSTGetVal(BSTNext(runner)));
		runner = BSTNext(runner);
	}
	
	printf("next test:	");
	!BSTIsEqual(runner, iter_smallest) ?
	printf("SUCCESS ✅️,") : printf("FAIL ❌️,");
	status ? printf("SUCCESS ✅️\n") : printf("FAIL ❌️\n");
	
	for (i = 0; (i < len - 1) && status; ++i)
	{
		status = (*(int *)BSTGetVal(runner) >
				*(int *)BSTGetVal(BSTPrev(runner)));
		runner = BSTPrev(runner);
	}

	printf("prev test:	");
	BSTIsEqual(runner, iter_smallest) ?
	printf("SUCCESS ✅️,") : printf("FAIL ❌️,");
	status ? printf("SUCCESS ✅️\n") : printf("FAIL ❌️\n");
	
	iter2 = BSTInsert(bst, &test1);
	
	iter1 = BSTFind(bst, &test1);
	
	printf("find + getval test:	");
	(test1 == *(int *)BSTGetVal(iter1)) ?
	printf("SUCCESS ✅️\n") : printf("FAIL ❌️\n");
	
	printf("is equal test:	");
	BSTIsEqual(iter1 ,iter2) ? printf("SUCCESS ✅️\n") : printf("FAIL ❌️\n");
	
	printf("bst end test:	");
	!BSTIsEqual(BSTEnd(bst), iter1) ?
	printf("SUCCESS ✅️\n") : printf("FAIL ❌️\n");
	
	i = 0;
	iter2 = BSTFind(bst, &i);
	
	printf("bst end test:	");
	BSTIsEqual(BSTEnd(bst), iter2) ?
	printf("SUCCESS ✅️\n") : printf("FAIL ❌️\n");
	
	printf("count test:	");
	((ARR_LEN + 1) == BSTCount(bst)) ?
	printf("SUCCESS ✅️\n") : printf("FAIL ❌️\n");
	
	iter2 = BSTFind(bst, data);
	
	printf("simple remove test:	");
	BSTRemove(iter2);
	BSTIsEqual(BSTFind(bst, data), BSTEnd(bst)) ?
	printf("SUCCESS ✅️\n") : printf("FAIL ❌️\n");
	
	for (i = 3; (i < len - 2) && status; ++i)
	{
		iter2 = BSTFind(bst, data + i);
		status = !BSTIsEqual(iter2, BSTEnd(bst));
		BSTRemove(iter2);
		status = BSTIsEqual(BSTFind(bst, data + i), BSTEnd(bst));
	}
	
	printf("remove test:	");
	(5 == BSTCount(bst)) ? printf("SUCCESS ✅️, ") : printf("FAIL ❌️, ");
	status ? printf("SUCCESS ✅️\n") : printf("FAIL ❌️\n");
	
	printf("begin test:	");
	printf("%d ", *(int *)BSTGetVal(BSTBegin(bst)));
	status ? printf("SUCCESS ✅️\n") : printf("FAIL ❌️\n");
	
	printf("is empty test:	");
	!BSTIsEmpty(bst) ? printf("SUCCESS ✅️\n") : printf("FAIL ❌️\n");
	
	printf("for each test:	");
	(0 == BSTForEach(BSTBegin(bst), BSTEnd(bst), &CallBack, NULL)) ?
	printf("SUCCESS ✅️\n") : printf("FAIL ❌️\n");
	
	start_time = clock();
	BSTDestroy(bst);
	end_time = clock();
	
	printf("destroy time: \n");
	printf("start time: %ld, end time: %ld, execution time: %fs\n", 
			start_time, end_time, 
			((double)(end_time - start_time) / CLOCKS_PER_SEC));
	printf("\n");
}

int CmpFunc(const void *data1, const void *data2)
{
	return (*(int *)data1 - *(int *)data2);
}

int CallBack(void *data, void *param)
{
	printf("%d, ", *(int *)data);
	(void)param;
	
	return 0;
}

void InitArr(int *arr, size_t len)
{
	size_t i = 0;
	
	for (i = 0; i < len; ++i)
	{
		arr[i] = rand();
	}
}

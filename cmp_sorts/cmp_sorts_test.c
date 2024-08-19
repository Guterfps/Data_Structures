/*-------------------------------------------*/
/* DEVELOPER: Itay Guter                    */
/* LAST MODIFIED: 1/2/2023	               */
/* WORKSHEET NAME: Comparison Sorts	      */
/* REVIEWER: Dotan + Gal		         */
/*--------------------------------------*/

#include <stdio.h>	/*printf()*/
#include <stdlib.h>	/*srand(), rand(), qsort()*/
#include <time.h>	/*time(), clock()*/
#include <assert.h>	/*assert()*/

#include "cmp_sorts.h"	/* header file */

#define ARR_LEN 5000

void InitArr(int *arr, size_t len);
void InitArr2(int *arr, size_t len);
int CmpFunc (const void *a, const void *b);
void BinarySearchTest(void);
void MergeSortTest(void);
void QSortTest(void);

int main(void)
{
	int arr1[ARR_LEN] = {0};
	size_t len1 = sizeof(arr1) / sizeof(*arr1);
	int arr2[ARR_LEN] = {0};
	size_t len2 = sizeof(arr2) / sizeof(*arr2);
	int arr3[ARR_LEN] = {0};
	size_t len3 = sizeof(arr3) / sizeof(*arr3);
	int arr4[ARR_LEN] = {0};
	size_t len4 = sizeof(arr4) / sizeof(*arr4);
	int status = 1;
	size_t i = 0;
	clock_t start_time = 0; 
	clock_t end_time = 0;
	
	srand(time(NULL));
	
	InitArr(arr1, len1);
	InitArr(arr2, len2);
	InitArr(arr3, len3);
	InitArr(arr4, len4);
	
	start_time = clock();
	BubbleSort(arr1, len1);
	end_time = clock();

	for (i = 0; (i < len1 - 1) && status; ++i)
	{
		status = (arr1[i] <= arr1[i + 1]);
	}
	printf("bubble sort test:	");
	status ? printf("SUCCESS ✅️\n") : printf("FAIL ❌️\n");
	printf("start time: %ld, end time: %ld, execution time: %fs\n", 
			start_time, end_time, 
			((double)(end_time - start_time) / CLOCKS_PER_SEC));
	printf("\n");
		
	start_time = clock();
	SelectionSort(arr2, len2);
	end_time = clock();
	
	for (i = 0; (i < len2 - 1) && status; ++i)
	{
		status = (arr2[i] <= arr2[i + 1]);
	}
	printf("Selection Sort test:	");
	status ? printf("SUCCESS ✅️\n") : printf("FAIL ❌️\n");
	printf("start time: %ld, end time: %ld, execution time: %fs\n", 
			start_time, end_time, 
			((double)(end_time - start_time) / CLOCKS_PER_SEC));
	printf("\n");
	
	start_time = clock();
	InsertionSort(arr3, len3);
	end_time = clock();
	
	for (i = 0; (i < len3 - 1) && status; ++i)
	{
		status = (arr3[i] <= arr3[i + 1]);
	}
	printf("Insertion Sort test:	");
	status ? printf("SUCCESS ✅️\n") : printf("FAIL ❌️\n");
	printf("start time: %ld, end time: %ld, execution time: %fs\n", 
			start_time, end_time, 
			((double)(end_time - start_time) / CLOCKS_PER_SEC));
	printf("\n");
	
	start_time = clock();
	qsort(arr4, len4, sizeof(int), &CmpFunc);
	end_time = clock();
	
	printf("qsort time:	\n");
	printf("start time: %ld, end time: %ld, execution time: %fs\n", 
			start_time, end_time, 
			((double)(end_time - start_time) / CLOCKS_PER_SEC));
	
	printf("\n");
	BinarySearchTest();
	
	printf("\n");
	MergeSortTest();
	
	printf("\n");
	QSortTest();
	
	return 0;
}

void BinarySearchTest(void)
{
	int arr[] = {-1,0,2,5,25,42,69,123,420};
	int len = sizeof(arr) / sizeof(*arr);
	int status = 1;
	int i = 0;
	
	for (i = 0; (i < len) && status; ++i)
	{
		status = ((arr + i) == IterBinarySearch(arr, len, arr[i]));
	}
	
	printf("iterative binary search test:	");
	(NULL == IterBinarySearch(arr, len, 7)) ? 
	printf("SUCCESS ✅️, ") : printf("FAIL ❌️, ");
	status ? printf("SUCCESS ✅️\n") : printf("FAIL ❌️\n");
	
	for (i = 0; (i < len) && status; ++i)
	{
		status = ((arr + i) == RecBinarySearch(arr, len, arr[i]));
	}
	
	printf("recursive binary search test:	");
	(NULL == RecBinarySearch(arr, len, 7)) ? 
	printf("SUCCESS ✅️, ") : printf("FAIL ❌️, ");
	status ? printf("SUCCESS ✅️\n") : printf("FAIL ❌️\n");
}

void MergeSortTest(void)
{
	int arr1[ARR_LEN] = {0};
	size_t len1 = sizeof(arr1) / sizeof(*arr1);
	int status = 1;
	size_t i = 0;
	clock_t start_time = 0; 
	clock_t end_time = 0;
	
	srand(time(NULL));
	
	InitArr2(arr1, len1);
	
	start_time = clock();
	status = (0 == MergeSort(arr1, len1));
	end_time = clock();
	
	for (i = 0; (i < len1 - 1) && status; ++i)
	{
		status = (arr1[i] <= arr1[i + 1]);
	}
	printf("merge sort test:	");
	status ? printf("SUCCESS ✅️\n") : printf("FAIL ❌️\n");
	printf("start time: %ld, end time: %ld, execution time: %fs\n", 
			start_time, end_time, 
			((double)(end_time - start_time) / CLOCKS_PER_SEC));
	printf("\n");
	
}

void QSortTest(void)
{
	int arr1[ARR_LEN] = {0};
	size_t len1 = sizeof(arr1) / sizeof(*arr1);
	int arr2[ARR_LEN] = {0};
	size_t len2 = sizeof(arr2) / sizeof(*arr2);
	int status = 1;
	size_t i = 0;
	clock_t start_time = 0; 
	clock_t end_time = 0;
	
	srand(time(NULL));
	
	InitArr2(arr1, len1);
	InitArr2(arr2, len2);
	
	start_time = clock();
	Qsort(arr1, len1, sizeof(int), &CmpFunc);
	end_time = clock();

	for (i = 0; (i < len1 - 1) && status; ++i)
	{
		status = (arr1[i] <= arr1[i + 1]);
	}
	printf("Qsort sort test:	");
	status ? printf("SUCCESS ✅️\n") : printf("FAIL ❌️\n");
	printf("start time: %ld, end time: %ld, execution time: %fs\n", 
			start_time, end_time, 
			((double)(end_time - start_time) / CLOCKS_PER_SEC));
	printf("\n");
	
	start_time = clock();
	qsort(arr2, len2, sizeof(int), &CmpFunc);
	end_time = clock();
	
	printf("qsort time:	\n");
	printf("start time: %ld, end time: %ld, execution time: %fs\n", 
			start_time, end_time, 
			((double)(end_time - start_time) / CLOCKS_PER_SEC));
}

void InitArr(int *arr, size_t len)
{
	size_t i = 0;
	
	assert(NULL != arr);
	
	for (i = 0; i < len; ++i)
	{
		arr[i] = rand();
	}
}

void InitArr2(int *arr, size_t len)
{
	size_t i = 0;
	
	assert(NULL != arr);
	
	for (i = 0; i < len; ++i)
	{
		arr[i] = rand() % 1000000;
	}
}

int CmpFunc (const void *a, const void *b)
{
   return (*(int *)a - *(int *)b);
}


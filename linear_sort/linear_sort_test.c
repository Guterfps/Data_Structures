/*-------------------------------------------*/
/* DEVELOPER: Itay Guter                    */
/* LAST MODIFIED: 17/1/2023	               */
/* WORKSHEET NAME: Linear Sort		      */
/* REVIEWER: Matan Isak			         */
/*--------------------------------------*/

#include <stdio.h>	/*printf()*/
#include <stdlib.h>	/*srand(), rand()*/
#include <time.h>	/*time(), clock()*/
#include <assert.h>	/*assert()*/

#include "linear_sort.h"	/* function declerations */

#define ARR_LEN 5000
#define SEVEN_DIGITS 10000000

void InitArr(int *arr, size_t len);
void InitArr2(int *arr, size_t len);

int main(void)
{
	int arr[ARR_LEN] = {0};
	size_t size = sizeof(arr) / sizeof(*arr);
	int arr2[ARR_LEN] = {0};
	size_t size2 = sizeof(arr2) / sizeof(*arr2);
	int status = 1;
	size_t i = 0;
	clock_t start_time = 0; 
	clock_t end_time = 0;
	
	srand(time(NULL));
	
	InitArr(arr, size);
	InitArr2(arr2, size2);
	
	start_time = clock();
	CountingSort(arr, size);
	end_time = clock();
	
	for (i = 0; (i < size - 1) && status; ++i)
	{
		status = (arr[i] <= arr[i + 1]);
	}
	
	printf("Counting sort test:	");
	status ? printf("SUCCESS ✅️\n") : printf("FAIL ❌️\n");
	printf("start time: %ld, end time: %ld, execution time: %fs\n", 
			start_time, end_time, 
			((double)(end_time - start_time) / CLOCKS_PER_SEC));
	printf("\n");
	
	start_time = clock();
	RadixSort(arr2, size2, 4);
	end_time = clock();
	
	for (i = 0; (i < size2 - 1) && status; ++i)
	{
		status = (arr2[i] <= arr2[i + 1]);
	}
	
	printf("Counting sort test:	");
	status ? printf("SUCCESS ✅️\n") : printf("FAIL ❌️\n");
	printf("start time: %ld, end time: %ld, execution time: %fs\n", 
			start_time, end_time, 
			((double)(end_time - start_time) / CLOCKS_PER_SEC));
	printf("\n");
	
	return 0;
}

void InitArr(int *arr, size_t len)
{
	size_t i = 0;
	
	assert(NULL != arr);
	
	for (i = 0; i < len; ++i)
	{
		arr[i] = rand() % 100;
	}
}

void InitArr2(int *arr, size_t len)
{
	size_t i = 0;
	
	assert(NULL != arr);
	
	for (i = 0; i < len; ++i)
	{
		arr[i] = rand() % SEVEN_DIGITS;
	}
}


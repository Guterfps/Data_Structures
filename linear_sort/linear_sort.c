/*-------------------------------------------*/
/* DEVELOPER: Itay Guter                    */
/* LAST MODIFIED: 17/1/2023	               */
/* WORKSHEET NAME: Linear Sort		      */
/* REVIEWER: Matan Isak			         */
/*--------------------------------------*/

#include <assert.h>	/* assert() */
#include <stdlib.h>	/* calloc() free() */

#include "linear_sort.h"	/* function declerations */

enum status
{
	SUCCESS,
	FAIL = -1
};

static int FindMaxValue(int *arr, size_t size);
static void FillHistogram(int *histogram, int *arr, size_t size);
static void FillSortedValues(int *histogram, int *arr, size_t size);
static int CountingSortForRadix(int *arr, size_t size, 
								size_t hist_size, size_t mask);
static void RadixFillHistogram(int *histogram, int *arr, size_t size, 
								size_t hist_size, size_t mask);								
static void BuildSorted(int *arr, int *histogram, int *sorted, size_t size, 
						size_t hist_size, size_t mask);
static size_t HistogramIndex(int element, size_t hist_size, size_t mask);
static void CopyArray(int *arr, int *sorted, size_t size);
static size_t Pow10(size_t exp_of_ten);

 												
int CountingSort(int *arr, size_t size)
{
	int *histogram = NULL;
	int max_val = 0;
	
	assert(NULL != arr);
	
	max_val = FindMaxValue(arr, size);
	
	histogram = (int *)calloc(max_val + 1, sizeof(int));
	if (NULL == histogram)
	{
		return FAIL;
	}
	
	FillHistogram(histogram, arr, size);
	
	FillSortedValues(histogram, arr, size);
	
	free(histogram);
	histogram = NULL;
	
	return SUCCESS;
}

int RadixSort(int *arr, size_t size, size_t exp_of_ten)
{
	int max_value = 0;
	size_t mask = 0;
	size_t ten_exp = 0;
	int status = SUCCESS;
	
	assert(NULL != arr);
	assert(0 != exp_of_ten);
	
	max_value = FindMaxValue(arr , size);
	ten_exp = Pow10(exp_of_ten);
	
	for (mask = 1; (FAIL != status) && 
		((max_value / mask) > 0); mask *= ten_exp)
	{
		status = CountingSortForRadix(arr, size, ten_exp, mask);
	}
	
	return status;
}

static int CountingSortForRadix(int *arr, size_t size, 
								size_t hist_size, size_t mask)
{
	int *histogram = NULL;
	int *sorted = NULL;
	
	assert(NULL != arr);
	
	histogram = (int *)calloc(hist_size, sizeof(int));
	if (NULL == histogram)
	{
		return FAIL;
	}
	
	sorted = (int *)calloc(size, sizeof(int));
	if (NULL == histogram)
	{
		free(histogram);
		histogram = NULL;
		return FAIL;
	}
	
	RadixFillHistogram(histogram, arr, size, hist_size, mask);
	
	BuildSorted(arr, histogram, sorted, size, hist_size, mask);
	
	CopyArray(arr, sorted, size);
	
	free(histogram);
	histogram = NULL;
	free(sorted);
	sorted = NULL;
	
	return SUCCESS;
}

static int FindMaxValue(int *arr, size_t size)
{
	size_t i = 0;
	int max_val = 0;
	
	assert(NULL != arr);
	
	for (i = 0; i < size; ++i)
	{
		max_val = (arr[i] > max_val) ? arr[i] : max_val;
	}
	
	return max_val;
}

static void FillHistogram(int *histogram, int *arr, size_t size)
{
	size_t i = 0;
	
	assert(NULL != arr);
	
	for (i = 0; i < size; ++i)
	{
		histogram[arr[i]] += 1;
	}
}

static void FillSortedValues(int *histogram, int *arr, size_t size)
{
	int i = 0;
	size_t j = 0;
	
	assert(NULL != arr);
	
	for (i = 0; i < (int)size; ++i)
	{
		if (histogram[j] > 0)
		{
			arr[i] = j;
			histogram[j] -= 1;
		}
		else
		{
			++j;
			--i;
		}
	}
}

static void RadixFillHistogram(int *histogram, int *arr, size_t size, 
								size_t hist_size, size_t mask)
{
	size_t i = 0;
	
	assert(NULL != arr);
	assert(NULL != histogram);
	
	for (i = 0; i < size; ++i)
	{
		histogram[HistogramIndex(arr[i], hist_size, mask)] += 1;
	}
	
	for (i = 1;i < hist_size; ++i)
	{
		histogram[i] += histogram[i - 1];
	}
}

static void BuildSorted(int *arr, int *histogram, int *sorted, size_t size, 
						size_t hist_size, size_t mask)
{
	int i = 0;
	
	assert(NULL != arr);
	assert(NULL != histogram);
	
	for (i = (size - 1); i >= 0; --i)
	{
		size_t hist_i = HistogramIndex(arr[i], hist_size, mask);
		sorted[histogram[hist_i] - 1] = arr[i];
		histogram[hist_i] -= 1;
	}
}

static size_t HistogramIndex(int element, size_t hist_size, size_t mask)
{	
	return ((element / mask) % hist_size);
}

static void CopyArray(int *arr, int *sorted, size_t size)
{
	size_t i = 0;
	
	assert(NULL != arr);
	assert(NULL != sorted);
	
	for (; i < size; ++i)
	{
		arr[i] = sorted[i];
	}
}

static size_t Pow10(size_t exp_of_ten)
{
	size_t result = 1;
	size_t ten = 10;
	
	while (exp_of_ten--)
	{
		result *= ten;
	}
	
	return result;
}






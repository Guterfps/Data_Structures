/*-------------------------------------------*/
/* DEVELOPER: Itay Guter                    */
/* LAST MODIFIED: 1/2/2023	               */
/* WORKSHEET NAME: Comparison Sorts	      */
/* REVIEWER: Dotan + Gal		         */
/*--------------------------------------*/

#include <assert.h>	/*assert()*/
#include <stdlib.h>	/* malloc() */

#include "cmp_sorts.h"	/* header file */

enum status
{
	SUCCESS = 0,
	FAIL = -1
};

static void Swap(int *a, int *b);
static int *RecursiveBS(int *arr, int low, int high, int find);
static int SplitMerge(int *arr, size_t start, size_t end);
static int Merge(int *arr, size_t start,  size_t mid, size_t end);
static void CopyArr(int *arr1, size_t start, size_t end, int *arr2);
static int AllocateTwoSubArrays(int **left_sub_arr, int **right_sub_arr, 
								size_t len1, size_t len2);
static void CopyRemainingElements(int *arr1, size_t idx1, int *arr2, 
												size_t idx2, size_t len);
static size_t Partition(void *arr, size_t low, size_t high, 
						size_t elem_size, compar_func_t cmp);
static void RecQsort(void *arr, size_t low, size_t high, 
					size_t elem_size, compar_func_t cmp);
static void ByteSwap(void *data1, void *data2, size_t size);
static void MergeSubArrays(int *arr, int *left, int *right, 
							size_t *k, size_t *i, size_t *j, 
							size_t len1, size_t len2);

void BubbleSort(int *arr, size_t len)
{
	size_t i = 0;
	size_t j = 0;
	
	assert(NULL != arr);
	
	for (; i < len; ++i)
	{
		for (j = 0; j < (len - 1 - i); ++j)
		{
			if (arr[j] > arr[j + 1])
			{
				Swap((arr + j), (arr + j + 1));
			}
		}
	}
}

void SelectionSort(int *arr, size_t len)
{
	size_t i = 0;
	size_t j = 0;
	size_t min_index = 0;
		
	assert(NULL != arr);

	for (; i < (len - 1); ++i)
	{
		min_index = i;
		
		for (j = (i + 1); j < len; ++j)
		{
			if (arr[min_index] > arr[j])
			{
				min_index = j;
			}
		}
		if (min_index != i)
		{
			Swap((arr + min_index), (arr + i));
		}
	}
}

void InsertionSort(int *arr, size_t len)
{
	size_t i = 0;
	int j = 0;
		
	assert(NULL != arr);
	
	for (i = 1; i < len; ++i)
	{
		int cur_elem = arr[i];
		
		for (j = (i - 1); (j >= 0) && (arr[j] > cur_elem); --j)
		{
			arr[j + 1] = arr[j];
		}
		arr[j + 1] = cur_elem;
	}
}

static void Swap(int *a, int *b)
{
	assert(NULL != a);
	assert(NULL != a);
	
	*a = *a ^ *b;
	*b = *a ^ *b;
	*a = *a ^ *b;
}

int *IterBinarySearch(int *arr, int arr_size, int element_to_find)
{
	int mid_idx = 0;
	int low = 0;
	int high = arr_size - 1;
	int *found_indx = NULL;
	
	assert(NULL != arr);
	
	while ((low <= high) && (NULL == found_indx))
	{
		mid_idx = (low + high) / 2;
		
		if (element_to_find == arr[mid_idx])
		{
			found_indx = arr + mid_idx;
		}
		else if (element_to_find > arr[mid_idx])
		{
			low = mid_idx + 1;
		}
		else
		{
			high = mid_idx - 1;
		}
	}
	
	return found_indx;
}

int *RecBinarySearch(int *arr, int arr_size, int element_to_find)
{
	int low = 0;
	int high = arr_size - 1;
	
	assert(NULL != arr);
	
	
	return (RecursiveBS(arr, low, high, element_to_find));
}

int MergeSort(int *arr_to_sort, size_t num_elements)
{	
	assert(NULL != arr_to_sort);
	
	return SplitMerge(arr_to_sort, 0, num_elements - 1);
}

void Qsort(void *base, size_t nmemb, size_t size, compar_func_t cmp)
{
	size_t low = 0;
	size_t high = nmemb * size;
	
	assert(NULL != base);
	assert(NULL != cmp);
	
	 RecQsort(base, low, high, size, cmp);
}

static void RecQsort(void *arr, size_t low, size_t high, 
					size_t elem_size, compar_func_t cmp)
{
	int part_indx = 0;
	
	assert(NULL != arr);
	assert(NULL != cmp);
	
	if ((low + elem_size) >= high)
	{
		return;
	}
	
	part_indx = Partition(arr, low, high, elem_size, cmp);
	RecQsort(arr, low, part_indx, elem_size, cmp);
	RecQsort(arr, part_indx + elem_size, high, elem_size, cmp);
}
static size_t Partition(void *arr, size_t low, size_t high, 
						size_t elem_size, compar_func_t cmp)
{
	unsigned char *pivot = (unsigned char *)arr;
	size_t j = low + elem_size;
	size_t i = low;
	
	assert(NULL != arr);
	assert(NULL != cmp);
	
	for (; j < high; j += elem_size)
	{
		if (0 >= cmp(pivot + j, pivot + low))
		{
			i += elem_size;
			ByteSwap((pivot + i), (pivot + j), elem_size);
		}
	}
	ByteSwap((pivot + low), (pivot + i), elem_size);
	
	return i;
}

static void ByteSwap(void *data1, void *data2, size_t size)
{
	unsigned char *p1 = (unsigned char *)data1;
	unsigned char *p2 = (unsigned char *)data2;
	
	assert(NULL != data1);
	assert(NULL != data2);
	
	while (0 < size--)
	{
		unsigned char c = *p1;
		*p1++ = *p2;
		*p2++ = c;
	}
}

static int *RecursiveBS(int *arr, int low, int high, int find)
{
	int mid = (low + high) / 2;
	
	assert(NULL != arr);
	
	if (low > high)
	{
		return NULL;
	}
	
	if (find == arr[mid])
	{
		return (arr + mid);
	}
	
	if(find > arr[mid])
	{
		return (RecursiveBS(arr, mid + 1, high, find));
	}
	
	return (RecursiveBS(arr, low , mid - 1, find));
}

static int SplitMerge(int *arr, size_t start, size_t end)
{
	size_t mid = (start + end) / 2;
	int status = SUCCESS;
	
	assert(NULL != arr);
	
	if (end <= start)
	{
		return status;
	}
	
	if ((FAIL == SplitMerge(arr, start, mid)) || 
		(FAIL == SplitMerge(arr, mid + 1, end)))
	{
		return FAIL;
	}
	
	status = Merge(arr, start, mid, end);
	
	return status;
}

static int Merge(int *arr, size_t start,  size_t mid, size_t end)
{
	size_t i = 0;
	size_t j = 0;
	size_t k = start;
	size_t len1 = mid - start + 1;
	size_t len2 = end - mid;
	int *left_sub_arr = NULL;
	int *right_sub_arr = NULL;
	
	assert(NULL != arr);
	
	if (FAIL == AllocateTwoSubArrays(&left_sub_arr, &right_sub_arr, 
														len1, len2))
	{
		return FAIL;
	}

	CopyArr(left_sub_arr, start, len1, arr);
	CopyArr(right_sub_arr, mid + 1, len2, arr);

	MergeSubArrays(arr, left_sub_arr, right_sub_arr, &k, &i, &j, len1, len2);
	
	CopyRemainingElements(arr, k, left_sub_arr, i, len1);
	CopyRemainingElements(arr, k, right_sub_arr, j, len2);

	free(left_sub_arr);
	left_sub_arr = NULL;
	free(right_sub_arr);
	right_sub_arr = NULL;
	
	return SUCCESS;
}

static void MergeSubArrays(int *arr, int *left, int *right, 
							size_t *k, size_t *i, size_t *j, 
							size_t len1, size_t len2)
{
	assert(NULL != arr);
	assert(NULL != left);
	assert(NULL != right);
	assert(NULL != k);
	assert(NULL != i);
	assert(NULL != j);
	
	for (; (*i < len1) && (*j < len2); ++*k) 
	{
		if (left[*i] <= right[*j])
		{
			arr[*k] = left[*i];
			++*i;
		}
		else 
		{
			arr[*k] = right[*j];
			++*j;
		}
	}
}

static void CopyArr(int *arr1, size_t start, size_t end, int *arr2)
{
	size_t i = 0;
	
	assert(NULL != arr1);
	assert(NULL != arr2);
	
	for (; i < end; ++start, ++i)
	{
		arr1[i] = arr2[start];
	}
}

static void CopyRemainingElements(int *arr1, size_t idx1, int *arr2, 
													size_t idx2, size_t len)
{
	assert(NULL != arr1);
	assert(NULL != arr2);
	
	while (idx2 < len) 
    {
        arr1[idx1] = arr2[idx2];
        ++idx2;
        ++idx1;
    }
}

static int AllocateTwoSubArrays(int **left_sub_arr, int **right_sub_arr, 
								size_t len1, size_t len2)
{
	assert(NULL != left_sub_arr);
	assert(NULL != right_sub_arr);
	
	*left_sub_arr = (int *)calloc(len1, sizeof(int));
	if (NULL == *left_sub_arr)
	{
		return FAIL;
	}
	
	*right_sub_arr = (int *)calloc(len2, sizeof(int));
	if (NULL == *right_sub_arr)
	{
		free(*left_sub_arr);
		*left_sub_arr = NULL;
		return FAIL;
	}
	
	return SUCCESS;
}


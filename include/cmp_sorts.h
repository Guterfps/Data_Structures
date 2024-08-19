/*-------------------------------------------*/
/* DEVELOPER: Itay Guter                    */
/* LAST MODIFIED: 1/2/2023	               */
/* WORKSHEET NAME: Comparison Sorts	      */
/* REVIEWER: Dotan + Gal		         */
/*--------------------------------------*/

#ifndef __CMP_SORTS__
#define __CMP_SORTS__

#include <stddef.h> /* size_t */

typedef int (*compar_func_t)(const void *, const void *);

/*----------------------------------------------------------------------------
Bubble Sort is the simplest sorting algorithm that works by repeatedly swapping 
the adjacent elements if they are in the wrong order. This algorithm is not 
suitable for large data sets as its average and worst-case time complexity is 
quite high.
Complexity: O(n^2).
----------------------------------------------------------------------------*/
void BubbleSort(int *arr, size_t len);
/*----------------------------------------------------------------------------
The selection sort algorithm sorts an array by repeatedly finding the minimum 
element (considering ascending order) from the unsorted part and putting it at 
the beginning. The algorithm maintains two subarrays in a given array.
Complexity: O(n^2).
----------------------------------------------------------------------------*/
void SelectionSort(int *arr, size_t len);
/*----------------------------------------------------------------------------
Insertion sort is a simple sorting algorithm that works similar to the way you 
sort playing cards in your hands. The array is virtually split into a sorted
and an unsorted part. Values from the unsorted part are picked and placed at 
the correct position in the sorted part.
Complexity: O(n^2)/ best case O(n).
----------------------------------------------------------------------------*/
void InsertionSort(int *arr, size_t len);

/*---------------------------------------------------------------------------
Description:
	
	
Return Value:
	
	
Complexity: 
	time: O(log(n))  / space: O(1) 
---------------------------------------------------------------------------*/
int *IterBinarySearch(int *arr, int arr_size, int element_to_find);

/*---------------------------------------------------------------------------
Description:
	
	
Return Value:
	
	
Complexity: 
	time: O(log(n))  / space: O(log(n)) 
---------------------------------------------------------------------------*/
int *RecBinarySearch(int *arr, int arr_size, int element_to_find);

/*---------------------------------------------------------------------------
Description:
	
	
Return Value:
	
	
Complexity: 
	time: O(nlogn)  / space: O(n) 
---------------------------------------------------------------------------*/
int MergeSort(int *arr_to_sort, size_t num_elements);

/*---------------------------------------------------------------------------
Description:
	
	
Return Value:
	
	
Complexity: 
	time: avg: O(nlogn) worst: O(n^2)  / space: O(logn) 
---------------------------------------------------------------------------*/
void Qsort(void *base, size_t nmemb, size_t size, compar_func_t cmp);


#endif /* __CMP_SORTS__ */

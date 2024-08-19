/*-------------------------------------------*/
/* DEVELOPER: Itay Guter                    */
/* LAST MODIFIED: 17/1/2023	               */
/* WORKSHEET NAME: Linear Sort		      */
/* REVIEWER: Matan Isak			         */
/*--------------------------------------*/

#ifndef __LINEAR_SORT_H__
#define __LINEAR_SORT_H__

/*********************************************************
General Description
-------------------
Linear Sort allows to sort in linear time (O(n)) but at the cost of space.
*********************************************************/

#include <stddef.h> /* size_t */

/*******************************************************************
Description: Counting sort is a sorting technique based on keys between a 
specific range. It works by counting the number of objects having distinct 
key values. Then do some arithmetic operations to calculate 
the position of each object in the output sequence.

Parameters: arr - array of ints to sort in accending order.
			size - the number of elements in the array.
	
Return Value: 0 on success, and -1 if it fails.

note: not stable.

Complexity
	Time: O(n + k) / Space: O(k)
	if k is n^2 then its O(n^2)
*******************************************************************/
int CountingSort(int *arr, size_t size);
/*******************************************************************
Description: a non-comparative sorting algorithm. It avoids comparison by 
creating and distributing elements into buckets according to their number of 
unique digits.

Parameters: arr - array of ints to sort in accending order.
			size - the number of elements in the array.
			exp_of_ten - the exponent of 10 to build the "buckets" for the sort,
						 its the number of unique digits.
			
Return Value: 0 on success, and -1 if it fails.

note: if the exp_of_ten is 0 the behivior is undefined.

Complexity
	Time: O(n * (k / d)) -> O(n) / Space: O(n + d)
*******************************************************************/
int RadixSort(int *arr, size_t size, size_t exp_of_ten);

#endif /* __LINEAR_SORT_H__ */


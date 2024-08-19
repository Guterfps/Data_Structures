/*-------------------------------------------*/
/* DEVELOPER: Itay Guter                    */
/* LAST MODIFIED: 21/12/2022               */
/* WORKSHEET NAME: Sorted list		      */
/* REVIEWER: Vladimir Levkovich          */
/*--------------------------------------*/

#ifndef __SORTLIST_H__
#define __SORTLIST_H__

#include <stddef.h>		/* size_t */

#include "dlist.h"      /*doubly linked list*/
/*-----------------------------------------------------------------------------
intro: sorted linked list, stores data in a specific order.

policy: sequntial access.

main functionalitis: SortListCreate, SortListDestroy, SortListInsert, 
						SortListRemove, SortListFind.
-----------------------------------------------------------------------------*/
typedef struct sort_list sort_list_t;


typedef int (*sort_list_cmp_t)(const void *data1, const void *data2);
typedef int (*sort_list_do_action_t)(void *data, void *param);
typedef int (*sort_list_is_match_t)(const void *data, void *param);

struct sort_list_iter
{
	dlist_iter_t iter;
    #ifndef NDEBUG
	    sort_list_t *list;
    #endif
};
typedef struct sort_list_iter sort_list_iter_t;

/*-----------------------------------------------------------------------------
Description: creates a new sorted list.

Parameters: cmp - pointer to function that will dictate the order of elements 
				in the list.
	
Return Value: pointer to the new list, NULL if it fails.

Complexity: 
	time: O(1)  / space: O(1) 
-----------------------------------------------------------------------------*/
sort_list_t *SortListCreate(sort_list_cmp_t cmp);
/*-----------------------------------------------------------------------------
Description: deletes a sorted list.

Parameters: list - pointer to the list to delete.
	
Return Value: none.

Complexity: 
	time: O(n)  / space: O(1) 
-----------------------------------------------------------------------------*/
void SortListDestroy(sort_list_t *list);
/*-----------------------------------------------------------------------------
Description: insert a new element to the list.

Parameters: list - sorted list to insert to.
			data - pointer to the data to be inserted.
	
Return Value: iterator of the new element inserted to the list, end of list if
				it fails.

Complexity: 
	time: O(n) / space: O(1) 
-----------------------------------------------------------------------------*/
sort_list_iter_t SortListInsert(sort_list_t *list, void *data);
/*-----------------------------------------------------------------------------
Description: removes an element from the list.

Parameters: iter - iterator of the element to be removed.
	
Return Value: iterator of the next element in the list.

Complexity: 
	time: O(1)  / space: O(1) 
-----------------------------------------------------------------------------*/
sort_list_iter_t SortListRemove(sort_list_iter_t iter);
/*-----------------------------------------------------------------------------
Description: findes an element in the list ,by maching data with the cmp 
			function of the list.

Parameters: list - sorted list to search.
			from - iterator of the element to start searching from.
			to - iterator of the element to stop searching (not include).
			param - data to match with the data in the list.
	
Return Value: iterator of the found element, 
				iterator "to" if element is not found.
note: if "from" and "to" are not from the same "list" the behivior is undefined.

Complexity: 
	time: O(n) / space: O(1) 
-----------------------------------------------------------------------------*/
sort_list_iter_t SortListFind(const sort_list_t *list ,const sort_list_iter_t from,
							 const sort_list_iter_t to, const void *param);
/*-----------------------------------------------------------------------------
Description: findes an element in the list ,by maching data with the is_mach
				function.

Parameters: from - iterator of the element to start searching from.
			to - iterator of the element to stop searching (not include).
			is_mach - function to check the data of the list.
			param - data to match with the data in the list.
	
Return Value: iterator of the found element, 
				iterator "to" if element is not found.

note: if "from" and "to" are not from the same "list" the behivior is undefined.

Complexity: 
	time: O(n) / space: O(1) 
-----------------------------------------------------------------------------*/										 
sort_list_iter_t SortListFindIf(const sort_list_iter_t from, 
							   const sort_list_iter_t to, 
							   sort_list_is_match_t is_match, void *param);	 
/*-----------------------------------------------------------------------------
Description: preforming "do_action" function on every element in a list
				in a given range.

Parameters: from - iterator of the element to start iterating from.
			to - iterator of the element to stop iterating (not include).
			do_action - function to preform on the data of the list.
			param - data to match with the data in the list.
	
Return Value: success if all "do_action"s return success, and fail otherwise.

note: if "from" and "to" are not from the same "list" the behivior is undefined.

Complexity: 
	time: O(n) / space: O(1) 
-----------------------------------------------------------------------------*/
int SortListForEach(sort_list_iter_t from, sort_list_iter_t to, 
			        sort_list_do_action_t do_action, void *param);
/*-----------------------------------------------------------------------------
Description: returns the first element in the list.

Parameters: list - sorted list.
	
Return Value: iterator of the first element in the list.

note: if list is empty iterator of the end of the list would be returnd. 

Complexity: 
	time: O(1)  / space: O(1) 
-----------------------------------------------------------------------------*/
sort_list_iter_t SortListBegin(const sort_list_t *list);
/*-----------------------------------------------------------------------------
Description: returns the end of the list.

Parameters: list - sorted list.
	
Return Value: iterator of the end of the list.

Complexity: 
	time: O(1)  / space: O(1) 
-----------------------------------------------------------------------------*/
sort_list_iter_t SortListEnd(const sort_list_t *list);
/*-----------------------------------------------------------------------------
Description: return the next element in the sorted list.

Parameters: current - iterator of the current element in the list.
	
Return Value: iterator of the next element in the list.

note: if current is the end of the list ,the behivior is undefined.

Complexity: 
	time: O(1)  / space: O(1) 
-----------------------------------------------------------------------------*/
sort_list_iter_t SortListNext(sort_list_iter_t current);
/*-----------------------------------------------------------------------------
Description: return the previos element in the sorted list.

Parameters: current - iterator of the current element in the list.
	
Return Value: iterator of the previos element in the list.

note: if current is the first element in the list ,the behivior is undefined.

Complexity: 
	time: O(1)  / space: O(1) 
-----------------------------------------------------------------------------*/
sort_list_iter_t SortListPrev(sort_list_iter_t current);
/*-----------------------------------------------------------------------------
Description: returns pointer to the data in the element.

Parameters: iter - iterator of an element in the sorted list.
	
Return Value: void pointer to the data.

note: if the iter is the end of the list the behivior is undefined.

Complexity: 
	time: O(1)  / space: O(1) 
-----------------------------------------------------------------------------*/
void *SortListGetVal(const sort_list_iter_t iter);
/*-----------------------------------------------------------------------------
Description: compers two iterators.

Parameters: one - iterator of sorted list.
			other - iterator of sorted list.
	
Return Value: return 1 if iterators are the same , and 0 otherwise.

Complexity: 
	time: O(1)  / space: O(1) 
-----------------------------------------------------------------------------*/
int SortListIterIsEqual(const sort_list_iter_t one, const sort_list_iter_t other);
/*-----------------------------------------------------------------------------
Description: count the amount of elements in the list.

Parameters: list - sorted list to count.
	
Return Value: size_t .

Complexity: 
	time: O(n)  / space: O(1) 
-----------------------------------------------------------------------------*/
size_t SortListCount(const sort_list_t *list);
/*-----------------------------------------------------------------------------
Description: checks if a list is empty.

Parameters: list - sorted list to check.
	
Return Value: return 1 if empty , and 0 otherwise.

Complexity: 
	time: O(1)  / space: O(1) 
-----------------------------------------------------------------------------*/
int SortListIsEmpty(const sort_list_t *list);
/*-----------------------------------------------------------------------------
Description: removes an element from the begining of the list.

Parameters: list - sorted list.
	
Return Value: void pointer to the data that was removed from the list.

note: if the list is empty behivior is undefined.

Complexity: 
	time: O(1)  / space: O(1) 
-----------------------------------------------------------------------------*/
void *SortListPopFront(sort_list_t *list);
/*-----------------------------------------------------------------------------
Description: removes an element from the end of the list.

Parameters: list - sorted list.
	
Return Value: void pointer to the data that was removed from the list.

note: if the list is empty behivior is undefined.

Complexity: 
	time: O(1)  / space: O(1) 
-----------------------------------------------------------------------------*/
void *SortListPopBack(sort_list_t *list);
/*-----------------------------------------------------------------------------
Description: merge two sorted lists into one sorted list by moving all the 
				elements from "src" to "dest".

Parameters: dest - sorted list to be merged into.
			src - sorted list to merge from.
	
Return Value: none.

Complexity: 
	time: O(n)  / space: O(1) 
-----------------------------------------------------------------------------*/
void SortListMerge(sort_list_t *dest, sort_list_t *src); 
/*----------------------------------------------------------------------------*/

#endif /* __SORTLIST_H__ */


/*-------------------------------------------*/
/* DEVELOPER: Itay Guter                    */
/* LAST MODIFIED: 18/12/2022               */
/* WORKSHEET NAME: Doubly linked list     */
/* REVIEWER: Or Abadi	                 */
/*--------------------------------------*/

#ifndef __DLIST_H__
#define __DLIST_H__
/*-----------------------------------------------------------------------------
intro: doubly linked list is a linear data structure that allows to store
		data in a specific order.
policy: sequntial access ,by refrence.

main functionalitis: DlistCreate, DlistDestroy, DlistInsertBefore, DlistRemove
					, DlistFind.

-----------------------------------------------------------------------------*/
#include <stddef.h>		/* size_t */

typedef struct dlist dlist_t;
typedef struct dlist_node *dlist_iter_t;

typedef int (*dlist_do_action_t)(void *data, void *param);
typedef int (*dlist_is_match_t)(const void *data, void *param);

/*-----------------------------------------------------------------------------
Description: creates a new dlist_t.

Parameters: none.
	
Return Value: pointer to the new list (dlist_t *).

Complexity: 
	time: O(1)  / space: O(1) 
-----------------------------------------------------------------------------*/
dlist_t *DlistCreate(void); 


/*-----------------------------------------------------------------------------
Description: deletes a dlist_t.

Parameters: pointer to the dlist_t to destroy.
	
Return Value: none.

Complexity: 
	time: O(n)  / space: O(1) 
-----------------------------------------------------------------------------*/
void DlistDestroy(dlist_t *list);


/*-----------------------------------------------------------------------------
Description: returns the iterator to the element at the begining of the list.

Parameters: pointer to the dlist_t.
	
Return Value: iterator of type dlist_iter_t.

Complexity: 
	time: O(1)  / space: O(1) 
-----------------------------------------------------------------------------*/
dlist_iter_t DlistBegin(const dlist_t *list);


/*-----------------------------------------------------------------------------
Description: returns the iterator of the End of the list.

Parameters: pointer to the dlist_t.
	
Return Value: iterator of type dlist_iter_t

Complexity: 
	time: O(1)  / space: O(1) 
-----------------------------------------------------------------------------*/
dlist_iter_t DlistEnd(const dlist_t *list);


/*-----------------------------------------------------------------------------
Description: returns an iterator of the next element in the list.

Parameters: current iterator of type dlist_iter_t.
	
Return Value: iterator of type dlist_iter_t.

note: if current is the end of the list, behivior is undefined.

Complexity: 
	time: O(1)  / space: O(1) 
-----------------------------------------------------------------------------*/
dlist_iter_t DlistNext(dlist_iter_t current);


/*-----------------------------------------------------------------------------
Description: returns an iterator of the previos element in the list.

Parameters: current iterator of type dlist_iter_t.
	
Return Value: iterator of type dlist_iter_t.

note: if current is the first element in the list, behivior is undefined.

Complexity: 
	time: O(1)  / space: O(1) 
-----------------------------------------------------------------------------*/
dlist_iter_t DlistPrev(dlist_iter_t current);


/*-----------------------------------------------------------------------------
Description: adds new element before the element at the begining of the list.

Parameters: list to push to, data to be pushed.
	
Return Value: iterator to the new element in the list.

note: if push fails time complexity increses to O(n), and a dummy iterator is 
		returned.

Complexity: 
	time: O(1), worst: O(n)  / space: O(1) 
-----------------------------------------------------------------------------*/
dlist_iter_t DlistPushFront(dlist_t *list, void *data);


/*-----------------------------------------------------------------------------
Description: adds new element after the element at the end of the list.

Parameters: list to push to, data to be pushed.
	
Return Value: iterator to the new element in the list.

note: if push fails time complexity increses to O(n), and a dummy iterator is 
		returned.

Complexity: 
	time: O(1), worst: O(n)  / space: O(1) 
-----------------------------------------------------------------------------*/
dlist_iter_t DlistPushBack(dlist_t *list, void *data);


/*-----------------------------------------------------------------------------
Description: removes element from the begining of the list.

Parameters: list to remove from.
	
Return Value: the data stored at that element.

note: if list is empty, behivior is undefined.

Complexity: 
	time: O(1)  / space: O(1) 
-----------------------------------------------------------------------------*/
void *DlistPopFront(dlist_t *list);


/*-----------------------------------------------------------------------------
Description: removes element from the end of the list.

Parameters: list to remove from.
	
Return Value: the data stored at that element.

note: if list is empty, behivior is undefined.

Complexity: 
	time: O(1)  / space: O(1) 
-----------------------------------------------------------------------------*/
void *DlistPopBack(dlist_t *list);


/*-----------------------------------------------------------------------------
Description: insert new data before a given iterator.

Parameters: where to insert before, data to insert.
	
Return Value: iterator of the new data inserted to the list.

note: if insert fails time complexity increses to O(n) and a dummy iterator is 
		returned.

Complexity: 
	time: O(1), worst: O(n) / space: O(1) 
-----------------------------------------------------------------------------*/
dlist_iter_t DlistInsertBefore(dlist_iter_t where, void *data);


/*-----------------------------------------------------------------------------
Description: removes data at a given iterator.

Parameters: where to remove the data.
	
Return Value: iterator of the next/previos element in the list.

note: if the element to be removed is at the end of the list then iterator
	  to the previos element would return ,
	  otherwise the next element would return.
	  if list is empty behivior is undefined.

Complexity: 
	time: O(1)  / space: O(1) 
-----------------------------------------------------------------------------*/
dlist_iter_t DlistRemove(dlist_iter_t where);


/*-----------------------------------------------------------------------------
Description: findes an element in a list from "from" until "to" not include.

Parameters: from - start the search. 
			to - stop the search.
			is_match - a pointer function to check the elements in the list.
			param - the data to check against the elements in the list.
	
Return Value: an iterator of the found element.

note: if element is not found, the function will return the iterator of "to".

Complexity: 
	time: O(n)  / space: O(1) 
-----------------------------------------------------------------------------*/
dlist_iter_t DlistFind(const dlist_iter_t from, const dlist_iter_t to, 
					   dlist_is_match_t is_match, void *param);
					   

/*-----------------------------------------------------------------------------
Description: findes all elements in a list from "from" until "to" not include,
			 that matches "param".

Parameters: result_list - a list to store the matching elements.
			from - start the search. 
			to - stop the search.
			is_match - a pointer function to check the elements in the list.
			param - the data to check against the elements in the list.
	
Return Value: 0 on sccessesful operation, 1 otherwise.

Complexity: 
	time: O(n)  / space: O(n) 
-----------------------------------------------------------------------------*/
int DlistMultiFind(dlist_t *result_list ,const dlist_iter_t from,
 		   const dlist_iter_t to, dlist_is_match_t is_match, void *param);


/*-----------------------------------------------------------------------------
Description: preforms an action on every element in the list from "from" 
			 until "to" not include.

Parameters: from - start the search. 
			to - stop the search.
			do_action - a pointer function to use on the elements in the list. 
			param - an extra parameter to use in do_action.
			
Return Value: returns 0 if all actions were seccessful, and 1(or what ever
			  do_action returns on fail) otherwise.

Complexity: 
	time: O(n)  / space: O(1) 
-----------------------------------------------------------------------------*/
int DlistForEach(dlist_iter_t from, dlist_iter_t to, 
			     dlist_do_action_t do_action, void *param); 


/*-----------------------------------------------------------------------------
Description: cuts part of a list from "from" to "to" (not include!) 
			 and insert it before "where".

Parameters: from - iterator of an element in a dlist_t, start of the 
					section to cut.
			to - iterator of an element in a dlist_t, end of the section to cut.
			where - iterator of an element in a dlist_t, the element to paste
					the cut section (before "where").
			
Return Value: returns an iterator of the element before "where".

note: if "where" is in between "from" and "to", or if "to" is before "from",
	  the behivior is undefined.

Complexity: 
	time: O(1)  / space: O(1) 
-----------------------------------------------------------------------------*/
dlist_iter_t DlistSplice(dlist_iter_t from, dlist_iter_t to,
														  dlist_iter_t where);


/*-----------------------------------------------------------------------------
Description: get the address of the value in the iterator iter.

Parameters: iter - iterator of an element in dlist_t.
	
Return Value: returns a void * to the value.

Complexity: 
	time: O(1)  / space: O(1) 
-----------------------------------------------------------------------------*/
void *DlistGetVal(const dlist_iter_t iter);


/*-----------------------------------------------------------------------------
Description: seting the value in iter to the data parameter.

Parameters: iter - iterator of an element in dlist_t.
			data - address of the value to be set.
	
Return Value: returns the iterator of the element that was set a new value.

Complexity: 
	time: O(1)  / space: O(1) 
-----------------------------------------------------------------------------*/
dlist_iter_t DlistSetVal(dlist_iter_t iter, void *data);


/*-----------------------------------------------------------------------------
Description: returns the amount of elements in list.

Parameters: list - pointer to a dlist_t. 
	
Return Value: size_t type.

Complexity: 
	time: O(n)  / space: O(1) 
-----------------------------------------------------------------------------*/
size_t DlistCount(const dlist_t *list);


/*-----------------------------------------------------------------------------
Description: checks if two iterators are the same.

Parameters: one - dlist_iter_t to comper.
			other - dlist_iter_t to comper.
	
Return Value: returns 1 if the two iterators are equal, and 0 otherwise.

Complexity: 
	time: O(1)  / space: O(1) 
-----------------------------------------------------------------------------*/
int DlistIterIsEqual(const dlist_iter_t one, const dlist_iter_t other);


/*-----------------------------------------------------------------------------
Description: checks if a list is empty(aka: there are no elements in it).

Parameters: list - pointer to dlist_t to check.
	
Return Value: returns 1 if empty, and 0 otherwise.

Complexity: 
	time: O(1)  / space: O(1) 
-----------------------------------------------------------------------------*/
int DlistIsEmpty(const dlist_t *list);


#endif /* __DLIST_H__ */

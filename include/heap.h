/*-------------------------------------------*/
/* DEVELOPER: Itay Guter                    */
/* LAST MODIFIED: 7/2/2023	               */
/* WORKSHEET NAME: Heap				      */
/* REVIEWER: Gali		                 */
/*--------------------------------------*/

#ifndef __HEAP_H__
#define __HEAP_H__

#include <stddef.h>	/* size_t */

/*-----------------------------------------------------------------------------
Heap: a heap is a specialized tree-based data structure which is essentially 
an almost complete tree that satisfies the heap property: in a 
max heap, for any given node C, if P is a parent node of C, then the key 
(the value) of P is greater than or equal to the key of C. In a min heap, 
the key of P is less than or equal to the key of C. 
The node at the "top" of the heap (with no parents) is called the root node.
The heap is one maximally efficient implementation of an abstract data type 
called a priority queue.

main functionalitis: HeapPush(), HeapPop(), HeapPeek().

-----------------------------------------------------------------------------*/

/* handler for the heap */
typedef struct heap heap_t;

/*-----------------------------------------------------------------------------
Description: compares the priority of elements in the heap. 
	
Parameters: heap_data - the data in the heap.
			new_data - the data being added to the heap.
			param - some extra parameter to evaluate the priority.
			
Return Value: 0, negative or positive if the priority of heap_data is 
			equal to, smaller or greater than new_data.

-----------------------------------------------------------------------------*/
typedef int(*heap_cmp_t)(const void *heap_data, const void *new_data, 
																   void *param); 

/*-----------------------------------------------------------------------------
Description: checks if two elements are the same in the heap.
	
Parameters: data - element in the heap.
			param - element to match with.
	
Return Value: 1 if they match, and 0 otherwise.

-----------------------------------------------------------------------------*/
typedef int(*heap_is_match_t)(const void *data, void *param);

/*-----------------------------------------------------------------------------
Description: creates a new heap.
	
Parameters: cmp - function to compare priority of elements(see heap_cmp_t).
			param - (see heap_cmp_t);
	
Return Value: pointer to the new heap, or NULL if it fails.

Complexity: 
	time: O(1) / space: O(1) 
-----------------------------------------------------------------------------*/
heap_t *HeapCreate(heap_cmp_t cmp, void *param);

/*-----------------------------------------------------------------------------
Description: deletes a heap.
	
Parameters: heap - pointer to the heap.
	
Return Value: none.

Complexity: 
	time: O(1) / space: O(1) 
-----------------------------------------------------------------------------*/
void HeapDestroy(heap_t *heap);

/*-----------------------------------------------------------------------------
Description: pushes new element to the heap.

Parameters: heap - pointer to the heap.
			data - element to push.

Return Value: 0 if it was pushed successfuly, or -1 otherwise.
	
Complexity: 
	time: Amortized O(logn) / space: Amortized O(n) 
-----------------------------------------------------------------------------*/
int HeapPush(heap_t *heap, void *data); 

/*-----------------------------------------------------------------------------
Description: removes the element at the top of the heap,
	
Parameters: heap - pointer to the heap.
	
Return Value: the removed element , or NULL if it fails(system problem).

note: even if it fails the element may still be removed.
note: if heap is empty the behivior is undefined.

Complexity: 
	time: Amortized O(logn) / space: Amortized O(n) 
-----------------------------------------------------------------------------*/
void *HeapPop(heap_t *heap); 

/*-----------------------------------------------------------------------------
Description: returns the element at the top of the heap.

Parameters: heap - pointer to the heap.
	
Return Value: the element at the top of the heap.

note: if heap is empty the behivior is undefined.

Complexity: 
	time: O(1)  / space: O(1) 
-----------------------------------------------------------------------------*/
void *HeapPeek(const heap_t *heap);

/*-----------------------------------------------------------------------------
Description: removes an element from the heap.
	
Parameters: heap - pointer to the heap.
			data - the element to remove.
			is_match - function to match data with elements in the heap.
			param - currently its useless.
	
Return Value: the removed element, and NULL if it dosent find the element or	
				fails(system problem).
				
note: even if it fails the element may still be removed.

Complexity: 
	time: O(n)  / space: O(1) 
-----------------------------------------------------------------------------*/
void *HeapRemove(heap_t *heap, void *data, heap_is_match_t is_match, 
																   void *param);

/*-----------------------------------------------------------------------------
Description: checks if the heap is empty.

Parameters: heap - pointer to the heap.

Return Value: 1 if empty, 0 otherwise. 

Complexity: 
	time: O(1)  / space: O(1) 
-----------------------------------------------------------------------------*/
int HeapIsEmpty(const heap_t *heap);

/*-----------------------------------------------------------------------------
Description: returns the amount of elements in the heap.
	
Parameters: heap - pointer to the heap
	
Return Value: number of elements in the heap

Complexity: 
	time: O(1)  / space: O(1) 
-----------------------------------------------------------------------------*/
size_t HeapSize(const heap_t *heap);


#endif 	/* __HEAP_H__ */


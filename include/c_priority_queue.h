/*-------------------------------------------*/
/* DEVELOPER: Itay Guter                    */
/* LAST MODIFIED: 28/12/2022               */
/* WORKSHEET NAME: Priority Queue	      */
/* REVIEWER: Yuval Atoun		         */
/*--------------------------------------*/

#ifndef __PRIORITY_QUEUE_H__
#define __PRIORITY_QUEUE_H__

#include <stddef.h>	/* size_t */
/*-----------------------------------------------------------------------------
intro: stores elements by priority and FIFO, similar to a regular queue
		in which each element additionally has a priority associated with it.
		An element of highest priority always appears at the front of the queue.
		If that element is removed, the next highest priority element advances 
		to the front

policy: priority, FIFO.

main functionalitis: PQCreate, PQDestroy, PQEnqueue, 
						PQDequeue.
-----------------------------------------------------------------------------*/
typedef struct ilrd_pq ilrd_pq_t;
/*-----------------------------------------------------------------------------
Description: compares data1 and data2 in priority context, acording to this
			function the priority of the queue is determined.

Parameters: data1 - element to be compared.
			data2 - element to be compared.
			
Return Value: returns negative number if data1 have lower priority then data2,
				0 if they have the same priority, and positive otherwise.

-----------------------------------------------------------------------------*/
typedef int(*pq_cmp_t)(const void *data1, const void *data2);
/*-----------------------------------------------------------------------------
Description: checks if two elements are matching.

Parameters: data - element in the queue.
			param - element to mach with.

Return Value: returns 1 if elements match, and 0 otherwise.

-----------------------------------------------------------------------------*/
typedef int(*pq_is_match_t)(const void *data, void *param);

/*-----------------------------------------------------------------------------
Description: creates a new priority queue.

Parameters: cmp - compares in priority context(see pq_cmp_t).

Return Value: returns pointer to the new queue, or NULL if it fails.

complexity: time: O(1), space: O(1) 
-----------------------------------------------------------------------------*/
ilrd_pq_t *PQCreate(pq_cmp_t cmp);

/*-----------------------------------------------------------------------------
Description: deletes a priority queue.

Parameters: pq - the queue to delete.

Return Value: none.

complexity: time: O(n), space: O(1)
-----------------------------------------------------------------------------*/
void PQDestroy(ilrd_pq_t *pq);

/*-----------------------------------------------------------------------------
Description: adds an element to the end of the queue, acording to its priority.

Parameters: pq - the priority queue to add to.
			data - the element to add.

Return Value: 0 on successful enqueue, and 1 otherwise.

complexity: time: O(n), space: O(1)
-----------------------------------------------------------------------------*/
int PQEnqueue(ilrd_pq_t *pq, void *data);

/*-----------------------------------------------------------------------------
Description: removes an element from the front of the queue.

Parameters: pq - priority queue to remove from.

Return Value: the element that was dequeued.

note: if the queue is empty the behivior is undefined.

complexity: time: O(1), space: O(1)
-----------------------------------------------------------------------------*/
void *PQDequeue(ilrd_pq_t *pq); 

/*-----------------------------------------------------------------------------
Description: checks if the queue is empty.

Parameters: pq - the priority queue to check.

Return Value: 1 if its empty, and 0 otherwise.

complexity: time: O(1), space: O(1)
-----------------------------------------------------------------------------*/
int PQIsEmpty(const ilrd_pq_t *pq);

/*-----------------------------------------------------------------------------
Description: "shows" the element in the front of the queue. 

Parameters: pq - the priority queue to peek.

Return Value: pointer to the element at the front of the queue.

note: if the queue is empty the behivior is undefined.

complexity: time: O(1), space: O(1)
-----------------------------------------------------------------------------*/
void *PQPeek(const ilrd_pq_t *pq); 

/*-----------------------------------------------------------------------------
Description: return the size of the queue(the amount of elements in the queue). 

Parameters: pq - the priority queue.

Return Value: returns the size of the queue(size_t).

complexity: time: O(n), space: O(1)
-----------------------------------------------------------------------------*/
size_t PQSize(const ilrd_pq_t *pq);

/*-----------------------------------------------------------------------------
Description: clears the queue(making it empty).

Parameters:	pq - priority queue to clear.

Return Value: none.

complexity: time: O(n), space: O(1)
-----------------------------------------------------------------------------*/
void PQClear(ilrd_pq_t *pq); 

/*-----------------------------------------------------------------------------
Description: removes a specific element from the queue, according to "is_match"
			function and the "data" to match with.

Parameters: pq - priority queue to remove from.
			data - element to match with.
			is_match - function to match the elements.

Return Value: pointer to the element that have been removed from the queue,
				or NULL if there is no match and no element is removed.

complexity: time: O(n), space: O(1)
-----------------------------------------------------------------------------*/
void *PQErase(ilrd_pq_t *pq, void *data, pq_is_match_t is_match);

#endif 	/* __PRIORITY_QUEUE_H__ */


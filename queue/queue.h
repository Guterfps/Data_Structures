/*-------------------------------------------*/
/* DEVELOPER: Itay Guter                    */
/* LAST MODIFIED: 12/12/2022               */
/* WORKSHEET NAME: Queue			      */
/* REVIEWER: Noy Cohen	                 */
/*--------------------------------------*/

#ifndef __QUEUE_H__
#define __QUEUE_H__

#include <stddef.h>		/* size_t */

typedef struct queue queue_t;

/*---------------------------------------------------------------------------
Description: creates new queue.
	
Return Value: returns queue_t * to the new queue or NULL if it fails.

Complexity: 
 time:O(1)  | space:O(1) 
---------------------------------------------------------------------------*/
queue_t *QueueCreate(void);

/*---------------------------------------------------------------------------
Description: Deletes a queue.
	
Return Value: none.

Complexity: 
 time:O(n)  | space:O(1) 
---------------------------------------------------------------------------*/
void QueueDestroy(queue_t *queue);

/*---------------------------------------------------------------------------
Description: add new item to the end of the queue.
	
Return Value: returns 0 on success and 1 if it fails.

Complexity: 
 time:O(1)  | space:O(1) 
---------------------------------------------------------------------------*/
int QueueEnqueue(queue_t *queue, void *data);

/*---------------------------------------------------------------------------
Description: removes item from the front of the queue, if queue is empty 
behivior is undifined.
	
Return Value: none.

Complexity: 
 time:O(1)  | space:O(1) 
---------------------------------------------------------------------------*/
void QueueDequeue(queue_t *queue);

/*---------------------------------------------------------------------------
Description: returns the item at the front of the queue, if queue is empty 
behivior is undifined.
	
Return Value: the address of the item(void *).

Complexity: 
 time:O(1)  | space:O(1) 
---------------------------------------------------------------------------*/
void *QueuePeek(const queue_t *queue);

/*---------------------------------------------------------------------------
Description: checks if the queue is empty or not.
	
Return Value: returns 1 if queue is empty and 0 if not.

Complexity: 
 time:O(1)  | space:O(1) 
---------------------------------------------------------------------------*/
int QueueIsEmpty(const queue_t *queue);
    
/*---------------------------------------------------------------------------
Description: returns the length of the queue.
	
Return Value: size_t.

Complexity: 
 time:O(n)  | space:O(1) 
---------------------------------------------------------------------------*/
size_t QueueSize(const queue_t *queue);

/*---------------------------------------------------------------------------
Description: append queue "src" to the end of queue "dest".
	
Return Value: queue_t * to the dest queue.

Complexity: 
 time:O(1)  | space:O(1) 
---------------------------------------------------------------------------*/
queue_t *QueueAppend(queue_t *dest, queue_t *src);


#endif /* __QUEUE_H__ */




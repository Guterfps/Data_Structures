/*-------------------------------------------*/
/* DEVELOPER: Itay Guter                    */
/* LAST MODIFIED: 12/12/2022               */
/* WORKSHEET NAME: Queue			      */
/* REVIEWER: Noy Cohen	                 */
/*--------------------------------------*/

#include <stdlib.h>		/*malloc(), free(()*/
#include <assert.h>		/*assert()*/

#include "queue.h"		/*function declerations and typedefs*/
#include "slist.h"		/*function declerations and typedefs*/

struct queue
{
	slist_t *list;
};

enum status
{
	SUCCESS = 0,
	FAIL = -1
};

queue_t *QueueCreate(void)
{
	queue_t *new_queue = (queue_t *)malloc(sizeof(struct queue));
	if (NULL == new_queue)
	{
		return NULL;
	}
	
	new_queue->list = SlistCreate();
	if (NULL == new_queue->list)
	{
		free(new_queue);
		new_queue = NULL;
		return NULL;
	}
	
	return new_queue;
}

void QueueDestroy(queue_t *queue)
{
	assert(NULL != queue);
	
	SlistDestroy(queue->list);
	queue->list = NULL;
	free(queue);
	queue = NULL;
}

int QueueEnqueue(queue_t *queue, void *data)
{
	slist_iter_t queue_end = NULL;
	
	assert(NULL != queue);
	assert(NULL != data);
	
	queue_end = SlistEnd(queue->list);
	if (NULL == SlistInsertBefore(queue_end, data))
	{
		return FAIL;
	}
	
	return SUCCESS;
}

void QueueDequeue(queue_t *queue)
{
	slist_iter_t queue_first = NULL;
	
	assert(NULL != queue);
	
	queue_first = SlistBegin(queue->list);
	SlistRemove(queue_first);
}

void *QueuePeek(const queue_t *queue)
{
	slist_iter_t queue_first = NULL;
	void *data = NULL;
	
	assert(NULL != queue);
	
	queue_first = SlistBegin(queue->list);
	data = SlistGetVal(queue_first);
	
	return data;
}

int QueueIsEmpty(const queue_t *queue)
{
	assert(NULL != queue);
	
	return (SlistIsEmpty(queue->list));
}

size_t QueueSize(const queue_t *queue)
{
	assert(NULL != queue);
	
	return (SlistCount(queue->list));
}

queue_t *QueueAppend(queue_t *dest, queue_t *src)
{
	assert(NULL != dest);
	assert(NULL != src);
	
	SlistAppend(dest->list, src->list);
	
	return dest;
}





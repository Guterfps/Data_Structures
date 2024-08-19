/*-------------------------------------------*/
/* DEVELOPER: Itay Guter                    */
/* LAST MODIFIED: 28/12/2022               */
/* WORKSHEET NAME: Priority Queue	      */
/* REVIEWER: Yuval Atoun		         */
/*--------------------------------------*/

#include <stdlib.h>		/* malloc() */
#include <assert.h>		/* assert() */

#include "c_priority_queue.h"	/* priority_queue header */
#include "sort_list.h"		/* sort list header */

struct ilrd_pq
{
	sort_list_t *pqueue;
};

ilrd_pq_t *PQCreate(pq_cmp_t cmp)
{
	ilrd_pq_t *new_pq = NULL; 
	
	assert(NULL != cmp);
	
	new_pq = (ilrd_pq_t *)malloc(sizeof(struct ilrd_pq));
	if (NULL == new_pq)
	{
		return NULL;
	}
	
	new_pq->pqueue = SortListCreate(cmp);
	if (NULL == new_pq->pqueue)
	{
		free(new_pq);
		new_pq = NULL;
		return NULL;
	}
	
	return new_pq;
}

void PQDestroy(ilrd_pq_t *pq)
{
	assert(NULL != pq);
	
	SortListDestroy(pq->pqueue);
	free(pq);
	pq = NULL;
}

int PQEnqueue(ilrd_pq_t *pq, void *data)
{
	sort_list_iter_t iter = {0};
	
	assert(NULL != pq);
	assert(NULL != data);
	
	iter = SortListInsert(pq->pqueue, data);
	
	return (SortListIterIsEqual(iter, SortListEnd(pq->pqueue)));
}

void *PQDequeue(ilrd_pq_t *pq)
{
	assert(NULL != pq);
	assert(!PQIsEmpty(pq));
	
	return (SortListPopFront(pq->pqueue));
}

void *PQPeek(const ilrd_pq_t *pq)
{
	assert(NULL != pq);
	assert(!PQIsEmpty(pq));
	
	return (SortListGetVal(SortListBegin(pq->pqueue)));
}

int PQIsEmpty(const ilrd_pq_t *pq)
{
	assert(NULL != pq);
	
	return (SortListIsEmpty(pq->pqueue));
}

size_t PQSize(const ilrd_pq_t *pq)
{
	assert(NULL != pq);
	
	return (SortListCount(pq->pqueue));
}

void PQClear(ilrd_pq_t *pq)
{
	assert(NULL != pq);
	
	for (;!PQIsEmpty(pq); SortListPopFront(pq->pqueue)) {/*empty loop*/}
}

void *PQErase(ilrd_pq_t *pq, void *data, pq_is_match_t is_match)
{
	void *removed_element = NULL;
	sort_list_iter_t iter = {0};
	
	assert(NULL != pq);
	assert(NULL != is_match);
	
	iter = SortListFindIf(SortListBegin(pq->pqueue), SortListEnd(pq->pqueue),
							is_match, data);
	if (!SortListIterIsEqual(iter, SortListEnd(pq->pqueue)))
	{
		removed_element = SortListGetVal(iter);
		SortListRemove(iter);
	}
	
	return removed_element;
}



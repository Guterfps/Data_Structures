/*-------------------------------------------*/
/* DEVELOPER: Itay Guter                    */
/* LAST MODIFIED: 7/2/2023	               */
/* WORKSHEET NAME: Heap_PQ			      */
/* REVIEWER: Gali		                 */
/*--------------------------------------*/

#include <stdlib.h>		/* malloc() */
#include <assert.h>		/* assert() */

#include "Heap_PQ.h"	/* Heap_PQ header */
#include "heap.h"		/* heap header */

struct ilrd_pq
{
	heap_t *heap;
};

static int CmpHeap(const void *heap_data, const void *new_data, void *param);

ilrd_pq_t *PQCreate(pq_cmp_t cmp)
{
	ilrd_pq_t *new_pq = NULL; 
	
	assert(NULL != cmp);
	
	new_pq = (ilrd_pq_t *)malloc(sizeof(ilrd_pq_t));
	if (NULL == new_pq)
	{
		return NULL;
	}
	
	new_pq->heap = HeapCreate(&CmpHeap, *(void **)&cmp);
	if (NULL == new_pq->heap)
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
	
	HeapDestroy(pq->heap);
	free(pq);
	pq = NULL;
}

int PQEnqueue(ilrd_pq_t *pq, void *data)
{	
	assert(NULL != pq);
	
	return (HeapPush(pq->heap, data));
}

void *PQDequeue(ilrd_pq_t *pq)
{
	assert(NULL != pq);
	assert(!PQIsEmpty(pq));
	
	return (HeapPop(pq->heap));
}

void *PQPeek(const ilrd_pq_t *pq)
{
	assert(NULL != pq);
	assert(!PQIsEmpty(pq));
	
	return (HeapPeek(pq->heap));
}

int PQIsEmpty(const ilrd_pq_t *pq)
{
	assert(NULL != pq);
	
	return (HeapIsEmpty(pq->heap));
}

size_t PQSize(const ilrd_pq_t *pq)
{
	assert(NULL != pq);
	
	return (HeapSize(pq->heap));
}

void PQClear(ilrd_pq_t *pq)
{
	assert(NULL != pq);
	
	for (;!PQIsEmpty(pq); PQDequeue(pq)) {/*empty loop*/}
}

void *PQErase(ilrd_pq_t *pq, void *data, pq_is_match_t is_match)
{	
	assert(NULL != pq);
	assert(NULL != is_match);	
	
	return (HeapRemove(pq->heap, data, is_match, NULL));
}

static int CmpHeap(const void *heap_data, const void *new_data, void *param)
{
	assert(NULL != param);
	
	return ((*(pq_cmp_t *)&param)(heap_data, new_data));
}
											

/*-------------------------------------------*/
/* DEVELOPER: Itay Guter                    */
/* LAST MODIFIED: 7/2/2023	               */
/* WORKSHEET NAME: Heap				      */
/* REVIEWER: Gali		                 */
/*--------------------------------------*/

#include <assert.h>	/* assert() */
#include <stdlib.h>	/* malloc() */

#include "d_vector.h"	/* d_vector library */
#include "heap.h"	/* function declerations and typedefs */

#define MIN_CAP 64

struct heap
{
	heap_cmp_t cmp;
	void *param;
	vector_t *vector;
};

enum status
{
	SUCCESS = 0,
	FAIL = -1
};

/* utility functions */
static heap_t *InitHeap(heap_t *heap, heap_cmp_t cmp, void *param);
static void *GetElemP(vector_t *vec, size_t indx);
static void Swap(void *a, void *b);
static void *GetElemVal(vector_t *vec, size_t indx);
static size_t FindElemIndx(heap_t *heap, heap_is_match_t is_match, void *data);
static int CheckPriority(heap_t *heap, size_t indx1, size_t indx2);

/* heapify functions */
static void HeapifyUp(heap_t *heap);
static void HeapifyDown(heap_t *heap, size_t indx);

/* tree index functions */
static size_t ParentIndex(size_t indx);
static size_t LeftIndex(size_t indx);
static size_t RightIndex(size_t indx);



heap_t *HeapCreate(heap_cmp_t cmp, void *param)
{
	heap_t *new_heap = NULL;
	
	assert(NULL != cmp);
	
	new_heap = (heap_t *)malloc(sizeof(heap_t));
	if (NULL == new_heap)
	{
		return NULL;
	}
	
	new_heap = InitHeap(new_heap, cmp, param);
	
	return new_heap;
}

void HeapDestroy(heap_t *heap)
{
	assert(NULL != heap);
	
	VectorDestroy(heap->vector);
	
	free(heap);
	heap = NULL;
}

int HeapPush(heap_t *heap, void *data)
{
	vector_t *temp_vec = NULL;
	
	assert(NULL != heap);
	
	temp_vec = VectorPushBack(heap->vector, &data);
	if (NULL == temp_vec)
	{
		return FAIL;
	}
	
	heap->vector = temp_vec;
	HeapifyUp(heap);
	
	return SUCCESS;
}

void *HeapPop(heap_t *heap)
{
	vector_t *temp_vec = NULL;
	size_t indx = 0;
	void *pop = NULL;
	
	assert(NULL != heap);
	assert(0 < VectorSize(heap->vector)); 
	
	pop = HeapPeek(heap);
	indx = VectorSize(heap->vector) - 1;
	Swap(GetElemP(heap->vector, 0), GetElemP(heap->vector, indx));
	
	temp_vec = VectorPopBack(heap->vector);
	if (NULL == temp_vec)
	{
		return NULL;
	}
	
	heap->vector = temp_vec;
	HeapifyDown(heap, 0);
	
	return pop;
}

void *HeapPeek(const heap_t *heap)
{
	assert(NULL != heap);
	assert(0 < VectorSize(heap->vector));
	
	return (GetElemVal(heap->vector, 0));
}

int HeapIsEmpty(const heap_t *heap)
{
	assert(NULL != heap);
	
	return (0 == VectorSize(heap->vector));
}

size_t HeapSize(const heap_t *heap)
{
	assert(NULL != heap);
	
	return (VectorSize(heap->vector));
}

void *HeapRemove(heap_t *heap, void *data, heap_is_match_t is_match, 
																   void *param)
{
	size_t elem_indx = 0;
	size_t last_indx = 0;
	vector_t *vec = NULL;
	void *removed = NULL;
	
	assert(NULL != heap);
	assert(NULL != is_match);
	
	(void)param;
	
	if(0 == VectorSize(heap->vector))
	{
		return NULL;
	}
	
	vec = heap->vector;
	elem_indx = FindElemIndx(heap, is_match, data);
	last_indx = VectorSize(heap->vector) - 1;
	
	if (elem_indx > last_indx)
	{
		return NULL;
	}
	
	Swap(GetElemP(vec, last_indx), GetElemP(vec, elem_indx));
	removed = GetElemVal(vec, last_indx);
	
	vec = VectorPopBack(heap->vector);
	if (NULL == vec)
	{
		return NULL;
	}
	
	heap->vector = vec;
	HeapifyDown(heap, elem_indx);
	
	return removed;
}

static void HeapifyUp(heap_t *heap)
{
	size_t indx = 0;
	vector_t *vec = NULL;
	
	assert(NULL != heap);
	
	indx = VectorSize(heap->vector) - 1;
	vec = heap->vector;
	
	while ((0 < indx) && 
		   CheckPriority(heap, ParentIndex(indx), indx))
	{
		Swap(GetElemP(vec, indx), GetElemP(vec, ParentIndex(indx)));
		indx = ParentIndex(indx);
	}
}

static void HeapifyDown(heap_t *heap, size_t indx)
{
	size_t indx_right = LeftIndex(indx);
	size_t indx_left = RightIndex(indx);
	size_t indx_curr = indx;
	vector_t *vec = NULL;
	
	assert(NULL != heap);
	
	vec = heap->vector;
	
	if ((indx_left < VectorSize(vec)) && 
		CheckPriority(heap, indx_curr, indx_left))
	{
		indx_curr = indx_left;
	}
	if ((indx_right < VectorSize(vec)) && 
		CheckPriority(heap, indx_curr, indx_right))
	{
		indx_curr = indx_right;
	}
	if (indx != indx_curr)
	{
		Swap(GetElemP(vec, indx), GetElemP(vec, indx_curr));
		HeapifyDown(heap, indx_curr);
	}
}

static int CheckPriority(heap_t *heap, size_t indx1, size_t indx2)
{
	int pririty = 0;
	vector_t *vec = NULL;
	
	assert(NULL != heap);
	
	vec = heap->vector;
	
	assert(indx1 < VectorSize(vec));
	assert(indx2 < VectorSize(vec));
	
	pririty = (0 < heap->cmp(GetElemVal(vec, indx1), 
					   		 GetElemVal(vec, indx2), heap->param));
	return pririty;
}

static size_t FindElemIndx(heap_t *heap, heap_is_match_t is_match, void *data)
{
	size_t i = 0;
	int status = 0;
	
	assert(NULL != heap);
	assert(NULL != is_match);
	
	for (; (i < VectorSize(heap->vector)) && !status; ++i)
	{
		status = is_match(GetElemVal(heap->vector, i), data);
	}
	
	return (status ? (i - 1) : i);
}

static heap_t *InitHeap(heap_t *heap, heap_cmp_t cmp, void *param)
{
	assert(NULL != heap);
	assert(NULL != cmp);
	
	heap->vector = VectorCreate(MIN_CAP, sizeof(void *));
	if (NULL == heap->vector)
	{
		free(heap);
		heap = NULL;
		return NULL;
	}
	
	heap->cmp = cmp;
	heap->param = param;
	
	return heap;
}

static size_t ParentIndex(size_t indx)
{
	assert(0 < indx);
	
	return ((indx - 1) / 2);
}

static size_t LeftIndex(size_t indx)
{
	return (2 * indx + 1);
}

static size_t RightIndex(size_t indx)
{
	return (2 * indx + 2);
}

static void *GetElemP(vector_t *vec, size_t indx)
{
	assert(NULL != vec);
	
	return (VectorGetAccessElement(vec, indx));
}

static void *GetElemVal(vector_t *vec, size_t indx)
{
	assert(NULL != vec);
	assert(indx < VectorSize(vec));
	
	return (*(void **)GetElemP(vec, indx));
}

static void Swap(void *a, void *b)
{
	size_t *pa = (size_t *)a;
	size_t *pb = (size_t *)b;
	
	assert(NULL != a);
	assert(NULL != b);
	
	if (pa != pb)
	{
		*pa ^= *pb;
		*pb ^= *pa;
		*pa ^= *pb;	
	}
}




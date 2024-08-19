/*-------------------------------------------*/
/* DEVELOPER: Itay Guter                    */
/* LAST MODIFIED: 21/12/2022               */
/* WORKSHEET NAME: Sorted list		      */
/* REVIEWER: Vladimir Levkovich          */
/*--------------------------------------*/

#include <stdlib.h>		/*malloc(), free()*/
#include <assert.h>		/*assert()*/

#include "sort_list.h"		/*function decleraitions and typedefs*/

#define EQUAL 0

struct sort_list
{
	dlist_t *dlist;
	sort_list_cmp_t cmp;
};

static sort_list_iter_t InitSortListIter(sort_list_t *list, dlist_iter_t iter);

sort_list_t *SortListCreate(sort_list_cmp_t cmp)
{
	sort_list_t *new_list = NULL;
	
	assert(NULL != cmp);
	
	new_list = (sort_list_t *)malloc(sizeof(sort_list_t));
	if (NULL == new_list)
	{
		return NULL;
	}
	
	new_list->dlist = DlistCreate();
	if (NULL == new_list->dlist)
	{
		free(new_list);
		new_list = NULL;
		return NULL;
	}
	
	new_list->cmp = cmp;
	
	return new_list;
}

void SortListDestroy(sort_list_t *list)
{
	assert(NULL != list);
	
	DlistDestroy(list->dlist);
	
	free(list);
	list = NULL;
}

sort_list_iter_t SortListInsert(sort_list_t *list, void *data)
{
	sort_list_iter_t runer = {NULL};
	
	assert(NULL != list);
	assert(NULL != data);

	runer = SortListBegin(list);
	
	while (!DlistIterIsEqual(runer.iter, DlistEnd(list->dlist)) && 
			0 <= list->cmp(data, SortListGetVal(runer)))
	{
		runer = SortListNext(runer);
	}
	
	runer.iter = DlistInsertBefore(runer.iter, data);
	
	return runer;
}

sort_list_iter_t SortListRemove(sort_list_iter_t iter)
{
	assert(NULL != iter.list);
	assert(!SortListIterIsEqual(SortListEnd(iter.list), iter));
	
	iter.iter = DlistRemove(iter.iter);
	
	return iter;
}


sort_list_iter_t SortListFind(const sort_list_t *list ,
								const sort_list_iter_t from,
							 	const sort_list_iter_t to, const void *param)
{
	sort_list_iter_t iter_found = {NULL};
	
	assert(NULL != list);
	assert(NULL != from.list);
	assert(NULL != to.list);
	assert(NULL != param);
	assert(from.list == to.list);
	
	iter_found = InitSortListIter((sort_list_t *)list, from.iter);
	
	while (!DlistIterIsEqual(iter_found.iter, to.iter) && 
			EQUAL != list->cmp(SortListGetVal(iter_found), param))
	{
		iter_found = SortListNext(iter_found);
	}
	
	return iter_found;
}

sort_list_iter_t SortListFindIf(const sort_list_iter_t from, 
							   const sort_list_iter_t to, 
							   sort_list_is_match_t is_match, void *param)
{
	sort_list_iter_t iter_found = {NULL};
	
	assert(NULL != from.list);
	assert(NULL != to.list);
	assert(NULL != is_match);
	assert(from.list == to.list);
	
	#ifndef NDEBUG
		iter_found.list = from.list;
	#endif
	iter_found.iter = DlistFind(from.iter, to.iter, is_match, param);
	
	return iter_found;
}


int SortListForEach(sort_list_iter_t from, sort_list_iter_t to, 
			        sort_list_do_action_t do_action, void *param)
{
	assert(NULL != from.list);
	assert(NULL != to.list);
	assert(NULL != do_action);
	assert(from.list == to.list);
	
	return (DlistForEach(from.iter, to.iter, do_action, param));
}

sort_list_iter_t SortListBegin(const sort_list_t *list)
{
	sort_list_iter_t begin_iter = {NULL};
	
	assert(NULL != list);
	
	begin_iter = InitSortListIter((sort_list_t *)list, DlistBegin(list->dlist));
	
	return begin_iter;
}

sort_list_iter_t SortListEnd(const sort_list_t *list)
{
	sort_list_iter_t end_iter = {NULL};
	
	assert(NULL != list);
	
	end_iter = InitSortListIter((sort_list_t *)list, DlistEnd(list->dlist));
	
	return end_iter;
}

sort_list_iter_t SortListNext(sort_list_iter_t current)
{
	assert(NULL != current.list);
	assert(!SortListIterIsEqual(SortListEnd(current.list), current));
	
	current.iter = DlistNext(current.iter);
	
	return current;
}

sort_list_iter_t SortListPrev(sort_list_iter_t current)
{
	assert(NULL != current.list);
	assert(!SortListIterIsEqual(SortListBegin(current.list), current));
	
	current.iter = DlistPrev(current.iter);
	
	return current;
}

void *SortListGetVal(const sort_list_iter_t iter)
{
	assert(NULL != iter.list);
	assert(!SortListIterIsEqual(SortListEnd(iter.list), iter));
	
	return (DlistGetVal(iter.iter));
}

int SortListIterIsEqual(const sort_list_iter_t one, 
							const sort_list_iter_t other)
{
	assert(NULL != one.list);
	assert(NULL != other.list);
	
	return (DlistIterIsEqual(one.iter, other.iter));
}

size_t SortListCount(const sort_list_t *list)
{
	assert(NULL != list);
	
	return (DlistCount(list->dlist));
}

int SortListIsEmpty(const sort_list_t *list)
{
	assert(NULL != list);
	
	return (DlistIsEmpty(list->dlist));
}

void *SortListPopFront(sort_list_t *list)
{
	assert(NULL != list);
	
	return (DlistPopFront(list->dlist));
}

void *SortListPopBack(sort_list_t *list)
{
	assert(NULL != list);
	
	return (DlistPopBack(list->dlist));
}

void SortListMerge(sort_list_t *dest, sort_list_t *src)
{
	dlist_iter_t from_runer = 0;
	dlist_iter_t to_runer = 0;
	dlist_iter_t where_runer = 0;
	 
	assert(NULL != dest);
	assert(NULL != src);
	assert(dest->cmp == src->cmp);

	
	from_runer = DlistBegin(src->dlist);
	to_runer = DlistBegin(src->dlist);
	where_runer = DlistBegin(dest->dlist);
	
	if (DlistIsEmpty(dest->dlist)) 
	{
		DlistSplice(from_runer, DlistEnd(src->dlist), where_runer);
	}
	
	while (!DlistIsEmpty(src->dlist))
	{
		if ((DlistEnd(dest->dlist) != where_runer) && 
			(0 < dest->cmp(DlistGetVal(from_runer), DlistGetVal(where_runer))))
		{
			where_runer = DlistNext(where_runer);
		}
		else if ((DlistEnd(src->dlist) != to_runer) && 
				(DlistEnd(dest->dlist) != where_runer) &&
				(0 < dest->cmp(DlistGetVal(where_runer), 
				DlistGetVal(to_runer))))
		{
			to_runer = DlistNext(to_runer);
		}
		else
		{
			DlistSplice(from_runer, to_runer, where_runer);
			from_runer = to_runer;
			to_runer = DlistNext(to_runer);
		}
	}
}

static sort_list_iter_t InitSortListIter(sort_list_t *list, dlist_iter_t iter)
{
	sort_list_iter_t sort_iter = {NULL};
	
	assert(NULL != list);
	
	#ifndef NDEBUG
		sort_iter.list = list;
	#endif
	(void)list;
	
	sort_iter.iter = iter;
	
	return sort_iter;
}



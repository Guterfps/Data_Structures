/*-------------------------------------------*/
/* DEVELOPER: Itay Guter                    */
/* LAST MODIFIED: 18/12/2022               */
/* WORKSHEET NAME: Doubly linked list     */
/* REVIEWER: Or Abadi	                 */
/*--------------------------------------*/

#include <stdlib.h>		/*malloc(), free()*/
#include <assert.h>		/*assert()*/

#include "dlist.h"		/*function declerations and typedefs*/

#define DUMMY NULL
#define TO_ITER(node) ((dlist_iter_t)node)

typedef struct dlist_node dlnode_t;

struct dlist_node
{
	void *data;
	dlnode_t *next;
	dlnode_t *prev;
};

struct dlist
{
	dlnode_t *dummy;
};

enum bool
{
	FALSE,
	TRUE = 1
};

enum status
{
	SUCCESS,
	FAIL = 1
};

static void InitDlist(dlist_t *list, dlnode_t *dummy);
static dlnode_t *FindDummy(dlnode_t *where);
static void ConectNodes(dlnode_t *node1, dlnode_t *node2);

dlist_t *DlistCreate(void)
{
	dlnode_t *dummy = NULL;
	dlist_t *new_list = (dlist_t *)malloc(sizeof(dlist_t));
	if (NULL == new_list)
	{
		return NULL;
	}
	
	dummy = (dlnode_t *)malloc(sizeof(dlnode_t));
	if (NULL == dummy)
	{
		free(new_list);
		new_list = NULL;
		return NULL;
	}
	
	InitDlist(new_list, dummy);
	
	return new_list;
}

dlist_iter_t DlistRemove(dlist_iter_t where)
{
	dlnode_t *temp = NULL;
	
	assert(NULL != where);
	
	temp = (DUMMY != where->next->data) ? where->next : where->prev;
	
	ConectNodes(where->prev, where->next);
	
	free(where);
	where = NULL;
	
	return (TO_ITER(temp));
}

void *DlistPopFront(dlist_t *list)
{
	void *temp_data = NULL;
	
	assert(NULL != list);
	
	temp_data = list->dummy->next->data;
	DlistRemove(list->dummy->next);
	
	return (temp_data);
}

void *DlistPopBack(dlist_t *list)
{
	void *temp_data = NULL;
	
	assert(NULL != list);
	
	temp_data = list->dummy->prev->data;
	DlistRemove(list->dummy->prev);
	
	return (temp_data);
}

void DlistDestroy(dlist_t *list)
{	
	while (DUMMY != DlistPopFront(list)) {/* empty loop */}
	
	free(list);
	list = NULL;
}

dlist_iter_t DlistBegin(const dlist_t *list)
{
	assert(NULL != list);
	
	return (TO_ITER(list->dummy->next));
}

dlist_iter_t DlistEnd(const dlist_t *list)
{
	assert(NULL != list);
	
	return (TO_ITER(list->dummy));
}

dlist_iter_t DlistNext(dlist_iter_t current)
{
	assert(NULL != current);
	
	return (current->next);
}

dlist_iter_t DlistPrev(dlist_iter_t current)
{
	assert(NULL != current);
	
	return (current->prev);
}

dlist_iter_t DlistInsertBefore(dlist_iter_t where, void *data)
{
	dlnode_t *new_node = NULL;
	
	assert(NULL != where);
	assert(NULL != data);
	
	new_node = (dlnode_t *)malloc(sizeof(dlnode_t));
	if (NULL == new_node)
	{
		return (TO_ITER(FindDummy(where)));
	}
	
	new_node->data = data;
	
	ConectNodes(where->prev, new_node);
	ConectNodes(new_node, where);
	
	return (TO_ITER(new_node));
}

dlist_iter_t DlistPushFront(dlist_t *list, void *data)
{	
	assert(NULL != list);
	assert(NULL != data);
	
	return (TO_ITER(DlistInsertBefore(list->dummy->next, data)));
}

dlist_iter_t DlistPushBack(dlist_t *list, void *data)
{
	assert(NULL != list);
	assert(NULL != data);
	
	return (TO_ITER(DlistInsertBefore(list->dummy, data)));
}

dlist_iter_t DlistFind(const dlist_iter_t from, const dlist_iter_t to, 
					   dlist_is_match_t is_match, void *param)
{
	dlnode_t *temp_node = NULL;
	 
	assert(NULL != from);
	assert(NULL != to);
	assert(NULL != is_match);
	
	temp_node = (dlnode_t *)from;
	
	while ((temp_node != to) && FALSE == is_match(temp_node->data, param))
	{
		temp_node = DlistNext(temp_node);
	}
	
	return (TO_ITER(temp_node));
}

int DlistMultiFind(dlist_t *result_list ,const dlist_iter_t from,
 		   const dlist_iter_t to, dlist_is_match_t is_match, void *param)
{
	dlnode_t *temp_node = NULL;
	int status = SUCCESS;
	
	assert(NULL != result_list);
	assert(NULL != from);
	assert(NULL != to);
	assert(NULL != is_match);
	
	temp_node = (dlnode_t *)from;
	
	while (((temp_node = DlistFind(temp_node, to, is_match, param)) != to) &&
			 SUCCESS == status)
	{	
		status = (DUMMY == DlistPushFront(result_list, temp_node->data)->data);
		temp_node = DlistNext(temp_node);
	}
	
	return status;
}

int DlistForEach(dlist_iter_t from, dlist_iter_t to, 
			     dlist_do_action_t do_action, void *param)
{
	int status = SUCCESS;
	dlnode_t *temp_node = NULL;
	
	assert(NULL != from);
	assert(NULL != to);
	assert(NULL != do_action);
	
	temp_node = (dlnode_t *)from;
	
	while ((temp_node != to) && SUCCESS == status)
	{
		status = do_action(temp_node->data, param);
		temp_node = DlistNext(temp_node);
	}
	
	return status;
}

dlist_iter_t DlistSplice(dlist_iter_t from, dlist_iter_t to,
														  dlist_iter_t where)
{
	dlnode_t *to_prev = NULL;
	
	assert(NULL != from);
	assert(NULL != to);
	assert(NULL != where);
	
	to_prev = to->prev;
	
	ConectNodes(from->prev, to);
	ConectNodes(where->prev, from);
	ConectNodes(to_prev, where);
	
	return (TO_ITER(to_prev));
}


void *DlistGetVal(const dlist_iter_t iter)
{
	assert(NULL != iter);
	
	return (iter->data);
}

dlist_iter_t DlistSetVal(dlist_iter_t iter, void *data)
{
	assert(NULL != iter);
	
	iter->data = data;
	
	return iter;
}

size_t DlistCount(const dlist_t *list)
{
	size_t counter = 0;
	dlnode_t *runer = NULL;
	
	assert(NULL != list);
	
	runer = DlistBegin(list);
	
	while (DUMMY != runer->data)
	{
		runer = DlistNext(runer);
		++counter;
	}
	
	return counter;
}

int DlistIterIsEqual(const dlist_iter_t one, const dlist_iter_t other)
{
	assert(NULL != one);
	assert(NULL != other);
	
	return (one == other);
}

int DlistIsEmpty(const dlist_t *list)
{
	assert(NULL != list);
	
	return (list->dummy->next == list->dummy);
}

static void InitDlist(dlist_t *list, dlnode_t *dummy)
{
	assert(NULL != list);
	assert(NULL != dummy);
	
	dummy->data = DUMMY;
	dummy->next = dummy;
	dummy->prev = dummy;
	list->dummy = dummy;
}

static void ConectNodes(dlnode_t *node1, dlnode_t *node2)
{
	assert(NULL != node1);
	assert(NULL != node2);
	
	node1->next = node2;
	node2->prev = node1;
}

static dlnode_t *FindDummy(dlnode_t *where)
{
	assert(NULL != where);
	
	while (DUMMY != where->data)
	{
		where = DlistNext(where);
	}
	
	return where;
}


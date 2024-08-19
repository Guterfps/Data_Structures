/*-------------------------------------------*/
/* DEVELOPER: Itay Guter                    */
/* LAST MODIFIED: 12/12/2022               */
/* WORKSHEET NAME: Queue			      */
/* REVIEWER: Noy Cohen	                 */
/*--------------------------------------*/

#include <assert.h>		/*assert()*/
#include <stdlib.h>		/*calloc()*/

#include "slist.h"		/*function declerations and typedefs*/

#define EOL NULL		/*End Of List*/

struct slist_node
{
	void *data;
	slist_iter_t next;
};

struct slist
{
	slist_iter_t head;
	slist_iter_t tail;
};

enum status
{
	SUCCESS,
	FAIL = 1
};

enum is_found
{
	FALSE,
	TRUE = 1
};

slist_t *SlistCreate(void)
{
	slist_t *new_list = (slist_t *)calloc(1, sizeof(slist_t));
	slist_iter_t dummy = NULL;
	if (NULL == new_list)
	{
		return NULL;
	}
	
	dummy = (slist_iter_t)calloc(1, sizeof(struct slist_node));
	if (NULL == dummy)
	{
		SlistDestroy(new_list);
		return NULL;
	}
	
	new_list->head = dummy;
	new_list->tail = dummy;
	dummy->data = new_list;
	dummy->next = EOL;
	
	return new_list;
}

void SlistDestroy(slist_t *list)
{
	slist_iter_t temp_node = NULL;
	
	assert(NULL != list);
	
	do
	{
		temp_node = list->head;
		list->head = temp_node->next;
		free(temp_node);
		temp_node = NULL;
		
	}while (EOL != list->head);

	
	free(list);
	list = NULL;
}

slist_iter_t SlistInsertBefore(slist_iter_t where, void *data)
{
	slist_iter_t new_node = NULL;
	
	assert(NULL != where);
	assert(NULL != data);
	
	new_node = (slist_iter_t)calloc(1, sizeof(struct slist_node));
	if (NULL == new_node)
	{
		return NULL;
	}
	
	new_node->data = where->data;
	new_node->next = where->next;
	
	if (EOL == where->next)
	{
		((slist_t *)(where->data))->tail = new_node;
	}
	
	
	where->data = data;
	where->next = new_node;
	
	return where;
}

slist_iter_t SlistRemove(slist_iter_t where)
{
	slist_iter_t temp_iter = NULL;
	
	assert(NULL != where);
	assert(EOL != where->next);
	
	if (EOL == where->next->next)
	{
		((slist_t *)(where->next->data))->tail = where;
	}
	
	temp_iter = where->next;
	where->data = temp_iter->data;
	where->next = temp_iter->next;	
	
	free(temp_iter);
	temp_iter = NULL;
	
	return where;
}

slist_iter_t SlistFind(const slist_iter_t from, const slist_iter_t to, 
					   slist_is_match_t is_match, void *param)
{
	slist_iter_t iter = NULL;
	
	assert(NULL != from);
	assert(NULL != to);
	assert(NULL != param);
	assert(NULL != is_match);
	
	iter = from;
	
	while (!SlistIterIsEqual(iter, to) && TRUE != is_match(iter->data, param))
	{
		iter = iter->next;
	}
	
	return iter;
}

int SlistForEach(slist_iter_t from, slist_iter_t to, 
			     slist_do_action_t do_action, void *param)
{
	slist_iter_t iter = NULL;
	int status = SUCCESS;
	
	assert(NULL != from);
	assert(NULL != to);
	assert(NULL != param);
	assert(NULL != do_action);
	
	iter = from;
	
	while (!SlistIterIsEqual(iter, to) && !status)
	{
		status = do_action(iter->data, param);
		iter = iter->next;
	}
	
	return status;
}


void *SlistGetVal(const slist_iter_t iter)
{
	assert(NULL != iter);
	assert(EOL != iter->next);
	
	return (iter->data);
}

slist_iter_t SlistSetVal(slist_iter_t iter, void *data)
{
	assert(NULL != iter);
	assert(NULL != data);
	
	iter->data = data;
	
	return iter;
}

size_t SlistCount(const slist_t *list)
{
	size_t counter = 0;
	slist_iter_t iter= NULL;
	
	assert(NULL != list);
	
	iter = list->head;
	
	while (EOL != iter->next)
	{
		++counter;
		iter = iter->next;
	}
	
	return counter;
}

int SlistIterIsEqual(const slist_iter_t one, const slist_iter_t other)
{
	assert(NULL != one);
	assert(NULL != other);
	
	return (one == other);
}

int SlistIsEmpty(const slist_t *list)
{
	assert(NULL != list);
	
	return (list->head == list->tail);
}

slist_iter_t SlistBegin(const slist_t *list)
{
	assert(NULL != list);
	
	return (list->head);
}

slist_iter_t SlistEnd(const slist_t *list)
{
	assert(NULL != list);
	
	return (list->tail);
}

slist_t *SlistAppend(slist_t *dest, slist_t *src)
{
	slist_iter_t dest_end = NULL;
	slist_iter_t src_start = NULL;
	
	assert(NULL != dest);
	assert(NULL != src);
	
	if (EOL == src->head->next)
	{
		return dest;
	}
	dest_end = SlistEnd(dest);
	src_start = SlistBegin(src);
	
	dest_end->data = src_start->data;
	dest_end->next = src_start->next;
	dest->tail = SlistEnd(src);
	dest->tail->data = dest;
	
	src_start->data = src;
	src_start->next = EOL;
	src->tail = src_start;
	src->head = src_start;

	return dest;
}




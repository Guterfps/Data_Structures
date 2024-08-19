/*-------------------------------------------*/
/* DEVELOPER: Itay Guter                    */
/* LAST MODIFIED: 5/2/2023	               */
/* WORKSHEET NAME: Hash Table		      */
/* REVIEWER: Eitan		                 */
/*--------------------------------------*/

#include <assert.h>	/* assert() */
#include <stdlib.h>	/* calloc(), free() */

#include "dlist.h"	/* doubly linked list */
#include "hash_table.h"	/* function declerations and typedefs */

struct hash
{
	hash_get_key_t get_key;
	hash_is_match_t is_match;
	hash_func_t hash_func;
	size_t table_size;
	dlist_t *table[1];
};

enum status
{
	SUCCESS = 0,
	FAIL = -1
};

enum empty
{
	NOT_EMPTY = 0,
	EMPTY
};

static void InitHashTable(hash_t *h_table, hash_get_key_t GetKey,
							hash_is_match_t IsMatch, hash_func_t hash_func,
							size_t table_size);
static int NewDlist(hash_t *h_table, size_t indx);
static void DestroyLists(hash_t *h_table);
static dlist_iter_t FindIter(dlist_t *list, const hash_t *hash, 
													const void *key);

hash_t *HashCreate(hash_get_key_t GetKey, hash_is_match_t IsMatch, 
								      hash_func_t hash_func, size_t table_size)
{
	hash_t *new_table = NULL;
	
	assert(NULL != GetKey);
	assert(NULL != IsMatch);
	assert(NULL != hash_func);
	assert(0 < table_size);
	
	new_table = (hash_t *)calloc(1, sizeof(hash_t) - sizeof(dlist_t *[1])
									+ table_size * sizeof(dlist_t *));
	if (NULL == new_table)
	{
		return NULL;
	}
	
	InitHashTable(new_table, GetKey, IsMatch, hash_func, table_size);
	
	return new_table;
}

void HashDestroy(hash_t *hash)
{
	assert(NULL != hash);
	
	DestroyLists(hash);
	
	free(hash);
	hash = NULL;
}

int HashInsert(hash_t *hash, void *item)
{
	size_t indx = 0;
	dlist_iter_t new_item_iter = NULL;
	int status = SUCCESS;
	
	assert(NULL != hash);
	assert(NULL == HashFind(hash, hash->get_key(item)));
	
	indx = hash->hash_func(hash->get_key(item));
	assert(indx < hash->table_size);
	
	if (NULL == hash->table[indx])
	{
		status = NewDlist(hash, indx);
		if (FAIL == status)
		{
			return status;
		}
	}
	
	new_item_iter = DlistPushBack(hash->table[indx], item);
	status = DlistIterIsEqual(new_item_iter, DlistEnd(hash->table[indx])) ? 
			 FAIL : SUCCESS;
	
	return status;
}

void *HashFind(const hash_t *hash, const void *key)
{
	size_t indx = 0;
	dlist_t *list = NULL;
	dlist_iter_t iter = NULL;
	
	assert(NULL != hash);
	
	indx = hash->hash_func(key);
	assert(indx < hash->table_size);
	
	list = hash->table[indx];
	if (NULL == list)
	{
		return NULL;
	}
	
	iter = FindIter(list, hash, key);
	if (DlistIterIsEqual(iter, DlistEnd(list)))
	{
		return NULL;
	}
	
	return (DlistGetVal(iter));
}

void HashRemove(hash_t *hash, const void *key)
{
	size_t indx = 0;
	dlist_t *list = NULL;
	dlist_iter_t iter = NULL;
	
	assert(NULL != hash);
	
	indx = hash->hash_func(key);
	assert(indx < hash->table_size);
	
	list = hash->table[indx];
	if (NULL == list)
	{
		return;
	}
	
	iter = FindIter(list, hash, key);
	if (!DlistIterIsEqual(iter, DlistEnd(list)))
	{
		DlistRemove(iter);
	}
}

int HashForeach(hash_t *hash, hash_callback_t callback, void *param)
{
	size_t i = 0;
	int status = SUCCESS;
	
	assert(NULL != hash);
	assert(NULL != callback);
	
	for (; (i < hash->table_size) && (SUCCESS == status); ++i)
	{
		dlist_t *list = hash->table[i];
		if (NULL != list)
		{
			status = DlistForEach(DlistBegin(list), DlistEnd(list), 
									callback, param);
		}
	}
	
	return status;
}

size_t HashSize(const hash_t *hash)
{
	size_t i = 0;
	size_t counter = 0;
	
	assert(NULL != hash);
	
	for (; i < hash->table_size; ++i)
	{
		dlist_t *list = hash->table[i];
		if (NULL != list)
		{
			counter += DlistCount(list);
		}
	}
	
	return counter;
}

int HashIsEmpty(const hash_t *hash)
{
	size_t i = 0;
	int is_empty = EMPTY;
	
	assert(NULL != hash);
	
	for (; (i < hash->table_size) && (EMPTY == is_empty); ++i)
	{
		dlist_t *list = hash->table[i];
		if (NULL != list)
		{
			is_empty = DlistIsEmpty(list);
		}
	}
	
	return is_empty;
}

static dlist_iter_t FindIter(dlist_t *list, const hash_t *hash, 
													const void *key)
{
	dlist_iter_t runner = 0;
	
	assert(NULL != hash);
	assert(NULL != list);
	
	runner = DlistBegin(list);
	
	while ((!DlistIterIsEqual(runner, DlistEnd(list))) && 
			!hash->is_match(key, hash->get_key(DlistGetVal(runner))))
	{
		runner = DlistNext(runner);
	}
	
	return runner;
}

static int NewDlist(hash_t *h_table, size_t indx)
{
	assert(NULL != h_table);
	
	return ((NULL != (h_table->table[indx] = DlistCreate())) ? SUCCESS : FAIL);
}

static void DestroyLists(hash_t *h_table)
{
	size_t i = 0;
	
	assert(NULL != h_table);
	
	for (; i < h_table->table_size; ++i)
	{
		if (NULL != h_table->table[i])
		{
			DlistDestroy(h_table->table[i]);
		}
	}
}

static void InitHashTable(hash_t *h_table, hash_get_key_t GetKey,
							hash_is_match_t IsMatch, hash_func_t hash_func,
							size_t table_size)
{
	assert(NULL != h_table);
	assert(NULL != GetKey);
	assert(NULL != IsMatch);
	assert(NULL != hash_func);
	
	h_table->get_key = GetKey;
	h_table->is_match = IsMatch;
	h_table->hash_func = hash_func;
	h_table->table_size = table_size;
}



/*-------------------------------------------*/
/* DEVELOPER: Itay Guter                    */
/* LAST MODIFIED: 5/2/2023	               */
/* WORKSHEET NAME: Hash Table		      */
/* REVIEWER: Eitan		                 */
/*--------------------------------------*/

#ifndef __HASH_H__
#define __HASH_H__

#include <stddef.h>		/* size_t */

/*------------------------------- Hash Table -----------------------------------
General Description: It is an abstract data type that maps keys to values. 
A hash table uses a hash function to compute an index, also called a hash code, 
into an array of buckets or slots, from which the desired value can be found. 
During lookup, the key is hashed and the resulting hash indicates where the 
corresponding value is stored.

Main Functionality:
	Search
	Insert
	Remove
	
Attributes:
	random access
	fixed size
	ordered value structure
	unique items
------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------
Description: function to perform on every item in the table. 

Parameters: item - item in the table.
			param - some parameter for the function.

Return Value: 0 on successful operation, non-zero if it fails.

------------------------------------------------------------------------------*/
typedef int (*hash_callback_t)(void *item, void *param);
/*------------------------------------------------------------------------------
Description: hash function to compute an index from a key.

Parameters: key - the key of an item.

Return Value: the index in the table.

------------------------------------------------------------------------------*/
typedef size_t (*hash_func_t)(const void *key);
/*------------------------------------------------------------------------------
Description: checks if two keys are the same.

Parameters: key1 - the key of an item.
			key2 - the key of an item.

Return Value: 1 if they are the same, 0 otherwise.

------------------------------------------------------------------------------*/
typedef int (*hash_is_match_t)(const void *key1, const void *key2);
/*------------------------------------------------------------------------------
Description: returns the key of an item.

Parameters:	item - an item.

Return Value: the key of the item.

------------------------------------------------------------------------------*/
typedef void *(*hash_get_key_t)(const void *item);
/*------------------------------------------------------------------------------
Description: typedef for the hash table.

------------------------------------------------------------------------------*/
typedef struct hash hash_t; 
/*------------------------------------------------------------------------------
Description: creates a hash table.

Parameters:	GetKey - pointer to a hash_get_key_t function.
			IsMatch - pointer to a hash_is_match_t function.
			hash_func - pointer to a hash_func_t function.
			table_size - the amount of buckets in the table(table_size > 0).
			
Return Value: pointer to the hash table, or NULL if it fails. 
	
Complexity: 
	time:  O(n) / space: O(n) 
------------------------------------------------------------------------------*/
hash_t *HashCreate(hash_get_key_t GetKey, hash_is_match_t IsMatch, 
								      hash_func_t hash_func, size_t table_size);
								      
/*------------------------------------------------------------------------------
Description: deletes a hash table.

Parameters: hash - pointer to a hash table.
	
Return Value: none.
	
Complexity: 
	time:  O(n) / space: O(1) 
------------------------------------------------------------------------------*/
void HashDestroy(hash_t *hash);

/*------------------------------------------------------------------------------
Description: inserting an item to the hash table.

Parameters: hash - pointer to a hash table.
			item - item to insert.
	
Return Value: 0 on success, -1 if it fails.

note: if item dosent have a unique key, the behivior is undefined.
	
Complexity: 
	time:  O(1) / space: O(1) 
------------------------------------------------------------------------------*/
int HashInsert(hash_t *hash, void *item);

/*------------------------------------------------------------------------------
Description: removes an item from the hash table.

Parameters: hash - pointer to a hash table.
			key - key of the item to remove.
	
Return Value: none.
	
Complexity: 
	time: Avg - O(1) , Worst - O(n) / space: O(1) 
------------------------------------------------------------------------------*/
void HashRemove(hash_t *hash, const void *key);

/*------------------------------------------------------------------------------
Description: searches for an item in a hash table.

Parameters: hash - pointer to a hash table.
			key - key of the item to search for.
	
Return Value: the item found, or NULL if no item matches the key.
	
Complexity: 
	time: Avg - O(1) , Worst - O(n) / space: O(1) 
------------------------------------------------------------------------------*/
void *HashFind(const hash_t *hash, const void *key);

/*------------------------------------------------------------------------------
Description: performs a callback function on every item in the table.

Parameters: hash - pointer to a hash table.
			callback - a function of type hash_callback_t.
			param - some parameter for the function.
	
Return Value: 0 if all callbackes were successful, otherwise one callback faild.

note: if a callback fails the function stops.
	
Complexity: 
	time: O(n)/ space: O(1) 
------------------------------------------------------------------------------*/
int HashForeach(hash_t *hash, hash_callback_t callback, void *param);

/*------------------------------------------------------------------------------
Description: counts the amount of items in the hash table.

Parameters: hash - pointer to a hash table.
	
Return Value: the amount of items in the hash table
	
Complexity: 
	time: O(n) / space: O(1) 
------------------------------------------------------------------------------*/
size_t HashSize(const hash_t *hash);

/*------------------------------------------------------------------------------
Description: checks if a hash table is empty.

Parameters: hash - pointer to a hash table.
	
Return Value: 1 if its empty, 0 otherwise.
	
Complexity: 
	time: O(table_size) / space: O(1) 
------------------------------------------------------------------------------*/
int HashIsEmpty(const hash_t *hash);

#endif /* __HASH_H__ */


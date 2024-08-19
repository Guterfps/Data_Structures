/*-------------------------------------------*/
/* DEVELOPER: Itay Guter                    */
/* LAST MODIFIED: 12/12/2022               */
/* WORKSHEET NAME: Queue			      */
/* REVIEWER: Noy Cohen	                 */
/*--------------------------------------*/

#ifndef SLIST_H
#define SLIST_H

#include <stddef.h>		/* size_t */

typedef struct slist slist_t;
typedef struct slist_node *slist_iter_t;

typedef int (*slist_do_action_t)(void *data, void *param);
typedef int (*slist_is_match_t)(const void *data, void *param);

/*---------------------------------------------------------------------------
Description: creats the container for the list.
	
Return Value: return slist_t * to the new list or NULL if fails.
	
Complexity: 
	time: O(1)  / space: O(1) 
---------------------------------------------------------------------------*/
slist_t *SlistCreate(void); 

/*---------------------------------------------------------------------------
Description: deletes a slist_t .
	
Return Value: non.
	
Complexity: 
	time: O(n)  / space: O(1) 
---------------------------------------------------------------------------*/
void SlistDestroy(slist_t *list);

/*---------------------------------------------------------------------------
Description: recives an iterator and data, and insert the data before the 
data at the current place(iterator) of the list.
	
Return Value: returns an iterator to the new data in the list or NULL if
it fails.
	
Complexity: 
	time: O(1)  / space: O(1) 
---------------------------------------------------------------------------*/
slist_iter_t SlistInsertBefore(slist_iter_t where, void *data);

/*---------------------------------------------------------------------------
Description: recives an iterator to a place in the list and remove the data
at that place. if iterator is at the end of the list behivior is undifined.
	
Return Value: returns an iterator to the new data added to the list or NULL 
if it fails.
	
Complexity: 
	time: O(1)  / space: O(1) 
---------------------------------------------------------------------------*/
slist_iter_t SlistRemove(slist_iter_t where);

/*---------------------------------------------------------------------------
Description: search for a specific data in the list from iterator "from" 
to iterator "to", user need to provide also an is_match of type slist_is_match_t
function for comparition of values in the list to param.
	
Return Value: returns iterator to the place in the list of the data if it finds
it or iterator to "to" if it dosent find.
	
Complexity: 
	time: O(n)  / space: O(1) 
---------------------------------------------------------------------------*/
slist_iter_t SlistFind(const slist_iter_t from, const slist_iter_t to, 
					   slist_is_match_t is_match, void *param);
					   
/*---------------------------------------------------------------------------
Description: go over the list and preform do_action function (provided by the 
user of type slist_do_action_t) from "from" to "to" on every data in the list
	
Return Value: return 0 if all actions works or 1 if one of the actions fails.
	
Complexity: 
	time: O(n)  / space: O(1) 
---------------------------------------------------------------------------*/
int SlistForEach(slist_iter_t from, slist_iter_t to, 
			     slist_do_action_t do_action, void *param); 

/*---------------------------------------------------------------------------
Description: get the data from the list at the place of the iterator.
	
Return Value: returns pointer to the data in the list.
	
Complexity: 
	time: O(1)  / space: O(1) 
---------------------------------------------------------------------------*/
void *SlistGetVal(const slist_iter_t iter);

/*---------------------------------------------------------------------------
Description: set the value at the iterator place in the list to "data".
	
Return Value: returns the iterator sent by the user.
	
Complexity: 
	time: O(1)  / space: O(1) 
---------------------------------------------------------------------------*/
slist_iter_t SlistSetVal(slist_iter_t iter, void *data);

/*---------------------------------------------------------------------------
Description: count the number of values in the list.
	
Return Value: returns size_t.
	
Complexity: 
	time: O(n)  / space: O(1) 
---------------------------------------------------------------------------*/
size_t SlistCount(const slist_t *list);

/*---------------------------------------------------------------------------
Description: recives two iterators and compers them.
	
Return Value: returns 1 if equal and 0 otherwise.
	
Complexity: 
	time: O(1)  / space: O(1) 
---------------------------------------------------------------------------*/
int SlistIterIsEqual(const slist_iter_t one, const slist_iter_t other);

/*---------------------------------------------------------------------------
Description: checks if a list is empty.
	
Return Value: returns 1 if empty and 0 otherwise.
	
Complexity: 
	time: O(1)  / space: O(1) 
---------------------------------------------------------------------------*/
int SlistIsEmpty(const slist_t *list);

/*---------------------------------------------------------------------------
Description: returns iterator to the beggining of the list.
	
Return Value: returns slist_iter_t.
	
Complexity: 
	time: O(1)  / space: O(1) 
---------------------------------------------------------------------------*/
slist_iter_t SlistBegin(const slist_t *list);

/*---------------------------------------------------------------------------
Description: returns iterator to the end of the list.
	
Return Value: returns slist_iter_t.
	
Complexity: 
	time: O(1)  / space: O(1) 
---------------------------------------------------------------------------*/
slist_iter_t SlistEnd(const slist_t *list);

/*---------------------------------------------------------------------------
Description: append "src" list to the end of "dest" list.
	
Return Value: returns slist_t * to the dest list.
	
Complexity: 
	time: O(1)  / space: O(1) 
---------------------------------------------------------------------------*/
slist_t *SlistAppend(slist_t *dest, slist_t *src);

#endif /* SLIST_H */


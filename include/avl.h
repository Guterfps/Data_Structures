/*-------------------------------------------*/
/* DEVELOPER: Itay Guter                    */
/* LAST MODIFIED: 30/1/2023	               */
/* WORKSHEET NAME: AVL					  */
/* REVIEWER: Shauli				         */
/*--------------------------------------*/

#ifndef __AVL_H__
#define __AVL_H__


#include <sys/types.h> /* ssize_t, size_t */

/*------------------------------------------------------------------------------
AVL tree: a self-balancing binary search tree. It was the first such data 
structure to be invented. In an AVL tree, the heights of the two child subtrees 
of any node differ by at most one; if at any time they differ by more than one, 
rebalancing is done to restore this property. Lookup, insertion, and deletion 
all take O(log n) time in both the average and worst cases, where n is the 
number of nodes in the tree prior to the operation. Insertions and deletions 
may require the tree to be rebalanced by one or more tree rotations.

main functionalities: AVLCreate(), AVLDestroy(), AVLInsert(), AVLRemove(), 
						AVLFind().

------------------------------------------------------------------------------*/
typedef struct avl avl_t;

typedef enum traversal_order
{
	PRE = 0,
	IN,
	POST
}order_t;

/*-----------------------------------------------------------------------------
Description: compares between two elements in the tree(keys).

Parameters: data1 - pointer to element one.
			data2 - pointer to element two.

Return Value: 0 if data1 = data2, 
			  positive if data1 > data2, 
			  negative if data2 > data1.
	  
-----------------------------------------------------------------------------*/
typedef int (*avl_cmp_t)(const void *data1, const void *data2);
/*-----------------------------------------------------------------------------
Description: performs logic on/related to the data in the tree.

Parameters: data - the data in the tree.
			param - some extra parameter.

Return Value: 0 on success, not 0 if it fails. 

note: changing the values of the keys(unique identifiers) of elements may cuse
	  undefined behivior.
	  
-----------------------------------------------------------------------------*/
typedef int (*avl_callback_t)(void *data, void *param);
/*------------------------------------------------------------------------------
Description: creates a new AVL tree

Parameters: cmp - a comperition function to determin the order of nodes in 
					the tree(avl_cmp_t).
			

Return Value: a pointer to the AVL tree, or NULL if it fails.

Complexity: 
	time: O(1) / space: O(1) 
------------------------------------------------------------------------------*/
avl_t *AVLCreate(avl_cmp_t cmp);
/*------------------------------------------------------------------------------
Description: deletes an AVL tree.

Parameters: avl - pointer to an AVL to delete.

Return Value: none.

Complexity: 
	time: O(n) / space: O(1) 
------------------------------------------------------------------------------*/
void AVLDestroy(avl_t *avl);
/*------------------------------------------------------------------------------
Description: inserting new element to the tree.

Parameters: avl - pointer to an AVL tree.
			data - pointer to the new element.

Return Value: 0 on seccessfull insertion, and -1 otherwise.

note: if the element dosent have a unique value(key) the behivior is undefined.
	
Complexity: 
	time: O(log(n)) / space: O(1) 
------------------------------------------------------------------------------*/
int AVLInsert(avl_t *avl, void *data);
/*------------------------------------------------------------------------------
Description: removes an element from the tree.

Parameters:	avl - pointer to an AVL tree.
			data - pointer to a unique value(key) of the element to be removed.

Return Value: none.

note: if the element is not in the tree nothing will be removed.
	
Complexity: 
	time: O(log(n)) / space: O(1) 
------------------------------------------------------------------------------*/
void AVLRemove(avl_t *avl, void *data);
/*------------------------------------------------------------------------------
Description: finds an element in the tree.

Parameters: avl - pointer to an AVL tree.
			data - pointer to a unique value(key) of the element to sereach for.
			found_data - pointer to a variable to hold the found element.
			 
Return Value: returns 1 if the element was found and put it in found_data,
			  returns 0 if the element was not found.

note: if the element was not found, value in found_data is unknown.

Complexity: 
	time: O(log(n))  / space: O(1) 
------------------------------------------------------------------------------*/
int AVLFind(const avl_t *avl, const void *data, void **found_data);
/*------------------------------------------------------------------------------
Description: performs the callback function on every element in the tree.

Parameters: avl - pointer to an AVL tree.
			callback - a callback function of type avl_callback_t.
			param - parameter to be passed to callback.
			order - in which order to perform the callback function. 

Return Value: 0 if all callbacks were successfull, or the return value of the 
			  first	callback that faild.

note:If callback fails in any operation. AVLForEach stops immediatly and returns
	 callback status result.

Complexity:
	time: O(n) / space: O(1) 
------------------------------------------------------------------------------*/
int AVLForEach(avl_t *avl, avl_callback_t callback, void *param, order_t order);
/*------------------------------------------------------------------------------
Description: returns the hieght of the tree(root node).

Parameters: avl - pointer to an AVL tree.

Return Value: the height of the tree, or -1 if the tree is empty.

Complexity: 
	time: O(1) / space: O(1) 
------------------------------------------------------------------------------*/
ssize_t AVLGetHeight(const avl_t *avl);
/*------------------------------------------------------------------------------
Description: counts the amount of elements in the tree.

Parameters: avl - pointer to an AVL tree.

Return Value: the amount of elements in the tree.

Complexity: 
	time: O(n) / space: O(1) 
------------------------------------------------------------------------------*/
size_t AVLCount(const avl_t *avl);
/*------------------------------------------------------------------------------
Description: checks if the tree is empty.

Parameters: avl - pointer to an AVL tree.

Return Value: 1 if its empty, and 0 otherwise.

Complexity: 
	time: O(1) / space: O(1) 
------------------------------------------------------------------------------*/
int AVLIsEmpty(const avl_t *avl);

#endif /* __AVL_H__ */


/*-------------------------------------------*/
/* DEVELOPER: Itay Guter                    */
/* LAST MODIFIED: 19/1/2023	               */
/* WORKSHEET NAME: Binary Tree Iterative  */
/* REVIEWER: Matan				         */
/*--------------------------------------*/

#ifndef __ILRD_BST_H__
#define __ILRD_BST_H__

#include <stddef.h> /* size_t */

/*------------------------------------------------------------------------------
Binary Search Tree:	rooted binary tree data structure with the key of each 
					internal node being greater than all the keys in the 
					respective node's left subtree and less than the ones in 
					its right subtree.

MAIN FUNCTIONALITY: BSTCreate(), BSTDestroy(), BSTInsert(), BSTRemove(), 
					BSTFind().
	
POLICY: Binary search trees allow binary search for fast lookup, addition, 
		and removal of data items.
------------------------------------------------------------------------------*/
/* handler for the Binary search tree */
typedef struct bst bst_t;
/* nodes of the tree */
typedef struct bst_node bst_node_t;
/* iterator for iterating over the tree and handler for elements stored in the 
tree */
typedef bst_node_t *bst_iter_t;

/*-----------------------------------------------------------------------------
Description: compare function for comparing two elements in the tree. 
	
Parameters: data1 - element1 key for comparition.
			data2 - element2 key for comparition.
			
Return Value: positive if data1 > data2, negative if data1 < data2, 
			 and 0 if equal. 
	
-----------------------------------------------------------------------------*/
typedef int (*bst_cmp_t)(const void *data1, const void *data2);
/*-----------------------------------------------------------------------------
Description: function to perform on every element in the tree.
	
Parameters: data - element in the tree.
			param - some parameter for the user if needed.
			
Return Value: 0 on success, and -1 otherwise.
	
-----------------------------------------------------------------------------*/
typedef int (*bst_callback_t)(void *data, void *param);
/*-----------------------------------------------------------------------------
Description: creates a BST.
	
Parameters: cmp - function to determine the order of elements in the tree.

Return Value: handler for the Binary search tree, or NULL if it fails.
	
Complexity: 
	time: O(1)  / space: O(1) 
-----------------------------------------------------------------------------*/
bst_t *BSTCreate(bst_cmp_t cmp);
/*-----------------------------------------------------------------------------
Description: deletes a BST.
	
Parameters: bst - handler of a BST.
		
Return Value: none.
		
Complexity: 
	time: O(n)  / space: O(1) 
-----------------------------------------------------------------------------*/
void BSTDestroy(bst_t *bst);
/*-----------------------------------------------------------------------------
Description: inserting an element to the BST.
		
Parameters: bst - handler of a BST.
			data - element to be inserted. 
	
Return Value: iterator to the new element, or to the end of the tree(BSTEnd())
				if it fails.

note: elements must have unique keys(to compare between), otherwise the 
		behivior is undefined.
		
Complexity: 
	time: average - O(log(n)) ,worst - O(n)  / space: O(1) 
-----------------------------------------------------------------------------*/
bst_iter_t BSTInsert(bst_t *bst, void *data);
/*-----------------------------------------------------------------------------
Description: deletes an element from the tree.
		
Parameters:	where - iterator of the element to be deleted.
	
Return Value: none.

note: if where is iterator to the end of tree the behivior is undefined.
note: after using BSTRemove() previous iterators may be unvalid.
		
Complexity: 
	time: average - O(log(n)) ,worst - O(n)  / space: O(1) 
-----------------------------------------------------------------------------*/
void BSTRemove(bst_iter_t where);
/*-----------------------------------------------------------------------------
Description: finds an element in the tree.
		
Parameters: bst - handler of a BST.
			data - value to compare with bst_cmp_t function.
	
Return Value: the iterator to the found element, or the end of the tree if 
				its not in the tree.
		
Complexity: 
	time: average - O(log(n)) ,worst - O(n)  / space: O(1) 
-----------------------------------------------------------------------------*/
bst_iter_t BSTFind(const bst_t *bst, const void *data);
/*-----------------------------------------------------------------------------
Description: iterate over the tree to the next bigger element.
		
Parameters:	current - iterator to the current element to iterate from.
	
Return Value: the iterator of the next bigger element.

note: if current is the end of the tree, the behivior is undefined.
		
Complexity: 
	time: average - O(log(n)) ,worst - O(n)  / space: O(1) 
-----------------------------------------------------------------------------*/
bst_iter_t BSTNext(bst_iter_t current);
/*-----------------------------------------------------------------------------
Description: iterate over the tree to the next smaller element.
		
Parameters: current - iterator to the current element to iterate from.
	
Return Value: the iterator of the next smaller element.

note: if current is the begin of the tree, the behivior is undefined.
	
Complexity: 
	time: average - O(log(n)) , worst - O(n)  / space: O(1) 
-----------------------------------------------------------------------------*/
bst_iter_t BSTPrev(bst_iter_t current);
/*-----------------------------------------------------------------------------
Description: checks if two iterators are the same.
		
Parameters:	one - iterator.
			other - iterator.	

Return Value: 1 if they are the same, and 0 otherwise.
		
Complexity: 
	time: O(1)  / space: O(1) 
-----------------------------------------------------------------------------*/
int BSTIsEqual(bst_iter_t one, bst_iter_t other);
/*-----------------------------------------------------------------------------
Description: finds the smallest element in the tree.
		
Parameters: bst - handler of a BST.
	
Return Value: the smallest element in the tree, and the end of the tree if 
				the tree is empty.
		
Complexity: 
	time: average - O(log(n)) ,worst - O(n) / space: O(1) 
-----------------------------------------------------------------------------*/
bst_iter_t BSTBegin(const bst_t *bst);
/*-----------------------------------------------------------------------------
Description: returns the end of the tree.
		
Parameters: bst - handler of a BST.
	
Return Value: end of the tree.
		
Complexity: 
	time: O(1) / space: O(1) 
-----------------------------------------------------------------------------*/
bst_iter_t BSTEnd(const bst_t *bst);
/*-----------------------------------------------------------------------------
Description: performing the callback function on every element in the tree 
			from "from" to "to"(not include).
		
Parameters: from - iterator to element to start from.
			to - iterator to element to stop at.
			callback - function to perform(see bst_callback_t for more info).
			param - parameter to pass to callback().
	
Return Value: returns 0 if all callbacks were successful, and -1 if at least
				one fail.
		
Complexity: 
	time: avg - O(nlog(n)), worst - (O(n^2)) / space: O(1) 
-----------------------------------------------------------------------------*/
int BSTForEach(bst_iter_t from, bst_iter_t to, bst_callback_t callback,
																	void *param);
/*-----------------------------------------------------------------------------
Description: counts the amount of elements in the tree.
		
Parameters: bst - handler of a BST.
	
Return Value: size_t elements.
		
Complexity: 
	time: avg - O(nlog(n)), worst - (O(n^2)) / space: O(1)  
-----------------------------------------------------------------------------*/
size_t BSTCount(const bst_t *bst);
/*-----------------------------------------------------------------------------
Description: checks if a tree is empty.
		
Parameters: bst - handler of a BST.
	
Return Value: 1 if empty, and 0 otherwise.
		
Complexity: 
	time: O(1) / space: O(1) 
-----------------------------------------------------------------------------*/
int BSTIsEmpty(const bst_t *bst);
/*-----------------------------------------------------------------------------
Description: get the value of an element in the tree.
		
Parameters: iter - iterator to the element.
	
Return Value: the value of the element.

note: if iter is end of tree, the behivior is undefined.
		
Complexity: 
	time: O(1) / space: O(1) 
-----------------------------------------------------------------------------*/
void *BSTGetVal(bst_iter_t iter);

#endif /* __ILRD_BST_H__ */


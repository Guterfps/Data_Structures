/*-------------------------------------------*/
/* DEVELOPER: Itay Guter                    */
/* LAST MODIFIED: 19/1/2023	               */
/* WORKSHEET NAME: Binary Tree Iterative  */
/* REVIEWER: Matan				         */
/*--------------------------------------*/

#include <stdlib.h>	/* malloc(), free() */
#include <assert.h>	/* assert() */

#include "ilrd_bst.h"	/* function declerations and typedefs */


struct bst
{
	bst_node_t *root;
	bst_cmp_t cmp;
};

struct bst_node
{
	bst_node_t *parent;
	bst_node_t *right;
	bst_node_t *left;
	void *data;
};

enum status
{
	SUCCESS = 0
};

static void *InitBst(bst_t *bst, bst_cmp_t cmp);
static bst_iter_t NodeToIter(bst_node_t *node);
static bst_node_t *IterToNode(bst_iter_t iter);
static bst_node_t *CreateNode(void *data);
#ifndef NDEBUG
static bst_iter_t FindEnd(bst_node_t *current);
#endif
static void UpdateParent(bst_node_t *parent, bst_node_t *new_child, 
												bst_node_t *old_child);
static void UpdateSuccessor(bst_node_t *Successor);

bst_t *BSTCreate(bst_cmp_t cmp)
{
	bst_t *new_bst = NULL;
	
	assert(NULL != cmp);
	
	new_bst = (bst_t *)malloc(sizeof(bst_t));
	if (NULL == new_bst)
	{
		return NULL;
	}
	
	if (NULL == InitBst(new_bst, cmp))
	{
		free(new_bst);
		new_bst = NULL;
	}
	
	return new_bst;
}

void BSTDestroy(bst_t *bst)
{	
	bst_node_t *runner = NULL;
	
	assert(NULL != bst);
	
	runner = bst->root;
	
	while (NULL != runner)
	{	
		if (NULL != runner->left)
		{
			runner = runner->left;
		}
		else if (NULL != runner->right)
		{
			runner = runner->right;
		}
		else
		{
			bst_node_t *parent = runner->parent;
			UpdateParent(parent, NULL, runner);	
			free(runner);
			runner = parent;
		}
	}
	
	free(bst);
	bst = NULL;
}

bst_iter_t BSTInsert(bst_t *bst, void *data)
{
	bst_node_t *runner = NULL;
	bst_node_t *new_node = NULL;
	
	assert(NULL != bst);
	
	runner = bst->root;
	
	new_node = CreateNode(data);
	if (NULL == new_node)
	{
		return BSTEnd(bst);
	}
	
	if (NULL == runner->left)
	{
		runner->left = new_node;
		new_node->parent = bst->root;
		return NodeToIter(new_node);
	}
	
	runner = runner->left;
	
	while (NULL != runner)
	{
		bst_node_t *parent = runner;
		
		assert(0 != bst->cmp(new_node->data, runner->data));
		
		if (0 > bst->cmp(new_node->data, runner->data))
		{
			if (NULL == (runner = runner->left))
			{
				parent->left = new_node;
				new_node->parent = parent;
			}
		}
		else if (0 < bst->cmp(new_node->data, runner->data))
		{
			if (NULL == (runner = runner->right))
			{
				parent->right = new_node;
				new_node->parent = parent;
			}
		}
	}
	
	return (NodeToIter(new_node));
}

void BSTRemove(bst_iter_t where)
{
	bst_node_t *node = NULL;
	
	assert(NULL != IterToNode(where));
	assert(!BSTIsEqual(where, FindEnd(where)));
	
	node = IterToNode(where);
	
	if ((NULL == node->left) && (NULL == node->right))
	{
		UpdateParent(node->parent, NULL, node);
	}
	else if (NULL == node->right)
	{
		UpdateParent(node->parent, node->left, node);
		node->left->parent = node->parent;
	}
	else if(NULL == node->left)
	{
		UpdateParent(node->parent, node->right, node);
		node->right->parent = node->parent;
	}
	else
	{
		bst_node_t *in_order_suces = IterToNode(BSTNext(NodeToIter(node)));
		node->data = in_order_suces->data;
		UpdateSuccessor(in_order_suces);
		node = in_order_suces;
	}
	
	free(node);
	node = NULL;
}

bst_iter_t BSTFind(const bst_t *bst, const void *data)
{
	bst_node_t *runner = NULL;
	
	assert(NULL != bst);
	
	if (BSTIsEmpty(bst))
	{
		return (BSTEnd(bst));
	}
	
	runner = bst->root->left;
	
	while (NULL != runner && (0 != bst->cmp(runner->data, data)))
	{
		if (bst->cmp(runner->data, data) > 0)
		{
			runner = runner->left;
		}
		else
		{
			runner = runner->right;
		}
	}
	
	return (runner ? NodeToIter(runner) : BSTEnd(bst));
}

void *BSTGetVal(bst_iter_t iter)
{
	assert(NULL != IterToNode(iter));
	assert(!BSTIsEqual(iter, FindEnd(iter)));
	
	return ((IterToNode(iter))->data);
}

int BSTIsEqual(bst_iter_t one, bst_iter_t other)
{
	assert(NULL != IterToNode(one));
	assert(NULL != IterToNode(other));
	
	return (one == other);
}

int BSTIsEmpty(const bst_t *bst)
{
	assert(NULL != bst);
	
	return (NULL == bst->root->left);
}

size_t BSTCount(const bst_t *bst)
{
	bst_iter_t runner = {NULL};
	bst_iter_t eot = {NULL};
	size_t counter = 0;
	
	assert(NULL != bst);
	
	eot = BSTEnd(bst);
	
	for (runner = BSTBegin(bst); !BSTIsEqual(runner, eot); 
		runner = BSTNext(runner), ++counter)
		{/* empty loop */}
	
	return counter;
}

bst_iter_t BSTBegin(const bst_t *bst)
{
	bst_node_t *smallest = NULL;
	
	assert(NULL != bst);
	
	smallest = bst->root;
	
	while (NULL != smallest->left)
	{
		smallest = smallest->left;
	}
	
	return (NodeToIter(smallest));
}

bst_iter_t BSTEnd(const bst_t *bst)
{
	assert(NULL != bst);
	
	return (NodeToIter(bst->root));
}

bst_iter_t BSTNext(bst_iter_t current)
{
	bst_node_t *runner = NULL;
	
	assert(NULL != IterToNode(current));
	assert(!BSTIsEqual(current, FindEnd(current)));
	
	runner = IterToNode(current);
	
	if (NULL != runner->right)
	{
		runner = runner->right;

		while (NULL != runner->left)
		{
			runner = runner->left;
		}
	}
	else
	{
		while ((NULL != runner->parent->parent) && 
				(runner->parent->left != runner))
		{
			runner = runner->parent;
		}
		runner = runner->parent;
	}
	
	return (NodeToIter(runner));
}

bst_iter_t BSTPrev(bst_iter_t current)
{
	bst_node_t *runner = NULL;
	
	assert(NULL != IterToNode(current));
	
	runner = IterToNode(current);
	
	if (NULL != runner->left)
	{
		runner = runner->left;
		
		while (NULL != runner->right)
		{
			runner = runner->right;
		}
	}
	else
	{
		while ((NULL != runner->parent->parent) && 
				(runner->parent->right != runner))
		{
			runner = runner->parent;
		}
		runner = runner->parent;
	}
	
	return  (NodeToIter(runner));
}

int BSTForEach(bst_iter_t from, bst_iter_t to, 
				bst_callback_t callback, void *param)
{
	bst_iter_t runner = {NULL};
	int status = SUCCESS;
	
	assert(NULL != IterToNode(from));
	assert(NULL != IterToNode(to));
	assert(NULL != callback);
	
	for (runner = from ;(!BSTIsEqual(runner, to)) && 
		(SUCCESS == (status =  callback((IterToNode(runner))->data, param)));
		runner = BSTNext(runner)) 
		{/* empty loop */}
	
	return status;
}


static bst_iter_t NodeToIter(bst_node_t *node)
{
	assert(NULL != node);
	
	return ((bst_iter_t)node);
}

static bst_node_t *IterToNode(bst_iter_t iter)
{
	assert(NULL != iter);
	
	return ((bst_node_t *)iter);
}

static bst_node_t *CreateNode(void *data)
{
	bst_node_t *new_node = NULL;
	
	new_node = (bst_node_t *)malloc(sizeof(bst_node_t));
	if (NULL == new_node)
	{
		return NULL;
	}
	
	new_node->data = data;
	new_node->left = NULL;
	new_node->right = NULL;
	
	return new_node;
}

#ifndef NDEBUG
static bst_iter_t FindEnd(bst_node_t *current)
{
	assert(NULL != current);
	
	while (NULL != current->parent)
	{
		current = current->parent;
	}
	
	return (NodeToIter(current));
}
#endif

static void UpdateParent(bst_node_t *parent, bst_node_t *new_child, 
												bst_node_t *old_child)
{
	if (NULL != parent)
	{
		if ((NULL != parent->left) && 
			BSTIsEqual(NodeToIter(old_child), NodeToIter(parent->left)))
		{
			parent->left = new_child;
		}
		else
		{
			parent->right = new_child;
		}
	}	
}

static void UpdateSuccessor(bst_node_t *Successor)
{
	assert(NULL != Successor);
	
	if (NULL != Successor->right)
	{
		Successor->right->parent = Successor->parent;
	}
	UpdateParent(Successor->parent, Successor->right, Successor);
}

static void *InitBst(bst_t *bst, bst_cmp_t cmp)
{
	bst_node_t *dummy = NULL;
	
	assert(NULL != bst);
	
	dummy = CreateNode(bst);
	if (NULL == dummy)
	{
		return NULL;
	}
	
	dummy->parent = NULL;
	
	bst->root = dummy;
	bst->cmp = cmp;
	
	return bst;
}


/*-------------------------------------------*/
/* DEVELOPER: Itay Guter                    */
/* LAST MODIFIED: 30/1/2023	               */
/* WORKSHEET NAME: AVL					  */
/* REVIEWER: Shauli				         */
/*--------------------------------------*/

#include <assert.h>	/* assert() */
#include <stdlib.h>	/* malloc() */

#include "avl.h"	/* function declerations and typedefs */

#define MAX(a, b) (((a) > (b)) ? (a) : (b))

typedef struct node node_t;

enum status
{
	SUCCESS = 0,
	FAIL = -1
};

enum bool
{
	NOT_FOUND = 0,
	FOUND = 1
};

struct avl
{
	node_t *root;
	avl_cmp_t cmp;
};

enum childs
{
	LEFT = 0,
	RIGHT,
	NUM_OF_CHILDES
};

struct node
{
	void *data;
	size_t height;
	node_t *child[NUM_OF_CHILDES];
};

typedef enum
{
	LL = 0,
	LR,
	RR,
	RL,
	NONE,
	NUM_OF_ROTATES
} rotate_type_t;

/* utility functions */
static void InitAvl(avl_t *avl, avl_cmp_t cmp);
static node_t *NewNode(void *data);
static size_t GetHeight(node_t *node);
static void UpdateHeight(node_t *node);
static int GetBalanceFactor(node_t *node);
static int CountFunc(void *data, void *param);
static void DeletePostOrder(node_t *root);

/* rotate functions */
static node_t *RotateRight(node_t *node);
static node_t *RotateLeft(node_t *node);
static node_t *HandleRotation(node_t *node);
static rotate_type_t CheckRotateType(node_t *node);

/* recursive functions */
static node_t *RecInsert(node_t *node, avl_cmp_t cmp, node_t *new_node);
static node_t *RecFind(node_t *node, const void *data, avl_cmp_t cmp);
static node_t *RecRemove(node_t *node, void *data, avl_cmp_t cmp);

/* remove utility functions */
static node_t *OneOrZeroChild(node_t *node);
static void TwoChildren(node_t *node, avl_cmp_t cmp);
static node_t *HandleRemove(node_t *node, avl_cmp_t cmp);
static node_t *MinNode(node_t *node);

/* traversal orders */
static int PostOrder(node_t *root, avl_callback_t callback, 
									void *param, int *status);
static int PreOrder(node_t *root, avl_callback_t callback, 
									void *param, int *status);
static int InOrder(node_t *root, avl_callback_t callback, 
									void *param, int *status);

avl_t *AVLCreate(avl_cmp_t cmp)
{
	avl_t *new_avl = NULL;
	
	assert(NULL != cmp);
	
	new_avl = (avl_t *)malloc(sizeof(avl_t));
	if (NULL == new_avl)
	{
		return NULL;
	}
	
	InitAvl(new_avl, cmp);
	
	return new_avl;
}

void AVLDestroy(avl_t *avl)
{
	assert(NULL != avl);
	
	DeletePostOrder(avl->root);
	
	free(avl);
	avl = NULL;
}

int AVLInsert(avl_t *avl, void *data)
{
	node_t *new_node = NULL;
	
	assert(NULL != avl);
	
	new_node = NewNode(data);
	if (NULL == new_node)
	{
		return FAIL;
	}
	
	avl->root = RecInsert(avl->root, avl->cmp, new_node);
	
	return SUCCESS;
}

void AVLRemove(avl_t *avl, void *data)
{
	assert(NULL != avl);
	
	avl->root = RecRemove(avl->root, data, avl->cmp);
}

int AVLFind(const avl_t *avl, const void *data, void **found_data)
{
	node_t *found_node = NULL;
	
	assert(NULL != avl);
	assert(NULL != found_data);
	
	found_node = RecFind(avl->root, data, avl->cmp);
	if (NULL == found_node)
	{
		return NOT_FOUND;
	}
	*found_data = found_node->data;
	
	return FOUND;
}

int AVLForEach(avl_t *avl, avl_callback_t callback, void *param, order_t order)
{
	int status = SUCCESS;
	
	assert(NULL != avl);
	assert(NULL != callback);
	
	switch (order)
	{
		case PRE:
			PreOrder(avl->root, callback, param, &status);
			break;
		case IN:
			InOrder(avl->root, callback, param, &status);
			break;
		case POST:
			PostOrder(avl->root, callback, param, &status);
			break;
		default:
			break;
	}
	
	return status;
}

size_t AVLCount(const avl_t *avl)
{
	size_t counter = 0;
	
	assert(NULL != avl);
	
	AVLForEach((avl_t *)avl, &CountFunc, &counter, IN);
	
	return counter;
}

ssize_t AVLGetHeight(const avl_t *avl)
{
	assert(NULL != avl);
	
	return ((ssize_t)GetHeight(avl->root) - 1);
}

int AVLIsEmpty(const avl_t *avl)
{
	assert(NULL != avl);
	
	return (NULL == avl->root);
}

static void InitAvl(avl_t *avl, avl_cmp_t cmp)
{
	assert(NULL != avl);
	assert(NULL != cmp);
	
	avl->root = NULL;
	avl->cmp = cmp;
}

static node_t *NewNode(void *data)
{
	node_t *new_node = NULL;
	
	assert(NULL != data);
	
	new_node = (node_t *)malloc(sizeof(node_t));
	if (NULL == new_node)
	{
		return NULL;
	}
	
	new_node->data = data;
	new_node->child[LEFT] = NULL;
	new_node->child[RIGHT] = NULL;
	new_node->height = 1;
	
	return new_node;
}

static size_t GetHeight(node_t *node)
{	
	return ((NULL != node) ? (node->height) : 0);
}

static node_t *RotateRight(node_t *node)
{
	node_t *left_child = NULL;
	node_t *left_right_child = NULL;
	
	assert(NULL != node);
	assert(NULL != node->child[LEFT]);
	
	left_child = node->child[LEFT];
	left_right_child = left_child->child[RIGHT];
	
	left_child->child[RIGHT] = node;
	node->child[LEFT] = left_right_child;
	
	UpdateHeight(node);
	UpdateHeight(left_child);

	return 	left_child;
}

static node_t *RotateLeft(node_t *node)
{
	node_t *right_child = NULL;
	node_t *right_left_child = NULL;
	
	assert(NULL != node);
	assert(NULL != node->child[RIGHT]);
	
	right_child = node->child[RIGHT];
	right_left_child = right_child->child[LEFT];
	
	right_child->child[LEFT] = node;
	node->child[RIGHT] = right_left_child;
	
	UpdateHeight(node);
	UpdateHeight(right_child);
	
	return right_child;
}

static void UpdateHeight(node_t *node)
{
	assert(NULL != node);
	
	node->height = MAX(GetHeight(node->child[LEFT]), 
					   GetHeight(node->child[RIGHT])) + 1;
}

static int GetBalanceFactor(node_t *node)
{
	assert(NULL != node);
	
	return (GetHeight(node->child[LEFT]) - GetHeight(node->child[RIGHT]));
}

static node_t *RecInsert(node_t *node, avl_cmp_t cmp, node_t *new_node)
{
	int direction = 0;
	
	assert(NULL != cmp);
	assert(NULL != new_node);
	
	if (NULL == node)
	{
		return new_node;
	}
	
	assert(0 != cmp(node->data, new_node->data));
	
	direction = (0 > cmp(node->data, new_node->data));
	node->child[direction] = RecInsert(node->child[direction], 
													cmp, new_node);
	
	return (HandleRotation(node));
}

static node_t *RecFind(node_t *node, const void *data, avl_cmp_t cmp)
{
	int child_indx = 0;
	
	if (NULL == node || (0 == cmp(node->data, data)))
	{
		return node;
	}
	
	child_indx = (0 > cmp(node->data, data));
	
	return RecFind(node->child[child_indx], data, cmp);
}

static void DeletePostOrder(node_t *root)
{
	if (NULL == root)
	{
		return;
	}
	
	DeletePostOrder(root->child[LEFT]);
	DeletePostOrder(root->child[RIGHT]);
	
	free(root);
	root = NULL;
}

static int PostOrder(node_t *root, avl_callback_t callback, 
									void *param, int *status)
{	
	assert(NULL != callback);
	
	if (NULL == root)
	{
		return SUCCESS;
	}
	if (SUCCESS != *status)
	{
		return *status;
	}
	
	*status = PostOrder(root->child[LEFT], callback, param, status);
	*status = PostOrder(root->child[RIGHT], callback, param, status);
	
	return callback(root->data, param);
}

static int PreOrder(node_t *root, avl_callback_t callback, 
									void *param, int *status)
{
	assert(NULL != callback);
	
	if (NULL == root)
	{
		return SUCCESS;
	}
	if (SUCCESS != *status)
	{
		return *status;
	}
	
	*status = callback(root->data, param);
	*status = PreOrder(root->child[LEFT], callback, param, status);
	*status = PreOrder(root->child[RIGHT], callback, param, status);
	
	return *status;
}

static int InOrder(node_t *root, avl_callback_t callback, 
									void *param, int *status)
{
	assert(NULL != callback);
	
	if (NULL == root)
	{
		return SUCCESS;
	}
	if (SUCCESS != *status)
	{
		return *status;
	}
	
	*status = InOrder(root->child[LEFT], callback, param, status);
	*status = callback(root->data, param);
	*status = InOrder(root->child[RIGHT], callback, param, status);
	
	return *status;
}

static node_t *RecRemove(node_t *node, void *data, avl_cmp_t cmp)
{
	assert(NULL != cmp);
	
	if (NULL == node)
	{
		return node;
	}
	
	if (0 != cmp(node->data, data))
	{
		int child_indx = (0 > cmp(node->data, data));
		node->child[child_indx] = RecRemove(node->child[child_indx], data, cmp);
	}
	else
	{
		node = HandleRemove(node, cmp);
	}
	
	return (HandleRotation(node));
}

static node_t *HandleRemove(node_t *node, avl_cmp_t cmp)
{
	assert(NULL != node);
	assert(NULL != cmp);
	
	if ((NULL == node->child[LEFT]) || (NULL == node->child[RIGHT]))
	{
		node = OneOrZeroChild(node);
	}
	else
	{
		TwoChildren(node, cmp);
	}
	
	return node;
}

static node_t *OneOrZeroChild(node_t *node)
{
	node_t *temp = NULL;
	
	assert(NULL != node);
	
	temp = node->child[LEFT] ? node->child[LEFT] : node->child[RIGHT];
	if (NULL == temp)
	{
		temp = node;
		node = NULL;
	}
	else
	{
		*node = *temp;
	}
	free(temp);
	temp = NULL;
	
	return node;
}

static void TwoChildren(node_t *node, avl_cmp_t cmp)
{
	node_t *in_ord_sucs = NULL;
	
	assert(NULL != node);
	assert(NULL != cmp);
	
	in_ord_sucs = MinNode(node->child[RIGHT]);
	node->data = in_ord_sucs->data;
	node->child[RIGHT] = RecRemove(node->child[RIGHT], in_ord_sucs->data, cmp);
}

static node_t *HandleRotation(node_t *node)
{
	node_t *rotated_node = node;
	
	if (NULL == node)
	{
		return rotated_node;
	}
	
	UpdateHeight(node);
	
	switch (CheckRotateType(node))
	{
		case LR:
			node->child[LEFT] = RotateLeft(node->child[LEFT]);
			/* FALLTHRU */
		case LL:
			rotated_node = RotateRight(node);
			break;
		case RL:
			node->child[RIGHT] = RotateRight(node->child[RIGHT]);
			/* FALLTHRU */
		case RR:
			rotated_node = RotateLeft(node);
			break;
		default:
			break;
	}
	
	return rotated_node;
}

static rotate_type_t CheckRotateType(node_t *node)
{
	rotate_type_t rotate_type = NONE;
	int balance = 0;
	
	assert(NULL != node);
	
	balance = GetBalanceFactor(node);
	
	if (1 < balance)
	{
		rotate_type = (0 > GetBalanceFactor(node->child[LEFT])) ? LR : LL;
	}
	
	if (-1 > balance)
	{
		rotate_type = (0 < GetBalanceFactor(node->child[RIGHT])) ? RL : RR;
	}
	
	return rotate_type;
}

static node_t *MinNode(node_t *node)
{
	assert(NULL != node);
	
	while (NULL != node->child[LEFT])
	{
		node = node->child[LEFT];
	}
	
	return node;
}

static int CountFunc(void *data, void *param)
{
	*(size_t *)param += 1;
	(void)data;
	
	return SUCCESS;
}


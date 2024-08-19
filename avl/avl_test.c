/*-------------------------------------------*/
/* DEVELOPER: Itay Guter                    */
/* LAST MODIFIED: 30/1/2023	               */
/* WORKSHEET NAME: AVL					  */
/* REVIEWER: Shauli				         */
/*--------------------------------------*/

#include <stdio.h>	/* printf() */
#include <stdlib.h>	/*srand(), rand()*/
#include <time.h>	/*time()*/

#include "avl.h"	/* function declerations and typedefs */

#define ARR_LEN 10
#define COUNT 10

typedef struct node node_t;
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

int CmpFunc(const void *data1, const void *data2);
int CallBack(void *data, void *param);

void Test(void);

void InitArr(int *arr, size_t len);
void print2D(struct node* root);

int main(void)
{
	Test();
	
	return 0;
}

void Test(void)
{
	avl_t *avl = AVLCreate(&CmpFunc);
	int data[ARR_LEN] = {0};
	size_t len = sizeof(data) / sizeof(*data);
	int status = 0;
	size_t i = 0;
	int *found = NULL; 
	int find_test = 100000;
	
	srand(time(NULL));
	
	InitArr(data, len);
	
	printf("is empty test:	");
	AVLIsEmpty(avl) ? printf("SUCCESS ✅️\n") : printf("FAIL ❌️\n");
	printf("count test:	");
	(0 == AVLCount(avl)) ? printf("SUCCESS ✅️\n") : printf("FAIL ❌️\n");
	printf("hight test:	");
	printf("%ld, ", AVLGetHeight(avl));
	(-1 == AVLGetHeight(avl)) ? printf("SUCCESS ✅️\n") : printf("FAIL ❌️\n");
	
	
	for (i = 0; (i < len) && (0 == status); ++i)
	{
		status = AVLInsert(avl, data + i);
	}
	
	printf("insert test:	");
	(0 == status) ? printf("SUCCESS ✅️\n") : printf("FAIL ❌️\n");
	printf("is empty test:	");
	!AVLIsEmpty(avl) ? printf("SUCCESS ✅️\n") : printf("FAIL ❌️\n");
	printf("hight test:	");
	printf("%ld, ", AVLGetHeight(avl));
	(3 == AVLGetHeight(avl)) ? printf("SUCCESS ✅️\n") : printf("FAIL ❌️\n");
	printf("count test:	");
	(ARR_LEN == AVLCount(avl)) ? printf("SUCCESS ✅️\n") : printf("FAIL ❌️\n");
	
	for (i = 0; (i < len) && (0 == status); ++i)
	{
		status = !AVLFind(avl, data + i, (void **)&found);
		status = !(*found == *(data + i));
	}
	
	printf("find test:	");
	(0 == AVLFind(avl, &find_test, (void **)&found)) ?
	printf("SUCCESS ✅️, ") : printf("FAIL ❌️, ");
	(0 == status) ? printf("SUCCESS ✅️\n") : printf("FAIL ❌️\n");
	
	print2D(avl->root);
	
	printf("remove 1 test:	");
	AVLRemove(avl, &find_test);
	AVLRemove(avl, data);
	(0 == AVLFind(avl, data, (void **)&found)) ?
	printf("SUCCESS ✅️\n") : printf("FAIL ❌️\n");
	AVLRemove(avl, data);
	
	printf("remove half:	");
	for (i = 1; (i < (len / 2)) && (0 == status); ++i)
	{
		AVLRemove(avl, data + i);
		status = !(0 == AVLFind(avl, data + i, (void **)&found));
	}
	
	(0 == status) ? printf("SUCCESS ✅️\n") : printf("FAIL ❌️\n");
	printf("is empty test:	");
	!AVLIsEmpty(avl) ? printf("SUCCESS ✅️\n") : printf("FAIL ❌️\n");
	printf("count test:	");
	((ARR_LEN - (len / 2)) == AVLCount(avl)) ? 
	printf("SUCCESS ✅️\n") : printf("FAIL ❌️\n");
	printf("hight test:	");
	printf("%ld, ", AVLGetHeight(avl));
	(2 == AVLGetHeight(avl)) ? printf("SUCCESS ✅️\n") : printf("FAIL ❌️\n");
	
	for (i = 0; (i < len / 2) && (0 == status); ++i)
	{
		status = AVLInsert(avl, data + i);
	}
	
	printf("insert half test:	");
	(0 == status) ? printf("SUCCESS ✅️\n") : printf("FAIL ❌️\n");
	printf("hight test:	");
	printf("%ld, ", AVLGetHeight(avl));
	(3 == AVLGetHeight(avl)) ? printf("SUCCESS ✅️\n") : printf("FAIL ❌️\n");
	printf("count test:	");
	(ARR_LEN == AVLCount(avl)) ? printf("SUCCESS ✅️\n") : printf("FAIL ❌️\n");
	
	printf("remove half:	");
	for (i = 0; (i < (len / 2)) && (0 == status); ++i)
	{
		AVLRemove(avl, data + i);
		status = !(0 == AVLFind(avl, data + i, (void **)&found));
	}
	(0 == status) ? printf("SUCCESS ✅️\n") : printf("FAIL ❌️\n");
	printf("hight test:	");
	printf("%ld, ", AVLGetHeight(avl));
	(2 == AVLGetHeight(avl)) ? printf("SUCCESS ✅️\n") : printf("FAIL ❌️\n");
	
	print2D(avl->root);
	
	for (i = len / 2; (i < len) && (0 == status); ++i)
	{
		AVLRemove(avl, data + i);
		status = !(0 == AVLFind(avl, data + i, (void **)&found));
	}
	
	printf("remove all test:	");
	(0 == status) ? printf("SUCCESS ✅️\n") : printf("FAIL ❌️\n");
	
	printf("is empty test:	");
	AVLIsEmpty(avl) ? printf("SUCCESS ✅️\n") : printf("FAIL ❌️\n");
	printf("count test:	");
	(0 == AVLCount(avl)) ? printf("SUCCESS ✅️\n") : printf("FAIL ❌️\n");
	printf("hight test:	");
	printf("%ld, ", AVLGetHeight(avl));
	(-1 == AVLGetHeight(avl)) ? printf("SUCCESS ✅️\n") : printf("FAIL ❌️\n");
	
	AVLDestroy(avl);
	avl = NULL;
}

int CmpFunc(const void *data1, const void *data2)
{
	return (*(int *)data1 - *(int *)data2);
}

int CallBack(void *data, void *param)
{
	printf("%d, ", *(int *)data);
	(void)param;
	
	return 0;
}

void InitArr(int *arr, size_t len)
{
	size_t i = 0;
	
	for (i = 0; i < len; ++i)
	{
		arr[i] = rand() % 10000;
	}
}

void print2DUtil(node_t* root, int space)
{
    int i = 0;
    /* Base case */
    if (root == NULL)
        return;
 
    /* Increase distance between levels */
    space += COUNT;
 
    /* Process right child first*/
    print2DUtil(root->child[RIGHT], space);
 
    /* Print current node after space */
    /* count */
    printf("\n");
    for (i = COUNT; i < space; ++i)
    {
        printf(" ");
    }
    printf("%d\n", *(int *)root->data);
 
    /* Process left child*/
    print2DUtil(root->child[LEFT], space);
}
 
/* Wrapper over print2DUtil() */
void print2D(node_t* root)
{
    /* Pass initial space count as 0*/
    print2DUtil(root, 0);
}


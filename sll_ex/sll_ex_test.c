/*-------------------------------------------*/
/* DEVELOPER: Itay Guter                    */
/* LAST MODIFIED: 11/12/2022               */
/* WORKSHEET NAME: SLL Exercises	      */
/* REVIEWER: Sveta		                 */
/*--------------------------------------*/

#include <stdio.h>		/*printf()*/
#include <assert.h>		/*assert()*/
#include <stdlib.h>		/*malloc()*/

#include "sll_ex.h"		/*function declerations and typedefs*/

node_t *PushNode(node_t *head, void *data);
void DestroyList(node_t *head);
void PrintList(node_t *head);


int main(void)
{
	int a = 1;
	int b = 2;
	int c = 3;
	int d = 4;
	int num1 = 1;
	int num2 = 2;
	node_t *head = NULL;
	node_t *test_node = NULL;
	node_t *head2 = NULL;
	node_t *test_node2 = NULL;
	node_t *test_intersection = NULL;
	
	
	head = PushNode(head, &a);
	PushNode(head, &b);
	test_node2 = PushNode(head, &c);
	PushNode(head, &d);
	test_node = head;
	
	PrintList(head);
	head = Flip(head);
	PrintList(head);
	(head->data == &a) ? printf("SUCCESS\n") : printf("FAIL\n");
	
	printf("Hasloop: %d ", HasLoop(head));
	HasLoop(head) ?  printf(" FAIL\n") : printf(" SUCCESS\n");
	test_node->next = head;
	printf("Hasloop: %d ", HasLoop(head));
	HasLoop(head) ?  printf(" SUCCESS\n") : printf(" FAIL\n");
	test_node->next = NULL;
	
	head2 = PushNode(head2, &num1);
	PushNode(head2, &num2);
	test_intersection = FindIntersection(head, head2);
	printf("intersection: ");
	(NULL == test_intersection) ? printf(" SUCCESS\n") : 
								  printf(" FAIL\n");
	head2->next->next = test_node2;
	test_intersection = FindIntersection(head, head2);
	PrintList(head);
	PrintList(head2);
	printf("intersection: ");
	(test_intersection == test_node2) ? printf(" SUCCESS\n") : 
										printf(" FAIL\n");
	free(head2->next);
	head2->next = NULL;
	free(head2);
	head2 = NULL;
	
	DestroyList(head);

	return 0;
}

node_t *PushNode(node_t *head, void *data)
{
	node_t *new_node = NULL;
	
	assert(NULL != data);
	
	new_node = (node_t *)malloc(sizeof(node_t));
	if (NULL == new_node)
	{
		return NULL;
	}
	
	if (NULL == head)
	{
		new_node->data = data;
		new_node->next = NULL;
	}
	else
	{
		new_node->data = head->data;
		new_node->next = head->next;
		head->data = data;
		head->next = new_node;
	}
	
	return new_node;
}

void DestroyList(node_t *head)
{
	node_t *temp_node = NULL;
	
	assert(NULL != head);
	
	while (NULL != head)
	{
		temp_node = head;
		head = head->next;
		free(temp_node);
		temp_node = NULL;
	}
}

void PrintList(node_t *head)
{
	assert(NULL != head);
	
	while (NULL != head)
	{
		printf("%d", *(int *)(head->data));
		head = head->next;
	}
	printf("\n");
}



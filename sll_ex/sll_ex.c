/*-------------------------------------------*/
/* DEVELOPER: Itay Guter                    */
/* LAST MODIFIED: 11/12/2022               */
/* WORKSHEET NAME: SLL Exercises	      */
/* REVIEWER: Sveta		                 */
/*--------------------------------------*/

#include <stddef.h>		/*size_t*/
#include <assert.h>		/*assert()*/

#include "sll_ex.h"		/*function declerations and typedefs*/

enum bool
{
	FALSE,
	TRUE = 1
};

static size_t CountList(node_t *head);

node_t *Flip(node_t *head)
{
	node_t *runer_node = NULL;
	node_t *temp_next = NULL;
	node_t *current_node = NULL;
	
	assert(NULL != head);
	
	current_node = head;
	
	while (NULL != current_node)
	{
		temp_next = current_node->next;
		current_node->next = runer_node;
		runer_node = current_node;
		current_node = temp_next;
	}
	
	return runer_node;
}

int HasLoop(const node_t *head)
{
	const node_t *fast_node = NULL;
	const node_t *slow_node = NULL;
	
	assert(NULL != head);
	
	fast_node = head;
	slow_node = head;
	
	while (NULL != fast_node && NULL != slow_node && NULL != fast_node->next)
	{
		slow_node = slow_node->next;
		fast_node = fast_node->next->next;
		
		if (slow_node == fast_node)
		{
			return TRUE;
		}
	}
	
	return FALSE;
}

node_t *FindIntersection(node_t *head_1, node_t *head_2)
{
	size_t counter1 = 0;
	size_t counter2 = 0;
	size_t dif = 0;
	node_t *long_list = NULL;
	node_t *Short_list = NULL;
	
	assert(NULL != head_1);
	assert(NULL != head_2);
	
	counter1 = CountList(head_1);
	counter2 = CountList(head_2);
	
	if (counter1 > counter2)
	{
		dif = counter1 - counter2;
		long_list = head_1;
		Short_list = head_2;
	}
	else
	{
		dif = counter2 - counter1;
		long_list = head_2;
		Short_list = head_1;
	}
	
	while (0 != dif)
	{
		long_list = long_list->next;
		--dif;
	}
	
	while (NULL != long_list && long_list != Short_list)
	{
		long_list = long_list->next;
		Short_list = Short_list->next;
	}
	
	return long_list;
}

static size_t CountList(node_t *head)
{
	size_t counter = 0;
	node_t *runer = NULL;
	
	assert(NULL != head);
	
	runer = head;
	
	while (NULL != runer)
	{
		++counter;
		runer = runer->next;
	}

	return counter;
}



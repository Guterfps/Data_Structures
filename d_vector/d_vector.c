/*****************************************/
/*   Developer: Itay Guter	           	 */
/*   Project: Vector		 	         */				         
/*   Date: 04/12/22		            	 */
/*	Reviewer: Eliran                     */
/*****************************************/

#include <stddef.h>		/*size_t*/
#include <assert.h>		/*assert()*/
#include <stdlib.h>		/*calloc(), free()*/
#include <string.h>		/*memcopy()*/

#include "d_vector.h"	/*function declaraitions and typedefs*/

#define RESIZE_MULTY 2
#define NEEDS_TO_GROW(size, cap) (size == cap)
#define MIN_RESIZE_CAP(size, cap) ((4 * size) <= cap) 

struct vector
{
	size_t size;
	size_t cap;
	size_t element_size;
	char *data;
};

vector_t *VectorCreate(size_t capacity, size_t element_size)
{
	vector_t *vector = (vector_t *)malloc(sizeof(vector_t) + 
										element_size * capacity);
	if (NULL == vector)
	{
		return NULL;
	}
	
	vector->size = 0;
	vector->cap = capacity;
	vector->element_size = element_size;
	vector->data = (char *)(vector + 1);
	
	return vector;
}

void VectorDestroy(vector_t *vector)
{
	assert(NULL != vector);
	
	free(vector);
	vector = NULL;
}

vector_t *VectorPushBack(vector_t *vector, const void *element)
{
	char *index_ptr = NULL;
	
	assert(NULL != vector);
	assert(NULL != element);
	
	index_ptr = vector->data + vector->size * vector->element_size;
	memcpy(index_ptr, element, vector->element_size);
	++(vector->size);
	
	if (NEEDS_TO_GROW(vector->size, vector->cap))
	{
		vector = VectorResize(vector, vector->cap * RESIZE_MULTY);
		if (NULL == vector)
		{
			return NULL;
		}
	}
	
	return vector;
}

vector_t *VectorPopBack(vector_t *vector)
{
	char *index_ptr = NULL;
		
	assert(NULL != vector);
	
	--(vector->size);
	index_ptr = vector->data + vector->size * vector->element_size;
	memset(index_ptr, 0, vector->element_size);
	
	if (MIN_RESIZE_CAP(vector->size, vector->cap))
	{
		vector = VectorResize(vector, vector->cap / RESIZE_MULTY);
		if (NULL == vector)
		{
			return NULL;
		}
	}
	
	return vector;
}

void *VectorGetAccessElement(const vector_t *vector, size_t index)
{
	char *element_ptr = NULL;
	
	assert(NULL != vector);
	assert(index < vector->size);
	
	element_ptr = vector->data + index * vector->element_size;
	
	return element_ptr;
}

size_t VectorSize(const vector_t *vector)
{
	assert(NULL != vector);
	
	return (vector->size);
}

size_t VectorCapacity(const vector_t *vector)
{
	assert(NULL != vector);
	
	return (vector->cap);
}

vector_t *VectorResize(vector_t *vector, size_t new_capacity)
{
	vector_t *temp_vector = NULL;
	
	assert(NULL != vector);
	assert(new_capacity > vector->size);
	
	temp_vector = vector;	
	temp_vector = (vector_t *)realloc(vector, sizeof(vector_t) +
								 	new_capacity * vector->element_size);
	if (NULL == temp_vector)
	{
		return NULL;
	}
	vector = temp_vector;
	vector->cap = new_capacity;
	vector->data = (char *)(vector + 1);
	
	return vector;
}



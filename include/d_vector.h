/*****************************************/
/*   Developer: Itay Guter	           	 */
/*   Project: Vector		 	         */				         
/*   Date: 04/12/22		            	 */
/*	Reviewer: Eliran                     */
/*****************************************/

#ifndef D_VECTOR_H
#define D_VECTOR_H

#include <stddef.h>	/*size_t*/

/************************struct*****************************/

typedef struct vector vector_t;

/******************Function Declarations********************/

/*time:O(1)  / space:O(n) */ 
vector_t *VectorCreate(size_t capacity, size_t element_size);
/*---------------------------------------------------------------------------
Description- creats a vector of same "element_size" elements,
and has initial capacity of "capacity", by allocating memory.

Return Value - vector_t * to the new vector or NULL on fail.
---------------------------------------------------------------------------*/

/*time:O(1)  / space:O(1) */
void VectorDestroy(vector_t *vector);
/*---------------------------------------------------------------------------
Description- deletes a vector_t and free the memory allocaated for it.

Return Value - non.
---------------------------------------------------------------------------*/

/*time:amortized - O(1) / space: amortized - O(n) */ 
vector_t *VectorPushBack(vector_t *vector, const void *element);
/*---------------------------------------------------------------------------
Description- recives an element to be pushed into a vector after the last 
element. pointer to the vector needs to be saved after every push.
capacity may increase by grow factor, if resize fails
user needs to resize before using push again.

Return Value - vector_t * to the current vector or NULL on fail..
---------------------------------------------------------------------------*/

/*time: amortized - O(1)  / space: amortized - O(n) */ 
vector_t *VectorPopBack(vector_t *vector);
/*---------------------------------------------------------------------------
Description- pops the last element pushed to the vector, 
if there are no elements undifined behivior. 
pointer to the vector needs to be saved after every pop.
capacity may decrease by grow factor, if resize fails
user needs to resize before using pop again.

Return Value - vector_t * to the current vector or NULL on fail..
---------------------------------------------------------------------------*/

/*time:O(1)  / space:O(1) */
void *VectorGetAccessElement(const vector_t *vector, size_t index);
/*---------------------------------------------------------------------------
Description- recives an index and a vector_t and returns the element at 
that index of the vector,if the index is equal or bigger then size of 
the vector the behaivior is undifined.

Return Value - void * pointer to the element in the vector.
---------------------------------------------------------------------------*/

/*time:O(1)  / space:O(1) */
size_t VectorSize(const vector_t *vector);
/*---------------------------------------------------------------------------
Description- returns the current size of the vector.

Return Value - size_t.
---------------------------------------------------------------------------*/

/*time:O(1)  / space:O(1) */	
size_t VectorCapacity(const vector_t *vector);
/*---------------------------------------------------------------------------
Description- returns the current capacity of the vector.

Return Value - size_t.
---------------------------------------------------------------------------*/

/*time:amortized - O(1)  / space:O(n) */ 
vector_t *VectorResize(vector_t *vector, size_t new_capacity);
/*---------------------------------------------------------------------------
Description- resizes the vector and gives it a new capacity, if new capacity
is equal or smaller then current size of the vector the behivior is undifined.
pointer to the vector needs to be saved after every Resize and if 
Resize fails returns NULL.

Return Value - vector_t * to the vector or NULL on fail..
---------------------------------------------------------------------------*/

#endif 		/* VECTOR_H */




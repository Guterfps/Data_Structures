/*****************************************/
/*   Developer: Itay Guter	           	 */
/*   Project: Vector		 	         */				         
/*   Date: 04/12/22		            	 */
/*	 Reviewer: Eliran			          */
/*****************************************/

#include <stdio.h>		/*printf()*/

#include "d_vector.h"	/*function declaraitions and typedefs*/

#define SUCCESS "\xE2\x9C\x93"
#define FAIL "\xe2\x9c\x97"

void TestVector(void);
void TestPush(vector_t **vector, int i);
void TestPop(vector_t **vector);
void TestAccessElement(vector_t *vector, size_t index);
void TestSize(vector_t *vector);
void TestCap(vector_t *vector);

typedef struct test
{
	int i;
	void *p;
	double d;
} test_t;

int main(void)
{
	TestVector();
	return 0;
}

void TestVector(void)
{
	size_t i = 0;
	vector_t *vector = NULL;
	vector = VectorCreate(10, sizeof(test_t));
	vector ? printf("SUCCESS %s\n", SUCCESS) : printf("FAIL %s\n", FAIL);
	TestSize(vector);
	VectorSize(vector) == 0 ? printf("SUCCESS %s\n", SUCCESS) : 
	printf("FAIL %s\n", FAIL);
	TestCap(vector);
	VectorCapacity(vector) == 10 ? printf("SUCCESS %s\n", SUCCESS) : 
	printf("FAIL %s\n", FAIL);
	for (i = 1; i < 13; ++i)
	{
		TestPush(&vector, i);
		TestAccessElement(vector, i - 1);
	}
	TestSize(vector);
	VectorSize(vector) == 12 ? printf("SUCCESS %s\n", SUCCESS) : 
	printf("FAIL %s\n", FAIL);
	TestCap(vector);
	VectorCapacity(vector) == 20 ? printf("SUCCESS %s\n", SUCCESS) :
	 printf("FAIL %s\n", FAIL);
	
	for (i = 12; i > 0; --i)
	{
		TestAccessElement(vector, i - 1);
		TestPop(&vector);
	}
	TestSize(vector);
	VectorSize(vector) == 0 ? printf("SUCCESS %s\n", SUCCESS) : 
	printf("FAIL %s\n", FAIL);
	TestCap(vector);
	VectorCapacity(vector) == 1 ? printf("SUCCESS %s\n", SUCCESS) : 
	printf("FAIL %s\n", FAIL);
	
	vector = VectorResize(vector, 30);
	TestSize(vector);
	VectorSize(vector) == 0 ? printf("SUCCESS %s\n", SUCCESS) : 
	printf("FAIL %s\n", FAIL);
	TestCap(vector);
	VectorCapacity(vector) == 30 ? printf("SUCCESS %s\n", SUCCESS) : 
	printf("FAIL %s\n", FAIL);
	for (i = 1; i < 10; ++i)
	{
		TestPush(&vector, i);
		TestAccessElement(vector, i - 1);
	}
	TestSize(vector);
	VectorSize(vector) == 9 ? printf("SUCCESS %s\n", SUCCESS) : 
	printf("FAIL %s\n", FAIL);
	TestCap(vector);
	VectorCapacity(vector) == 30 ? printf("SUCCESS %s\n", SUCCESS) : 
	printf("FAIL %s\n", FAIL);
	
	for (i = 9; i > 6; --i)
	{
		TestAccessElement(vector, i - 1);
		TestPop(&vector);
	}
	TestSize(vector);
	VectorSize(vector) == 6 ? printf("SUCCESS %s\n", SUCCESS) :
	 printf("FAIL %s\n", FAIL);
	TestCap(vector);
	VectorCapacity(vector) == 15 ? printf("SUCCESS %s\n", SUCCESS) : 
	printf("FAIL %s\n", FAIL);
	vector = VectorResize(vector, 10);
	TestSize(vector);
	VectorSize(vector) == 6 ? printf("SUCCESS %s\n", SUCCESS) : 
	printf("FAIL %s\n", FAIL);
	TestCap(vector);
	VectorCapacity(vector) == 10 ? printf("SUCCESS %s\n", SUCCESS) :
	printf("FAIL %s\n", FAIL);
	
	
	VectorDestroy(vector);
	vector = NULL;
}

void TestPush(vector_t **vector, int i)
{
	test_t test = {0};
	test.d = i;
	
	*vector = VectorPushBack(*vector, &test);
}

void TestPop(vector_t **vector)
{
	*vector = VectorPopBack(*vector);
}

void TestAccessElement(vector_t *vector, size_t index)
{
	test_t element = {0};
	
	element = *(test_t *)VectorGetAccessElement(vector, index);
	printf("element at indx %ld: %.2f\n", index, element.d);
}

void TestSize(vector_t *vector)
{
	printf("size is: %ld 		", VectorSize(vector));
}

void TestCap(vector_t *vector)
{
	printf("capacity is: %ld 	", VectorCapacity(vector));
}



/*-------------------------------------------*/
/* DEVELOPER: Itay Guter                    */
/* LAST MODIFIED: 28/12/2022               */
/* WORKSHEET NAME: Priority Queue	      */
/* REVIEWER: Yuval Atoun		         */
/*--------------------------------------*/

#include <stdio.h>		/* printf() */

#include "c_priority_queue.h"	/* function declerations and typedefs */

typedef struct test
{
	int pr;
	double data;
} test_t;

int CmpFunc(const void *data1, const void *data2);
int IsMatchFunc(const void *data, void *param);

void Test1(void);

int main(void)
{
	Test1();

	return 0;
}

int CmpFunc(const void *data1, const void *data2)
{
	return (((test_t *)data1)->pr - ((test_t *)data2)->pr);
}

int IsMatchFunc(const void *data, void *param)
{
	return (((test_t *)data)->data == ((test_t *)param)->data);
}

void Test1(void)
{
	ilrd_pq_t *pq = PQCreate(&CmpFunc);
	test_t elements[10] = {{1,3.14},{5,1.7},{3,1},{10,123},{12,111},
							{15,69},{0,420},{1,-301},{10,-10},{3,-1}};
	size_t size = sizeof(elements) / sizeof(*elements);
	size_t i = 0;
	int status = 0;
	int priority_test = 1;
	test_t erase_test = {0};
	
	printf("is empty test:	");
	PQIsEmpty(pq) ? printf("SUCCESS ✅️\n") : printf("FAIL ❌️\n");
	
	printf("size test:	");
	(0 == PQSize(pq)) ? printf("SUCCESS ✅️\n") : printf("FAIL ❌️\n");
	
	for (; (i < size) && !status; ++i)
	{
		status = PQEnqueue(pq, elements + i);
	}
	
	printf("enqueue test:	");
	!status ? printf("SUCCESS ✅️\n") : printf("FAIL ❌️\n");
	
	printf("size test:	");
	(size == PQSize(pq)) ? printf("SUCCESS ✅️\n") : printf("FAIL ❌️\n");
	
	printf("is empty test:	");
	!PQIsEmpty(pq) ? printf("SUCCESS ✅️\n") : printf("FAIL ❌️\n");
	
	for (; (i > 1) && priority_test; i -= 2)
	{
		priority_test = (((test_t *)PQDequeue(pq))->pr <= 
												((test_t *)PQDequeue(pq))->pr);
	}
	
	printf("priority test:	");
	priority_test ? printf("SUCCESS ✅️,") : printf("FAIL ❌️,");
	PQIsEmpty(pq) ? printf("SUCCESS ✅️\n") : printf("FAIL ❌️\n");
	
	for (; (i < size) && !status; ++i)
	{
		status = PQEnqueue(pq, elements + i);
	}
	
	printf("dequeue test1:	");
	(elements[6].data == ((test_t *)PQDequeue(pq))->data) ? 
	printf("SUCCESS ✅️\n") : printf("FAIL ❌️\n");
	
	printf("dequeue test2:	");
	(elements[0].data == ((test_t *)PQDequeue(pq))->data) ? 
	printf("SUCCESS ✅️\n") : printf("FAIL ❌️\n");
	
	printf("peek test:	");
	(elements[7].data == ((test_t *)PQPeek(pq))->data) ? 
	printf("SUCCESS ✅️\n") : printf("FAIL ❌️\n");
	
	printf("is empty test:	");
	!PQIsEmpty(pq) ? printf("SUCCESS ✅️\n") : printf("FAIL ❌️\n");
	
	printf("size test:	");
	((size - 2) == PQSize(pq)) ? printf("SUCCESS ✅️\n") : printf("FAIL ❌️\n");
	
	printf("erase test1:	");
	erase_test = *(test_t *)PQErase(pq, (elements + 8), &IsMatchFunc);
	(erase_test.data == elements[8].data) ?
	printf("SUCCESS ✅️,") : printf("FAIL ❌️,");
	(elements[7].data == ((test_t *)PQPeek(pq))->data) ? 
	printf("SUCCESS ✅️,") : printf("FAIL ❌️,");
	((size - 3) == PQSize(pq)) ? printf("SUCCESS ✅️\n") : printf("FAIL ❌️\n");
	
	printf("erase test2:	");
	(NULL == PQErase(pq, (elements + 8), &IsMatchFunc)) ?
	printf("SUCCESS ✅️,") : printf("FAIL ❌️,");
	((size - 3) == PQSize(pq)) ? printf("SUCCESS ✅️\n") : printf("FAIL ❌️\n");
	
	PQClear(pq);
	printf("clear test:	");
	(0 == PQSize(pq)) ? printf("SUCCESS ✅️,") : printf("FAIL ❌️,");
	PQIsEmpty(pq) ? printf("SUCCESS ✅️,") : printf("FAIL ❌️,");
	PQEnqueue(pq, elements);
	PQEnqueue(pq, elements + 1);
	(elements[0].data == ((test_t *)PQPeek(pq))->data) ? 
	printf("SUCCESS ✅️\n") : printf("FAIL ❌️\n");
	
	
	PQDestroy(pq);

}

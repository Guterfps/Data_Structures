/*-------------------------------------------*/
/* DEVELOPER: Itay Guter                    */
/* LAST MODIFIED: 7/2/2023	               */
/* WORKSHEET NAME: Heap				      */
/* REVIEWER: Gali		                 */
/*--------------------------------------*/

#include <stdio.h>	/* printf() */

#include "heap.h"	/* function declerations and typedefs */

void Test(void);

int CmpFunc(const void *heap_data, const void *new_data, void *param);
int IsMatch(const void *data, void *param);


int main(void)
{
	Test();
	
	return 0;
}

void Test(void)
{
	heap_t *heap = HeapCreate(&CmpFunc, NULL);
	int arr[] = {2,-10,-5,-4,0,-1,2,0,3,-4,0,-1};
	int sort_arr[] = {-10,-4,-4,-1,-1,0,0,2,2,3};
	size_t len = sizeof(arr) / sizeof(*arr);
	int status = 0;
	size_t i = 0;
	int remove_test = 1;
	int remove_test2 = -2;
	
	printf("is empty test:	");
	HeapIsEmpty(heap) ? printf("SUCCESS ✅️\n") : printf("FAIL ❌️\n");
	printf("size test:	");
	(0 == HeapSize(heap)) ? printf("SUCCESS ✅️\n") : printf("FAIL ❌️\n");
	
	for (; i < len; ++i)
	{
		status += HeapPush(heap, arr + i);
	}
	
	printf("push test:	");
	(0 == status) ? printf("SUCCESS ✅️, ") : printf("FAIL ❌️, ");
	(-10 == *(int *)HeapPeek(heap)) ? 
	printf("SUCCESS ✅️\n") : printf("FAIL ❌️\n");
	printf("%d\n", *(int *)HeapPeek(heap));
	printf("is empty test:	");
	!HeapIsEmpty(heap) ? printf("SUCCESS ✅️\n") : printf("FAIL ❌️\n");
	printf("size test:	");
	(len == HeapSize(heap)) ? printf("SUCCESS ✅️\n") : printf("FAIL ❌️\n");
	
	HeapPush(heap, &remove_test);
	
	printf("size test:	");
	((len + 1) == HeapSize(heap)) ? 
	printf("SUCCESS ✅️\n") : printf("FAIL ❌️\n");
	
	printf("remove test:	");
	(1 == *(int *)HeapRemove(heap, &remove_test, &IsMatch, NULL)) ?
	printf("SUCCESS ✅️, ") : printf("FAIL ❌️, ");
	(NULL == HeapRemove(heap, &remove_test, &IsMatch, NULL)) ?
	printf("SUCCESS ✅️\n") : printf("FAIL ❌️\n");
	
	HeapPush(heap, &remove_test2);
	
	printf("remove test:	");
	(-2 == *(int *)HeapRemove(heap, &remove_test2, &IsMatch, NULL)) ?
	printf("SUCCESS ✅️, ") : printf("FAIL ❌️, ");
	(NULL == HeapRemove(heap, &remove_test2, &IsMatch, NULL)) ?
	printf("SUCCESS ✅️\n") : printf("FAIL ❌️\n");
	
	printf("remove test:	");
	(arr[4] == *(int *)HeapRemove(heap, arr + 4, &IsMatch, NULL)) ?
	printf("SUCCESS ✅️\n") : printf("FAIL ❌️\n");
	
	
	printf("remove test:	");
	(arr[2] == *(int *)HeapRemove(heap, arr + 2, &IsMatch, NULL)) ?
	printf("SUCCESS ✅️, ") : printf("FAIL ❌️, ");
	(NULL == HeapRemove(heap, arr + 2, &IsMatch, NULL)) ?
	printf("SUCCESS ✅️\n") : printf("FAIL ❌️\n");
	
	printf("size test:	");
	((len - 2) == HeapSize(heap)) ? 
	printf("SUCCESS ✅️\n") : printf("FAIL ❌️\n");
	
	status = 1;
	for (i = 0; (i < len - 3) && status; ++i)
	{
		status = (sort_arr[i] == *(int *)HeapPop(heap));
	}
	
	printf("pop test:	");
	status ? printf("SUCCESS ✅️, ") : printf("FAIL ❌️, ");
	(3 == *(int *)HeapPeek(heap)) ? 
	printf("SUCCESS ✅️\n") : printf("FAIL ❌️\n");
	printf("%d\n", *(int *)HeapPeek(heap));
	printf("is empty test:	");
	!HeapIsEmpty(heap) ? printf("SUCCESS ✅️\n") : printf("FAIL ❌️\n");
	printf("size test:	");
	(1 == HeapSize(heap)) ? printf("SUCCESS ✅️\n") : printf("FAIL ❌️\n");
	
	printf("pop test:	");
	(3 == *(int *)HeapPop(heap)) ?
	printf("SUCCESS ✅️\n") : printf("FAIL ❌️\n");
	printf("is empty test:	");
	HeapIsEmpty(heap) ? printf("SUCCESS ✅️\n") : printf("FAIL ❌️\n");
	printf("size test:	");
	(0 == HeapSize(heap)) ? printf("SUCCESS ✅️\n") : printf("FAIL ❌️\n");
	
	HeapDestroy(heap);
	heap = NULL;
}

int CmpFunc(const void *heap_data, const void *new_data, void *param)
{
	(void)param;
	
	return (*(int *)heap_data - *(int *)new_data);
}

int IsMatch(const void *data, void *param)
{
	return (*(int *)data == *(int *)param);
}


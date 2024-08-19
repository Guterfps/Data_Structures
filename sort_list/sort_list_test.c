/*-------------------------------------------*/
/* DEVELOPER: Itay Guter                    */
/* LAST MODIFIED: 21/12/2022               */
/* WORKSHEET NAME: Sorted list		      */
/* REVIEWER: Vladimir Levkovich          */
/*--------------------------------------*/

#include <stdio.h>		/*printf()*/

#include "sort_list.h"		/*function decleraitions and typedefs*/

int CmpFunc(const void *data1, const void *data2);
int PrintList(void *data, void *param);
int IsMatchIf(const void *data, void *param);
void Test1(void);
void Test2(void);
void Test3(void);

int main(void)
{
	Test1();
	Test2();
	Test3();

	return 0;
}

int CmpFunc(const void *data1, const void *data2)
{
	
	return (*(int *)data1 - *(int *)data2);
}

int IsMatchIf(const void *data, void *param)
{
	return (0 == (*(int *)data % *(int *)param));
}

void Test1(void)
{
	sort_list_t *list = SortListCreate(CmpFunc);
	int nums[] = {1,-1,3,4,10,-25,42,0};
	size_t len = sizeof(nums) / sizeof(*nums);
	size_t i = 0;
	int param = 5;
	sort_list_iter_t sort_iter = {NULL};
	sort_list_iter_t find_iter = {NULL};
	
	printf("count test:  ");
	(0 == SortListCount(list)) ?
	printf("SUCCESS ✅️\n") : printf("FAIL ❌️\n");
	printf("is empty test:  ");
	SortListIsEmpty(list) ? printf("SUCCESS ✅️\n") : printf("FAIL ❌️\n");
	
	for (; i < len; ++i)
	{
		sort_iter = SortListInsert(list, nums + i);
	}
	
	SortListForEach(SortListBegin(list), SortListEnd(list), &PrintList, &param);
	printf("\n");
	printf("get value + insert test:  ");
	(nums[len - 1] == *(int *)SortListGetVal(sort_iter)) ? 
	printf("SUCCESS ✅️\n") : printf("FAIL ❌️\n");
	printf("count test:  ");
	(i == SortListCount(list)) ?
	printf("SUCCESS ✅️\n") : printf("FAIL ❌️\n");
	printf("is empty test:  ");
	(0 == SortListIsEmpty(list)) ? 
	printf("SUCCESS ✅️\n") : printf("FAIL ❌️\n");
	
	for (; i > 5; --i)
	{
		sort_iter = SortListRemove(sort_iter);
	}
	
	SortListForEach(SortListBegin(list), SortListEnd(list), &PrintList, &param);
	printf("\n");
	
	printf("get value + remove test:  ");
	(nums[3] == *(int *)SortListGetVal(sort_iter)) ? 
	printf("SUCCESS ✅️\n") : printf("FAIL ❌️\n");
	printf("count test:  ");
	(i == SortListCount(list)) ?
	printf("SUCCESS ✅️\n") : printf("FAIL ❌️\n");
	printf("is empty test:  ");
	(0 == SortListIsEmpty(list)) ? 
	printf("SUCCESS ✅️\n") : printf("FAIL ❌️\n");
	
	find_iter = SortListFind(list, SortListBegin(list), SortListEnd(list), 
														nums + 3);
	printf("find test:  ");
	(nums[3] == *(int *)SortListGetVal(find_iter)) ? 
	printf("SUCCESS ✅️\n") : printf("FAIL ❌️\n");
	
	find_iter = SortListFind(list, SortListBegin(list), SortListEnd(list), 
														nums + 5);
	printf("find test:  ");
	(nums[5] == *(int *)SortListGetVal(find_iter)) ? 
	printf("SUCCESS ✅️\n") : printf("FAIL ❌️\n");
	
	find_iter = SortListFind(list, SortListBegin(list), SortListEnd(list), 
														nums + 6);
	printf("find test:  ");
	(nums[6] == *(int *)SortListGetVal(find_iter)) ? 
	printf("SUCCESS ✅️\n") : printf("FAIL ❌️\n");
	
	find_iter = SortListFind(list, SortListBegin(list), SortListEnd(list), 
														nums);
	printf("find + iter is equal test:  ");
	SortListIterIsEqual(find_iter, SortListEnd(list)) ? 
	printf("SUCCESS ✅️\n") : printf("FAIL ❌️\n");
	
	printf("pop front test:  ");
	(nums[5] == *(int *)SortListPopFront(list)) ?
	printf("SUCCESS ✅️\n") : printf("FAIL ❌️\n");
	printf("pop back test:  ");
	(nums[6] == *(int *)SortListPopBack(list)) ?
	printf("SUCCESS ✅️\n") : printf("FAIL ❌️\n");
	printf("count test:  ");
	(i - 2 == SortListCount(list)) ?
	printf("SUCCESS ✅️\n") : printf("FAIL ❌️\n");
	
	find_iter = SortListFindIf(SortListBegin(list), SortListEnd(list), 
								&IsMatchIf, &param);
	printf("findIf test:  ");
	(nums[4] == *(int *)SortListGetVal(find_iter)) ? 
	printf("SUCCESS ✅️\n") : printf("FAIL ❌️\n");							
	
	
	SortListDestroy(list);
}

int PrintList(void *data, void *param)
{
	printf("%d, ", *(int *)data);
	(void)param;
	
	return 0;
}


void Test2(void)
{
	sort_list_t *list1 = SortListCreate(&CmpFunc);
	int nums1[] = {1,-1,3,4,10,10,21,-25,42};
	size_t len1 = sizeof(nums1) / sizeof(*nums1);
	size_t i = 0;
	sort_list_t *list2 = SortListCreate(&CmpFunc);
	int nums2[] = {-100,-252,15,15,10};
	size_t len2 = sizeof(nums2) / sizeof(*nums2);
	int param = 5;
	sort_list_iter_t sort_iter = {NULL};
	int status = 1;
	
	for (; i < len1; ++i)
	{
		SortListInsert(list1, nums1 + i);
	}
	
	for (i = 0; i < len2; ++i)
	{
		SortListInsert(list2, nums2 + i);
	}
	printf("merge test1:  \n");
	SortListForEach(SortListBegin(list1), SortListEnd(list1),
															&PrintList, &param);
	printf("\n");
	
	SortListForEach(SortListBegin(list2), SortListEnd(list2),
															&PrintList, &param);
	printf("\n");
	
	SortListMerge(list1, list2);
	
	SortListForEach(SortListBegin(list1), SortListEnd(list1),
															&PrintList, &param);
	printf("\n");
	
	sort_iter = SortListBegin(list1);
	
	for (i = 0; i < (len1 + len2 - 1); ++i)
	{
		status *= (*(int *)SortListGetVal(SortListNext(sort_iter)) >= 
					*(int *)SortListGetVal(sort_iter));
		sort_iter = SortListNext(sort_iter);
	}
	printf("merge1:  ");
	status ? printf("SUCCESS ✅️\n") : printf("FAIL ❌️\n");
	
	
	SortListDestroy(list1);
	SortListDestroy(list2);
}


void Test3(void)
{
	sort_list_t *list1 = SortListCreate(&CmpFunc);
	int nums1[] = {1,-1,-30,4,-10,-25,42,0, 0};
	size_t len1 = sizeof(nums1) / sizeof(*nums1);
	size_t i = 0;
	sort_list_t *list2 = SortListCreate(&CmpFunc);
	int nums2[] = {10,-1,310,41,2,-2,5,70, 111,-3,15};
	size_t len2 = sizeof(nums2) / sizeof(*nums2);
	int param = 5;
	sort_list_iter_t sort_iter = {NULL};
	int status = 1;
	
	for (; i < len1; ++i)
	{
		SortListInsert(list1, nums1 + i);
	}
	
	for (i = 0; i < len2; ++i)
	{
		SortListInsert(list2, nums2 + i);
	}
	
	printf("merge test2:  \n");
	SortListForEach(SortListBegin(list1), SortListEnd(list1),
															&PrintList, &param);
	printf("\n");
	
	SortListForEach(SortListBegin(list2), SortListEnd(list2),
															&PrintList, &param);
	printf("\n");
	
	SortListMerge(list1, list2);
	
	SortListForEach(SortListBegin(list1), SortListEnd(list1),
															&PrintList, &param);
	printf("\n");
	
	sort_iter = SortListBegin(list1);
	for (i = 0; i < (len1 + len2 - 1); ++i)
	{
		status *= (*(int *)SortListGetVal(SortListNext(sort_iter)) >= 
					*(int *)SortListGetVal(sort_iter));
		sort_iter = SortListNext(sort_iter);
	}
	printf("merge2:  ");
	status ? printf("SUCCESS ✅️\n") : printf("FAIL ❌️\n");
	
	SortListMerge(list1, list2);
	
	sort_iter = SortListBegin(list1);
	for (i = 0; i < (len1 + len2 - 1); ++i)
	{
		status *= (*(int *)SortListGetVal(SortListNext(sort_iter)) >= 
					*(int *)SortListGetVal(sort_iter));
		sort_iter = SortListNext(sort_iter);
	}
	printf("merge3:  ");
	status ? printf("SUCCESS ✅️\n") : printf("FAIL ❌️\n");
	
	SortListMerge(list2, list1);
	
	SortListForEach(SortListBegin(list2), SortListEnd(list2),
															&PrintList, &param);
	printf("\n");
	sort_iter = SortListBegin(list2);
	for (i = 0; i < (len1 + len2 - 1); ++i)
	{
		status *= (*(int *)SortListGetVal(SortListNext(sort_iter)) >= 
					*(int *)SortListGetVal(sort_iter));
		sort_iter = SortListNext(sort_iter);
	}
	printf("merge4:  ");
	status ? printf("SUCCESS ✅️\n") : printf("FAIL ❌️\n");
	
	SortListDestroy(list1);
	SortListDestroy(list2);
}



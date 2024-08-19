/*-------------------------------------------*/
/* DEVELOPER: Itay Guter                    */
/* LAST MODIFIED: 30/12/2022               */
/* WORKSHEET NAME: Task				      */
/* REVIEWER: Dotan Tamir		         */
/*--------------------------------------*/

#include <stdio.h>	/* printf() */
#include <stdlib.h>	/* malloc() */
#include <unistd.h>	/* sleep() */

#include "task.h"	/* function declerations and typedefs */

#define TEST_NUM 10

int Action(void *param);
void Cleanup(void *param);

int main(void)
{
	int *test_int = NULL;
	time_t time_test = time(NULL);
	int i = 1;
	task_t *test = TaskCreate(&Action, &test_int, &Cleanup, &test_int, time_test);
	
	printf("get run time test:	");
	(time_test == TaskGetRunTime(test)) ? 
	printf("SUCCESS ✅️\n") : printf("FAIL ❌️\n");
	
	sleep(1);
	printf("set run time test:	");
	time_test = time(NULL);
	!(time_test == TaskGetRunTime(test)) ? 
	printf("SUCCESS ✅️,") : printf("FAIL ❌️,");
	TaskSetRunTime(test, time_test);
	(time_test == TaskGetRunTime(test)) ? 
	printf("SUCCESS ✅️\n") : printf("FAIL ❌️\n");
	
	printf("execute test:	");
	(0 == TaskExecuteFunc(test)) ?
	printf("SUCCESS ✅️,") : printf("FAIL ❌️,");
	
	for (;i < TEST_NUM; ++i)
	{
		TaskExecuteFunc(test);
	}
	
	((123 + TEST_NUM) == *test_int) ?
	printf("SUCCESS ✅️\n") : printf("FAIL ❌️\n");
	
	printf("get uid test:	");
	!UIDIsEqual(bad_uid, TaskGetUID(test)) ?
	printf("SUCCESS ✅️\n") : printf("FAIL ❌️\n");
	
	
	
	TaskDestroy(test);
	
	return 0;
}


int Action(void *param)
{
	if (NULL == *(int **)param)
	{
		*(int **)param = (int *)malloc(sizeof(100));
		if (NULL == *(int **)param)
		{
			return -1;
		}
		**(int **)param = 123;
	}
	
	++**(int **)param;
	
	return 0;
}

void Cleanup(void *param)
{
	free(*(void **)param);
	*(void **)param = NULL;
}


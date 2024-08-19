/*-------------------------------------------*/
/* DEVELOPER: Itay Guter                    */
/* LAST MODIFIED: 2/1/2023	               */
/* WORKSHEET NAME: Scheduler		      */
/* REVIEWER: Gal Ventura		         */
/*--------------------------------------*/

#include <stdio.h>	/* printf() */
#include <stdlib.h>	/* malloc(), free() */
#include <string.h>	/* strcmp() */

#include "scheduler.h"	/* function declerations and typedefs*/

#define STOP_LEN 5

typedef struct remove_task
{
	scheduler_t *sched;
	ilrd_uid_t uid;
} remove_task_t;

typedef struct stop
{
	scheduler_t *sched;
	FILE *file;
} stop_t;

void Test1(void);
void TestRemoveItself(void);
void TestDynamicStop(void);

int ActionFunc(void *param);
int ActionFunc2(void *param);
int StopFunc(void *param);
int RemoveSelfFunc(void *param);
int StopDynamicFunc(void *param);
int AddTaskFunc(void *param);
void CleanFunc(void *param);
void CleanFunc2(void *param);
void StopCleanFunc(void *param);
int AddedFunc(void *param);

int main(void)
{
	Test1();
	TestRemoveItself();
	TestDynamicStop();
	
	return 0;
}

void Test1(void)
{
	scheduler_t *sched = SchedCreate();
	int test_param1 = 1;
	int test_param2 = 2;
	ilrd_uid_t test_uid = bad_uid;
	int remove_test = 0;
	
	printf("is empty test:	");
	SchedIsEmpty(sched) ? printf("SUCCESS ✅️\n") : printf("FAIL ❌️\n");
	
	printf("size test:	");
	(0 == SchedSize(sched)) ? printf("SUCCESS ✅️\n") : printf("FAIL ❌️\n");
	
	test_uid = SchedAddTask(sched, &ActionFunc, &test_param1, &CleanFunc, 
							&test_param1, time(NULL) + 1);
	printf("add test:	");
	!UIDIsEqual(test_uid, bad_uid) ? 
	printf("SUCCESS ✅️\n") : printf("FAIL ❌️\n");
	
	SchedAddTask(sched, &ActionFunc, &test_param1, &CleanFunc, 
							&test_param1, time(NULL));						
	SchedAddTask(sched, &ActionFunc, &test_param2, &CleanFunc, 
							&test_param2, time(NULL) + 1);
	
	printf("is empty test:	");
	!SchedIsEmpty(sched) ? printf("SUCCESS ✅️\n") : printf("FAIL ❌️\n");
	
	printf("size test:	");
	(3 == SchedSize(sched)) ? printf("SUCCESS ✅️\n") : printf("FAIL ❌️\n");
	
	printf("remove test:	");
	remove_test = SchedRemoveTask(sched, test_uid);
	remove_test ? printf("SUCCESS ✅️,") : printf("FAIL ❌️,");
	remove_test = SchedRemoveTask(sched, test_uid);
	!remove_test ? printf("SUCCESS ✅️\n") : printf("FAIL ❌️\n");
	
	printf("size test:	");
	(2 == SchedSize(sched)) ? printf("SUCCESS ✅️\n") : printf("FAIL ❌️\n");
	
	printf("simple run test:	");
	!SchedRun(sched) ? printf("SUCCESS ✅️\n") : printf("FAIL ❌️\n");
	
	printf("is empty test:	");
	SchedIsEmpty(sched) ? printf("SUCCESS ✅️\n") : printf("FAIL ❌️\n");
	
	SchedAddTask(sched, &ActionFunc, &test_param1, &CleanFunc, 
							&test_param1, time(NULL));						
	SchedAddTask(sched, &ActionFunc, &test_param2, &CleanFunc, 
							&test_param2, time(NULL) + 1);
	printf("clear test:	");
	(2 == SchedSize(sched)) ? printf("SUCCESS ✅️,") : printf("FAIL ❌️,");
	SchedClearTasks(sched);
	(0 == SchedSize(sched)) ? printf("SUCCESS ✅️\n") : printf("FAIL ❌️\n");
	
	SchedAddTask(sched, &ActionFunc, &test_param1, &CleanFunc, 
							&test_param1, time(NULL));
	SchedAddTask(sched, &StopFunc, sched, &CleanFunc, 
							&test_param1, time(NULL) + 1);						
	SchedAddTask(sched, &ActionFunc, &test_param2, &CleanFunc, 
							&test_param2, time(NULL) + 2);
	SchedAddTask(sched, &ActionFunc, &test_param2, &CleanFunc, 
							&test_param2, time(NULL) + 2);
							
	printf("stop test:	");
	!SchedRun(sched) ? printf("SUCCESS ✅️,") : printf("FAIL ❌️,");
	(2 == SchedSize(sched)) ? printf("SUCCESS ✅️,") : printf("FAIL ❌️,");
	!SchedRun(sched) ? printf("SUCCESS ✅️,") : printf("FAIL ❌️,");
	SchedIsEmpty(sched) ? printf("SUCCESS ✅️\n") : printf("FAIL ❌️\n");
	
	printf("task adds another task:	");
	SchedAddTask(sched, &AddTaskFunc, sched, &CleanFunc, 
							sched, time(NULL));
	SchedAddTask(sched, &ActionFunc, &test_param1, &CleanFunc, 
							&test_param1, time(NULL));
	SchedAddTask(sched, &ActionFunc, &test_param2, &CleanFunc, 
							&test_param2, time(NULL) + 2);
	!SchedRun(sched) ? printf("SUCCESS ✅️\n") : printf("FAIL ❌️\n");
	
	SchedDestroy(sched);
}

void TestRemoveItself(void)
{
	scheduler_t *sched = SchedCreate();
	int test_param1 = 1;
	int *test_param2 = NULL;
	remove_task_t test_task = {0};
	
	test_task.sched = sched;
	
	SchedAddTask(sched, &ActionFunc, &test_param1, &CleanFunc, 
							&test_param1, time(NULL));
	test_task.uid = SchedAddTask(sched, &RemoveSelfFunc, &test_task, &CleanFunc, 
													&test_task, time(NULL));						
	SchedAddTask(sched, &ActionFunc2, &test_param2, &CleanFunc2, 
							&test_param2, time(NULL) + 1);
	SchedAddTask(sched, &ActionFunc2, &test_param2, &CleanFunc2, 
							&test_param2, time(NULL) + 1);
	
	printf("task remove itself test:	");
	!SchedRun(sched) ? printf("SUCCESS ✅️\n") : printf("FAIL ❌️\n");
	
	printf("is empty test:	");
	SchedIsEmpty(sched) ? printf("SUCCESS ✅️\n") : printf("FAIL ❌️\n");
	test_task.uid = SchedAddTask(sched, &RemoveSelfFunc, &test_task, &CleanFunc, 
													&test_task, time(NULL) + 2);
	printf("task remove itself test2:	");
	!SchedRun(sched) ? printf("SUCCESS ✅️\n") : printf("FAIL ❌️\n");
	
	SchedDestroy(sched);
}

void TestDynamicStop(void)
{
	scheduler_t *sched = SchedCreate();
	int test_param1 = 1;
	stop_t stop = {0};
	
	stop.sched = sched;
	stop.file = NULL;
	
	SchedAddTask(sched, &ActionFunc, &test_param1, &CleanFunc, 
							&test_param1, time(NULL));
	SchedAddTask(sched, &ActionFunc, &test_param1, &CleanFunc, 
							&test_param1, time(NULL) + 5);
	SchedAddTask(sched, &ActionFunc, &test_param1, &CleanFunc, 
							&test_param1, time(NULL) + 10);
	SchedAddTask(sched, &StopDynamicFunc, &stop, &StopCleanFunc, 
							&stop, time(NULL));
	
	printf("dynamic stop test:	\n");
	!SchedRun(sched) ? printf("SUCCESS ✅️\n") : printf("FAIL ❌️\n");
	printf("size of sched after stop: %ld\n", SchedSize(sched));
	!SchedRun(sched) ? printf("SUCCESS ✅️\n") : printf("FAIL ❌️\n");
	
	SchedDestroy(sched);
}

int RemoveSelfFunc(void *param)
{	
	if (SchedRemoveTask(((remove_task_t *)param)->sched, 
							((remove_task_t *)param)->uid))
	{
		return 0;
	}
	else {return -1;}
}

int ActionFunc(void *param)
{
	
	printf("%d, ", *(int *)param);
	
	if (3 != *(int *)param)
	{
		 ++*(int *)param;
	}
	else
	{
		return 0;
	}
	
	return 1;
}

int ActionFunc2(void *param)
{
	if (NULL == *(int **)param)
	{
		*(int **)param = (int *)malloc(sizeof(int));
		if (NULL == *(int **)param)
		{
			return -1;
		}
		**(int **)param = 10;
	}
	
	printf("%d, ", **(int **)param);
	
	if (12 != **(int **)param)
	{
		 ++**(int **)param;
	}
	else
	{
		return 0;
	}
	
	return 1;
}

void CleanFunc(void *param)
{
	(void)param;
}

void CleanFunc2(void *param)
{
	free(*(void **)param);
	*(void **)param = NULL;
}

int StopFunc(void *param)
{
	SchedStop(param);
	
	return 0;
}

int StopDynamicFunc(void *param)
{
	char stop[STOP_LEN] = {0};
	
	((stop_t *)param)->file = fopen("stopfile.txt","r");
	if (NULL == ((stop_t *)param)->file)
	{
		return -1;
	}

	fscanf(((stop_t *)param)->file, "%s", stop);
	
	if (0 == strcmp(stop, "stop"))
	{
		SchedStop(((stop_t *)param)->sched);
	}
	
	if (EOF == fclose(((stop_t *)param)->file))
	{
		return -1;
	}
	((stop_t *)param)->file = NULL;
	
	if (1 == SchedSize(((stop_t *)param)->sched))
	{
		return 0;
	}
	
	return 1;
}

void StopCleanFunc(void *param)
{
	if (NULL != ((stop_t *)param)->file)
	{
		fclose(((stop_t *)param)->file);
	}
}

int AddTaskFunc(void *param)
{
	static int num_of_exec = 0;
	
	SchedAddTask(param, &AddedFunc, (void *)0, &CleanFunc, 
							NULL, time(NULL));
	SchedAddTask(param, &AddedFunc, (void *)1, &CleanFunc, 
							NULL, time(NULL) + 1);
	SchedAddTask(param, &AddedFunc, (void *)-2, &CleanFunc, 
							NULL, time(NULL) - 2);
	
	return (num_of_exec ? 0 : ++num_of_exec);
}

int AddedFunc(void *param)
{
	printf("added %d, ", *(int *)&param);
	
	return 0;
}




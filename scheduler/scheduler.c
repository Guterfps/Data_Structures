/*-------------------------------------------*/
/* DEVELOPER: Itay Guter                    */
/* LAST MODIFIED: 2/1/2023	               */
/* WORKSHEET NAME: Scheduler		      */
/* REVIEWER: Gal Ventura		         */
/*--------------------------------------*/

#include <stdlib.h>	/* malloc(), free() */
#include <assert.h>	/* assert() */
#include <unistd.h>	/* sleep() */

#include "scheduler.h"	/* function declerations and typedefs*/
#include "Heap_PQ.h"	/* priority queue data structure */
#include "task.h"	/* task lib */

struct scheduler
{
	ilrd_pq_t *pq;
	int stop_flag;
};

enum run_status
{
	RUN,
	STOP = 1
};

static int CmpTasks(const void *data1, const void *data2);
static int IsMatch(const void *data, void *param);
static void TaskManage(scheduler_t *sched, task_t *task, int *status,  
						int temp_status);

scheduler_t *SchedCreate(void)
{
	scheduler_t *new_scheduler = (scheduler_t *)malloc(sizeof(scheduler_t));
	if (NULL == new_scheduler)
	{
		return NULL;
	}
	
	new_scheduler->pq = PQCreate(&CmpTasks);
	if (NULL == new_scheduler->pq)
	{
		free(new_scheduler);
		new_scheduler = NULL;
		return NULL;
	}
	
	new_scheduler->stop_flag = 0;
	
	return new_scheduler;
}

void SchedDestroy(scheduler_t *sched)
{
	assert(NULL != sched);
	
	SchedClearTasks(sched);
	
	PQDestroy(sched->pq);
	free(sched);
	sched = NULL;
}

ilrd_uid_t SchedAddTask(scheduler_t *sched, sched_action_func_t action_func, 
						void *action_param, sched_cleanup_func_t cleanup_func, 
						void *cleanup_param, time_t run_time)
{
	task_t *new_task = NULL;
	
	assert(NULL != sched);
	assert(NULL != action_func);
	assert(NULL != cleanup_func);
	assert(-1 != run_time);
	
	new_task = TaskCreate(action_func, action_param, 
							cleanup_func, cleanup_param, run_time);
	if (NULL == new_task)
	{
		return bad_uid;
	}
	
	if (PQEnqueue(sched->pq, new_task))
	{
		TaskDestroy(new_task);
		return bad_uid;
	}
	
	return (TaskGetUID(new_task));
}

int SchedRemoveTask(scheduler_t *sched, ilrd_uid_t uid)
{
	task_t *task_to_remove = NULL;
	
	assert(NULL != sched);
	assert(!UIDIsEqual(uid, bad_uid));
	
	task_to_remove = PQErase(sched->pq, &uid, &IsMatch);
	if (NULL == task_to_remove)
	{
		return 0;
	}
	
	TaskDestroy(task_to_remove);
	
	return 1;
}

int SchedRun(scheduler_t *sched)
{
	task_t *task = NULL;
	int status = 0;
	int temp_status = 0;
	time_t current_time = 0;
	time_t time_to_sleep = 0;
	ilrd_uid_t temp_uid = bad_uid;
	
	assert(NULL != sched);
	
	sched->stop_flag = RUN;
	
	while (!PQIsEmpty(sched->pq) && (RUN == sched->stop_flag))
	{
		current_time = time(NULL);
		if (-1 == current_time)
		{
			return -1;
		}
		
		task = PQPeek(sched->pq);
		time_to_sleep = TaskGetRunTime(task) - current_time;
		time_to_sleep = (0 > time_to_sleep) ? 0 :  time_to_sleep;
		
		while (0 != (time_to_sleep = sleep(time_to_sleep))) {/* empty loop */}
		
		temp_uid = TaskGetUID(task);
		temp_status = TaskExecuteFunc(task);
		
		if (PQErase(sched->pq, &temp_uid, &IsMatch))
		{
			TaskManage(sched, task, &status, temp_status);
		}	
	}
	
	return status;
}

int SchedIsEmpty(const scheduler_t *sched)
{
	assert(NULL != sched);
	
	return (PQIsEmpty(sched->pq));
}

size_t SchedSize(const scheduler_t *sched)
{
	assert(NULL != sched);
	
	return (PQSize(sched->pq));
}

void SchedClearTasks(scheduler_t *sched)
{
	assert(NULL != sched);
	
	while (!PQIsEmpty(sched->pq))
	{
		TaskDestroy(PQDequeue(sched->pq));
	}
}

void SchedStop(scheduler_t *sched)
{
	assert(NULL != sched);
	
	sched->stop_flag = STOP;
}

static int CmpTasks(const void *data1, const void *data2)
{
	assert(NULL != data1);
	assert(NULL != data2);
	
	return (TaskGetRunTime(data1) - TaskGetRunTime(data2));
}

static int IsMatch(const void *data, void *param)
{
	assert(NULL != data);
	assert(NULL != param);
	
	return (UIDIsEqual(TaskGetUID(data), *(ilrd_uid_t *)param));
}

static void TaskManage(scheduler_t *sched, task_t *task, int *status,  
						int temp_status)
{
	if (0 < temp_status)
	{
		TaskSetRunTime(task, TaskGetRunTime(task) + temp_status);
		if (1 == PQEnqueue(sched->pq, task))
		{
			--(*status);
			TaskDestroy(task);
		}
	}
	else
	{
		*status += temp_status;
		TaskDestroy(task);
	}
}


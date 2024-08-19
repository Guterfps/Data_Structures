/*-------------------------------------------*/
/* DEVELOPER: Itay Guter                    */
/* LAST MODIFIED: 30/12/2022               */
/* WORKSHEET NAME: Task				      */
/* REVIEWER: Dotan Tamir		         */
/*--------------------------------------*/

#include <stdlib.h>	/* malloc() */
#include <assert.h>	/* assert() */

#include "task.h"	/* function declerations and typedefs */

struct task 
{
	task_action_func_t action;
	void *action_param;
	task_cleanup_func_t cleanup;
	void *cleanup_param;
	time_t run_time;
	ilrd_uid_t uid;
};

static void InitTask(task_t *task, 
					task_action_func_t action_func, void *action_param,
					task_cleanup_func_t cleanup_func, void *cleanup_param,
                   	time_t run_time);

task_t *TaskCreate(task_action_func_t action_func, void *action_param,
                   task_cleanup_func_t cleanup_func, void *cleanup_param,
                   time_t run_time)
{
	task_t *new_task = NULL;
	
	assert(NULL != action_func);
	assert(NULL != cleanup_func);
	assert(-1 != run_time);
	
	new_task = (task_t *)malloc(sizeof(task_t));
	if (NULL == new_task)
	{
		return NULL;
	}
	
	new_task->uid = UIDGenerate();
	
	if (UIDIsEqual(new_task->uid, bad_uid))
	{
		free(new_task);
		new_task = NULL;
		return NULL;
	}
	
	InitTask(new_task, action_func, action_param, cleanup_func, cleanup_param,
				run_time);
	
	return new_task;
}

void TaskDestroy(task_t *task)
{
	assert(NULL != task);
	
	task->cleanup(task->cleanup_param);
	
	free(task);
	task = NULL;
}

time_t TaskGetRunTime(const task_t *task)
{
	assert(NULL != task);
	
	return (task->run_time);
}

void TaskSetRunTime(task_t *task, time_t run_time)
{
	assert(NULL != task);
	assert(-1 != run_time);
	
	task->run_time = run_time;
}

int TaskExecuteFunc(const task_t *task)
{
	assert(NULL != task);
	
	return (task->action(task->action_param));
}

ilrd_uid_t TaskGetUID(const task_t *task)
{
	assert(NULL != task);
	
	return (task->uid);
}


static void InitTask(task_t *task, 
					task_action_func_t action_func, void *action_param,
					task_cleanup_func_t cleanup_func, void *cleanup_param,
                   	time_t run_time)
{
	assert(NULL != task);
	assert(NULL != action_func);
	assert(NULL != cleanup_func);
	assert(-1 != run_time);
	
	task->action = action_func;
	task->action_param = action_param;
	task->cleanup = cleanup_func;
	task->cleanup_param = cleanup_param;
	task->run_time = run_time;
}

                   	

/*-------------------------------------------*/
/* DEVELOPER: Itay Guter                    */
/* LAST MODIFIED: 30/12/2022               */
/* WORKSHEET NAME: Task				      */
/* REVIEWER: Dotan Tamir		         */
/*--------------------------------------*/

#ifndef __TASK_H__
#define __TASK_H__

#include <time.h> /* time_t */

#include "uid.h" /* ilrd_uid_t */

/*-----------------------------------------------------------------------------
intro: a task to preform with a time to run and a UID.

main functionalitis: TaskCreate, TaskDestroy, TaskExecuteFunc.

personal note: in my opinion this is a confusing design and it would have been
				much more clear and intuitive to add an task_setup_func_t or
				task_resources_func_t.
-----------------------------------------------------------------------------*/
typedef struct task task_t;

/*-----------------------------------------------------------------------------
Description: an action to be preformed as part of the task.

Parameters: param - anything the function needs.

Return Value: up to the user, usualy 0 on success and -1 otherwise.

-----------------------------------------------------------------------------*/
typedef int(*task_action_func_t)(void *param);

/*-----------------------------------------------------------------------------
Description: cleans the resources that the actions of "task_action_func_t" used.

Parameters: param - anything the function needs.

Return Value: none

-----------------------------------------------------------------------------*/
typedef void(*task_cleanup_func_t)(void *param);  

/*-----------------------------------------------------------------------------
Description: creates a new task.

Parameters: action_func - function to execute on TaskExecuteFunc().
			action_param - parameter to send to action_func().
			cleanup_func - function to execute on TaskDestroy().
			cleanup_param - parameter to send to cleanup_func().
			run_time - the time to make the task.

Return Value: pointer to the new task, or NULL if it fails.

Complexity: 
	time: O(1)  / space: O(1)
-----------------------------------------------------------------------------*/
task_t *TaskCreate(task_action_func_t action_func, void *action_param,
                   task_cleanup_func_t cleanup_func, void *cleanup_param,
                   time_t run_time);

/*-----------------------------------------------------------------------------
Description: deletes a task and cleans the resources used by it with 
			"task_cleanup_func_t" passed to TaskCreate().

Parameters:	task - pointer to the task.

Return Value: none.

-----------------------------------------------------------------------------*/
void TaskDestroy(task_t *task);

/*-----------------------------------------------------------------------------
Description: returns the time to make the task.

Parameters: task - pointer to the task.

Return Value: time_t type.

Complexity: 
	time: O(1)  / space: O(1)
-----------------------------------------------------------------------------*/
time_t TaskGetRunTime(const task_t *task);

/*-----------------------------------------------------------------------------
Description: set the run time of the task to a new one.

Parameters: task - pointer to the task.
			run_time - the new run time.

Return Value: none.

Complexity: 
	time: O(1)  / space: O(1)
-----------------------------------------------------------------------------*/
void TaskSetRunTime(task_t *task, time_t run_time);

/*-----------------------------------------------------------------------------
Description: excute the "task_action_func_t" passed to TaskCreate().

Parameters: task - pointer to the task.

Return Value: the return value of "task_action_func_t".

-----------------------------------------------------------------------------*/
int TaskExecuteFunc(const task_t *task);

/*-----------------------------------------------------------------------------
Description: returns the UID of the task.

Parameters: task - pointer to the task.

Return Value: ilrd_uid_t type.

Complexity: 
	time: O(1)  / space: O(1)
-----------------------------------------------------------------------------*/
ilrd_uid_t TaskGetUID(const task_t *task);

#endif /* __TASK_H__ */


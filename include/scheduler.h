/*-------------------------------------------*/
/* DEVELOPER: Itay Guter                    */
/* LAST MODIFIED: 2/1/2023	               */
/* WORKSHEET NAME: Scheduler		      */
/* REVIEWER: Gal Ventura		         */
/*--------------------------------------*/

#ifndef __SCHEDULER_H__
#define __SCHEDULER_H__

#include <stddef.h>		/*size_t*/

#include "uid.h"        /* ilrd_uid_t */

/*---------------------------------------------------------------------------
intro: a scheduler allows to schedule and track tasks.

policy: tasks run at their run time and if they have the same run time
		its FIFO.

main functionalities: SchedCreate, SchedDestroy, SchedAddTask, SchedRemoveTask,
						SchedRun, SchedStop.
---------------------------------------------------------------------------*/
typedef struct scheduler scheduler_t;

/*---------------------------------------------------------------------------
Description: a function to be executed as part of the task.

Parameters: param - an argument, if needed ,for the function operation.

Return Value: 0 on success, negative on fail, and positive if the task need
				to be added to the scheduler again at n(the positive return 
				value) seconds after execution.
		
---------------------------------------------------------------------------*/
typedef int(*sched_action_func_t)(void *param);

/*---------------------------------------------------------------------------
Description: free the resources of the task.

Parameters: param - an argument, if needed ,for the function operation.

Return Value: none.
		
---------------------------------------------------------------------------*/
typedef void(*sched_cleanup_func_t)(void *param);  

/*---------------------------------------------------------------------------
Description: creates a new scheduler(an empty one).

Parameters: none.

Return Value: pointer to the new scheduler, or NULL if it fails.

Complexity: time: O(1) / space: O(1) 		
---------------------------------------------------------------------------*/
scheduler_t *SchedCreate(void);

/*---------------------------------------------------------------------------
Description: deletes a scheduler, frees all the resources, important to use at
			 the end of usage in sched

Parameters: sched - pointer to a scheduler.

Return Value: none.

Complexity: time: O(n)  / space: O(1)		
---------------------------------------------------------------------------*/
void SchedDestroy(scheduler_t *sched);

/*---------------------------------------------------------------------------
Description: adds a new task to a scheduler.

Parameters: sched - pointer to a scheduler.
			action_func - pointer to a function to be excuted as part of 
			the task.
			action_param - parameter for the "action_func".
			cleanup_func - pointer to a function to be excuted when the 
			task is deleted from the scheduler.
			cleanup_param - parameter for the "cleanup_func".
			run_time - the time to run the task.

Return Value: the UID of the new task added to the scheduler, if it fails
				returns "bad_uid"(see UID docs).

Complexity: time: O(n)  / space: O(1)		
---------------------------------------------------------------------------*/
ilrd_uid_t SchedAddTask(scheduler_t *sched, sched_action_func_t action_func, 
						void *action_param, sched_cleanup_func_t cleanup_func, 
						void *cleanup_param, time_t run_time);

/*---------------------------------------------------------------------------
Description: removes a task from the scheduler.

Parameters: sched - pointer to a scheduler.
			uid - the UID of the task to be removed.

Return Value: 1 if it was removed, and 0 if it wasn't found in the scheduler.

Complexity: time: O(n)  / space: O(1)	
---------------------------------------------------------------------------*/
int SchedRemoveTask(scheduler_t *sched, ilrd_uid_t uid);

/*---------------------------------------------------------------------------
Description: runs all the tasks in the scheduler.

Parameters: sched - pointer to a scheduler.

Return Value: 0 if all tasks were excuted successfuly, and negative if one 
				or more tasks have faild.

note: a task can remove itself.

Complexity: depends on user "sched_action_func_t".
---------------------------------------------------------------------------*/
int SchedRun(scheduler_t *sched);

/*---------------------------------------------------------------------------
Description: stop a run of a scheduler.

Parameters: sched - pointer to a scheduler.

Return Value: none.

note: you can use it as a task.

Complexity: time: O(1)  / space: O(1) 	
---------------------------------------------------------------------------*/
void SchedStop(scheduler_t *sched); 

/*---------------------------------------------------------------------------
Description: checks if a scheduler is empty.

Parameters: sched - pointer to a scheduler.

Return Value: 1 if scheduler is empty, and 0 otherwise.

Complexity: time: O(1)  / space: O(1)
---------------------------------------------------------------------------*/
int SchedIsEmpty(const scheduler_t *sched);

/*---------------------------------------------------------------------------
Description: return the amount of tasks in a scheduler.

Parameters: sched - pointer to a scheduler.

Return Value: size_t.

Complexity: time: O(n)  / space: O(1)	
---------------------------------------------------------------------------*/
size_t SchedSize(const scheduler_t *sched);

/*---------------------------------------------------------------------------
Description: clears all tasks in a scheduler(making it empty).

Parameters: sched - pointer to a scheduler.

Return Value: none.

Complexity: time: O(n)  / space: O(1) 
---------------------------------------------------------------------------*/
void SchedClearTasks(scheduler_t *sched);


#endif 	/* __SCHEDULER_H__ */


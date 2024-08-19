/*-------------------------------------------*/
/* DEVELOPER: Itay Guter                    */
/* LAST MODIFIED: 28/12/2022               */
/* WORKSHEET NAME: UID				      */
/* REVIEWER: Or Abadi	                 */
/*--------------------------------------*/

#include <unistd.h>		/* getpid() */
#include <stdatomic.h> /* atomic_fetch_add() */

#include "uid.h"		/* function declerations and typedefs */

const ilrd_uid_t bad_uid = {0};

static size_t GetCounter(void);

ilrd_uid_t UIDGenerate(void)
{
	ilrd_uid_t new_uid = {0};
	
	new_uid.pid = getpid();
	new_uid.time = time(NULL);
	if (-1 == new_uid.time)
	{
		return bad_uid;
	}
	
	new_uid.counter = GetCounter();
	
	return new_uid;
}

int UIDIsEqual(ilrd_uid_t handle1, ilrd_uid_t handle2)
{
	int is_equal = 0;
	
	is_equal += handle1.pid ^ handle2.pid;
	is_equal += handle1.time ^ handle2.time;
	is_equal += handle1.counter ^ handle2.counter;
	
	return (!is_equal);
}

static size_t GetCounter(void)
{
	static atomic_size_t s_counter = 0;
	
	atomic_fetch_add(&s_counter, 1);
	
	return (atomic_load(&s_counter));
}


/*-------------------------------------------*/
/* DEVELOPER: Itay Guter                    */
/* LAST MODIFIED: 28/12/2022               */
/* WORKSHEET NAME: UID				      */
/* REVIEWER: Or Abadi	                 */
/*--------------------------------------*/

#ifndef __UID_H__
#define __UID_H__

#include <sys/types.h>	/*pid_t*/
#include <time.h> /*time_t*/
/*---------------------------------------------------------------------------
intro: A unique identifier that is associated with a single entity 
		within a given system.

main functionalitis: UIDGenerate, UIDIsEqual.

---------------------------------------------------------------------------*/
typedef struct ilrd_uid ilrd_uid_t;

/* indication for faild generation of UID*/
extern const ilrd_uid_t bad_uid;

struct ilrd_uid
{
   pid_t pid;
   time_t time;
   size_t counter;
};

/*---------------------------------------------------------------------------
Description: generates a UID of type ilrd_uid_t.

Parameters: none.

Return Value: the new UID on success, if it fails it returns the bad_uid.

Complexity: 
	time: O(1)  / space: O(1) 		
---------------------------------------------------------------------------*/
ilrd_uid_t UIDGenerate(void);

/*---------------------------------------------------------------------------
Description: compares two UIDs to check if they are equal.

Parameters: handle1 - UID of type ilrd_uid_t.
			handle2 - UID of type ilrd_uid_t.

Return Value: returns 1 if equal and 0 otherwise.

Complexity: 
	time: O(1)  / space: O(1) 		
---------------------------------------------------------------------------*/
int UIDIsEqual(ilrd_uid_t handle1, ilrd_uid_t handle2);

#endif /* __UID_H__ */


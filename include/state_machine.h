/*-------------------------------------------*/
/* DEVELOPER: Itay Guter                    */
/* LAST MODIFIED: 22/1/2023	               */
/* WORKSHEET NAME: State Machine		  */
/* REVIEWER: Eitan				         */
/*--------------------------------------*/

#ifndef __STATE_MACHINE_H__
#define __STATE_MACHINE_H__

/*------------------------------------------------------------------------------
Finite State Machine(FSM): computational abstraction which maps a finite number 
of states to other states within the same set, via transitions. An FSM can only 
be in one state at any given moment.

MAIN FUNCTIONALITY: FSMValidString().

------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------
Description: determins if a string of 1s and 0s is accepted.

parameters: str - the string input.

return value: 0 if accepted, and 1 otherwise.

note: if the string include other characters(not 0/1) the behivior is undefined. 

Complexity:
	time: O(n) / space: O(1).
------------------------------------------------------------------------------*/
int FSMValidString(const char *str);

#endif /* __STATE_MACHINE_H__ */

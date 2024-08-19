/*-------------------------------------------*/
/* DEVELOPER: Itay Guter                    */
/* LAST MODIFIED: 22/1/2023	               */
/* WORKSHEET NAME: State Machine		  */
/* REVIEWER: Eitan				         */
/*--------------------------------------*/

#include <assert.h>	/* assert() */
#include <stddef.h>	/* NULL */

#include "state_machine.h"	/* function declarations */

typedef enum 
{ 
	STATE_INITIAL = 0, 
	VALID, 
	NOT_VALID,
	INVALID, 
	NUM_STATES
} state_t;

enum 
{
	ACCEPTED = 0,
	NOT_ACCEPTED
};

typedef state_t state_func_t(void *data);

static state_t DoStateInitial(void *data);
static state_t DoStateValid(void *data);
static state_t DoStateNotValid(void *data );
static state_t DoStateInvalid(void *data);
static state_t RunState(state_t current, void *data);

static state_func_t *const state_table[NUM_STATES] = 
{
	&DoStateInitial, &DoStateNotValid, &DoStateValid, &DoStateInvalid
};

int FSMValidString(const char *str)
{
	char *current_input = (char *)str;
	state_t cur_state = STATE_INITIAL;
	
	assert(NULL != str);
	
	while ('\0' != *current_input)
	{
		cur_state = RunState(cur_state, current_input);
		++current_input;
	}
	
	return ((VALID == cur_state) ? ACCEPTED : NOT_ACCEPTED);
}

static state_t DoStateInitial(void *data)
{
	assert(NULL != data);
	assert(('0' == *(char *)data) || ('1' == *(char *)data));
	
	return (ACCEPTED == (*(char *)data - '0') ? NOT_VALID : INVALID);
}

static state_t DoStateNotValid(void *data )
{
	assert(NULL != data);
	assert(('0' == *(char *)data) || ('1' == *(char *)data));
	
	return (ACCEPTED == (*(char *)data - '0') ? VALID : NOT_VALID);
}

static state_t DoStateValid(void *data)
{
	assert(NULL != data);
	assert(('0' == *(char *)data) || ('1' == *(char *)data));
	
	return (ACCEPTED == (*(char *)data - '0') ? VALID : NOT_VALID);
}

static state_t DoStateInvalid(void *data)
{
	assert(NULL != data);
	
	(void)data;
	
	return INVALID;
}

static state_t RunState(state_t current, void *data)
{
	assert(NULL != data);
	assert(('0' == *(char *)data) || ('1' == *(char *)data));
	
	return (state_table[current](data));
}



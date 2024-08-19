/*-------------------------------------------*/
/* DEVELOPER: Itay Guter                    */
/* LAST MODIFIED: 25/1/2023	               */
/* WORKSHEET NAME: Caculator		      */
/* REVIEWER: Karin				         */
/*--------------------------------------*/

#ifndef __CALCULATOR_H__
#define __CALCULATOR_H__


/*----------------------------------------------------------------------------
Calculator: can calculate basic operations(+,-,*,/), also supports parentheses.
			works with two stacks and is based on state machine architecture.

Main functionality: Calculate().

----------------------------------------------------------------------------*/

/* return status of the calculate function */
typedef enum status
{
    SYS_FAULT = -1,
    SUCCESS = 0,
    MATH_FAULT = 1,
    SYNTAX_FAULT = 2
}status_t;

/*----------------------------------------------------------------------------
Description: can calculate basic operations(+,-,*,/), also supports parentheses.

parameters: string - the expression to calculate(a null tarminated string).
			result - pointer to a variable that will hold the result.

return value: returns SUCCESS if expression was evaluated with no problems,
			  returns SYS_FAULT if there was a problem in the system,
			  returns MATH_FAULT if an undefined expression was found,
			  returns SYNTAX_FAULT if the syntax of the expression is wrong.

Complexity:
	time: O(n^2) / space: O(n).
----------------------------------------------------------------------------*/
status_t Calculate(const char *string, double *result);

#endif /* __CALCULATOR_H__ */


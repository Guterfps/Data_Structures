/*-------------------------------------------*/
/* DEVELOPER: Itay Guter                    */
/* LAST MODIFIED: 25/1/2023	               */
/* WORKSHEET NAME: Caculator		      */
/* REVIEWER: Karin				         */
/*--------------------------------------*/

#include <assert.h>	/* assert() */
#include <stdlib.h>	/* calloc(), strtod() */
#include <string.h>	/* strlen() */

#include "calculator.h"	/* function declerations and typedefs */

#define ASCII_SIZE 256

typedef struct stack
{
	int top;
	char stack[1];
} stack_t;

typedef enum state
{
	READ_NUM = 0,
	READ_OP,
	ERROR,
	RESULT,
	NUM_OF_STATES
} state_t;

typedef struct instance_data
{
	stack_t *nums;
	stack_t *ops;
	const char *input;
	status_t status;
} instance_data_t;

typedef enum input_type
{
	OP = 0,
	NUM,
	PLUS_MINUS,
	END,
	PAR_LEFT,
	PAR_RIGHT,
	INVALID_TYPE,
	NUM_OF_TYPES
} input_type_t;

typedef state_t state_func_t(instance_data_t *data);

/* stack by value functions */
static stack_t *StackInit(size_t capacity);
static void StackDestroy(stack_t *stack);
static void StackPush(stack_t *stack, const void *data, size_t data_size);
static void StackPop(stack_t *stack, void *data, size_t data_size);
static void *StackPeek(stack_t *stack, size_t data_size);
static int StackIsEmpty(stack_t *stack);
static size_t StackSize(stack_t *stack);

static void ReasultAndCleanUp(instance_data_t *data, double *result);
static input_type_t InputType(const char *input);
static const char *SymbolAfterSpace(const char *input);

/* state functions */
static state_t DoReadNum(instance_data_t *data);
static state_t DoReadOp(instance_data_t *data);
static state_t DoError(instance_data_t *data);
static state_t DoResult(instance_data_t *data);
static state_t DoParentheses(instance_data_t *data);
static state_t DoReadLeftPrantheses(instance_data_t *data);

static state_t RunState(state_t current, instance_data_t *data);

static state_func_t *const state_table[NUM_OF_TYPES][NUM_OF_STATES] = 
{
	{&DoError, &DoReadOp, &DoError, &DoError},
	{&DoReadNum, &DoError, &DoError, &DoError},
	{&DoReadNum, &DoReadOp, &DoError, &DoError},
	{&DoError, &DoResult, &DoError,&DoResult},
	{&DoReadLeftPrantheses, &DoError, &DoError,&DoError},
	{&DoError, &DoParentheses, &DoError,&DoError},
	{&DoError, &DoError, &DoError,&DoError}
};

static input_type_t inputs_table[ASCII_SIZE] = {0};

/* init functions */
static status_t Build2Stacks(stack_t **nums, stack_t **ops, size_t size);
void InitInputTable(void);
static void InitData(instance_data_t *data, stack_t *nums, 
					stack_t *ops, status_t status, const char *input);

/* calculations functions */
static double AddFunc(double num1, double num2);
static double SubFunc(double num1, double num2);
static double MultFunc(double num1, double num2);
static double DivFunc(double num1, double num2);
static int IsPrior(char oper1, char oper2);
static int GetPriority(char oper);
static status_t Evaluate(stack_t *nums, stack_t *ops);
static void EvaluateLoop(instance_data_t *data);

status_t Calculate(const char *string, double *result)
{
	stack_t *nums = NULL;
	stack_t *ops = NULL;
	state_t cur_state = READ_NUM;
	status_t status = SUCCESS;
	instance_data_t data_struct = {0};
	
	assert(NULL != string);
	assert(NULL != result);
	
	status = Build2Stacks(&nums, &ops, strlen(string));
	if (SYS_FAULT == status)
	{
		return status;
	}
	
	InitData(&data_struct, nums, ops, status, string);
	InitInputTable();
	
	while ((ERROR != cur_state) && (RESULT != cur_state))
	{
		data_struct.input = SymbolAfterSpace(data_struct.input);
		cur_state = RunState(cur_state, &data_struct);
	}
	
	status = data_struct.status;
	if (SUCCESS == status)
	{
		status = StackIsEmpty(data_struct.ops) ? SUCCESS : SYNTAX_FAULT;
	}
	
	ReasultAndCleanUp(&data_struct, result);
	
	return status;
}

static state_t RunState(state_t current, instance_data_t *data)
{
	assert(NULL != data);
	
	return (state_table[InputType(data->input)][current](data));
}

static state_t DoReadNum(instance_data_t *data)
{
	char *end = NULL;
	double num = 0;
	int sign = 1;
	
	assert(NULL != data);
	
	if (('-' == *(data->input)) || ('+' == *(data->input)))
	{
		sign = ('-' == *(data->input)) ? -1 : 1;
		++(data->input);
	}
	
	end = (char *)data->input;
	num = strtod(data->input, &end);
	
	num *= sign;
	StackPush(data->nums, &num, sizeof(num));
	data->input = SymbolAfterSpace(end);

	return READ_OP;
}

static state_t DoReadOp(instance_data_t *data)
{	
	assert(NULL != data);
	
	EvaluateLoop(data);
	
	StackPush(data->ops, data->input, sizeof(char));
	data->input += 1;
	
	return ((SUCCESS == data->status) ? READ_NUM : ERROR);
}

static state_t DoReadLeftPrantheses(instance_data_t *data)
{
	assert(NULL != data);
	
	StackPush(data->ops, data->input, sizeof(char));
	data->input += 1;
	
	return READ_NUM;
}

static state_t DoParentheses(instance_data_t *data)
{	
	char left_par = 0;
	
	assert(NULL != data);
	
	EvaluateLoop(data);
	
	if (!StackIsEmpty(data->ops))
	{
		StackPop(data->ops, &left_par, sizeof(left_par));
	}
	
	if (PAR_LEFT != inputs_table[(int)left_par])
	{
		data->status = SYNTAX_FAULT;
	}
	data->input += 1;
	
	return ((SUCCESS == data->status) ? READ_OP : ERROR);
}

static state_t DoError(instance_data_t *data)
{
	assert(NULL != data);
	
	data->status = SYNTAX_FAULT;
	
	return ERROR;
}

static state_t DoResult(instance_data_t *data)
{
	assert(NULL != data);
	
	if (1 < StackSize(data->nums))
	{
		data->status = Evaluate(data->nums, data->ops);
	}
	
	return RESULT;
}

static int IsPrior(char oper1, char oper2)
{
	return (GetPriority(oper1) <= GetPriority(oper2));
}

static int GetPriority(char oper)
{
	int priority = 0;
	
	switch (oper)
	{
		case '+':
			priority = 3;
			break;
		case '-':
			priority = 3;
			break;
		case '*':
			priority = 2;
			break;
		case '/':
			priority = 2;
			break;
		case '(':
			priority = 1;
			break;
		case ')':
			priority = 4;
			break;
		default:
			break;
	}
	
	return priority;
}

static void EvaluateLoop(instance_data_t *data)
{
	char current_op = 0;
	
	assert(NULL != data);
	
	if (!StackIsEmpty(data->ops))
	{
		current_op = *(char *)StackPeek(data->ops, sizeof(current_op));
		
		while (!StackIsEmpty(data->ops) && 
				IsPrior(current_op, *(data->input)) && 
				(SUCCESS == data->status) &&
				(PAR_LEFT != inputs_table[(int)current_op]))
		{
			data->status = Evaluate(data->nums, data->ops);
			current_op = *(char *)StackPeek(data->ops, sizeof(current_op));
		}
	}
}

static status_t Evaluate(stack_t *nums, stack_t *ops)
{
	double num1 = 0;
	double num2 = 0;
	char oper = '\0';
	double result = 0;
	status_t status = SUCCESS;
	
	assert(NULL != nums);
	assert(NULL != ops);
	
	StackPop(nums, &num1, sizeof(num1));
	StackPop(nums, &num2, sizeof(num2));
	StackPop(ops, &oper, sizeof(oper));
	
	switch (oper)
	{
		case '+': 
			result = AddFunc(num1, num2);
			break;
		case '-':
			result = SubFunc(num1, num2);
			break;
		case '*':
			result = MultFunc(num1, num2);
			break;
		case '/':
			(0 != num1) ? (result = DivFunc(num1, num2)) : 
									(status = MATH_FAULT);
			break;
		default:
			status = SYNTAX_FAULT;
			break;
	}
	
	StackPush(nums, &result, sizeof(result));
	
	return status;
}

static double AddFunc(double num1, double num2)
{
	return (num2 + num1);
}

static double SubFunc(double num1, double num2)
{
	return (num2 - num1);
}

static double MultFunc(double num1, double num2)
{
	return (num2 * num1);
}

static double DivFunc(double num1, double num2)
{
	return (num2 / num1);
}

static input_type_t InputType(const char *input)
{
	input_type_t type = INVALID_TYPE;
	
	assert(NULL != input);
	
	type = inputs_table[(int)*input];
	
	return type;
}

void InitInputTable(void)
{
	size_t i = 0;
	
	for (; i < ASCII_SIZE; ++i)
	{
		inputs_table[i] = INVALID_TYPE;
	}
	
	for (i = '0'; i <= '9'; ++i)
	{
		inputs_table[i] = NUM;
	}
	
	inputs_table['+'] = PLUS_MINUS;
	inputs_table['-'] = PLUS_MINUS;
	inputs_table['*'] = OP;
	inputs_table['/'] = OP;
	inputs_table['('] = PAR_LEFT;
	inputs_table[')'] = PAR_RIGHT;
	inputs_table['\0'] = END;
}

static const char *SymbolAfterSpace(const char *input)
{
	assert(NULL != input);
	
	while (' ' == *input)
	{
		++input;
	}
	
	return input;
}

static stack_t *StackInit(size_t capacity)
{
	stack_t *new_stack = (stack_t *)calloc(1, sizeof(stack_t) - sizeof(char[1])
											 + capacity);
	if (NULL == new_stack)
	{
		return NULL;
	}
	
	new_stack->top = -1;
	
	return new_stack;
}

static void StackDestroy(stack_t *stack)
{
	assert(NULL != stack);
	
	free(stack);
	stack = NULL;
}

static void StackPush(stack_t *stack, const void *data, size_t data_size)
{
	assert(NULL != stack);
	
	stack->top += 1;
	memcpy(stack->stack + (stack->top * data_size), data, data_size); 
}

static void StackPop(stack_t *stack, void *data, size_t data_size)
{	
	assert(NULL != stack);
	
	memcpy(data, stack->stack + (stack->top * data_size), data_size);
	stack->top -= 1;
}

static void *StackPeek(stack_t *stack, size_t data_size)
{
	assert(NULL != stack);
	
	return (stack->stack + (stack->top * data_size));
}

static int StackIsEmpty(stack_t *stack)
{
	assert(NULL != stack);
	
	return (-1 == stack->top);
}

static size_t StackSize(stack_t *stack)
{
	assert(NULL != stack);
	
	return (stack->top + 1);
}

static status_t Build2Stacks(stack_t **nums, stack_t **ops, size_t size)
{
	assert(NULL != nums);
	assert(NULL != ops);
	
	*nums = StackInit(size * sizeof(double));
	if (NULL == *nums)
	{
		return SYS_FAULT;
	}
	*ops = StackInit(size);
	if (NULL == *ops)
	{
		StackDestroy(*nums);
		return SYS_FAULT;
	}
	
	return SUCCESS;
}

static void InitData(instance_data_t *data, stack_t *nums, 
					stack_t *ops, status_t status, const char *input)
{
	assert(NULL != data);
	assert(NULL != nums);
	assert(NULL != ops);
	assert(NULL != input);
	
	data->nums = nums;
	data->ops = ops;
	data->input = input;
	data->status = status;
}

static void ReasultAndCleanUp(instance_data_t *data, double *result)
{
	assert(NULL != data);
	assert(NULL != result);
	
	if (!StackIsEmpty(data->nums))
	{
		StackPop(data->nums, result, sizeof(*result));
	}
	StackDestroy(data->nums);
	StackDestroy(data->ops);
}



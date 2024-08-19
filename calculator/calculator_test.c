/*-------------------------------------------*/
/* DEVELOPER: Itay Guter                    */
/* LAST MODIFIED: 25/1/2023	               */
/* WORKSHEET NAME: Caculator		      */
/* REVIEWER: Karin				         */
/*--------------------------------------*/

#include <stdio.h>	/* printf() */

#include "calculator.h"	/* function declerations and typedefs */



int main(void)
{
	const char *test_plus = " 11 + 1+ + 13 ";
	const char *test_minus = " 21 - - 1 - 10";
	const char *test_mult = "+ 4 *  +  21 * - 1";
	const char *test_div = " 3 / 2 / 2 / 4";
	const char *test_math_error = " 1-3 * 10 /0 - 123";
	const char *test_syntax_error = " 3 + * 1 ";
	const char *test_syntax_error2 = " 3 123 / 1 ";
	const char *test_syntax_error3 = "* 3 + 123 ";
	const char *test_complex = "-1 - 7.1*3 -   420/69 - 25 / -10 * 8 + 1";
	const char *test_parentheses = 
						"3 * 10 - ( ( - 5 ) * ((2 / - 3) / ( + 6) ) ) / 4 + 5 ";
	const char *test_parentheses_error = "(10 - -5 * ((2 / 3) - 2 )) / 2 + 5) ";
	const char *test_parentheses_error2 = "(10 - -5 * ((2 / 3) - 2  / 2 + 5";
	const char *test_parentheses_error3 = "10 - -5 * (2 / 3 - 2  / 2 + 5";
	double result_plus = 0;
	double result_minus = 0;
	double result_mult = 0;
	double result_div = 0;
	double result_complex = 0;
	double result_parentheses = 0;
	status_t status = 0;
	
	printf("status:%d \n", status = Calculate(test_plus, &result_plus));
	printf("simple plus test:	");
	printf("%.2f, ", result_plus);
	(SUCCESS == status) ? printf("SUCCESS ✅️, ") : printf("FAIL ❌️, ");
	(25 == result_plus) ? printf("SUCCESS ✅️\n") : printf("FAIL ❌️\n");
	
	printf("status:%d \n", status = Calculate(test_minus, &result_minus));
	printf("simple minus test:	");
	printf("%.2f, ", result_minus);
	(SUCCESS == status) ? printf("SUCCESS ✅️, ") : printf("FAIL ❌️, ");
	((21 - -1 - 10) == result_minus) ? printf("SUCCESS ✅️\n") : printf("FAIL ❌️\n");
	
	printf("status:%d \n", status = Calculate(test_mult, &result_mult));
	printf("simple mult test:	");
	printf("%.2f, ", result_mult);
	(SUCCESS == status) ? printf("SUCCESS ✅️, ") : printf("FAIL ❌️, ");
	((4 * 21 * - 1) == result_mult) ? 
	printf("SUCCESS ✅️\n") : printf("FAIL ❌️\n");
	
	printf("status:%d \n",  status = Calculate(test_div, &result_div));
	printf("simple div test:	");
	printf("%.2f, ", result_div);
	(SUCCESS == status) ? printf("SUCCESS ✅️, ") : printf("FAIL ❌️, ");
	((3 / (double)2 / (double)2 / (double)4) == result_div) ? 
	printf("SUCCESS ✅️\n") : printf("FAIL ❌️\n");
	
	printf("math error test:	");
	(MATH_FAULT == Calculate(test_math_error, &result_plus)) ? 
	printf("SUCCESS ✅️\n") : printf("FAIL ❌️\n");
	
	printf("syntax error test:	");
	(SYNTAX_FAULT == Calculate(test_syntax_error, &result_plus)) ? 
	printf("SUCCESS ✅️\n") : printf("FAIL ❌️\n");
	
	printf("syntax error test2:	");
	(SYNTAX_FAULT == Calculate(test_syntax_error2, &result_plus)) ? 
	printf("SUCCESS ✅️\n") : printf("FAIL ❌️\n");
	
	printf("syntax error test3:	");
	(SYNTAX_FAULT == Calculate(test_syntax_error3, &result_plus)) ? 
	printf("SUCCESS ✅️\n") : printf("FAIL ❌️\n");
	
	printf("status:%d \n", status = Calculate(test_complex, &result_complex));
	printf("comlex test:	");
	printf("%.2f, ", result_complex);
	(SUCCESS == status) ? printf("SUCCESS ✅️, ") : printf("FAIL ❌️, ");
	((-1 - 7.1*3 - 420/(double)69 - 25 / (double)-10 * 8 + 1) == result_complex) ? 
	printf("SUCCESS ✅️\n") : printf("FAIL ❌️\n");
	
	printf("status:%d \n", status = 
							Calculate(test_parentheses, &result_parentheses));
	printf("parentheses test:	");
	printf("%.2f, ", result_parentheses);
	(SUCCESS == status) ? printf("SUCCESS ✅️, ") : printf("FAIL ❌️, ");
	((3*10 - (-5 * ((2 / (double)-3) / + 6)) / (double)4 + 5) == result_parentheses) ? 
	printf("SUCCESS ✅️\n") : printf("FAIL ❌️\n");
	
	printf("syntax error test4:	");
	(SYNTAX_FAULT == Calculate(test_parentheses_error, &result_plus)) ? 
	printf("SUCCESS ✅️\n") : printf("FAIL ❌️\n");
	
	printf("syntax error test5:	");
	(SYNTAX_FAULT == Calculate(test_parentheses_error2, &result_plus)) ? 
	printf("SUCCESS ✅️\n") : printf("FAIL ❌️\n");
	
	printf("syntax error test6:	");
	(SYNTAX_FAULT == Calculate(test_parentheses_error3, &result_plus)) ? 
	printf("SUCCESS ✅️\n") : printf("FAIL ❌️\n");
	
	return 0;
}

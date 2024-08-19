/*-------------------------------------------*/
/* DEVELOPER: Itay Guter                    */
/* LAST MODIFIED: 22/1/2023	               */
/* WORKSHEET NAME: State Machine		  */
/* REVIEWER: Eitan				         */
/*--------------------------------------*/

#include <stdio.h>	/* printf() */

#include "state_machine.h"	/* function declarations */

int main(void)
{
	const char *test1 = "01110";
	const char *test2 = "00";
	const char *test3 = "0101010";
	const char *test4 = "0";
	const char *test5 = "01";
	const char *test6 = "10001";
	const char *test7 = "101010";
	const char *test8 = "001001";
	
	printf("string %s is:	", test1);
	(0 == FSMValidString(test1)) ? 
	printf("accepted ✅️\n") : printf("non-accepted ❌️\n");
	printf("string %s is:	", test2);
	(0 == FSMValidString(test2)) ? 
	printf("accepted ✅️\n") : printf("non-accepted ❌️\n");
	printf("string %s is:	", test3);
	(0 == FSMValidString(test3)) ? 
	printf("accepted ✅️\n") : printf("non-accepted ❌️\n");
	
	printf("string %s is:	", test4);
	(0 != FSMValidString(test4)) ? 
	printf("non-accepted ✅️\n") : printf("accepted ❌️\n");
	printf("string %s is:	", test5);
	(0 != FSMValidString(test5)) ? 
	printf("non-accepted ✅️\n") : printf("accepted ❌️\n");
	printf("string %s is:	", test6);
	(0 != FSMValidString(test6)) ? 
	printf("non-accepted ✅️\n") : printf("accepted ❌️\n");
	printf("string %s is:	", test7);
	(0 != FSMValidString(test7)) ? 
	printf("non-accepted ✅️\n") : printf("accepted ❌️\n");
	printf("string %s is:	", test8);
	(0 != FSMValidString(test8)) ? 
	printf("non-accepted ✅️\n") : printf("accepted ❌️\n");
	
	return 0;
}

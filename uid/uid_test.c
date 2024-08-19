/*-------------------------------------------*/
/* DEVELOPER: Itay Guter                    */
/* LAST MODIFIED: 28/12/2022               */
/* WORKSHEET NAME: UID				      */
/* REVIEWER: Or Abadi	                 */
/*--------------------------------------*/

#include <stdio.h>		/* printf() */

#include "uid.h"		/* function declerations and typedefs */

int main(void)
{
	ilrd_uid_t test1 = UIDGenerate();
	ilrd_uid_t test2 = UIDGenerate();
	size_t i = 0;
	int million_tests = 1;
	
	for (; (i < 1000000) && million_tests; ++i)
	{
		million_tests = !UIDIsEqual(test1, UIDGenerate());
	}
	
	printf("is equal test:	");
	!UIDIsEqual(test1, test2) ? printf("SUCCESS ✅️, ") : printf("FAIL ❌️, ");
	UIDIsEqual(test2, test2) ? printf("SUCCESS ✅️, ") : printf("FAIL ❌️, ");
	!UIDIsEqual(test1, bad_uid) ? printf("SUCCESS ✅️,") : printf("FAIL ❌️,");
	UIDIsEqual(test1, test1) ? printf("SUCCESS ✅️\n") : printf("FAIL ❌️\n");
	
	printf("million uid test:	");
	million_tests ? printf("SUCCESS ✅️\n") : printf("FAIL ❌️\n");
	
	
	return 0;
}

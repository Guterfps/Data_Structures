/*-------------------------------------------*/
/* DEVELOPER: Itay Guter                    */
/* LAST MODIFIED: 14/12/2022               */
/* WORKSHEET NAME: Circular Buffer	      */
/* REVIEWER: Noy Elankry                 */
/*--------------------------------------*/

#include <stdio.h>		/*printf()*/

#include "c_buff.h"		/*function declerations and typedefs*/

static void Test1(void);
static void Test2(void);
static void Test3(void);

int main(void)
{
	Test1();
	Test2();
	Test3();

	return 0;
}

void Test1(void)
{
	c_buff_t *cbuffer = CbuffCreate(6);
	int test = 123123;
	int test_read = 0;
	ssize_t eob_test = 0;
	
	printf("capacity test:  ");
	(CbuffCapacity(cbuffer) == 6) ? printf("SUCCESS 👌️\n") :
						   			printf("FAIL ❌️\n");
	
	printf("isempty test:  ");
	CbuffIsEmpty(cbuffer) ? printf("SUCCESS 👌️\n") :
							printf("FAIL ❌️\n");
	
	printf("FreeSpace test:  ");
	(CbuffGetFreeSpace(cbuffer) == 6) ? printf("SUCCESS 👌️\n") :
										printf("FAIL ❌️\n");
	CbuffWrite(cbuffer, &test, sizeof(test));

	printf("FreeSpace test:  ");
	(CbuffGetFreeSpace(cbuffer) == 2) ? printf("SUCCESS 👌️\n") :
										printf("FAIL ❌️\n");
	printf("partial write:  ");
	(2 == CbuffWrite(cbuffer, &test, sizeof(test))) ? printf("SUCCESS 👌️\n") :
													  printf("FAIL ❌️\n");
	
	printf("FreeSpace test:  ");
	(CbuffGetFreeSpace(cbuffer) == 0) ? printf("SUCCESS 👌️\n") :
										printf("FAIL ❌️\n");
	eob_test = CbuffWrite(cbuffer, &test, sizeof(test));
	printf("end of buffer test:  ");
	(eob_test == 0) ? printf("SUCCESS 👌️\n") : printf("FAIL ❌️\n");
	
	printf("isempty test:  ");
	CbuffIsEmpty(cbuffer) ? printf("FAIL ❌️\n") :
							printf("SUCCESS 👌️\n");
	printf("capacity test:  ");
	(CbuffCapacity(cbuffer) == 6) ? printf("SUCCESS 👌️\n") :
						   			printf("FAIL ❌️\n");
							
	CbuffRead(cbuffer, &test_read, sizeof(test));
	printf("FreeSpace test:  ");
	(CbuffGetFreeSpace(cbuffer) == 4) ? printf("SUCCESS 👌️\n") :
										printf("FAIL ❌️\n");
	printf("test read value:  ");
	(test_read == test) ? printf("SUCCESS 👌️\n") : printf("FAIL ❌️\n");
	test_read = 0;
	
	printf("partial read:  ");
	(2 == CbuffRead(cbuffer, &test_read, sizeof(test))) ?
	printf("SUCCESS 👌️\n") : printf("FAIL ❌️\n");
	printf("test read value:  ");
	((short)test_read == (short)test) ? printf("SUCCESS 👌️\n") :
										printf("FAIL ❌️\n");
	
	eob_test = CbuffRead(cbuffer, &test_read, sizeof(test));
	printf("end of buffer test:  ");
	(eob_test == 0) ? printf("SUCCESS 👌️\n") : printf("FAIL ❌️\n");
	
	printf("FreeSpace test:  ");
	(CbuffGetFreeSpace(cbuffer) == 6) ? printf("SUCCESS 👌️\n") :
										printf("FAIL ❌️\n");
	printf("isempty test:  ");
	CbuffIsEmpty(cbuffer) ? printf("SUCCESS 👌️\n") :
							printf("FAIL ❌️\n");
	printf("capacity test:  ");
	(CbuffCapacity(cbuffer) == 6) ? printf("SUCCESS 👌️\n") :
						   			printf("FAIL ❌️\n");						
	
	
	CbuffDestroy(cbuffer);

}

void Test2(void)
{
	c_buff_t *cbuffer = CbuffCreate(20);
	long test = 123123;
	long test_read = 0;
	
	
	printf("\n\n write and read test: \n\n");
	
	printf("write..  ");
	(sizeof(long) == CbuffWrite(cbuffer, &test, sizeof(test))) ? 
	printf("SUCCESS 👌️\n") : printf("FAIL ❌️\n");
	printf("write..  ");
	(sizeof(long) == CbuffWrite(cbuffer, &test, sizeof(test))) ?
	printf("SUCCESS 👌️\n") : printf("FAIL ❌️\n");
	printf("read..  ");
	(sizeof(long) == CbuffRead(cbuffer, &test_read, sizeof(test))) ?
	printf("SUCCESS 👌️\n") : printf("FAIL ❌️\n");
	printf("FreeSpace test:  ");
	(CbuffGetFreeSpace(cbuffer) == 12) ? printf("SUCCESS 👌️\n") :
										printf("FAIL ❌️\n");
	printf("write..  ");
	(sizeof(long) == CbuffWrite(cbuffer, &test, sizeof(test))) ?
	printf("SUCCESS 👌️\n") : printf("FAIL ❌️\n");
	printf("read..  ");
	(sizeof(long) == CbuffRead(cbuffer, &test_read, sizeof(test))) ?
	printf("SUCCESS 👌️\n") : printf("FAIL ❌️\n");
	printf("read..  ");
	test_read = 0;
	(sizeof(long) == CbuffRead(cbuffer, &test_read, sizeof(test))) ?
	printf("SUCCESS 👌️\n") : printf("FAIL ❌️\n");
	
	printf("test for values:  ");
	(test == test_read) ? printf("SUCCESS 👌️\n") : printf("FAIL ❌️\n");
	
	printf("isempty test:  ");
	CbuffIsEmpty(cbuffer) ? printf("SUCCESS 👌️\n") :
							printf("FAIL ❌️\n");
	
	printf("write..  ");
	(sizeof(long) == CbuffWrite(cbuffer, &test, sizeof(test))) ? 
	printf("SUCCESS 👌️\n") : printf("FAIL ❌️\n");
	printf("write..  ");
	(sizeof(long) == CbuffWrite(cbuffer, &test, sizeof(test))) ?
	printf("SUCCESS 👌️\n") : printf("FAIL ❌️\n");
	printf("read..  ");
	test_read = 0;
	(sizeof(long) == CbuffRead(cbuffer, &test_read, sizeof(test))) ?
	printf("SUCCESS 👌️\n") : printf("FAIL ❌️\n");
	
	printf("test for values:  ");
	(test == test_read) ? printf("SUCCESS 👌️\n") : printf("FAIL ❌️\n");
	
	printf("FreeSpace test:  ");
	(CbuffGetFreeSpace(cbuffer) == 12) ? printf("SUCCESS 👌️\n") :
										printf("FAIL ❌️\n");
	printf("write..  ");
	(sizeof(long) == CbuffWrite(cbuffer, &test, sizeof(test))) ?
	printf("SUCCESS 👌️\n") : printf("FAIL ❌️\n");
	printf("read..  ");
	(sizeof(long) == CbuffRead(cbuffer, &test_read, sizeof(test))) ?
	printf("SUCCESS 👌️\n") : printf("FAIL ❌️\n");
	printf("read..  ");
	(sizeof(long) == CbuffRead(cbuffer, &test_read, sizeof(test))) ?
	printf("SUCCESS 👌️\n") : printf("FAIL ❌️\n");
	
	CbuffDestroy(cbuffer);
}

void Test3(void)
{
	c_buff_t *cbuffer = CbuffCreate(9);
	int test = 123123;
	int test_read = 0;
	int eob_test = 0;
	
	printf("\n\n more edge cases: \n\n");
	
	CbuffWrite(cbuffer, &test, sizeof(test));
	CbuffWrite(cbuffer, &test, sizeof(test));
	CbuffRead(cbuffer, &test_read, 1);
	(2 == CbuffWrite(cbuffer, &test, sizeof(test))) ? 
	printf("SUCCESS 👌️\n") : printf("FAIL ❌️\n");
	eob_test = CbuffWrite(cbuffer, &test, sizeof(test));
	printf("end of buffer test:  ");
	(eob_test == 0) ? printf("SUCCESS 👌️\n") : printf("FAIL ❌️\n");
	
	eob_test = 0;
	
	CbuffRead(cbuffer, &test_read, sizeof(test));
	CbuffRead(cbuffer, &test_read, sizeof(test));
	(1 == CbuffRead(cbuffer, &test_read, sizeof(test))) ? 
	printf("SUCCESS 👌️\n") : printf("FAIL ❌️\n");
	eob_test = CbuffRead(cbuffer, &test_read, sizeof(test));
	printf("end of buffer test:  ");
	(eob_test == 0) ? printf("SUCCESS 👌️\n") : printf("FAIL ❌️\n");
	
	CbuffDestroy(cbuffer);
}



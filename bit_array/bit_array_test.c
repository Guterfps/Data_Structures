/*****************************************/
/*   Developers: Itay Guter			 */
/*   Project: Bitarray		 	 */
/*   Reviewer: 	Noy Elankry		 */
/*   Date: 30/11/22			 */
/*					 */
/*****************************************/

#include <stdio.h>	/*printf()*/

#include "bit_array.h"	/*function declarations and typedefs*/

#define MAX_BUFFER 65

void TestBitArrSetOn(bit_array_t *bitarr, char *str);
void TestBitArrSetOff(bit_array_t *bitarr, char *str);
void TestBitArrGetVal(bit_array_t *bitarr);
void TestBitArrFlipBit(bit_array_t *bitarr, char *str);
void TestBitArrSetVal(bit_array_t *bitarr, char *str);
void TestBitArrFlipAll(bit_array_t *bitarr, char *str);
void TestBitArrSetAll(bit_array_t *bitarr, char *str);
void TestBitArrUnsetAll(bit_array_t *bitarr, char *str);
void TestBitArrRotateLeft(bit_array_t *bitarr, char *str);
void TestBitArrRotateRight(bit_array_t *bitarr, char *str);
void TestBitArrMirror(bit_array_t *bitarr, char *str);
void TestBitArrCountBits(bit_array_t *bitarr);

int main(void)
{
	char bit_arr_str[MAX_BUFFER] = {'\0'};
	bit_array_t bitarr = 0;

	TestBitArrSetOn(&bitarr, bit_arr_str);
	TestBitArrSetOff(&bitarr, bit_arr_str);
	TestBitArrGetVal(&bitarr);
	TestBitArrFlipBit(&bitarr, bit_arr_str);
	TestBitArrSetVal(&bitarr, bit_arr_str);
	TestBitArrFlipAll(&bitarr, bit_arr_str);
	TestBitArrSetAll(&bitarr, bit_arr_str);
	TestBitArrUnsetAll(&bitarr, bit_arr_str);
	bitarr = BitArrSetOn(bitarr, 0);
	bitarr = BitArrSetOn(bitarr, 1);
	bitarr = BitArrSetOn(bitarr, 25);
	bitarr = BitArrSetOn(bitarr, 42);
	bitarr = BitArrSetOn(bitarr, 63);
	TestBitArrRotateLeft(&bitarr, bit_arr_str);
	TestBitArrRotateRight(&bitarr, bit_arr_str);
	TestBitArrMirror(&bitarr, bit_arr_str);
	TestBitArrCountBits(&bitarr);
	
	return 0;
}

void TestBitArrSetOn(bit_array_t *bitarr, char *str)
{
	printf("bit array is: %s \n", BitArrToString(*bitarr, str));
	*bitarr = BitArrSetOn(*bitarr, 0);
	*bitarr = BitArrSetOn(*bitarr, 63);
	*bitarr = BitArrSetOn(*bitarr, 25);
	printf("set on bits\n");
	printf("bit array is: %s \n", BitArrToString(*bitarr, str));
	printf("\n");
}

void TestBitArrSetOff(bit_array_t *bitarr, char *str)
{
	*bitarr = BitArrSetOff(*bitarr, 25);
	printf("set off bit\n");
	printf("bit array is: %s \n", BitArrToString(*bitarr, str));
	printf("\n");
}

void TestBitArrGetVal(bit_array_t *bitarr)
{
	printf("bit at indx 0: %d \n", BitArrGetVal(*bitarr, 0));
	printf("bit at indx 25: %d \n", BitArrGetVal(*bitarr, 25));
	printf("\n");
}

void TestBitArrFlipBit(bit_array_t *bitarr, char *str)
{
	*bitarr = BitArrFlipBit(*bitarr, 25);
	printf("flip bit\n");
	printf("bit array is: %s \n", BitArrToString(*bitarr, str));
	*bitarr = BitArrFlipBit(*bitarr, 63);
	printf("flip bit\n");
	printf("bit array is: %s \n", BitArrToString(*bitarr, str));
	*bitarr = BitArrFlipBit(*bitarr, 25);
	printf("flip bit\n");
	printf("bit array is: %s \n", BitArrToString(*bitarr, str));
	printf("\n");
}

void TestBitArrSetVal(bit_array_t *bitarr, char *str)
{
	*bitarr = BitArrSetVal(*bitarr, 10, bit_on);
	printf("set bit to on\n");
	printf("bit array is: %s \n", BitArrToString(*bitarr, str));
	*bitarr = BitArrSetVal(*bitarr, 10, bit_off);
	printf("set bit to off\n");
	printf("bit array is: %s \n", BitArrToString(*bitarr, str));
	*bitarr = BitArrSetVal(*bitarr, 0, bit_off);
	printf("set bit to off\n");
	printf("bit array is: %s \n", BitArrToString(*bitarr, str));
	*bitarr = BitArrSetVal(*bitarr, 63, bit_on);
	printf("set bit to on\n");
	printf("bit array is: %s \n", BitArrToString(*bitarr, str));
	*bitarr = BitArrSetVal(*bitarr, 25, bit_on);
	printf("set bit to on\n");
	printf("bit array is: %s \n", BitArrToString(*bitarr, str));
	printf("\n");
}

void TestBitArrFlipAll(bit_array_t *bitarr, char *str)
{
	*bitarr = BitArrFlipAll(*bitarr);
	printf("flip all bit\n");
	printf("bit array is: %s \n", BitArrToString(*bitarr, str));
	printf("\n");
}

void TestBitArrSetAll(bit_array_t *bitarr, char *str)
{
	*bitarr = BitArrSetAll(*bitarr);
	printf("set all bits\n");
	printf("bit array is: %s \n", BitArrToString(*bitarr, str));
	printf("\n");
}

void TestBitArrUnsetAll(bit_array_t *bitarr, char *str)
{
	*bitarr = BitArrUnsetAll(*bitarr);
	printf("unset all bits\n");
	printf("bit array is: %s \n", BitArrToString(*bitarr, str));
	printf("\n");
}

void TestBitArrRotateLeft(bit_array_t *bitarr, char *str)
{
	printf("bit array is: %s \n", BitArrToString(*bitarr, str));
	*bitarr = BitArrRotateLeft(*bitarr, 25);
	printf("rotate left 25\n");
	printf("bit array is: %s \n", BitArrToString(*bitarr, str));
	*bitarr = BitArrRotateLeft(*bitarr, 25);
	printf("rotate left 25\n");
	printf("bit array is: %s \n", BitArrToString(*bitarr, str));
	*bitarr = BitArrRotateLeft(*bitarr, 65);
	printf("rotate left 65\n");
	printf("bit array is: %s \n", BitArrToString(*bitarr, str));
	printf("\n");
}

void TestBitArrRotateRight(bit_array_t *bitarr, char *str)
{
	*bitarr = BitArrRotateRight(*bitarr, 25);
	printf("rotate right 25\n");
	printf("bit array is: %s \n", BitArrToString(*bitarr, str));
	*bitarr = BitArrRotateRight(*bitarr, 25);
	printf("rotate right 25\n");
	printf("bit array is: %s \n", BitArrToString(*bitarr, str));
	*bitarr = BitArrRotateRight(*bitarr, 65);
	printf("rotate right 65\n");
	printf("bit array is: %s \n", BitArrToString(*bitarr, str));
	printf("\n");
}

void TestBitArrMirror(bit_array_t *bitarr, char *str)
{
	printf("bit array is: %s \n", BitArrToString(*bitarr, str));
	*bitarr = BitArrMirror(*bitarr);
	printf("mirror bitarray O(n)\n");
	printf("bit array is: %s \n", BitArrToString(*bitarr, str));
	*bitarr = BitArrMirrorO1(*bitarr);
	printf("mirror bitarray O(1)\n");
	printf("bit array is: %s \n", BitArrToString(*bitarr, str));
	*bitarr = BitArrMirrorLut(*bitarr);
	printf("mirror bitarray (LUT)\n");
	printf("bit array is: %s \n", BitArrToString(*bitarr, str));
	printf("\n");
}

void TestBitArrCountBits(bit_array_t *bitarr)
{
	printf("number of set bits: %ld \n", BitArrCountSetBits(*bitarr));
	printf("number of set bits(LUT): %ld \n", BitArrCountSetBitsLut(*bitarr));
	printf("number of off bits: %ld \n", BitArrCountOffBits(*bitarr));
	printf("\n");
}


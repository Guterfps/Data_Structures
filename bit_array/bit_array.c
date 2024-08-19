/*****************************************/
/*   Developers: Itay Guter			 */
/*   Project: Bitarray		 	 */
/*   Reviewer: 	Noy Elankry		 */
/*   Date: 30/11/22			 */
/*					 */
/*****************************************/

#include <limits.h>		/*CHAR_BIT*/
#include <assert.h>		/*assert()*/

#include "bit_array.h"	/* function declarations and typedefs */

#define MAX_INDX ((sizeof(size_t) * CHAR_BIT) - 1)
#define BITARR_SIZE (sizeof(size_t) * CHAR_BIT)
#define NUM_OF_VALUES_IN_BYTE (1 << CHAR_BIT)

/* macros to create the LUT for BitArrCountSetBitsLut */
#   define B2(n) n,     n+1,     n+1,     n+2
#   define B4(n) B2(n), B2(n+1), B2(n+1), B2(n+2)
#   define B6(n) B4(n), B4(n+1), B4(n+1), B4(n+2)

/* macros to create the LUT for BitArrMirrorLut */
#   define R2(n)     n,     n + 2*64,     n + 1*64,     n + 3*64
#   define R4(n) R2(n), R2(n + 2*16), R2(n + 1*16), R2(n + 3*16)
#   define R6(n) R4(n), R4(n + 2*4 ), R4(n + 1*4 ), R4(n + 3*4 )

static const unsigned char BitReverseTable256[NUM_OF_VALUES_IN_BYTE] = 
{
    R6(0), R6(2), R6(1), R6(3)
};

static const unsigned char BitsSetTable256[NUM_OF_VALUES_IN_BYTE] = 
{
    B6(0), B6(1), B6(1), B6(2)
};

bit_array_t BitArrSetOn(bit_array_t bitarr, size_t i)
{
	assert(BITARR_SIZE > i);
	
	return (((bit_array_t)bit_on << i) | bitarr);
}

bit_array_t BitArrSetOff(bit_array_t bitarr, size_t i)
{
	assert(BITARR_SIZE > i);
	
	return (~((bit_array_t)bit_on << i) & bitarr);
}

bit_array_t BitArrFlipBit(bit_array_t bitarr, size_t i)
{
	assert(BITARR_SIZE > i);
	
	return (((bit_array_t)bit_on << i) ^ bitarr);
}

int BitArrGetVal(bit_array_t bitarr, size_t i)
{	
	assert(BITARR_SIZE > i);
	
	return ((((bit_array_t)bit_on << i) & bitarr) >> i);
}

bit_array_t BitArrSetVal(bit_array_t bitarr, size_t i, bit_val_t value)
{	
	assert(BITARR_SIZE > i);
	
	return (value ? BitArrSetOn(bitarr, i) : BitArrSetOff(bitarr, i));
}

bit_array_t BitArrFlipAll(bit_array_t bitarr)
{
	return (~bitarr);
}

bit_array_t BitArrSetAll(bit_array_t bitarr)
{
	return (~((bit_array_t)bit_off & bitarr));
}

bit_array_t BitArrUnsetAll(bit_array_t bitarr)
{
	return ((bit_array_t)bit_off & bitarr);
}

bit_array_t BitArrRotateLeft(bit_array_t bitarr, size_t n)
{
	n &= MAX_INDX;
	
	return ((bitarr >> (BITARR_SIZE - n)) | (bitarr << n));
}

bit_array_t BitArrRotateRight(bit_array_t bitarr, size_t n)
{
	n &= MAX_INDX;
	
	return ((bitarr << (BITARR_SIZE - n)) | (bitarr >> n));
}

bit_array_t BitArrMirror(bit_array_t bitarr)
{
    bit_array_t mirror = 0;
	size_t i = 0;
	
    for (; i <= MAX_INDX; ++i)
    {
    	mirror <<= 1;
    	
        if (bitarr & bit_on)
        {
            mirror ^= bit_on;
		}
        bitarr >>= 1;
    }

    return mirror;
}

bit_array_t BitArrMirrorLut(bit_array_t bitarr)
{
	size_t reverse = 0;
	size_t i = 0;
	unsigned char *pbitarr = (unsigned char *)&bitarr;
	unsigned char *preverse = (unsigned char *)&reverse;
	
	while (i < (BITARR_SIZE / CHAR_BIT))
	{
		preverse[(BITARR_SIZE / CHAR_BIT) - 1 - i] = 
		BitReverseTable256[pbitarr[i]];
		++i; 
	}
	
	return reverse;
}

bit_array_t BitArrMirrorO1(bit_array_t bitarr)
{
	bitarr = (bitarr & 0xAAAAAAAAAAAAAAAA) >> 1 |
			 (bitarr & 0x5555555555555555) << 1;
	bitarr = (bitarr & 0xcccccccccccccccc) >> (BITARR_SIZE / 32) |
			 (bitarr & 0x3333333333333333) << (BITARR_SIZE / 32);
	bitarr = (bitarr & 0xF0F0F0F0F0F0F0F0) >> (BITARR_SIZE / 16) |
			 (bitarr & 0x0F0F0F0F0F0F0F0F) << (BITARR_SIZE / 16);
	bitarr = (bitarr & 0xFF00FF00FF00FF00) >> (BITARR_SIZE / 8) |
			 (bitarr & 0x00FF00FF00FF00FF) << (BITARR_SIZE / 8);
	bitarr = (bitarr & 0xFFFF0000FFFF0000) >> (BITARR_SIZE / 4) |
			 (bitarr & 0x0000FFFF0000FFFF) << (BITARR_SIZE / 4);
	
	return (bitarr << (BITARR_SIZE / 2) | bitarr >> (BITARR_SIZE / 2));	
}

size_t BitArrCountSetBits(bit_array_t bitarr)
{
	size_t counter = 0;
	for (; bitarr; ++counter)
	{
	  bitarr &= (bitarr - 1);
	}
	
	return counter;
}

size_t BitArrCountSetBitsLut(bit_array_t bitarr)
{
	size_t i = CHAR_BIT;
	size_t counter = BitsSetTable256[bitarr & 0xff];
    
    while (i < (BITARR_SIZE - CHAR_BIT))
    {
    	counter += BitsSetTable256[(bitarr >> (BITARR_SIZE - i)) & 0xff];
    	i += CHAR_BIT;
    }
    
    return counter;
}


size_t BitArrCountOffBits(bit_array_t bitarr)
{
	return (BITARR_SIZE - BitArrCountSetBits(bitarr));
}


char *BitArrToString(bit_array_t bitarr, char *buffer)
{
    char *temp = NULL;
    size_t i = 0;
    
    assert(NULL != buffer);
    
    temp = buffer + BITARR_SIZE;
	*temp = '\0';
    
    for (;i < BITARR_SIZE; ++i)
    {
    	--temp;
        *temp = (BitArrGetVal(bitarr, i)) ? '1' : '0';
	}
	
	
	return buffer;
}



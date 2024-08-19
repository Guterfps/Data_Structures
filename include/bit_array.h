/*****************************************/
/*   Developers: Itay Guter			 */
/*   Project: Bitarray		 	 */
/*   Reviewer: 	Noy Elankry		 */
/*   Date: 30/11/22			 */
/*					 */
/*****************************************/

#ifndef __BITARR_H__
#define __BITARR_H__

#include <stddef.h>	/*size_t*/

/************************struct*****************************/
typedef size_t bit_array_t;

typedef enum bit_val
{
	bit_off = 0,
	bit_on	= 1
}bit_val_t;
/******************Function Declarations********************/

/*time: o(1) / space: o(1)*/
bit_array_t BitArrSetOn(bit_array_t bitarr, size_t i);
/*---------------------------------------------------------------------------
Description - gets a bit_array_t and indx i and set on the bit at that indx

i larger then bitarr's size will lead to undefined behavior
Return Value - returns the bit array

---------------------------------------------------------------------------*/
/*time: o(1) / space: o(1)*/
bit_array_t BitArrSetOff(bit_array_t bitarr, size_t i);
/*-----------------------------------------------------------------------------
Description - gets a bit_array_t and indx i and set off the bit at that indx

i larger then bitarr's size will lead to undefined behavior	
Return Value - returns the bit array

-----------------------------------------------------------------------------*/	 
/*time: o(1) / space: o(1)*/	 	
bit_array_t BitArrFlipBit(bit_array_t bitarr, size_t i);
/*-----------------------------------------------------------------------------
Description - gets a bit_array_t and indx i and flips the bit at that indx

i larger then bitarr's size will lead to undefined behavior
Return Value - returns the bit array

-----------------------------------------------------------------------------*/	 

/*time: o(1) / space: o(1)*/	
int BitArrGetVal(bit_array_t bitarr, size_t i);	
/*-----------------------------------------------------------------------------
Description - gets a bit_array_t and indx i and returns the bit at that indx

i larger then bitarr's size will lead to undefined behavior
Return Value - the value of the bit 

-----------------------------------------------------------------------------*/	 

/*time: o(1) / space: o(1)*/	
bit_array_t BitArrSetVal(bit_array_t bitarr, size_t i, bit_val_t value);
/*-----------------------------------------------------------------------------
Description - gets a bit_array_t, bit_val_t and indx i and set the bit 
			  at that indx to the value.
i larger then bitarr's size will lead to undefined behavior
Return Value - returns the bit array

-----------------------------------------------------------------------------*/	 

/*time: o(1) / space: o(1)*/	
bit_array_t BitArrFlipAll(bit_array_t bitarr);
/*-----------------------------------------------------------------------------
Description - gets a bit_array_t and flip all bits inside.

	
Return Value - returns the bit array

-----------------------------------------------------------------------------*/	 

/*time: o(1) / space: o(1)*/	
bit_array_t BitArrSetAll(bit_array_t bitarr);
/*-----------------------------------------------------------------------------
Description - gets a bit_array_t and set on all bits inside.


Return Value - returns the bit array

-----------------------------------------------------------------------------*/	 
/*time: o(1) / space: o(1)*/	
bit_array_t BitArrUnsetAll(bit_array_t bitarr);
/*-----------------------------------------------------------------------------
Description - gets a bit_array_t and set off all bits inside.

	
Return Value - returns the bit array

-----------------------------------------------------------------------------*/	
/*time: o(1) / space: o(1)*/	
bit_array_t BitArrRotateLeft(bit_array_t bitarr, size_t n);
/*-----------------------------------------------------------------------------
Description - gets a bit_array_t and rotates left all bits inside n times.

	
Return Value - returns the bit array

-----------------------------------------------------------------------------*/	
/*time: o(1) / space: o(1)*/	
bit_array_t BitArrRotateRight(bit_array_t bitarr, size_t n);
/*-----------------------------------------------------------------------------
Description - gets a bit_array_t and rotates right all bits inside n times.

	
Return Value - returns the bit array

-----------------------------------------------------------------------------*/	
/*time: o(1) / space: o(1)*/	
bit_array_t BitArrMirror(bit_array_t bitarr);
/*-----------------------------------------------------------------------------
Description - gets a bit_array_t and reverse it.

	
Return Value - returns the bit array

-----------------------------------------------------------------------------*/	

/*time: o(1) / space: o(1)*/	
bit_array_t BitArrMirrorLut(bit_array_t bitarr);
/*-----------------------------------------------------------------------------
Description - gets a bit_array_t and reverse it.

	
Return Value - returns the bit array

-----------------------------------------------------------------------------*/	

/*time: o(1) / space: o(1)*/	
bit_array_t BitArrMirrorO1(bit_array_t bitarr);
/*-----------------------------------------------------------------------------
Description - gets a bit_array_t and reverse it.

	
Return Value - returns the bit array

-----------------------------------------------------------------------------*/	

/*time: o(n) / space: o(1)*/	
size_t BitArrCountSetBits(bit_array_t bitarr);
/*-----------------------------------------------------------------------------
Description - gets a bit_array_t and returns the number of set bits.

	
Return Value - return the number of set bits.

-----------------------------------------------------------------------------*/	

/*time: o(1) / space: o(n)*/	
size_t BitArrCountSetBitsLut(bit_array_t bitarr);
/*-----------------------------------------------------------------------------
Description - gets a bit_array_t and returns the number of set bits.

	
Return Value - return the number of set bits.

-----------------------------------------------------------------------------*/	

/*time: o(1) / space: o(n)*/	
size_t BitArrCountSetBitsHamming(bit_array_t bitarr);
/*-----------------------------------------------------------------------------
Description 

	
Return Value

-----------------------------------------------------------------------------*/	


/*time: o(n) / space: o(1)*/	
size_t BitArrCountOffBits(bit_array_t bitarr);
/*-----------------------------------------------------------------------------
Description - gets a bit_array_t and returns the number of unset bits.

	
Return Value - return the number of unset bits.

-----------------------------------------------------------------------------*/	
/*time: o(1) / space: o(1)*/	
char *BitArrToString(bit_array_t bitarr, char *buffer);
/*-----------------------------------------------------------------------------
Description - gets a bit_array_t and char * and translate the array values 
			  into a string.

Return Value - returns a pointer to the string.

-----------------------------------------------------------------------------*/	

#endif 		/* __BITARR_H__ */



/*-------------------------------------------*/
/* DEVELOPER: Itay Guter                    */
/* LAST MODIFIED: 14/12/2022               */
/* WORKSHEET NAME: Circular Buffer	      */
/* REVIEWER: Noy Elankry                 */
/*--------------------------------------*/

#ifndef __C_BUFF_H__
#define __C_BUFF_H__
/*-----------------------------------------------------------------------------
intro: circular buffer is a data structure that allows to write to and read 
		from in bytes.
policy: FIFO.

main functionalitys: create ("CbuffCreate") a "c_buff_t *" (with capacity > 0) 
					and use "CbuffWrite"/"CbuffRead" to write and read to/from
					the buffer. after you finish dont forget to use 
					"CbuffDestroy" to delete the buffer.
					
-----------------------------------------------------------------------------*/
#include <sys/types.h>	/*ssize_t, size_t*/

typedef struct c_buff c_buff_t;

/*-----------------------------------------------------------------------------
params: capacity - should be bigger then zero ,otherwise buffer is useless. 

description: creates a circular buffer in memory.
			if "capacity" = 0 buffer is useless.

return value: return pointer to the new buffer or NULL if it fails.

-----------------------------------------------------------------------------*/
/* Complexity: time: O(1)  / space: O(n) */ 
c_buff_t *CbuffCreate(size_t capacity);
/*-----------------------------------------------------------------------------
params: cbuff - pointer to a circular buffer.

description: deletes the buffer.

return value: none.

-----------------------------------------------------------------------------*/
/* Complexity: time: O(1)  / space: O(1) */ 
void CbuffDestroy(c_buff_t *cbuff);
/*-----------------------------------------------------------------------------
params: cbuff - pointer to a circular buffer.
		src - pointer to the bytes to store.
		count - number of bytes to store.

description: writes "count" bytes from "src" to "cbuff", if the freespace 
			 in cbuff is not big enough to store all the bytes, only 
			 the first bytes will be saved until the buffer is full. 

return value: returns the amount of bytes writen to buffer. 

-----------------------------------------------------------------------------*/
/* Complexity: time: O(n)  / space: O(1) */ 
ssize_t CbuffWrite(c_buff_t *cbuff, const void *src, size_t count); 
/*-----------------------------------------------------------------------------
params: cbuff - pointer to a circular buffer.
		src - pointer to the adrress to copy the bytes to.
		count - number of bytes to read.

description: reads "count" bytes from "cbuff" to "dest", if the amount of
			 bytes in cbuff is not big enough to read all the bytes, only 
			 the first bytes will be read until the buffer is empty.

return value: returns the amount of bytes read from the buffer.

-----------------------------------------------------------------------------*/
/* Complexity: time: O(n)  / space: O(1) */ 
ssize_t CbuffRead(c_buff_t *cbuff, void *dest, size_t count);
/*-----------------------------------------------------------------------------
params: cbuff - pointer to a circular buffer.

description: returns the amount of free bytes to store data in the buffer.

return value: size_t.

-----------------------------------------------------------------------------*/
/* Complexity: time: O(1)  / space: O(1) */
size_t CbuffGetFreeSpace(const c_buff_t *cbuff);
/*-----------------------------------------------------------------------------
params: cbuff - pointer to a circular buffer.

description: checks if the buffer is empty or not.

return value: returns 1 if empty and 0 otherwise.

-----------------------------------------------------------------------------*/
/* Complexity: time: O(1)  / space: O(1) */
int CbuffIsEmpty(const c_buff_t *cbuff);
/*-----------------------------------------------------------------------------
params: cbuff - pointer to a circular buffer.

description: returns the capacity of the buffer in bytes.

return value: size_t.

-----------------------------------------------------------------------------*/
/* Complexity: time: O(1)  / space: O(1) */
size_t CbuffCapacity(const c_buff_t *cbuff);

#endif		/* __C_BUFF_H__ */


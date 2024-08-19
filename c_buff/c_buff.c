/*-------------------------------------------*/
/* DEVELOPER: Itay Guter                    */
/* LAST MODIFIED: 14/12/2022               */
/* WORKSHEET NAME: Circular Buffer	      */
/* REVIEWER: Noy Elankry                 */
/*--------------------------------------*/

#include <stdlib.h>		/*malloc(), free()*/
#include <assert.h>		/*assert()*/
#include <string.h>		/*memecpy()*/

#include "c_buff.h"		/*function declerations and typedefs*/


#define END_OF_BUFF(cbuff) (cbuff->buff + cbuff->cap)
#define BYTES_UNTIL_THE_END(place) (END_OF_BUFF(cbuff) - place)

struct c_buff
{
	size_t cap;
	size_t size;
	char *read;
	char buff[1];
};

static void InitCBuff(c_buff_t *buffer, size_t cap);
static char *WritePlace(c_buff_t *cbuff);
static void UpdateWriteVariables(c_buff_t *cbuff, const void **src,
								size_t *count, ssize_t *nbytes, char **write);
static void UpdateReadVariables(c_buff_t *cbuff, void **dest, size_t *count,
								ssize_t *nbytes);

c_buff_t *CbuffCreate(size_t capacity)
{
	c_buff_t *buffer = NULL;
	
	assert(0 != capacity);
	
	buffer = (c_buff_t *)malloc(sizeof(c_buff_t) - sizeof(char *) + capacity);
	if (NULL == buffer)
	{
		return NULL;
	}							
	
	InitCBuff(buffer, capacity);
	
	return buffer;
}

static void InitCBuff(c_buff_t *buffer, size_t cap)
{
	assert(NULL != buffer);
	
	buffer->cap = cap;
	buffer->size = 0;
	buffer->read = buffer->buff;
}

void CbuffDestroy(c_buff_t *cbuff)
{	
	free(cbuff);
	cbuff = NULL;
}

ssize_t CbuffWrite(c_buff_t *cbuff, const void *src, size_t count)
{
	char *write = NULL;
	ssize_t nbytes = 0;
	
	assert(NULL != cbuff);
	assert(NULL != src);
	
	write = WritePlace(cbuff);
		
	if (count > CbuffGetFreeSpace(cbuff))
	{
		count = CbuffGetFreeSpace(cbuff);
	}
	
	if ((write + count) > END_OF_BUFF(cbuff))
	{
		memcpy(write, src, BYTES_UNTIL_THE_END(write));
		UpdateWriteVariables(cbuff, &src, &count, &nbytes, &write);
	}
	
	memcpy(write, src, count);
	cbuff->size += count;
	nbytes += count;
	
	return nbytes;
}

static char *WritePlace(c_buff_t *cbuff)
{
	assert(NULL != cbuff);
	
	return ((cbuff->buff) + 
			(cbuff->read - cbuff->buff + cbuff->size) % (cbuff->cap));
}

static void UpdateWriteVariables(c_buff_t *cbuff, const void **src,
								size_t *count, ssize_t *nbytes, char **write)
{
	assert(NULL != cbuff);
	assert(NULL != src);
	assert(NULL != count);
	assert(NULL != nbytes);
	assert(NULL != write);
	
	*count -= BYTES_UNTIL_THE_END(*write);
	cbuff->size += BYTES_UNTIL_THE_END(*write);
	*nbytes += BYTES_UNTIL_THE_END(*write);
	*(char **)src += BYTES_UNTIL_THE_END(*write);
	*write = cbuff->buff;
}


ssize_t CbuffRead(c_buff_t *cbuff, void *dest, size_t count)
{
	ssize_t nbytes = 0;
	
	assert(NULL != cbuff);
	assert(NULL != dest);
	
	if (count > cbuff->size)
	{
		count = cbuff->size;
	}

	if ((cbuff->read + count) > END_OF_BUFF(cbuff))
	{
		memcpy(dest, cbuff->read, BYTES_UNTIL_THE_END(cbuff->read));
		UpdateReadVariables(cbuff, &dest, &count, &nbytes);
	}
	
	memcpy(dest, cbuff->read, count);
	cbuff->read += count;
	cbuff->size -= count;
	nbytes += count;
	
	return nbytes;
}

static void UpdateReadVariables(c_buff_t *cbuff, void **dest, size_t *count,
								ssize_t *nbytes)
{
	assert(NULL != cbuff);
	assert(NULL != dest);
	assert(NULL != count);
	assert(NULL != nbytes);
	
	*count -= BYTES_UNTIL_THE_END(cbuff->read);
	cbuff->size -= BYTES_UNTIL_THE_END(cbuff->read);
	*nbytes += BYTES_UNTIL_THE_END(cbuff->read);
	*(char **)dest += BYTES_UNTIL_THE_END(cbuff->read);
	cbuff->read = cbuff->buff;
}


size_t CbuffGetFreeSpace(const c_buff_t *cbuff)
{
	assert(NULL != cbuff);
	
	return (cbuff->cap - cbuff->size);
}

int CbuffIsEmpty(const c_buff_t *cbuff)
{
	assert(NULL != cbuff);
	
	return (!cbuff->size);
}

size_t CbuffCapacity(const c_buff_t *cbuff)
{
	assert(NULL != cbuff);
	
	return (cbuff->cap);
}



/*-------------------------------------------*/
/* DEVELOPER: Itay Guter                    */
/* LAST MODIFIED: 5/2/2023	               */
/* WORKSHEET NAME: Hash Table		      */
/* REVIEWER: Eitan		                 */
/*--------------------------------------*/

#include <stdio.h>	/* printf() */
#include <string.h>	/* strcmp() */
#include <stdlib.h>	/* malloc() */

#include "hash_table.h"	/* function declerations and typedefs */

#define TABLE_SIZE 10
#define TABLE_SIZE_2 ((size_t)5381)

typedef struct item
{
	size_t key;
	char value;
} item_t;

void Test(void);
void Test2(void);

size_t HashFunc(const void *key);
int IsMatch(const void *key1, const void *key2);
void *GetKey(const void *item);
int Print(void *item, void *param);

size_t HashFunc2(const void *key);
int IsMatch2(const void *key1, const void *key2);
void *GetKey2(const void *item);
int Clean(void *item, void *param);

int main(void)
{
	Test();
	Test2();
	
	return 0;
}

void Test(void)
{
	hash_t *hash = HashCreate(&GetKey, &IsMatch, &HashFunc, TABLE_SIZE);
	item_t arr[26] = {0};
	size_t len = sizeof(arr) / sizeof(*arr);
	size_t i = 0;
	int status = 0;
	size_t key = 0;
	
	for (i = 0; i < len; ++i)
	{
		item_t item = {0};
		item.key = i + 1;
		item.value = 'a' + i;
		arr[i] = item;
	}
	
	printf("is empty test:	");
	HashIsEmpty(hash) ? printf("SUCCESS ✅️\n") : printf("FAIL ❌️\n");
	
	printf("size test:	");
	(0 == HashSize(hash)) ? printf("SUCCESS ✅️\n") : printf("FAIL ❌️\n");
	
	for (i = 0; (i < len) && (0 == status); ++i)
	{
		status = HashInsert(hash, arr + i);
	}
	
	printf("insert test:	");
	(0 == status) ? printf("SUCCESS ✅️\n") : printf("FAIL ❌️\n");
	printf("is empty test:	");
	!HashIsEmpty(hash) ? printf("SUCCESS ✅️\n") : printf("FAIL ❌️\n");
	
	printf("size test:	");
	(len == HashSize(hash)) ? printf("SUCCESS ✅️\n") : printf("FAIL ❌️\n");
	
	status = 1;
	for (i = 0; (i < len) && status; ++i)
	{
		key = i + 1;
		status = (((item_t *)HashFind(hash, &key))->value == (char)('a' + i));
	}
	
	key += 10 ;
	status = (NULL == HashFind(hash, &(key)));
	
	printf("find test:	");
	(1 == status) ? printf("SUCCESS ✅️\n") : printf("FAIL ❌️\n");
	
	for (i = 0; (i < len / 2); ++i)
	{
		size_t key = i + 1;
		HashRemove(hash, &key);
	}
	
	printf("remove test:	");
	HashRemove(hash, &(arr[0].key));
	!HashIsEmpty(hash) ? printf("SUCCESS ✅️,") : printf("FAIL ❌️,");
	(len / 2 == HashSize(hash)) ? printf("SUCCESS ✅️\n") : printf("FAIL ❌️\n");
	
	printf("for each test:	");
	HashForeach(hash, &Print, NULL);
	printf("\n");
	
	HashDestroy(hash);
	hash = NULL;
}

void Test2(void)
{
	hash_t *hash = HashCreate(&GetKey2, &IsMatch2, &HashFunc2, TABLE_SIZE_2);
	FILE *fp = NULL;
	char temp[64] = {0};
	char input[64] = {0};
	int status = 0;
	
	if (NULL == (fp = fopen("/usr/share/dict/words", "r")))
	{
		printf("cant read file\n");
	}
	
	while (1 == fscanf(fp, "%s", temp) && (0 == status))
	{
		char *item = (char *)malloc(strlen(temp) + 1);
		if (NULL == item) 
		{
			HashForeach(hash, &Clean, NULL);
			fclose(fp);
			HashDestroy(hash);
			hash = NULL;
			return;
		}
		strcpy(item, temp);
		status = HashInsert(hash, item);
	}
	printf("dict test:	");
	(0 == status) ? printf("SUCCESS ✅️\n") : printf("FAIL ❌️\n");
	printf("is empty test:	");
	!HashIsEmpty(hash) ? printf("SUCCESS ✅️\n") : printf("FAIL ❌️\n");
	printf("size test:	");
	printf("%ld\n", HashSize(hash));
	
	do
	{
		printf("enter word('q' to quit):	");
		scanf("%s", input);
		
		printf("\n");
		(NULL != HashFind(hash, input)) ? 
		printf("word in dictionary\n") : printf("word not in dictionary\n");
	} while(0 != strcmp("q", input));
		
	HashForeach(hash, &Clean, NULL);
		
	fclose(fp);
	HashDestroy(hash);
	hash = NULL;
}

size_t HashFunc(const void *key)
{
	return (*(size_t *)key % TABLE_SIZE);
}


int IsMatch(const void *key1, const void *key2)
{
	return (*(size_t *)key1 == *(size_t *)key2);
}

void *GetKey(const void *item)
{
	return (&(((item_t *)item)->key));
}

int Print(void *item, void *param)
{
	printf("%c, ", ((item_t *)item)->value);
	(void)param;
	
	return 0;
}

size_t HashFunc2(const void *key)
{
	size_t hash = TABLE_SIZE_2;
	int c = 0;
	unsigned char *str = (unsigned char *)key;

	while (0 != (c = *str++))
	{
		hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
	}

	return (hash % TABLE_SIZE_2);
}

int IsMatch2(const void *key1, const void *key2)
{
	return (0 == strcmp((char *)key1, (char *)key2));
}

void *GetKey2(const void *item)
{
	return ((void *)item);
}

int Clean(void *item, void *param)
{
	free(item);
	item = NULL;
	(void)param;
	
	return 0;
}



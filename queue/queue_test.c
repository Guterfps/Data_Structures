/*-------------------------------------------*/
/* DEVELOPER: Itay Guter                    */
/* LAST MODIFIED: 12/12/2022               */
/* WORKSHEET NAME: Queue			      */
/* REVIEWER: Noy Cohen	                 */
/*--------------------------------------*/

#include <stdio.h>		/*printf()*/

#include "queue.h"		/*function declerations and typedefs*/

#define MAX_QUEUE 10000

void Test1(void);
void Test2(void);
void Test3(void);

int main(void)
{
	Test1();
	Test2();
	Test3();
	
	return 0;
}

void Test1(void)
{
	queue_t *queue = QueueCreate();
	int item = 1;
	size_t i = 0;
	int flag = 0;
	
	for (; i < MAX_QUEUE; ++i)
	{
		flag = QueueEnqueue(queue, &item);
	}
	
	printf("Is queue empty:  ");
	QueueIsEmpty(queue) ? printf("FAIL\n") : printf("SUCCESS\n");
	printf("size of queue:  ");
	(QueueSize(queue) == MAX_QUEUE) ?  printf("SUCCESS\n") : printf("FAIL\n");
	printf("Enqueue test:	");
	(0 == flag) ? printf("SUCCESS\n") : printf("FAIL\n");
	
	for (i = 0; i < MAX_QUEUE; ++i)
	{
		QueueDequeue(queue);
	}
	
	printf("Dequeue test:	");
	QueueIsEmpty(queue) ? printf("SUCCESS\n") : printf("FAIL\n");
	printf("size of queue:  ");
	(0 == QueueSize(queue)) ? printf("SUCCESS\n") : printf("FAIL\n");
	
	QueueDestroy(queue);
}

void Test2(void)
{
	queue_t *queue = QueueCreate();
	int item1 = 1;
	int item2 = 2;
	int item3 = 3;
	
	printf("\n Test2: \n");
	printf("Is queue empty:  ");
	QueueIsEmpty(queue) ? printf("SUCCESS\n") : printf("FAIL\n");
	
	
	QueueEnqueue(queue, &item1);
	QueueEnqueue(queue, &item2);
	QueueEnqueue(queue, &item3);
	printf("Is queue empty:  ");
	QueueIsEmpty(queue) ? printf("FAIL\n") : printf("SUCCESS\n");
	
	QueueDequeue(queue);
	printf("size of queue:  ");
	(*(int *)QueuePeek(queue) == item2) ? printf("SUCCESS\n") : printf("FAIL\n");
	QueueDequeue(queue);
	printf("Is queue empty:  ");
	QueueIsEmpty(queue) ? printf("FAIL\n") : printf("SUCCESS\n");
	printf("size of queue:  ");
	(QueueSize(queue) == 1) ? printf("SUCCESS\n") : printf("FAIL\n");
	
	QueueDequeue(queue);
	
	printf("Is queue empty:  ");
	QueueIsEmpty(queue) ? printf("SUCCESS\n") : printf("FAIL\n");
	
	QueueDestroy(queue);
}

void Test3(void)
{
	queue_t *queue1 = QueueCreate();
	int item1 = 1;
	int item2 = 2;
	int item3 = 3;
	int item4 = 4;
	queue_t *queue2 = QueueCreate();
	int item5 = 1;
	int item6 = 2;
	int item7 = 3;
	
	printf("\n Test3: \n");
	QueueEnqueue(queue1, &item1);
	QueueEnqueue(queue1, &item2);
	QueueEnqueue(queue1, &item3);
	QueueEnqueue(queue1, &item4);
	QueueEnqueue(queue2, &item5);
	QueueEnqueue(queue2, &item6);
	QueueEnqueue(queue2, &item7);

	QueueAppend(queue1, queue2);
	printf("size of queue1: ");
	(QueueSize(queue1) == 7) ? printf("SUCCESS\n") : printf("FAIL\n");
	printf("Is queue1 empty:  ");
	QueueIsEmpty(queue1) ? printf("FAIL\n") : printf("SUCCESS\n");
	
	printf("size of queue2: ");
	(QueueSize(queue2) == 0) ? printf("SUCCESS\n") : printf("FAIL\n");
	printf("Is queue2 empty:  ");
	QueueIsEmpty(queue2) ? printf("SUCCESS\n") : printf("FAIL\n");
	
	QueueAppend(queue1, queue2);
	printf("size of queue1: ");
	(QueueSize(queue1) == 7) ? printf("SUCCESS\n") : printf("FAIL\n");
	printf("Is queue1 empty:  ");
	QueueIsEmpty(queue1) ? printf("FAIL\n") : printf("SUCCESS\n");
	
	printf("size of queue2: ");
	(QueueSize(queue2) == 0) ? printf("SUCCESS\n") : printf("FAIL\n");
	printf("Is queue2 empty:  ");
	QueueIsEmpty(queue2) ? printf("SUCCESS\n") : printf("FAIL\n");
	
	QueueAppend(queue2, queue1);
	printf("size of queue1: ");
	(QueueSize(queue1) == 0) ? printf("SUCCESS\n") : printf("FAIL\n");
	printf("Is queue1 empty:  ");
	QueueIsEmpty(queue1) ? printf("SUCCESS\n") : printf("FAIL\n");
	
	printf("size of queue2: ");
	(QueueSize(queue2) == 7) ? printf("SUCCESS\n") : printf("FAIL\n");
	printf("Is queue2 empty:  ");
	QueueIsEmpty(queue2) ? printf("FAIL\n") : printf("SUCCESS\n");
	
	QueueAppend(queue1, queue2);
	printf("size of queue1: ");
	(QueueSize(queue1) == 7) ? printf("SUCCESS\n") : printf("FAIL\n");
	printf("Is queue1 empty:  ");
	QueueIsEmpty(queue1) ? printf("FAIL\n") : printf("SUCCESS\n");
	
	printf("size of queue2: ");
	(QueueSize(queue2) == 0) ? printf("SUCCESS\n") : printf("FAIL\n");
	printf("Is queue2 empty:  ");
	QueueIsEmpty(queue2) ? printf("SUCCESS\n") : printf("FAIL\n");
	
	QueueDequeue(queue1);

	QueueDequeue(queue1);

	QueueDequeue(queue1);

	QueueDequeue(queue1);

	QueueDequeue(queue1);

	QueueDequeue(queue1);
	printf("size of queue1: ");
	(QueueSize(queue1) == 1) ? printf("SUCCESS\n") : printf("FAIL\n");
	printf("Is queue1 empty:  ");
	QueueIsEmpty(queue1) ? printf("FAIL\n") : printf("SUCCESS\n");
	
	QueueEnqueue(queue2, &item6);
	printf("size of queue2: ");
	(QueueSize(queue2) == 1) ? printf("SUCCESS\n") : printf("FAIL\n");
	printf("Is queue2 empty:  ");
	QueueIsEmpty(queue1) ? printf("FAIL\n") : printf("SUCCESS\n");
	
	QueueDestroy(queue1);
	QueueDestroy(queue2);
}


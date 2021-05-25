#define _CRT_SECURE_NO_WARNINGS 1
#include"Queue.h"
void QueueTest()
{
	Queue q;
	QueueInit(&q);
	QueuePush(&q,1);
	QueuePush(&q,2);
	QueuePush(&q,3);
	QueuePush(&q,4);
	QueuePush(&q,5);
	QueuePop(&q);
	printf("%d\n", QueueFront(&q));
	printf("%d\n", QueueBack(&q));
	printf("%d\n", QueueSize(&q));
	if (!QueueEmpty(&q))
		printf("Not Empty\n");
	else
		printf("Empty\n");
	while (!QueueEmpty(&q))
	{
		printf("%d ", QueueFront(&q));
		QueuePop(&q);
	}
	printf("\n");
	QueueDestroy(&q);
}
int main()
{
	QueueTest();
	return 0;
}
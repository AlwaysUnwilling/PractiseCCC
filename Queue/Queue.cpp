#define _CRT_SECURE_NO_WARNINGS 1
#include"Queue.h"
void QueueInit(Queue* pq)//初始化
{
	assert(pq);
	pq->head = pq->tail = NULL;
}
void QueueDestroy(Queue* pq)//销毁
{
	assert(pq);
	QNode* cur = pq->head;
	while (cur)
	{
		QNode* next = cur->next;
		free(cur);
		cur = next;
	}
	pq->head = pq->tail = NULL;
}
void QueuePush(Queue* pq, QDataType x)//队尾入（尾插）
{
	assert(pq);
	QNode* node = (QNode*)malloc(sizeof(QNode));
	if (node == NULL)
	{
		printf("malloc fail\n");
		exit(-1);
	}
	node->data = x;
	node->next = NULL;
	if (pq->head==NULL)
	{
		pq->head = pq->tail = node;
	}
	else
	{
		pq->tail->next = node;
		pq->tail = pq->tail->next;
	}
}
void QueuePop(Queue* pq)//队头出（头删）
{
	assert(pq);
	assert(pq->head);	
	if (pq->head->next == NULL)
	{
		free(pq->head);
		pq->head = pq->tail = NULL;
	}
	else
	{
		QNode* next = pq->head->next;
		free(pq->head);
		pq->head = next;
	}
}
QDataType QueueFront(Queue* pq)//取头数据
{
	assert(pq);
	assert(pq->head);
	return pq->head->data;
}
QDataType QueueBack(Queue* pq)//取队尾数据
{
	assert(pq);
	assert(pq->head);
	return pq->tail->data;
}
int QueueSize(Queue* pq)//输出队列大小
{
	assert(pq);
	int size = 0;
	QNode* cur = pq->head;
	while (cur)
	{
		size++;
		cur = cur->next;
	}
	return size;
}
bool QueueEmpty(Queue* pq)//判空
{
	assert(pq);
	return pq->head == NULL;
}
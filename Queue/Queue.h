#pragma once
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<assert.h>
#include<stdbool.h>

typedef int QDataType;
typedef struct QueueNode
{
	struct QueueNode* next;
	QDataType data;
}QNode;
struct Queue
{
	QNode* head;
	QNode* tail; 
};

void QueueInit(Queue* pq);//初始化
void QueueDestroy(Queue* pq);//销毁
void QueuePush(Queue* pq, QDataType x);//队尾入（尾插）
void QueuePop(Queue* pq);//队头出（头删）
QDataType QueueFront(Queue* pq);//取头数据
QDataType QueueBack(Queue* pq);//取队尾数据
int QueueSize(Queue* pq);//输出队列大小
bool QueueEmpty(Queue* pq);//判空

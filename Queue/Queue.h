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

void QueueInit(Queue* pq);//��ʼ��
void QueueDestroy(Queue* pq);//����
void QueuePush(Queue* pq, QDataType x);//��β�루β�壩
void QueuePop(Queue* pq);//��ͷ����ͷɾ��
QDataType QueueFront(Queue* pq);//ȡͷ����
QDataType QueueBack(Queue* pq);//ȡ��β����
int QueueSize(Queue* pq);//������д�С
bool QueueEmpty(Queue* pq);//�п�

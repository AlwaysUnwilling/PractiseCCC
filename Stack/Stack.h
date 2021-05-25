#pragma once
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<assert.h>
#include<stdbool.h>
typedef int STDataType;
typedef struct Stack
{
	STDataType* a;
	int top;
	int capacity;
}ST;
void StackInit(Stack* ps);
void StackDestroy(Stack* ps);
//ջ������ɾ��
void StackPush(Stack* ps,STDataType x);
void StackPop(Stack* ps);
STDataType StackTop(Stack* ps);  // ȡջ��������
int StackSize(Stack* ps);// ��ջ�Ĵ�С
bool StackEmpty(Stack* ps);//�ж�ջ�Ƿ�Ϊ��
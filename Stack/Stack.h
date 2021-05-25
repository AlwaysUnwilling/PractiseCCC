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
//栈顶插入删除
void StackPush(Stack* ps,STDataType x);
void StackPop(Stack* ps);
STDataType StackTop(Stack* ps);  // 取栈顶的数据
int StackSize(Stack* ps);// 求栈的大小
bool StackEmpty(Stack* ps);//判断栈是否为空
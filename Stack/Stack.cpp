#define _CRT_SECURE_NO_WARNINGS 1
#include"Stack.h"
void StackInit(Stack* ps)//初始化
{
	assert(ps);
	ps->a = (STDataType*)malloc(sizeof(STDataType)*4);
	if (ps->a == NULL)
	{
		printf("malloc fail\n");
		exit(-1);
	}
	ps->capacity = 4;
	ps->top = 0;
}
void StackDestroy(Stack* ps)//销毁
{
	assert(ps);
	free(ps->a);
	ps->a = NULL;
}
//栈顶插入删除
void StackPush(Stack* ps, STDataType x)//入栈
{
	assert(ps);
	if (ps->top == ps->capacity)
	{
		STDataType* tmp = (STDataType*)realloc(ps->a, sizeof(STDataType) * 2 * (ps->capacity));
		if (tmp == NULL)
		{
			printf("realloc fail\n");
			exit(-1);
		}
		else
		{
			ps->a = tmp;
			ps->capacity *= 2;
		}
	}
	ps->a[ps->top] = x;
	ps->top++;
}
void StackPop(Stack* ps)//出栈
{
	assert(ps);
	assert(ps->top > 0);//栈为空直接报错
	ps->top--;
}
STDataType StackTop(Stack* ps)  // 取栈顶的数据
{
	assert(ps);
	assert(ps->top > 0);
	return ps->a[ps->top - 1];
}
int StackSize(Stack* ps)// 求栈的大小
{
	assert(ps);
	return ps->top;
}
bool StackEmpty(Stack* ps)//判断栈是否为空
{
	assert(ps);
	return ps->top == 0;
}
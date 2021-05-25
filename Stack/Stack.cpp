#define _CRT_SECURE_NO_WARNINGS 1
#include"Stack.h"
void StackInit(Stack* ps)//��ʼ��
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
void StackDestroy(Stack* ps)//����
{
	assert(ps);
	free(ps->a);
	ps->a = NULL;
}
//ջ������ɾ��
void StackPush(Stack* ps, STDataType x)//��ջ
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
void StackPop(Stack* ps)//��ջ
{
	assert(ps);
	assert(ps->top > 0);//ջΪ��ֱ�ӱ���
	ps->top--;
}
STDataType StackTop(Stack* ps)  // ȡջ��������
{
	assert(ps);
	assert(ps->top > 0);
	return ps->a[ps->top - 1];
}
int StackSize(Stack* ps)// ��ջ�Ĵ�С
{
	assert(ps);
	return ps->top;
}
bool StackEmpty(Stack* ps)//�ж�ջ�Ƿ�Ϊ��
{
	assert(ps);
	return ps->top == 0;
}
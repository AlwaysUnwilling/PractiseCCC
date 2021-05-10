#define _CRT_SECURE_NO_WARNINGS 1
#include"Seqlist.h"

void SeqlistCheckCapicity(SL* ps)
{
	assert(ps);
	if (ps->size >= ps->capacity)
	{
		ps->capacity *= 2;   //通常是按2倍去增容
		ps->a = (SLDataType*)realloc(ps->a, sizeof(SLDataType) * ps->capacity);
		if (ps->a == NULL)
		{
			printf("增容失败\n");
			exit(-1);
		}
	}
}
void SeqlistInit(SL* ps)
{
	/*s.size = 0;      //其中一种初始化
	s.a =NULL;
	s.capicity = 0;*/

     // 另一种初始化
	ps->a = (SLDataType*)malloc(sizeof(SLDataType) * 4);
	if (ps->a == NULL)
	{
		printf("申请内存失败！\n");
		exit(-1);  //申请内存失败，字节结束程序！
	}
	ps->size = 0;
	ps->capacity = 4;
}
void SeqlistPushBack(SL* ps, SLDataType x) //尾插
{
	assert(ps);
	//如果满了需要增容
	void SeqlistCheckCapicity(SL * ps);
	ps->a[ps->size] = x;
	ps->size++;
}
void SeqlistPrint(SL* ps)
{
	assert(ps);
	for (int i = 0; i < ps->size; i++)
	{
		printf("%d ", ps->a[i]);
	}
	printf("\n");
}
void SeqlistPopBack(SL* ps) //尾删
{
	assert(ps);
	ps->size--;
}
void SeqlistPushFront(SL* ps, SLDataType x) //头插
{
	assert(ps);
	int end = ps->size - 1;
	void SeqlistCheckCapicity(SL * ps);
	while (end >= 0)
	{
		ps->a[end + 1] = ps->a[end];
		end--;
	}
	ps->a[0] = x;
	ps->size++;
}
void SeqlistPopFront(SL* ps) //头删
{
	assert(ps);
	int front = 0;
	while (front < ps->size - 1)
	{
		ps->a[front] = ps->a[front + 1];
		front++;
	}
	ps->size--;
}
void SeqlistInsert(SL* ps, int pos, SLDataType x)  //任意位置插入
{
	assert(ps);
	void SeqlistCheckCapicity(SL * ps);
	int tmp = 0;
	while (tmp<=ps->size-pos)
	{
		ps->a[ps->size-tmp] = ps->a[ps->size - 1-tmp];
		tmp++;
	}
	ps->a[pos-1] = x;
	ps->size++;
}
void SeqlistErase(SL* ps, int pos) // 任意位置删除
{
	assert(ps);
	int tmp = 0;
	while (tmp<=ps->size-pos)
	{
		ps->a[pos+tmp-1] = ps->a[pos +tmp];
		tmp++;
	}
	ps->size--;
}

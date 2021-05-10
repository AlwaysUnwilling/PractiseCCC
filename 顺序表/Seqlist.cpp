#define _CRT_SECURE_NO_WARNINGS 1
#include"Seqlist.h"

void SeqlistCheckCapicity(SL* ps)
{
	assert(ps);
	if (ps->size >= ps->capacity)
	{
		ps->capacity *= 2;   //ͨ���ǰ�2��ȥ����
		ps->a = (SLDataType*)realloc(ps->a, sizeof(SLDataType) * ps->capacity);
		if (ps->a == NULL)
		{
			printf("����ʧ��\n");
			exit(-1);
		}
	}
}
void SeqlistInit(SL* ps)
{
	/*s.size = 0;      //����һ�ֳ�ʼ��
	s.a =NULL;
	s.capicity = 0;*/

     // ��һ�ֳ�ʼ��
	ps->a = (SLDataType*)malloc(sizeof(SLDataType) * 4);
	if (ps->a == NULL)
	{
		printf("�����ڴ�ʧ�ܣ�\n");
		exit(-1);  //�����ڴ�ʧ�ܣ��ֽڽ�������
	}
	ps->size = 0;
	ps->capacity = 4;
}
void SeqlistPushBack(SL* ps, SLDataType x) //β��
{
	assert(ps);
	//���������Ҫ����
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
void SeqlistPopBack(SL* ps) //βɾ
{
	assert(ps);
	ps->size--;
}
void SeqlistPushFront(SL* ps, SLDataType x) //ͷ��
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
void SeqlistPopFront(SL* ps) //ͷɾ
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
void SeqlistInsert(SL* ps, int pos, SLDataType x)  //����λ�ò���
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
void SeqlistErase(SL* ps, int pos) // ����λ��ɾ��
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

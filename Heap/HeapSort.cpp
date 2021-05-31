#define _CRT_SECURE_NO_WARNINGS 1
#include"Heap.h"
void HeapSort(HPDataType* a, int size)//��С�� ���µ��� �Ž���
{
	assert(a);
	for (int i = (size - 2) / 2; i >= 0; i--)
	{
		AdjustDown(a, size, i);
	}
	int end = size - 1;
	while (end > 0)
	{
		Swap(&a[0], &a[end]);
		//�ټ���ѡ��С��
		AdjustDown(a, end, 0);
		--end;
	}
}

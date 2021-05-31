#define _CRT_SECURE_NO_WARNINGS 1
#include"Heap.h"
void Swap(HPDataType* element1, HPDataType* element2)
{
	HPDataType tmp = *element1;
	*element1 = *element2;
	*element2 = tmp;
}
//左右子树都是小堆
void AdjustDown(HPDataType* a, int n,int root)
{
	int parent = root;
	int child = 2 * parent + 1;
	while (child < n)
	{
		if (child + 1 < n && a[child + 1] < a[child])
		{
			child++;
		}
		if (a[child] < a[parent])
		{
			Swap(&a[child], &a[parent]);
			parent = child;
			child = 2 * parent + 1;
		}
		else
		{
			break;
		}
	}
}
void AdjustUP(HPDataType* a, int n, int child)
{
	assert(a);
	int parent = (child - 1) / 2;
	while (child > 0)
	{
		if (a[child] < a[parent])
		{
			Swap(&a[child], &a[parent]);
			child = parent;
			parent = (child - 1) / 2;
		}
		else
		{
			break;
		}
	}
}
void HeapInit(Heap* php, HPDataType* a, int n)//初始化
{
	php->_a = (HPDataType*)malloc(sizeof(HPDataType) * n);
	if (php->_a == NULL)
	{
		printf("malloc fail\n");
		exit(-1);
	}
	php->size = php->capacity = n;
	memcpy(php->_a, a, sizeof(HPDataType) * n);
	//构建小堆
	for (int i = (n - 2) / 2; i >= 0; i--)
	{
		AdjustDown(php->_a, php->size, i);
	}
}
void HeapDestroy(Heap* php)//销毁
{
	assert(php);
	free(php->_a);
	php->_a = NULL;
	php->capacity = php->size = 0;
}
void HeapPush(Heap* php, HPDataType x)
{
	assert(php);
	if (php->size == php->capacity)
	{
		HPDataType* tmp = (HPDataType*)realloc(php->_a,sizeof(HPDataType) * 2 * php->capacity);
		if (tmp == NULL)
		{
			printf("realloc fail\n");
			exit(-1);
		}
		php->capacity *= 2;
		php->_a = tmp;
	}
	php->_a[php->size++] = x;
	AdjustUP(php->_a, php->size, php->size - 1);
}
void HeapPop(Heap* php)
{
	assert(php);
	assert(php->size>0);
	Swap(&php->_a[0], &php->_a[php->size - 1]);
	php->size--;
	AdjustDown(php->_a, php->size, 0);
}
HPDataType HeapTop(Heap* php)
{
	assert(php);
	assert(php->size > 0);
	return php->_a[0];
}
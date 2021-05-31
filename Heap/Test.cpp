#define _CRT_SECURE_NO_WARNINGS 1
#include"Heap.h"
int main()
{
	int a[] = { 27,15,19,18,28,34,65,49,25,37 };
	Heap hp;
	HeapInit(&hp, a, sizeof(a) / sizeof(HPDataType));
	HeapPush(&hp, 13);
	HeapPop(&hp);
	printf("%d\n", HeapTop(&hp));
	HeapDestroy(&hp);
	return 0;
}
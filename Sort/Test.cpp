#define _CRT_SECURE_NO_WARNINGS 1
#include"Sort.h"
void PrintArry(int* a, int n)
{
	for (int i = 0; i < n; i++)
	{
		printf("%d ", a[i]);
	}
	printf("\n");
	printf("\n");
}
void InsertSortTest()
{
	int a[] = { 9,5,2,3,7,6,21,6,42,4,0,6,4,7,8,1 };
	PrintArry(a, sizeof(a) / sizeof(int));
	InsertSort(a, sizeof(a) / sizeof(int));
	printf("InsertSort:");
	PrintArry(a, sizeof(a) / sizeof(int));
}
void ShellSortTest()
{
	int a[] = { 9,5,2,3,7,6,21,6,42,4,0,6,4,7,8,1 };
	PrintArry(a, sizeof(a) / sizeof(int));
	ShellSort(a, sizeof(a) / sizeof(int));
	printf("ShellSort:");
	PrintArry(a, sizeof(a) / sizeof(int));
}
void SelectSortTest()
{
	int a[] = { 9,5,2,3,7,6,21,6,42,4,0,6,4,7,8,1 };
	PrintArry(a, sizeof(a) / sizeof(int));
	SelectSort(a, sizeof(a) / sizeof(int));
	printf("SelectSort:");
	PrintArry(a, sizeof(a) / sizeof(int));
}
void HeapSortTest()
{
	int a[] = { 9,5,2,3,7,6,21,6,42,4,0,6,4,7,8,1 };
	PrintArry(a, sizeof(a) / sizeof(int));
	HeapSort(a, sizeof(a) / sizeof(int),0);
	printf("HeapSort:");
	PrintArry(a, sizeof(a) / sizeof(int));
}
void BubbleSortTest()
{
	int a[] = { 9,5,2,3,7,6,21,6,42,4,0,6,4,7,8,1 };
	PrintArry(a, sizeof(a) / sizeof(int));
	BubbleSort(a, sizeof(a) / sizeof(int));
	printf("BubbleSort:");
	PrintArry(a, sizeof(a) / sizeof(int));
}
void QuickSortTest()
{
	int a[] = { 9,5,2,3,7,6,21,6,42,4,0,6,4,7,8,1 };
	PrintArry(a, sizeof(a) / sizeof(int));
	QuickSort(a, 0,sizeof(a) / sizeof(int)-1);
	printf("QuickSort:");
	PrintArry(a, sizeof(a) / sizeof(int));
}
int main()
{
	/*InsertSortTest();
	ShellSortTest();
	SelectSortTest();
	HeapSortTest();
	BubbleSortTest();*/
	QuickSortTest();
	return 0;
}

#define _CRT_SECURE_NO_WARNINGS 1
#include"Sort.h"

void InsertSortTest()
{
	int a[] = { 9,5,2,3,7,6,21,6,42,4,0,6,4,7,8,1 };
	PrintArray(a, sizeof(a) / sizeof(int));
	InsertSort(a, sizeof(a) / sizeof(int));
	printf("InsertSort:");
	PrintArray(a, sizeof(a) / sizeof(int));
}
void ShellSortTest()
{
	int a[] = { 9,5,2,3,7,6,21,6,42,4,0,6,4,7,8,1 };
	PrintArray(a, sizeof(a) / sizeof(int));
	ShellSort(a, sizeof(a) / sizeof(int));
	printf("ShellSort:");
	PrintArray(a, sizeof(a) / sizeof(int));
}
void SelectSortTest()
{
	int a[] = { 9,5,2,3,7,6,21,6,42,4,0,6,4,7,8,1 };
	PrintArray(a, sizeof(a) / sizeof(int));
	SelectSort(a, sizeof(a) / sizeof(int));
	printf("SelectSort:");
	PrintArray(a, sizeof(a) / sizeof(int));
}
void HeapSortTest()
{
	int a[] = { 9,5,2,3,7,6,21,6,42,4,0,6,4,7,8,1 };
	PrintArray(a, sizeof(a) / sizeof(int));
	HeapSort(a, sizeof(a) / sizeof(int),0);
	printf("HeapSort:");
	PrintArray(a, sizeof(a) / sizeof(int));
}
void BubbleSortTest()
{
	int a[] = { 9,5,2,3,7,6,21,6,42,4,0,6,4,7,8,1 };
	PrintArray(a, sizeof(a) / sizeof(int));
	BubbleSort(a, sizeof(a) / sizeof(int));
	printf("BubbleSort:");
	PrintArray(a, sizeof(a) / sizeof(int));
}
void QuickSortTest()
{
	int a[] = { 9,5,2,3,7,6,21,6,42,4,0,6,4,7,8,1 };
	PrintArray(a, sizeof(a) / sizeof(int));
	QuickSort(a, 0,sizeof(a) / sizeof(int)-1);
	printf("QuickSort:");
	PrintArray(a, sizeof(a) / sizeof(int));
}
void QuickSortNonRTest() 
{
	int a[] = { 9,5,2,3,7,6,21,6,42,4,0,6,4,7,8,1 };
	PrintArray(a, sizeof(a) / sizeof(int));
	QuickSortNonR(a, 0, sizeof(a) / sizeof(int) - 1);
	printf("QuickSortNonR:");
	PrintArray(a, sizeof(a) / sizeof(int));
}
void MergeSortTest()
{
	int a[] = { 9,5,2,3,7,6,21,6,42,4,0,6,4,7,8,1 };
	PrintArray(a, sizeof(a) / sizeof(int));
	MergeSort(a, sizeof(a) / sizeof(int));
	printf("MergeSort:");
	PrintArray(a, sizeof(a) / sizeof(int));
}
void MergeSortNonRTest()
{
	int a[] = { 9,5,2,3,7,6,21,6,42,4,0,6,4,7,8,1 };
	PrintArray(a, sizeof(a) / sizeof(int));
	MergeSortNonR(a, sizeof(a) / sizeof(int));
	printf("MergeSortNonR:");
	PrintArray(a, sizeof(a) / sizeof(int));
}
void CountSortTest()
{
	int a[] = { 9,5,2,3,7,6,0,6,9,4,0,6,4,7,8,1 };
	PrintArray(a, sizeof(a) / sizeof(int));
	CountSort(a, sizeof(a) / sizeof(int));
	printf("CountSort:");
	PrintArray(a, sizeof(a) / sizeof(int));
}
int main()
{
	/*InsertSortTest();
	ShellSortTest();
	SelectSortTest();
	HeapSortTest();
	BubbleSortTest();*/
	//QuickSortTest();
	/*QuickSortNonRTest();
	MergeSortTest();
	MergeSortNonRTest();*/
	//MergeSortFile("sort.txt");
	CountSortTest();
	return 0;
}


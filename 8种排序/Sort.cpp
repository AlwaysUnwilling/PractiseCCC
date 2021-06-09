#define _CRT_SECURE_NO_WARNINGS 1
#include"Sort.h"
#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<assert.h>
#include<stdbool.h >
typedef char STDataType;
typedef struct Stack
{
	STDataType* a;
	int top;
	int capacity;
}ST;
void StackInit(ST* st)
{
	st->a = (STDataType*)malloc(sizeof(STDataType) * 4);
	if (st->a == NULL)
	{
		printf("malloc fail\n");
		exit(-1);
	}
	st->capacity = 4;
	st->top = 0;
}
void StackPush(ST* st, STDataType x)
{
	assert(st);
	if (st->top == st->capacity)
	{
		STDataType* tmp = (STDataType*)realloc(st->a, st->capacity * 2 * sizeof(STDataType));
		if (tmp == NULL)
		{
			printf("realloc fail\n");
			exit(-1);
		}
		st->a = tmp;
		st->capacity *= 2;
	}
	st->a[st->top] = x;
	st->top++;
}
void StackPop(ST* st)
{
	assert(st);
	assert(st->top > 0);
	st->top--;
}
STDataType StackTop(ST* st)
{
	assert(st);
	assert(st->top > 0);
	return st->a[st->top - 1];
}
bool StackEmpty(ST* st)
{
	assert(st);
	return st->top == 0;
}
int StackSize(ST* st)
{
	assert(st);
	return st->top;
}
void StackDestroy(ST* st)
{
	assert(st);
	free(st->a);
	st->a = NULL;
}

void PrintArray(int* a, int n)
{
	for (int i = 0; i < n; i++)
	{
		printf("%d ", a[i]);
	}
	printf("\n");
	printf("\n");
}
void Swap(int* element1, int* element2)
{
	int tmp = *element1;
	*element1 = *element2;
	*element2 = tmp;
}
void InsertSort(int* a, int n)
{
	assert(a);
	for (int i = 0; i < n - 1; i++)
	{
		int end = i;
		int tmp = a[end + 1];
		while (end >= 0)
		{
			if (tmp < a[end])
			{
				a[end + 1] = a[end];
				end--;
			}
			else
				break;
		}
		a[end + 1] = tmp;
	}
}
void ShellSort(int* a, int n)
{
	assert(a);
	int gap = n;
	while (gap > 1)
	{
		gap = gap / 3 + 1;
		for (int i = 0; i < n - gap; i++)
		{
			int end = i;
			int tmp = a[end + gap];
			while (end >= 0)
			{
				if (tmp < a[end])
				{
					a[end + gap] = a[end];
					end -= gap;
				}
				else
					break;
			}
			a[end+gap] = tmp;
		}
	}
	
}
void SelectSort(int* a, int n)
{
	assert(a);
	int begin = 0;
	int end = n - 1;
	while (begin < end)
	{
		int mini, maxi;
		mini = maxi = begin;
		for (int i = begin + 1; i <= end; i++)
		{
			if (a[i]>a[maxi])
			{
				maxi = i;
			}
			if (a[i] < a[mini])
			{
				mini = i;
			}
		}
		Swap(&a[begin], &a[mini]);
		if (begin == maxi)
			maxi = mini;
		Swap(&a[end], &a[maxi]);
		++begin;
		--end; 
	}
}
void AdjustDown(int* a, int n,int root)
{
	int parent = root;
	int child = 2 * parent + 1;
	int end = n;
	while (child < n)
	{
		if (child + 1 < n && a[child + 1] > a[child])
			++child;
		if (a[child] > a[parent])
		{
			Swap(&a[child], &a[parent]);
			parent = child;
			child = 2 * parent + 1;
		}
		else
			break;
	}
}
void HeapSort(int* a, int n, int root)
{
	assert(a);
	for (int i = (n - 2) / 2; i >= 0; --i)
	{
		AdjustDown(a, n, i);
	}
	int end = n - 1;
	while (end > 0)
	{
		Swap(&a[end], &a[0]);
		AdjustDown(a, end, 0);
		--end;
	}
}
void BubbleSort(int* a, int n)
{
	assert(a);
	int end = n - 1;
	while (end > 0)
	{
		int exchange = 0;
		for (int i = 0; i < end; i++)
		{
			if (a[i] > a[i + 1])
			{
				Swap(&a[i], &a[i + 1]);
				exchange = 1;
			}
		}
		if (exchange == 0)
			break;
		--end;
	}
}
int GetMidIndex(int* a, int begin, int end)
{
	assert(a);
	int mid = (begin + end) / 2;
	if (a[begin] > a[mid])
	{
		if (a[mid] > a[end])
			return mid;
		else if (a[end] < a[begin])
			return end;
		else
			return begin;
	}
	else
	{
		if (a[begin] > a[end])
			return begin;
		else if (a[end] < a[mid])
			return end;
		else
			return mid;
	}
}
int PartSort(int* a, int begin, int end)
{
	Swap(&a[GetMidIndex(a, begin, end)], &a[end]);
	int midindex = end;
	while (begin < end)
	{
		while (begin < end && a[begin]<=a[midindex])
		{
			++begin;
		}
		while (begin < end && a[end]>=a[midindex])
		{
			--end;
		}

		Swap(&a[begin], &a[end]);
	}
	Swap(&a[begin], &a[midindex]);
	return begin;
}
int PartSort2(int* a, int begin, int end)//�ڿӷ�
{
	Swap(&a[GetMidIndex(a, begin, end)], &a[end]);
	int key = a[end];//�ڿӣ������һ��λ�����߱�����������Ϊ���һ��λ��Ϊ��
	while (begin < end)
	{
		while (begin < end && a[begin] <= key)//��߿�ʼ�Ҵ���key��ֵ���ҵ���beginλ�õ�ֵ���߷���end�Ŀ����ʱ�γ����µĿ�begin
			++begin;

		a[end] = a[begin];
		while (begin < end && a[end] >= key)//�ұ߿�ʼ��С��key��ֵ���ҵ���beginλ�õ�ֵ���߷���begin�Ŀ����ʱ�γ����µĿ�end
			--end;

		a[begin] = a[end];
	}
	a[begin] = key;//��begin��end������begin==end�����˳�ѭ�����µĿӣ�begin����end������ԭ�������key����
	return begin;
}
int PartSort3(int* a, int begin, int end)
{
	Swap(&a[GetMidIndex(a, begin, end)], &a[end]);
	int key = a[end];
	//int prev = 0;
	//int cur = 0;
	//while (cur <= end)
	//{
	//	while (cur <= end && a[cur] > key)
	//		++cur;

	//	Swap(&a[prev], &a[cur]);
	//	++prev;
	//	++cur;
	//}
	//return prev-1;

	int cur = begin;
	int prev = begin - 1;
	while (cur < end)
	{
		if (a[cur] < key && ++prev != cur)
			Swap(&a[prev], &a[cur]);
		++cur;
	}
	Swap(&a[++prev], &a[cur]);
	return prev;
}
void QuickSort(int* a, int left, int right)
{
	assert(a);
	if (left >= right)
		return;
	//int divindex = PartSort(a, left, right);
	//int divindex = PartSort2(a, left, right);
	if (right - left + 1 > 10)
	{
		int divindex = PartSort3(a, left, right);
		QuickSort(a, left, divindex - 1);
		QuickSort(a, divindex + 1, right);
	}
	else
	{
		InsertSort(a + left, right - left + 1);
	}
}
void QuickSortNonR(int* a, int left, int right)
{
	assert(a);
	Stack st;
	StackInit(&st);
	StackPush(&st, right);
	StackPush(&st, left);
	while (!StackEmpty(&st))
	{
		int begin = StackTop(&st);
		StackPop(&st);
		int end = StackTop(&st);
		StackPop(&st);
		int div = PartSort3(a, begin, end);
		if (div + 1 < end)
		{
			StackPush(&st, end);
			StackPush(&st, div + 1);
		}
		if (begin < div - 1)
		{
			StackPush(&st, div - 1);
			StackPush(&st, begin);
		}
	}
	StackDestroy(&st);
}

void MergeArray(int* a, int begin1, int end1, int begin2, int end2, int* tmp)
{
	int left = begin1, right = end2;
	//�鲢[left,mid]��[mid+1,right]����
	int index = begin1;
	while (begin1 <= end1 && begin2 <= end2)
	{
		if (a[begin1] < a[begin2])
			tmp[index++] = a[begin1++];
		else
			tmp[index++] = a[begin2++];
	}
	while (begin1 <= end1)
		tmp[index++] = a[begin1++];
	while (begin2 <= end2)
		tmp[index++] = a[begin2++];
	//�鲢��ɺ�ѹ鲢�õ����ݴ�tmp������ԭ����
	for (int i = left; i <= right; i++)
		a[i] = tmp[i];
}
void _MergeSort(int* a, int left, int right, int* tmp)
{
	if (left >= right)
		return;
	int mid = (left + right) / 2;
	_MergeSort(a, left, mid, tmp);
	_MergeSort(a, mid+1, right, tmp);
	////�鲢[left,mid]��[mid+1,right]����
	//int begin1 = left, end1 = mid;
	//int begin2 = mid+1, end2 = right;
	//int index = begin1;
	//while (begin1 <= end1 && begin2 <= end2)
	//{
	//	if (a[begin1] < a[begin2])
	//		tmp[index++] = a[begin1++];
	//	else
	//		tmp[index++] = a[begin2++];
	//}
	//while (begin1 <= end1)
	//	tmp[index++] = a[begin1++];
	//while (begin2 <= end2)
	//	tmp[index++] = a[begin2++];
	////�鲢��ɺ�ѹ鲢�õ����ݴ�tmp������ԭ����
	//for (int i = left; i <= right; i++)
	//	a[i] = tmp[i];
	MergeArray(a, left, mid, mid + 1, right, tmp);
}
void MergeSort(int* a, int n)
{
	assert(a);
	int* tmp = (int*)malloc(sizeof(int) * n);
	if (tmp == NULL)
	{
		printf("malloc fail\n");
		exit(-1);
	}
	_MergeSort(a, 0, n - 1, tmp);
	free(tmp);
	tmp = NULL;
}
void MergeSortNonR(int* a, int n)
{
	assert(a);
	int* tmp = (int*)malloc(sizeof(int) * n);
	if (tmp == NULL)
	{
		printf("malloc fail\n");
		exit(-1);
	}
	int gap = 1;
	while (gap < n)
	{
		for (int i = 0; i < n; i += 2 * gap)
		{
			//[i,i+gap-1]  [i+gap,i+2*gap-1]
			int begin1 = i, end1 = i + gap - 1;
			int begin2 = i + gap, end2 = i + 2 * gap - 1;
			//1.�ϲ�ʱֻ�е�һ��,�ڶ��鲻���ڣ��Ͳ���Ҫ�ϲ�
			if (begin2 >= n)
				break;
			//2.�ϲ�ʱ�ڶ���ֻ�в������ݣ���Ҫ����end2�߽�
			if (end2 >= n)
				end2 = n - 1;

			MergeArray(a, begin1, end1, begin2,  end2, tmp);
		}
		//PrintArray(a, n);
		gap *= 2;
	}
	free(tmp);
	tmp = NULL;
}

void CountSort(int* a, int n)
{
	assert(a);
	int max = a[0];
	int min = a[0];
	for (int i = 0; i < n; i++)
	{
		if (a[i] > max)
			max = a[i];
		if (a[i] < min)
			min = a[i];
	}
	int range = max - min + 1;
	int* countArr = (int*)malloc(sizeof(int) * range);
	if (countArr == NULL)
	{
		printf("malloc fail\n");
		exit(-1);
	}
	//��ʼ��Ϊȫ0
	memset(countArr, 0, sizeof(int) * range);
	for (int i = 0; i < n; i++)//ͳ�ƴ���
	{
		countArr[a[i] - min]++;
	}
	//����
	int index = 0;
	for (int i = 0; i < range; i++)
	{
		while (countArr[i]--)
		{
			a[index++] = i + min;
		}
	}
	free(countArr);
	countArr = NULL;
}
void _MergeFile(const char* file1, const char* file2, const char* mfile)
{
	FILE* fout1 = fopen(file1, "r");
	if (fout1 == NULL)
	{
		printf("fout1�ļ���ʧ��\n");
		exit(-1);
	}
	FILE* fout2 = fopen(file2, "r");
	if (fout2 == NULL)
	{
		printf("fout2�ļ���ʧ��\n");
		exit(-1);
	}
	FILE* fin = fopen(mfile, "w");
	if (fin == NULL)
	{
		printf("�ļ���ʧ��\n");
		exit(-1);
	} 
	int num1, num2;
	int ret1 = fscanf(fout1, "%d\n", &num1);
	int ret2 = fscanf(fout2, "%d\n", &num2);
	while (ret1 != EOF && ret2 != EOF)
	{
		if (num1 < num2)
		{
			fprintf(fin, "%d\n", num1);
			ret1 = fscanf(fout1, "%d\n", &num1);
		}
		else
		{
			fprintf(fin, "%d\n", num2);
			ret2 = fscanf(fout2, "%d\n", &num2); 
		}
	}
	while (ret1 != EOF)
	{
		fprintf(fin, "%d\n", num1);
		ret1 = fscanf(fout1, "%d\n", &num1);
	}
	while (ret2 != EOF)
	{
		fprintf(fin, "%d\n", num2);
		ret2 = fscanf(fout2, "%d\n", &num2);
	}
	fclose(fout1);
	fclose(fout2);
	fclose(fin);
}
void MergeSortFile(const char* file)
{
	FILE* fout = fopen(file, "r");
	if (fout == NULL)
	{
		printf("�ļ���ʧ��\n");
		exit(-1);
	}
	//�ָ��һС��һС�ε����ݣ��ڴ������д�뵽С�ļ���ȥ
	int n = 10;
	int a[10];
	int i = 0;
	int num = 0;
	char subfile[20];
	int filei = 1;
	while (fscanf(fout, "%d\n", &num) != EOF)
	{
		if (i < n-1)//ǰ9�����ݶ���ŵ������У���10��������if������ʱ�Ѿ���������û�зŽ���������
		{
			a[i++] = num;
		}
		else
		{
			a[i] = num;//�ѵ�10�����ݷŽ��������У������д�ʱ����10������
			QuickSort(a, 0, n - 1);
			sprintf(subfile, "%d", filei++);
			FILE* fin = fopen(subfile, "w");
			if (fin == NULL)
			{
				printf("�ļ���ʧ��\n");
				exit(-1);
			}
		    for (int i = 0; i < n; i++)
			{
				fprintf(fin, "%d\n", a[i]);
			}
		   fclose(fin);
		   i = 0;
			
		}
	}
	//���û���鲢���ļ���ʵ����������
	//...
	char mfile[100] = "12"; 
	char file1[100] = "1";
	char file2[100] ;
	for (int i = 2; i <= n; ++i)
	{
		sprintf(file2, "%d", i);
		//��ȡfile1��file2�����й鲢��mfile
		_MergeFile(file1, file2, mfile);		
		strcpy(file1, mfile);
		//sprintf(file2, "%d", i + 1);
		sprintf(mfile, "%s%d", mfile, i + 1);
	}
	fclose(fout);
}

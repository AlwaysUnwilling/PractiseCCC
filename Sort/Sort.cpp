#define _CRT_SECURE_NO_WARNINGS 1
#include"Sort.h"
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
int PartSort2(int* a, int begin, int end)//挖坑法
{
	Swap(&a[GetMidIndex(a, begin, end)], &a[end]);
	int key = a[end];//挖坑，把最后一个位置拿走保存起来，认为最后一个位置为坑
	while (begin < end)
	{
		while (begin < end && a[begin] <= key)//左边开始找大于key的值，找到后将begin位置的值挖走放在end的坑里，此时形成了新的坑begin
			++begin;

		a[end] = a[begin];
		while (begin < end && a[end] >= key)//右边开始找小于key的值，找到后将begin位置的值挖走放在begin的坑里，此时形成了新的坑end
			--end;

		a[begin] = a[end];
	}
	a[begin] = key;//当begin和end相遇（begin==end），退出循环，新的坑（begin或者end）将由原来保存的key来填
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
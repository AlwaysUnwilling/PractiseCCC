#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
#include<math.h>
//void swp(int* x, int* y)
//{
//	int tmp = 0;
//	tmp = *x;
//	*x = *y;
//	*y = tmp;
//}
//int main()
//{
//	int a = 10;
//	int b = 20;
//	printf("a=%d b=%d\n", a, b);
//	swp(&a, &b);
//	printf("a=%d b=%d\n", a, b);
//	return 0;
//}
//void jud(int x)
//{
//	int j = 1;
//	for (j = 2; j < x; j++)
//	{
//		if (x % j == 0)
//		{
//			break;
//		}
//	}
//	if (j == x)
//	{
//		printf("%d是素数\n", x);
//	}
//	else
//		printf("%d不是素数\n", x);
//}
//int main()
//{
//	int i = 0;
//	do
//	{
//		scanf("%d", &i);
//		jud(i);
//	} while (i<200);
//	return 0;
//}
//int is_prime(int n)
//{
//	int m = 0;
//	for (m = 2; m <= sqrt(n); m++)
//	{
//		if ((n % m) == 0)
//		{
//			return 0;
//		}
//	}
//	if (m > sqrt(n))
//		return 1;
//
//}
//int main()
//{
//	int i = 0;
//	int count = 0;
//	for (i = 100; i <= 200; i++)
//	{
//		if (is_prime(i) == 1)
//		{
//			printf("%d ", i);
//			count++;
//		}
//	}
//	printf("\ncount=%d\n", count);
//	return 0;
//}
//int jude(int n)
//{
//	if ((n % 4 == 0 && n % 100 != 0) || (n % 400 == 0))
//		return 1;
//	else
//		return 0;
//}
//int main()
//{
//	int year = 0;
//	int count = 0;
//	for (year = 1000; year <= 2000; year++)
//	{
//		jude(year);
//		if (jude(year) == 1)
//		{
//			printf("%d  ", year);
//			count++;
//		}
//	}
//	printf("\ncount=%d\n", count);
//	return 0;
//}
//int search(int arr1[],int n ,int j)
//{
//	int left = 0;
//	int right = n - 1;
//	//int mid = (left + right) / 2;
//	while (left<=right)
//	{
//		int mid = (left + right) / 2;
//		if (j > arr1[mid])
//		{
//			left = mid + 1;
//		}
//		else if (j < arr1[mid])
//		{
//			right = mid - 1;
//		}
//		else
//			return mid;
//	}
//		return -1;
//}
//int main()
//{
//	int arr[] = { 1,2,3,4,5,6,7,8,9,10 };
//	int sz = sizeof(arr) / sizeof(arr[0]);
//	int i = 5;
//	//int ret = 0;
//	scanf("%d", &i);
//	int ret=search(arr, sz, i);
//	if (ret == -1)
//	{
//		printf("找不到指定的数字\n");
//	}
//	else
//	{
//		printf("找到了，下标是:%d\n", ret);
//	}
//	return 0;
//}
//int Sum(int x, int y)
//{
//	int z = x + y;
//	return z;
//}
//int main()
//{
//	int num = 0;
//	int i = 0;
//	for (i = 1; i <= 10; i++)
//	{
//		int sum = Sum(i, 10);
//		num++;
//	}
//	printf("num=%d\n", num);
//	return 0;
//}
//void add(int* x, int y, int z)
//{
//	int p = y + z;
//	(*x)++;
//}
//int main()
//{
//	int num = 0;
//	int i = 0;
//	int j = 0;
//	while(num<11)
//	{
//		scanf("%d%d", &i, &j);
//		add(&num, i, j);
//		printf("%d\n", num);
//	}
//	return 0;
//}
int main()
{
	printf("%d", printf("%d", printf("%d", 43)));
	return 0;
}
#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
//   ******************************************* void* malloc()  &  free()
//int main()
//{
//	int* p=(int*)malloc(10 * sizeof(int));  //���ڴ�����40���ֽ�
//	if (p == NULL)
//	{
//		printf("%s\n", strerror(errno));    //ʹ��malloc���������ڴ�ռ�ʱһ��Ҫ�����ж�������ڴ��Ƿ����
//	}
//	else
//	{
//		//����ʹ��
//		int i = 0;
//		for (i = 0; i < 10; i++)
//		{
//			*(p + i) = i;
//			printf("%d ", *(p + i));
//		}
//	 }
//	free(p);//ʹ����malloc ���ٵĿռ��һ���ü�ʱ�ͷŸÿռ�  ����ָ��ÿռ��ַ��ָ��P ��ֵΪ��ָ�� NULL
//	p = NULL;
//	return 0;
//}

//  ****************************************** void*  calloc (num,size) 

//int main()
//{
//	int* p=(int*)calloc(10, sizeof(int));  // ʹ��calloc ����40���ֽڵĿռ�  ���һ��ʼ���ռ�ÿ���ֽ�ȫΪ0
//	if (p == NULL)
//	{
//		printf("%s\n", strerror(errno));
//	}
//	else
//	{
//		//����ʹ��
//		int i = 0;
//		for (i = 0; i < 10; i++)
//		{
//			*(p + i) = i;
//			printf("%d ", *(p + i));
//		}
//	}
//	free(p);
//	p = NULL;
//	return 0;
//}

//  *********************************************  void* realloc(void* ptr,size_t size)  ������̬�ڴ濪�ٵĴ�С

//int main()
//{
//	int* p = (int*)malloc(20);
//	int i = 0;
//	if (p == NULL)
//	{
//		printf("%s\n", strerror(errno));
//	}
//	else
//	{
//		int i = 0;
//		for (i = 0; i < 5; i++)
//		{
//			*(p + i) = i;  //��������20���ֽڲ�������ʹ��������Ҫ������20���ռ䣬��ʱ���ǾͿ���ʹ��realloc�������е��� size_t sizeָ�����ܹ���Ҫ�Ŀռ��С����λ���ֽڣ�
//		}
//	}
//	int* p2 = (int*)realloc(p,40);//1. ���Pָ��Ŀռ�֮�����㹻��Ŀռ䣬����ֱ��׷�ӣ�׷�Ӻ󷵻ص��µ�ַҲ��P��
//	if (p2 == NULL)                               //2.���pָ��Ŀռ�֮��û���㹻��Ŀռ䣬��realloc�����¿���һ���µĿռ䣬�¿��ٵĿռ��ַ��P�ĵ�ַ��ͬ��
//	{
//		printf("%s\n", strerror(errno));  // ԭ���ڴ��е����ݻ��Զ��������¿ռ���
//	 }
//	else
//	{
//		for (i = 5; i < 10; i++)
//		{                              // 3.realloc���ٿռ������ܵ���ʧ�ܣ������Ҫһ���µı���������realloc���صĵ�ַ��Ȼ���жϸõ�ַ�Ƿ���Ч
//			*(p2 + i) = i;
//			printf("%d ", *(p2 + i));
//		}
//	}
//	free(p2);
//	return 0;
//} 

//  ***********************************************  ��������  *****************************************************

struct S
{
	int n;
	int arr[0];//δ֪��С��--���������Ա--����Ĵ�С�ǿ��Ե�����   Ҳ����д�� arr[]
};
int main()
{
	struct S s;
	printf("%d ", sizeof(s));// 4
	struct S* ps = (struct S*)malloc(sizeof(S) + 5 * sizeof(int));
	ps->n = 100;
	int i = 0;
	for (i = 0; i < 5; i++)
	{
		ps->arr[i] = i;
	}
	free(ps);
	ps = NULL;
	return 0;
}
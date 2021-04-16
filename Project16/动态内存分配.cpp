#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
//   ******************************************* void* malloc()  &  free()
//int main()
//{
//	int* p=(int*)malloc(10 * sizeof(int));  //向内存申请40个字节
//	if (p == NULL)
//	{
//		printf("%s\n", strerror(errno));    //使用malloc函数申请内存空间时一定要首先判断申请的内存是否合理
//	}
//	else
//	{
//		//正常使用
//		int i = 0;
//		for (i = 0; i < 10; i++)
//		{
//			*(p + i) = i;
//			printf("%d ", *(p + i));
//		}
//	 }
//	free(p);//使用完malloc 开辟的空间后，一定得及时释放该空间  并将指向该空间地址的指针P 赋值为空指针 NULL
//	p = NULL;
//	return 0;
//}

//  ****************************************** void*  calloc (num,size) 

//int main()
//{
//	int* p=(int*)calloc(10, sizeof(int));  // 使用calloc 开辟40个字节的空间  并且会初始化空间每个字节全为0
//	if (p == NULL)
//	{
//		printf("%s\n", strerror(errno));
//	}
//	else
//	{
//		//正常使用
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

//  *********************************************  void* realloc(void* ptr,size_t size)  调整动态内存开辟的大小

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
//			*(p + i) = i;  //假如现在20个字节不能满足使用需求，需要再申请20个空间，此时我们就可以使用realloc函数进行调整 size_t size指的是总共需要的空间大小（单位：字节）
//		}
//	}
//	int* p2 = (int*)realloc(p,40);//1. 如果P指向的空间之后有足够大的空间，可以直接追加，追加后返回的新地址也是P，
//	if (p2 == NULL)                               //2.如果p指向的空间之后没有足够大的空间，着realloc会重新开辟一块新的空间，新开辟的空间地址与P的地址不同，
//	{
//		printf("%s\n", strerror(errno));  // 原来内存中的数据会自动拷贝到新空间里
//	 }
//	else
//	{
//		for (i = 5; i < 10; i++)
//		{                              // 3.realloc开辟空间过大可能导致失败，因此需要一个新的变量来接受realloc返回的地址，然后判断该地址是否有效
//			*(p2 + i) = i;
//			printf("%d ", *(p2 + i));
//		}
//	}
//	free(p2);
//	return 0;
//} 

//  ***********************************************  柔型数组  *****************************************************

struct S
{
	int n;
	int arr[0];//未知大小的--柔型数组成员--数组的大小是可以调整的   也可以写成 arr[]
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
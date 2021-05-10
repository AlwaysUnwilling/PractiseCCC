#pragma once
#include<malloc.h>
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<assert.h>
//  顺序表，有效数据在数组中必须使连续的
//  静态顺序表
//typedef int SLDataType;  // 重新定义了 int ；以后修改int 即可实现数据类型的转换。
//#define N 10
//struct Seqlist
//{
//	SLDataType a[N];
//	int size;
//};
//void SeqlistPushBack(struct Seqlist* ps, SLDataType x);
//void SeqlistPopBack(struct Seqlist* ps);
//void SeqlistPushFront(struct Seqlist* ps, SLDataType x);
//void SeqlistPopFront(struct Seqlist* ps);

//  动态顺序表
typedef int SLDataType;  // 重新定义了 int ；以后修改int 即可实现数据类型的转换。

typedef struct Seqlist
{
	SLDataType* a;
	int size;
	SLDataType capacity;
}SL;
void SeqlistCheckCapacity(SL* ps);//检测是否需要扩容
void SeqlistPrint(SL* ps);
void SeqlistInit(SL* ps);
void SeqlistPushBack(SL* ps, SLDataType x);  //尾插
void SeqlistPopBack(SL* ps); //尾删
void SeqlistPushFront(SL* ps, SLDataType x); //头插
void SeqlistPopFront(SL* ps); //头删
void SeqlistInsert(SL* ps, int pos, SLDataType x);  //任意位置插入
void SeqlistErase(SL* ps, int pos); // 任意位置删除


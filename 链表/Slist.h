#pragma once
#include<stdio.h>
#include<stdlib.h>
//节点/结点
typedef int SlistDataType;
typedef struct SlistNode 
{
	SlistDataType data;
	struct SlistNode* Next;
}SLTNode,SlistNode;



//  另一种定义链表的方式

//struct Slist
//{
//	SlistNode* head;
//	SlistNode* tail;
//};

void SlistPushBack(SlistNode** phead,SlistDataType x); //尾插
void SlistPopBack(SlistNode** phead);                   // 尾删
void SlistPushFront(SlistNode** phead, SlistDataType x); // 头插
void SlistPopFront(SlistNode** phead);                  // 头删

void SlistPrint(SlistNode* phead);  //遍历打印链表
void SlistSize(SlistNode** phead);
SlistNode* BuySlistNode(SlistDataType x);
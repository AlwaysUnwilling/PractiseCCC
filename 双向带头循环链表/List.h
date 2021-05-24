#pragma once
#include<assert.h>
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
typedef int LTDataType;
typedef struct ListNode   //双向循环链表
{
	struct ListNode* next;
	struct ListNode* prev;
	LTDataType data;
}ListNode;
void ListInit(ListNode** head);
void ListNodeClear(ListNode* head);
void ListNodeDestroy(ListNode** head);
ListNode* BuyListNode(LTDataType x);
void ListNodePrint(ListNode* head);
void ListPushBack(ListNode* head, LTDataType x);
void ListPopBack(ListNode* head);
void ListPushFront(ListNode* head, LTDataType x);
void ListPopFront(ListNode* head);
ListNode* ListFind(ListNode* head, LTDataType x);
void ListNodeInsert(ListNode* pos, LTDataType x);  //在pos的前面插入x
void ListNodeErase(ListNode* pos);

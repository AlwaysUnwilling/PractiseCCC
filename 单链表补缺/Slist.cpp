#define _CRT_SECURE_NO_WARNINGS 1
#include"Slist.h"
SlistNode* BuySlistNode(SlistDataType x)
{
	SlistNode* NewNode = (struct SlistNode*)malloc(sizeof(SlistNode));
	if (NewNode == NULL)
	{
		printf("内存申请失败！\n");
		exit(-1);
	}
	NewNode->data = x;
	NewNode->Next = NULL;
	return NewNode;
}
void SlistPrint(SlistNode* phead)
{
	SlistNode* cur = phead;
	while (cur != NULL)
	{
		printf("%d->", cur->data);
		cur = cur->Next;
	}
	printf("NULL\n");
}
void SlistPushBack(SlistNode** phead, SlistDataType x)
{
	SlistNode* NewNode = BuySlistNode(x);
	if (*phead == NULL)
	{
		/*SlistNode* NewNode = (struct SlistNode*)malloc(sizeof(SlistNode));
		if (NewNode == NULL)
		{
			printf("内存申请失败！\n");
			exit(-1);
		}
		NewNode->data = x;
		NewNode->Next = NULL;
		phead = NewNode;*/
		*phead = NewNode;
	}
	else
	{
		SlistNode* tail = *phead;
		while (tail->Next != NULL)  //找尾
		{
			tail = tail->Next;
		}
		/*SlistNode* NewNode = (struct SlistNode*)malloc(sizeof(SlistNode));
		if (NewNode == NULL)
		{
			printf("内存申请失败！\n");
			exit(-1);
		}
		NewNode->data = x;
		NewNode->Next = NULL;
		tail->Next = NewNode;*/
		tail->Next = NewNode;
	}
	
}
void SlistPopBack(SlistNode** phead)
{
	// 1.空；2.一个结点；3.一个以上结点
	if (*phead == NULL)
	{
		return;
	}
	else if ((*phead)->Next == NULL)
	{
		free(*phead);
		*phead = NULL;
	}
	else
	{
		SlistNode* tail = *phead;
		SlistNode* pre = NULL;
		while (tail->Next != NULL)
		{
			pre = tail;
			tail = tail->Next;
		}
		free(tail);
		tail = NULL;
		pre->Next = NULL;
	}
}
void SlistPushFront(SlistNode** phead,SlistDataType x)
{
	SlistNode* NewNode = BuySlistNode(x);
	////1.空链表
	//if (*phead == NULL)
	//{
	//	*phead = NewNode;
	//	(*phead)->Next = NULL;
	//}
	////2.非空
	//else
	//{
	//	NewNode->Next = *phead;
	//	*phead = NewNode;
	//}
	NewNode->Next = *phead;
	*phead = NewNode;
}
void SlistPopFront(SlistNode** phead)
{
	//1.空链表
	if (*phead == NULL)
	{
		return;
	}
	//2.只有一个结点；
	//else if ((*phead)->Next == NULL)
	//{
	//	free(*phead);
	//	*phead = NULL;
	//}
	////3.一个以上的结点；
	//else
	//{
	//	SlistNode* pre = NULL;
	//	pre = (*phead)->Next;
	//	free(*phead);
	//	*phead = pre;
	//}
	else
	{
		SlistNode* pre = NULL;
		pre = (*phead)->Next;
		free(*phead);
		*phead = pre;
	}
}
SlistNode* SlistFind(SlistNode* phead, SlistDataType x)
{
	SlistNode* cur = phead;
	while (cur)
	{
		if ((cur->data) == x)
		{
			return cur;
		}
		else
		{
			cur = cur->Next;
		}
	}
	  return NULL;
 }
void SlistInsertAfter(SlistNode* pos, SlistDataType x)
{
	assert(pos);
	SlistNode* NewNode=BuySlistNode(x);
	NewNode->Next = pos->Next;
	pos->Next = NewNode;
}
void SlistEraseAfter(SlistNode* pos)
{
	assert(pos);
	//if (pos->Next)
	//{
	//	SlistNode* cur = pos;
	//	pos = pos->Next->Next;
	//	free(cur->Next);
	//	cur->Next = pos;
	//}
	if (pos->Next)
	{
		SlistNode* next = pos->Next;
		SlistNode* nextnext = next->Next;
		free(next);
		pos->Next = nextnext;
	}
}
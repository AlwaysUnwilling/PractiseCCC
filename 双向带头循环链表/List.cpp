#define _CRT_SECURE_NO_WARNINGS 1
#include"List.h"
void ListInit(ListNode** head)
{
	*head = BuyListNode(0);
	(*head)->next = *head;
	(*head)->prev = *head;
}
void ListNodeClear(ListNode* head)  //清除所有数据结点，保留头结点，可以继续使用。
{
	assert(head);
	ListNode* cur = head->next;  
	while (cur != head)
	{
		ListNode* next = cur->next;
		free(cur);
		cur = next;
	}
	head->next = head;
	head->prev = head;
}
void ListNodeDestroy(ListNode** head)//完全清除所有结点，包括头结点
{
	assert(head);
	ListNodeClear(*head);
	free(*head);
	*head = NULL;
}
ListNode* BuyListNode(LTDataType x)
{
	ListNode* element = (ListNode*)malloc(sizeof(ListNode));
	if (element == NULL)
	{
		printf("内存申请失败！\n");
		exit(-1);
	}
	ListNode* prev = NULL;
	ListNode* next = NULL;
	element->data = x;
	return element;
}
void ListNodePrint(ListNode* head)
{
	assert(head);
	ListNode* cur = head->next;
	if (cur == NULL)
	{
		printf("NULL\n");
		return;
	}
	printf("ListNodeHead<=>");
	while (cur!=head)
	{
		printf("%d<=>", cur->data);
		cur = cur->next;
	}
	if (cur == head)
		printf("ListNodeHead\n");
}
void ListPushBack(ListNode* head, LTDataType x)
{
	assert(head);
	//ListNode* tail = head->prev;
	//ListNode* newNode = BuyListNode(x);
	//tail->next = newNode;
	//newNode->prev=tail;
	//newNode->next = head;
	//head->prev = newNode;
	ListNodeInsert(head , x);
}
void ListPopBack(ListNode* head)
{
	assert(head);
	assert(head->next != head);
	/*ListNode* tail = head->prev;
	head->prev = tail->prev;
	tail->prev->next = head;
	free(tail);
	tail = NULL;*/
	ListNodeErase(head->prev);
}
void ListPushFront(ListNode* head, LTDataType x)
{
	assert(head);
	/*ListNode* node = BuyListNode(x);
	ListNode* next = head->next;
	head->next = node;
	node->prev = head;
	node->next = next;
	next->prev = node;*/
	ListNodeInsert(head->next, x);
}
void ListPopFront(ListNode* head)
{
	assert(head);
	assert(head->next!=head);
	/*ListNode* first = head->next;
	ListNode* second = first->next;
	free(first);
	first = NULL;
	head->next = second;
	second->prev = head;*/
	ListNodeErase(head->next);
}
ListNode* ListFind(ListNode* head, LTDataType x)
{
	assert(head);
	ListNode* cur = head->next;
	while (cur != head)
	{
		if (cur->data == x)
		{
			return cur;
		}
		else
			cur = cur->next;
	}
	return NULL;
}
void ListNodeInsert(ListNode* pos, LTDataType x)
{
	assert(pos);
	ListNode* node = BuyListNode(x);
	ListNode* posPrev = pos->prev;
	posPrev->next = node;
	node->next = pos;
	pos->prev = node;
	node->prev = posPrev;
}
void ListNodeErase(ListNode* pos)
{
	assert(pos);
	ListNode* posPrev = pos->prev;
	ListNode* posNext = pos->next;
	posPrev->next = posNext;
	posNext->prev = posPrev;
	free(pos);
	pos = NULL;
}

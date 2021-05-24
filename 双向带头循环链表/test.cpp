#define _CRT_SECURE_NO_WARNINGS 1
#include"List.h"
void ListNodeTest1()
{
	ListNode* head = NULL;
	ListInit(&head);
	ListPushBack(head, 1);
	ListPushBack(head, 2);
	ListPushBack(head, 3);
	ListPushBack(head, 4);
	ListPushBack(head, 5);
	ListNodePrint(head);
	ListPopBack(head);
	ListNodePrint(head);
	ListPushFront(head, 5);
	ListPushFront(head, 6);
	ListPushFront(head, 7);
	ListNodePrint(head);
	ListPopFront(head);
	ListNodePrint(head);
	ListNode* node =ListFind(head, 6);
	printf("%p\n", node);
	ListNodeInsert(node, 8);
	ListNodePrint(head);
	ListNodeErase(node);
    ListNodePrint(head);
	//ListNode* node1 =ListFind(head, 8);
	//printf("%p\n", node1);
	ListNodeDestroy(&head);
	
}
int main()
{
	ListNodeTest1();
	return 0;
}
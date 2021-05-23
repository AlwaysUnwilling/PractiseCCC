#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<assert.h>
struct ListNode
{
	int data;
	struct ListNode* next;
};
struct ListNode* BuyListNode(int x)
{
	struct ListNode* newnode = (struct ListNode*)malloc(sizeof(ListNode));
	if (newnode == NULL)
	{
		printf("开辟内存失败\n");
		exit(-1);
	}
	newnode->data = x;
	newnode->next = NULL;
	return newnode;
}
void ListNodePrint(struct ListNode* head)
{
	ListNode* cur = head;
	while (cur!=NULL)
	{
		printf("%d->", cur->data);
		cur = cur->next;
	}
	printf("NULL\n");
}
void ListNodePushBack(struct ListNode** head, int x)  //尾插
{
	struct ListNode* newnode = BuyListNode(x);
	//1.链表为空
	if (*head==NULL)
	{
		*head = newnode;
	}
	else
		//2.链表中只有一个结点
		//3.链表中有一个以上的结点
	{
		struct ListNode* tail = *head;
		while (tail->next!=NULL)  //找尾
		{
			tail=tail->next;
		}
		tail->next= newnode;
	}
}
void ListNodePushFront(struct ListNode** head, int x)
{
	struct ListNode* newnode = BuyListNode(x);
	if (*head == NULL)  //空链表
	{
		*head = newnode;
	}
	else   //非空链表
	{
		ListNode* cur = *head;
		*head = newnode;
		(*head)->next = cur;
	}
}
//题目：删除链表中等于给定值val的所有结点
//void ListNodeDeleteTheSameVal(struct ListNode** head, int x)
//{
//	// 	   //方法1.0
//	assert(*head);
//	ListNode* nextnext = NULL;
//	ListNode* pre = NULL;
//	ListNode* cur = NULL;
//	while ((*head)->data == x)  //如果头结点与X相等
//	{
//		pre=*head;
//		*head = (*head)->next;
//		free(pre);
//	}
//	cur = *head;    //头结点与X不相等
//	while (cur->next != NULL)
//	{
//		if (cur->next->data == x)
//		{
//			pre = cur->next;
//			nextnext = pre->next;
//			cur->next = nextnext;
//			free(pre);
//		}
//		else
//			cur = cur->next;
//	}
	//      // 方法2.0
	/*assert(*head);*/
	/*ListNode* pre = NULL;
	ListNode* cur = *head;
	while (cur != NULL)
	{
		if (cur->data == x)
		{
			if (cur == *head)
			{
				*head = cur->next;
				free(cur);
				cur = *head;
			}
			else
			{
				pre->next = cur->next;
				free(cur);
				cur = pre->next;
				
			}
		}
		else
		{
			pre = cur;
			cur = cur->next;
		}
	}*/
//
//}
//void ListNodeTest2()
//{
//	struct ListNode* head = NULL;
//	ListNodePushBack(&head, 2);
//	ListNodePushBack(&head, 1);
//	ListNodePushBack(&head, 1);
//	ListNodePushBack(&head, 1);
//	ListNodePushBack(&head, 2);
//	ListNodePushBack(&head, 3);
//	ListNodePushBack(&head, 4);
//	ListNodePushBack(&head, 2);
//	ListNodePushBack(&head, 2);
//	ListNodePrint(head);
//    ListNodeDeleteTheSameVal(&head,2);
//	ListNodePrint(head);
//}
//int  main()
//{
//	ListNodeTest2();
//	return 0;
//}

//题目：翻转一个单链表
//struct ListNode* reverseList(struct ListNode* head)
//{
//	if (head == NULL || head->next == NULL)
//		return head;
//		struct ListNode* n1 = NULL;
//		struct ListNode* n2 = head;
//		struct ListNode* n3 = head->next;
//		while (n2)
//		{
//			//翻转
//			n2->next = n1;
//			//迭代
//			n1 = n2;
//			n2 = n3;
//			if(n3)  //如果n3为空指针，则n3不再需要迭代
//			n3 = n3->next;
//		}
//		return n1;
//
//}
//struct ListNode* reverseList1(struct ListNode* head)
//{
//	/*if (head == NULL || head->next == NULL)
//		return head;*/
//	struct ListNode* cur = head;
//	struct ListNode* newhead = NULL;
//	struct ListNode* next = head->next;
//	while (cur!=NULL)
//	{
//		/*struct ListNode* next = cur->next;*/
//		/*cur->next=newhead;
//		newhead = cur;*/
//		ListNodePushFront(&newhead, cur->data);   //头插
//		cur = next;     //迭代
//		if(next!=NULL)
//		next = next->next;
//	}
//	return newhead;
//}
//void ListNodeTest1()
//{
//	struct ListNode* head=NULL;
//	ListNodePushBack(&head, 1);
//	ListNodePushBack(&head, 2);
//	ListNodePushBack(&head, 3);
//	ListNodePushBack(&head, 4);
//	ListNodePrint(head);
//	//struct ListNode* newhead = reverseList(head);
//	/*ListNodePrint(newhead);*/
//	//ListNodePushFront(&newhead, 5);
//	//ListNodePushFront(&newhead, 6);
//	//ListNodePushFront(&newhead, 7);
//	//ListNodePushFront(&newhead, 8);
//	//ListNodePushFront(&newhead, 9);
//	/*ListNodePrint(newhead);*/
//	struct ListNode* newhead1 = reverseList1(head);
//	ListNodePrint(newhead1);
//}
//int  main()
//{
//	ListNodeTest1();
//	return 0;
//}
// 方法2：头插法
// 
//题目：给定一个带头结点head的非空单链表，返回链表的中间结点。如果有俩个中间结点，则返回第二个中间结点
//int ReturnInterNode(struct ListNode* head)
//{
//	assert(head);
//	int count = 1;
//	ListNode* cur = head;
//	while (cur->next != NULL)
//	{
//		cur = cur->next;
//		count++;
//	}
//	if (count == 1)
//	{
//		return head->data;
//	}
//	else
//	{
//		int n = count / 2;
//		while (n)
//		{
//			head = head->next;
//			n--;
//		}
//		return head->data;
//	}
//}
//   方法2.0     快慢指针法
//struct ListNode* ReturnInterNode1(struct ListNode* head)
//{
//	struct ListNode* slow = head;
//	struct ListNode* fast = head;
//	while (fast && fast->next)
//	{
//		slow = slow->next;
//		fast = fast->next->next;
//	}
//	return slow;
//}
//void ListNodeTest3()
//{
 /*   struct ListNode* head=NULL;
	ListNodePushBack(&head, 1);
	ListNodePushBack(&head, 2);
	ListNodePushBack(&head, 3);
	ListNodePushBack(&head, 4);
	ListNodePushBack(&head, 4);
	ListNodePushBack(&head, 4);
	ListNodePrint(head);*/
//	struct ListNode* inter= ReturnInterNode1(head);
//	printf("%d\n", inter->data);
//	/*int ret = ReturnInterNode(head);
//	printf("%d\n", ret);*/
//}
//int main()
//{
//	ListNodeTest3();
//	return 0;
//}
//题目：输入一个链表，输出该链表中倒数第k个结点。
//struct ListNode* Return_k_Node(struct ListNode* head,int k)    //先让快指针先走K步，然后再让快慢指针一起走。
//	                                                            //当快指针为NULL时，慢指针即为所求
//{
//	struct ListNode* slow = head;
//	struct ListNode* fast = head;
//	while (k--)   //k有可能大于整个链表的长度
//	{
//		if (fast)
//			fast = fast->next;
//		else
//			return NULL;
//	}
//	do
//	{
//		slow = slow->next;
//		fast = fast->next;
//	} while (fast);
//	return slow;
//
//}
//void ListNodeTest4()
//{
//	struct ListNode* head = NULL;
//	ListNodePushBack(&head, 1);
//	ListNodePushBack(&head, 2);
//	ListNodePushBack(&head, 3);
//	ListNodePushBack(&head, 4);
//	ListNodePushBack(&head, 4);
//	ListNodePushBack(&head, 4);
//	ListNodePrint(head);
//	struct ListNode* ret = Return_k_Node(head,4);
//	printf("%d\n", ret->data);
//}
//int main()
//{
//	ListNodeTest4();
//	return 0;
//}

//题目：将俩个有序链表合并为一个有序链表，并返回。新链表是通过拼接俩个给定链表的所有结点组成的。
//struct ListNode* MergeListNode(struct ListNode* l1, struct ListNode* l2)    //先去一个小的下来做新链表的头，然后每次都去小的进行尾插
//{
//	if (l1 == NULL)
//		return l2;
//	if (l2 == NULL)
//		return l1;
//	struct ListNode* head = NULL;
//	struct ListNode* tail = NULL;
//	if (l1->data < l2->data)
//	{
//		head =tail= l1;
//		l1 = l1->next;
//	}
//	else
//	{
//		head = tail=l2;
//		l2 = l2->next;
//	}
//	while (l1 && l2)
//	{
//		if (l1->data < l2->data)
//		{
//			tail->next=l1;
//			l1 = l1->next;
//		}
//		else
//		{
//			tail->next = l2;	
//			l2 = l2->next;
//		}
//		tail = tail->next;
//	}
//	if (l1 == NULL)
//	{
//		tail->next = l2;
//	}
//	else
//		tail->next = l1;
//	return head;
//}
///////////////////方法2.0---带哨兵位的头结点  （创建一个头结点（不存储有效值，只用来做头））
//struct ListNode* MergeListNode(struct ListNode* l1, struct ListNode* l2)    //带哨兵位的头结点
//{
//	if (l1 == NULL)
//		return l2;
//	if (l2 == NULL)
//		return l1;
//	struct ListNode* head = NULL;
//	struct ListNode* tail = NULL;
//	head = tail = (ListNode*)malloc(sizeof(ListNode));
//	if (head ==NULL || tail == NULL)
//	{
//		exit(-1);
//	}
//	while (l1 && l2)
//	{
//		if (l1->data < l2->data)
//		{
//			tail->next = l1;
//			l1 = l1->next;
//		}
//		else
//		{
//			tail->next = l2;
//			l2 = l2->next;
//		}
//		tail = tail->next;
//	}
//	if (l1 == NULL)
//	{
//		tail->next = l2;
//	}
//	else
//		tail->next = l1;
//	struct ListNode* realHead = head->next;
//	free(head);
//	return realHead;
//}
//void ListNodeTest4()
//{
	//struct ListNode* l1 = NULL;
	//struct ListNode* l2 = NULL;
	//ListNodePushBack(&l1, 1);
	//ListNodePushBack(&l1, 1);
	//ListNodePushBack(&l1, 3);
	//ListNodePushBack(&l1, 5);
	//ListNodePushBack(&l1, 7);
	//ListNodePushBack(&l2, 0);
	//ListNodePushBack(&l2, 2);
	//ListNodePushBack(&l2, 4);
	//ListNodePushBack(&l2, 6);
	//ListNodePushBack(&l2, 8);
	//ListNodePushBack(&l2, 10);
//	ListNodePrint(l1);
//	ListNodePrint(l2);
//	struct ListNode* newhead = MergeListNode(l1, l2);
//	ListNodePrint(newhead);
//}
//int main()
//{
//	ListNodeTest4();
//	return 0;
//}
//题目：编写代码，以给定值x为基准将链表分割成俩部分，所有小于x的结点排在大于等于x的结点之前。
//struct ListNode* ListNodeBreakUp(struct ListNode* head, int x)
//{
//	assert(head);
//	struct ListNode* newhead = NULL;
//	struct ListNode* h1 = (struct ListNode*)malloc(sizeof(ListNode));
//	struct ListNode* t1 = h1;
//	struct ListNode* h2 = (struct ListNode*)malloc(sizeof(ListNode));
//	struct ListNode* t2 = h2;
//	while (head)
//	{
//		if (head->data < x)
//		{
//			t1->next = head;
//			t1 = t1->next;
//			head = head->next;
//		}
//		else
//		{
//			t2->next = head;
//			t2 = t2->next;
//			head = head->next;
//		}
//	}
//	t2->next = NULL;
//	t1->next = h2->next;
//	newhead = h1->next;
//	free(h1);
//	free(h2);
//	return newhead;
//}
//void ListNodeTest5()
//{
//	struct ListNode* head = NULL;
//	ListNodePushBack(&head, 1);
//	ListNodePushBack(&head, 8);
//	ListNodePushBack(&head, 9);
//	ListNodePushBack(&head, 2);
//	ListNodePushBack(&head, 10);
//	ListNodePushBack(&head, 3);
//	ListNodePushBack(&head, 7);
//	ListNodePushBack(&head, 0);
//	ListNodePushBack(&head, 4);
//	ListNodePushBack(&head, 12);
//	ListNodePushBack(&head, 7);
//	ListNodePushBack(&head, 6);
//	ListNodePrint(head);
//	struct ListNode* newhead = ListNodeBreakUp(head, 7);
//	ListNodePrint(newhead);
//}
//int main()
//{
//	ListNodeTest5();
//	return 0;
//}
//题目：链表的回文结构。
//struct ListNode* ListNodeReverse(struct ListNode* head)
//{
//	if (head == NULL || head->next == NULL)
//		return head;
//	struct ListNode* n1 = NULL;
//	struct ListNode* n2 = head;
//	struct ListNode* n3 = head->next;
//	while (n2)
//	{
//		n2->next = n1;
//		n1 = n2;
//		n2 = n3;
//		if(n3)
//		n3 = n3->next;
//	}
//	return n1;
//}
//int ListNodeJudPalDrome(struct ListNode* head)
//{
//	if (head == NULL)
//		return 0;
//	struct ListNode* slow = head;
//	struct ListNode* fast = head;
//	while (fast && fast->next)
//	{
//		slow = slow->next;
//		fast = fast->next->next;
//	}
//	struct ListNode* nhead=ListNodeReverse(slow);
//	while (head != slow)
//	{
//		if (head->data == nhead->data)
//		{
//			head = head->next;
//			nhead = nhead->next;
//		}
//		else
//			return 0;
//	}
//	return 1;
//}
//void ListNodeTest6()
//{
//	struct ListNode* head = NULL;
//	ListNodePushBack(&head, 1);
//	ListNodePushBack(&head, 2);
//	ListNodePushBack(&head, 3);
//	ListNodePushBack(&head, 4);
//	ListNodePushBack(&head, 4);
//	ListNodePushBack(&head, 3);
//	ListNodePushBack(&head, 2);
//	ListNodePushBack(&head, 1);
//	ListNodePrint(head);
//	int ret=ListNodeJudPalDrome(head);
//	if (ret == 1)
//		printf("该链表是回文结构！\n");
//	else
//		printf("该链表不是回文结构！\n");
//}
//int main()
//{
//	ListNodeTest6();
//	return 0;
//}
//题目：输入俩个链表，找出他们的第一个公共结点。
//struct ListNode* getIntersectionNode(struct ListNode* headA, struct ListNode* headB)
//{
//	struct ListNode* curA = headA;
//	struct ListNode* curB = headB;
//	int lA = 0;
//	int lB = 0;
//	while (curA)
//	{
//		curA = curA->next;
//		lA++;
//	}
//	while (curB)
//	{
//		curB = curB->next;
//		lB++;
//	}
//	int k = abs(lA - lB);
//	struct ListNode* slow = headA;
//	struct ListNode* fast = headB;
//	if (lA > lB)
//	{
//		struct ListNode* slow = headB;
//		struct ListNode* fast = headA;
//	}
//	while (k--)
//	{
//		fast = fast->next;
//	}
//
//	while (fast)
//	{
//		slow = slow->next;
//		fast = fast->next;
//		if (fast == slow)
//		{
//			return fast;
//		}
//	}
//	return NULL;
//}
//void ListNodeTest7()
//{
//	struct ListNode* l1 = NULL;
//	struct ListNode* l2 = NULL;
//	ListNodePushBack(&l1, 1);
//	ListNodePushBack(&l1, 1);
//	ListNodePushBack(&l1, 3);
//	ListNodePushBack(&l1, 5);
//	ListNodePushBack(&l1, 7);
//	ListNodePushBack(&l2, 0);
//	ListNodePushBack(&l2, 2);
//	ListNodePushBack(&l2, 4);
//	ListNodePushBack(&l2, 6);
//	ListNodePushBack(&l2, 8);
//	ListNodePushBack(&l2, 10);
//	ListNodePrint(l1);
//	ListNodePrint(l2);
//	struct ListNode* node = getIntersectionNode(l1,l2);
//	printf("%p\n", node);
//}
//int main()
//{
//	ListNodeTest7();
//	return 0;
//}
//题目：给定一个链表，判断链表中是否有环。
//int hasCycle(struct ListNode* head)
//{
//	struct ListNode* fast=head;
//	struct ListNode* slow = head;
//	while (fast && fast->next)
//	{
//		slow = slow->next;
//		fast = fast->next->next;
//		if (slow == fast)
//		{
//			return 1;
//		}
//	}
//	return 0;
//}
//void ListNodeTest8()
//{
//	struct ListNode* head = NULL;
//	ListNodePushBack(&head, 1);
//	ListNodePushBack(&head, 2);
//	ListNodePushBack(&head, 3);
//	ListNodePushBack(&head, 4);
//	ListNodePushBack(&head, 4);
//	ListNodePushBack(&head, 3);
//	ListNodePushBack(&head, 2);
//	ListNodePushBack(&head, 1);
//	ListNodePrint(head);
//	int ret = hasCycle(head);
//	if (ret == 1)
//		printf("Yes!\n");
//	else
//		printf("No!\n");
//}
//int main()
//{
//	ListNodeTest8();
//	return 0;
//
//}
//题目：给定一个链表，返回链表开始入环的第一个结点，如果无环返回NULL。
//struct ListNode* detectCycle(struct ListNode* head)
//{
//	struct ListNode* fast = head;
//	struct ListNode* slow = head;
//	while (fast && fast->next)
//	{
//		fast = fast->next->next;
//		slow = slow->next;
//		if (fast == slow)
//			break;
//	}
//	if (fast == NULL && fast->next == NULL)
//		return NULL;
//	while (head != fast)
//	{
//		head = head->next;
//		fast = fast->next;
//    }
//	return fast;
//}
//void ListNodeTest9()
//{
//	/*struct ListNode* head = NULL;*/
//	//ListNodePushBack(&head, 1);
//	//ListNodePushBack(&head, 2);
//	//ListNodePushBack(&head, 3);
//	//ListNodePushBack(&head, 4);
//	//ListNodePushBack(&head, 4);
//	//ListNodePushBack(&head, 3);
//	//ListNodePushBack(&head, 2);
//	//ListNodePushBack(&head, 1);
//	//ListNodePrint(head);
//	struct ListNode* n3 = (struct ListNode*)malloc(sizeof(struct ListNode));
//	n3->data = 3;
//	struct ListNode* n1 = (struct ListNode*)malloc(sizeof(struct ListNode));
//	n1->data = 1;
//	n1->next = n3;
//	struct ListNode* n2 = (struct ListNode*)malloc(sizeof(struct ListNode));
//	n2->data = 2;
//	n2->next = n1;
//
//	n3->next = n2;
//	struct ListNode* n4 = (struct ListNode*)malloc(sizeof(struct ListNode));
//	n4->data = 4;
//	n4->next = n3;
//	struct ListNode* node=detectCycle(n4);
//	printf("%d\n", node->data);
//
//}
//int main()
//{
//	ListNodeTest9();
//	return 0;
//}
//题目：给定一个链表，每个结点包含一个额外增加的随机指针，该指针指向链表中的任意结点或者空节点。要求返回这个链表的深度拷贝。
//struct ListNode1
//{
//	int data;
//	struct ListNode1* next;
//	struct ListNode1* random;
//};
//typedef struct ListNode1 Node;
//struct ListNode1* copyRandomListNode(struct ListNode1* head)
//{
//	if (head == NULL)
//		return NULL;
//	Node* cur = head;
//	//1.0  复制链表结点链接在该节点的原结点的后面。
//	while (cur)
//	{
//		Node* copy = (Node*)malloc(sizeof(Node));
//		copy->data = cur->data;
//		copy->next = NULL;
//		copy->random = NULL;
//		Node* next = cur->next;
//		cur->next = copy;
//		copy->next = next;
//		cur = next->next;
//	}
//	//2.0复制random
//	cur = head;
//	while (cur)
//	{
//		Node* copy = cur->next;
//		if (cur->random)
//			copy->random = cur->random->next;
//		else
//			copy->random = NULL;
//
//		//迭代
//		cur = cur->next->next;
//
//	}
//	//3.0拆分copy链表和原链表
//	cur = head;
//	Node* copyHead = cur->next;
//	while (cur)
//	{
//		Node* copy = cur->next;
//		Node* next = copy->next;
//		cur->next = next;
//		if (next)
//			copy->next = next->next;
//		//迭代
//		else
//			copy->next = NULL;
//
//		cur = next;
//	}
//	return copyHead;
//}
//int main()
//{  
//	struct ListNode1* n3 = (Node*)malloc(sizeof(Node));
//	n3->data = 3;
//	n3->next = NULL;
//	n3->random = NULL;
//	struct ListNode1* n2 = (Node*)malloc(sizeof(Node));
//	n2->data = 3;
//	n2->next = n3;
//	n2->random = n3;
//
//	struct ListNode1* n1 = (Node*)malloc(sizeof(Node));
//	n1->data = 1;
//	n1->next = n2;
//	n1->random =n2;
//
//
//	struct ListNode1* newhead = copyRandomListNode(n1);
//	printf("%p\n", newhead);
//	return 0;
//}
//题目：对链表进行插入排序。
//typedef ListNode Node;
//struct ListNode* listNodeInsertSort(struct ListNode* head)
//{
//	if (head == NULL)
//		return NULL;
//	Node* cur = head->next;
//	head->next = NULL;
//	Node* next = NULL;
//	Node* pre = NULL;
//	while (cur)
//	{
//		//1.0小于head->data的直接头插。
//		if (cur->data < head->data)
//		{
//			Node* next = cur->next;
//			cur->next = head;
//			head = cur;
//			cur = next;
//		}
//		else   //2.0大于等于head->data的 向head后比较找合适位置插入
//		{
//			pre = head;
//			Node* prenext = pre->next;
//			while (prenext)
//			{
//				if (prenext->data >= cur->data)    //找到插入位置了
//				{
//					pre->next = cur;
//					next = cur->next;
//					cur->next = prenext;
//					cur = next;
//					break;
//				}
//				pre = prenext;
//				prenext = prenext->next;
//			}
//			if (prenext == NULL)  //找完都没找到就直接尾插。
//			{
//				pre->next = cur;
//				next = cur->next;
//				cur->next = NULL;
//				cur = next;
//			}
//		}
//		
//	}
//	return head;
//}
//void ListNodeTest10()
//{
//	struct ListNode* head = NULL;
//	//ListNodePushBack(&head, 10);
//	//ListNodePushBack(&head, 9);
//	//ListNodePushBack(&head, 8);
//	//ListNodePushBack(&head, 7);
//	//ListNodePushBack(&head, 6);
//	//ListNodePushBack(&head, 5);
//	//ListNodePushBack(&head, 10);
//	//ListNodePushBack(&head, 4);
//	//ListNodePushBack(&head, 3);
//	//ListNodePushBack(&head, 3);
//	//ListNodePushBack(&head, 2);
//	//ListNodePushBack(&head, 1);
//	ListNodePushBack(&head, -1);
//	ListNodePushBack(&head, 5);
//	ListNodePushBack(&head, 3);
//	ListNodePushBack(&head, 4);
//	ListNodePushBack(&head, 0);
//	ListNodePrint(head);
//	struct ListNode* newhead=listNodeInsertSort(head);
//	ListNodePrint(newhead);
//}
//int main()
//{
//	ListNodeTest10();
//	return 0;
//}
//题目：在一个排序链表中，存在重复的结点，请删除该链表中的重复结点。重复结点不保留，返回链表的头指针。
struct ListNode* ListNodeDeleteTheSameVal1(struct ListNode* head)
{
	if (head == NULL)
		return NULL;
	struct ListNode* first = (struct ListNode*)malloc(sizeof(ListNode));
	//1.0判断头结点是否重复,不重复指针走下下个结点继续判断直到遇到相等结点或者head->next==NULL 跳出循环。
	// 把不重复的点链接到新链表first下。
	struct ListNode* tail = first;
	struct ListNode* newHead = NULL;
	if (head->next == NULL)
		return head;
	while (head->data != head->next->data)
	{
		tail->next = head;
		tail = tail->next;
		head = head->next;
		if (head->next == NULL)
			break;
	}
	if (head->next == NULL)
	{
		tail->next = head;
		newHead = first->next;
		free(first);
		return newHead;
	}
	//2.0重复删除
	struct ListNode* n1 = head;
	struct ListNode* n2 = n1->next;
	struct ListNode* n3 = n2->next;

	if (n3 == NULL)
	{
		tail->next = NULL;
		newHead = first->next;
		free(first);
		return newHead;
	}
	while (n3)
	{
		if (n1->data != n2->data && n2->data != n3->data)
		{
			tail->next = n2;
			tail = tail->next;
		}
		n1 = n2;
		n2 = n3;
		n3 = n3->next;
	}
	if (n1->data != n2->data)
	{
		tail->next = n2;
		newHead = first->next;
		free(first);
		return newHead;
	}
	else
	{
		tail->next = NULL;
		newHead = first->next;
		free(first);
		return newHead;
	}
	
}
void ListNodeTest11()
{
	struct ListNode* head = NULL;
	ListNodePushBack(&head, 1);
	ListNodePushBack(&head, 1);
	ListNodePushBack(&head, 3);
	ListNodePushBack(&head, 4);
	ListNodePushBack(&head, 5);
	ListNodePushBack(&head, 5);
	ListNodePushBack(&head, 6);
	ListNodePushBack(&head, 7);
	ListNodePushBack(&head, 8);
	ListNodePushBack(&head, 9);
	ListNodePushBack(&head, 9);
	ListNodePushBack(&head, 9);
	/*ListNodePushBack(&head, 1);
	ListNodePushBack(&head, 2);
	ListNodePushBack(&head, 3);
	ListNodePushBack(&head, 4);
	ListNodePushBack(&head, 5);
	ListNodePushBack(&head, 6);*/
	ListNodePrint(head);
	struct ListNode* newhead = ListNodeDeleteTheSameVal1(head);
	ListNodePrint(newhead);
}
int main()
{
	ListNodeTest11();
	return 0;
}
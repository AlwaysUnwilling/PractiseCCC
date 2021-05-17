#define _CRT_SECURE_NO_WARNINGS 1
#include"Slist.h"

void TestSlistNode1()
{
	SlistNode* phead = NULL;  //这俩种都表示的是一个单链表。头指针接受malloc申请的空间地址即可
	SlistPushBack(&phead, 1);
	SlistPushBack(&phead, 2);
	SlistPushBack(&phead, 3);
	SlistPushBack(&phead, 4);
	SlistPrint(phead);
	SlistPopBack(&phead);
	SlistPopBack(&phead);
	SlistPopBack(&phead);
	SlistPopBack(&phead);
	SlistPopBack(&phead);
	SlistPrint(phead);
	SlistPushFront(&phead, 1);
	SlistPushFront(&phead, 2);
	SlistPushFront(&phead, 3);
	SlistPushFront(&phead, 4);
	SlistPushFront(&phead, 5);
	SlistPrint(phead);
	SlistPopFront(&phead);
	/*SlistPopFront(&phead);
	SlistPopFront(&phead);
	SlistPopFront(&phead);
	SlistPopFront(&phead);
	SlistPopFront(&phead);
	SlistPopFront(&phead);*/
	SlistPrint(phead);
	
}
void TestSlistNode2()
{
	SlistNode* phead = NULL;
	SlistPushBack(&phead, 1);
	SlistPushBack(&phead, 2);
	SlistPushBack(&phead, 3);
	SlistPushBack(&phead, 4);
	SlistNode* pos = SlistFind(phead, 3);
	if (pos)
	{
		pos->data = 7;
	}
	else
		printf("未找到！\n");
	SlistPrint(phead);
	SlistEraseAfter(phead);
	SlistPrint(phead);
}
int main()
{
	
	//SlistNode* pList = NULL;
	//TestSlistNode1();
	TestSlistNode2();
	return 0;
}
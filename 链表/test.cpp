#define _CRT_SECURE_NO_WARNINGS 1
#include"Slist.h"

void TestSlistNode1()
{
	SlistNode* phead = NULL;  //�����ֶ���ʾ����һ��������ͷָ�����malloc����Ŀռ��ַ����
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
int main()
{
	
	//SlistNode* pList = NULL;
	TestSlistNode1();
	return 0;
}
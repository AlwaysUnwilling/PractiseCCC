#pragma once
#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
//�ڵ�/���
typedef int SlistDataType;
typedef struct SlistNode 
{
	SlistDataType data;
	struct SlistNode* Next;
}SLTNode,SlistNode;



//  ��һ�ֶ�������ķ�ʽ

//struct Slist
//{
//	SlistNode* head;
//	SlistNode* tail;
//};

void SlistPushBack(SlistNode** phead,SlistDataType x); //β��
void SlistPopBack(SlistNode** phead);                   // βɾ
void SlistPushFront(SlistNode** phead, SlistDataType x); // ͷ��
void SlistPopFront(SlistNode** phead);                  // ͷɾ

void SlistPrint(SlistNode* phead);  //������ӡ����
void SlistSize(SlistNode** phead);
SlistNode* BuySlistNode(SlistDataType x);  // �������
SlistNode* SlistFind(SlistNode* phead, SlistDataType x);  //����
void SlistInsertAfter(SlistNode* pos, SlistDataType x);//pos�����
void SlistEraseAfter(SlistNode* pos);//posλ�ú�ɾ��
#pragma once
#include<malloc.h>
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<assert.h>
//  ˳�����Ч�����������б���ʹ������
//  ��̬˳���
//typedef int SLDataType;  // ���¶����� int ���Ժ��޸�int ����ʵ���������͵�ת����
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

//  ��̬˳���
typedef int SLDataType;  // ���¶����� int ���Ժ��޸�int ����ʵ���������͵�ת����

typedef struct Seqlist
{
	SLDataType* a;
	int size;
	SLDataType capacity;
}SL;
void SeqlistCheckCapacity(SL* ps);//����Ƿ���Ҫ����
void SeqlistPrint(SL* ps);
void SeqlistInit(SL* ps);
void SeqlistPushBack(SL* ps, SLDataType x);  //β��
void SeqlistPopBack(SL* ps); //βɾ
void SeqlistPushFront(SL* ps, SLDataType x); //ͷ��
void SeqlistPopFront(SL* ps); //ͷɾ
void SeqlistInsert(SL* ps, int pos, SLDataType x);  //����λ�ò���
void SeqlistErase(SL* ps, int pos); // ����λ��ɾ��


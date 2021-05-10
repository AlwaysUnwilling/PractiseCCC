#define _CRT_SECURE_NO_WARNINGS 1
#include"Seqlist.h"
void TestSeqlist1()
{
	Seqlist s;
	SeqlistInit(&s);
	SeqlistPushBack(&s, 1);
	SeqlistPushBack(&s, 2);
	SeqlistPushBack(&s, 3);
	SeqlistPushBack(&s, 4);
	SeqlistPushBack(&s, 5);
	SeqlistPushBack(&s, 6);
	SeqlistPushBack(&s, 7);
	SeqlistPrint(&s);
	//SeqlistPopBack(&s);
	//SeqlistPopBack(&s);
	SeqlistInsert(&s,2,-3);
	SeqlistInsert(&s,4,-4);
	SeqlistInsert(&s,6,-5);
	SeqlistPrint(&s);
	SeqlistErase(&s, 2);
	SeqlistErase(&s, 4);
	SeqlistErase(&s, 6);
	SeqlistPrint(&s);
}
int main()
{
	TestSeqlist1();
	return 0;
}
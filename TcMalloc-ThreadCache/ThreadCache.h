#pragma once
#include"Common.h"


class ThreadCache
{
public:
	void* Allocate(size_t size);   //������Ҫ�Ŀռ��С bytes
	void Deallocate(void* ptr, size_t size);  //size���㻹�����Ŀռ�ͨ��size���Сӳ�䵽��Ӧ��hashͰ�й���
	//�����Ļ����ȡ����
	void* FetchFromCenTralCache(size_t index, size_t size);
private:
	FreeList _freeLists[NFREELIST];
};

//Thread Local Storage���ֲ߳̾��洢��TLS
//�ֲ߳̾��洢��TLS������һ�ֱ����Ĵ洢��������������������ڵ��߳�����ȫ�ֿɷ��ʵģ���
//�ǲ��ܱ������̷߳��ʵ��������ͱ��������ݵ��̶߳����ԡ�����֪��ȫ�ֱ������������̶߳���
//�Է��ʵģ������Ͳ��ɱ�����Ҫ�������ƣ������˿��Ƴɱ��ʹ��븴�Ӷȡ�
static _declspec(thread) ThreadCache* pTLSThreadCache = nullptr;

#pragma once

#include"Common.h"

//Ϊ����ÿ�����̶������ҵ�ͬһ��centralcache�����Խ�centralcache���Ϊ����ģʽ
class CentralCache
{
private:
	SpanList _spanLists[NFREELIST]; //SpanList��ӳ������FreeListӳ�������ͬ
private:
	CentralCache()
	{}
	CentralCache(const CentralCache&) = delete;
	static CentralCache _sInst;
	//��ͷ�ļ���������.cpp�ж��壬������ͷ�ļ��ж��壬����ᱻ������Σ���������
public:
	static CentralCache* GetInstance()
	{
		return &_sInst;
	}
	//�����Ļ����ȡһ�������Ķ����threadcache
	size_t FetchRangeObj(void*& start, void*& end, size_t batchNum  , size_t byte_size);
	//��ȡһ���ǿյ�span
	Span* GetOneSpan(SpanList& list, size_t byte_size);
};

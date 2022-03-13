#pragma once
#include"Common.h"

class PageCache
{
private:
	SpanList _spanLists[NPAGES];
	std::mutex _pageMtx;
	static PageCache _sInstan;
private:
	PageCache()
	{}
	PageCache(const PageCache&) = delete;
public:
	std::mutex& GetPageMutex()
	{
		return _pageMtx;
	}
	static PageCache* GetPageInstance()
	{
		return &_sInstan;
	}
	//��ȡһ��kҳ��span
	Span* NewSpan(size_t k);
};

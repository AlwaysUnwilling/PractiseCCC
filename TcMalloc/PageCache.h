#pragma once
#include"Common.h"

class PageCache
{
private:
	SpanList _spanLists[NPAGES];
	std::unordered_map<PAGE_ID, Span*> _idSpanMap;
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
	//获取从对象到span的映射
	Span* MapObjectToSpan(void* obj);
	//释放空闲span回到PageCache,并合并相邻的span
	void ReleaseSpanToPageCache(Span* span);
	//获取一个k页的span
	Span* NewSpan(size_t k);
};

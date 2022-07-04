#pragma once
#include"Common.h"
#include"ObjectPool.h"
#include"PageMap.h"

class PageCache
{
private:
	SpanList _spanLists[NPAGES];
	ObjectPool<Span> spanPool;
	//std::unordered_map<PAGE_ID, Span*> _idSpanMap;
#ifdef _WIN64
	TCMalloc_PageMap2<64 - PAGE_SHIFT> _idSpanMap;
#elif _WIN32
	TCMalloc_PageMap1<32 - PAGE_SHIFT> _idSpanMap;
#elif
	//...
#endif
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

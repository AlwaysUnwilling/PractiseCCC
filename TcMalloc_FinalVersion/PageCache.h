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
	//��ȡ�Ӷ���span��ӳ��
	Span* MapObjectToSpan(void* obj);
	//�ͷſ���span�ص�PageCache,���ϲ����ڵ�span
	void ReleaseSpanToPageCache(Span* span);
	//��ȡһ��kҳ��span
	Span* NewSpan(size_t k);
};

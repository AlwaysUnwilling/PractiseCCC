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
	//��ȡ�Ӷ���span��ӳ��
	Span* MapObjectToSpan(void* obj);
	//�ͷſ���span�ص�PageCache,���ϲ����ڵ�span
	void ReleaseSpanToPageCache(Span* span);
	//��ȡһ��kҳ��span
	Span* NewSpan(size_t k);
};

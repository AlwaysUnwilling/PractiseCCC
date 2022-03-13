#pragma once

#include"Common.h"

//为了让每个进程都可以找到同一个centralcache，可以将centralcache设计为单例模式
class CentralCache
{
private:
	SpanList _spanLists[NFREELIST]; //SpanList的映射规则和FreeList映射规则相同
private:
	CentralCache()
	{}
	CentralCache(const CentralCache&) = delete;
	static CentralCache _sInst;
	//在头文件声明，在.cpp中定义，不可在头文件中定义，否则会被包含多次，出现问题
public:
	static CentralCache* GetInstance()
	{
		return &_sInst;
	}
	//从中心缓存获取一定数量的对象给threadcache
	size_t FetchRangeObj(void*& start, void*& end, size_t batchNum  , size_t byte_size);
	//获取一个非空的span
	Span* GetOneSpan(SpanList& list, size_t byte_size);
};

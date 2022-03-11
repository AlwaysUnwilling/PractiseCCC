#include"CentralCache.h"

CentralCache CentralCache::_sInst;

//获取一个非空的span
Span* CentralCache::GetOneSpan(SpanList& list, size_t byte_size)
{
	//...
	return nullptr;
}
//从中心缓存获取一定数量的对象给threadcache
size_t CentralCache::FetchRangeObj(void*& start, void*& end, size_t batchNum, size_t byte_size)
{
	size_t index = SizeClass::Index(byte_size);

	_spanLists[index].GetMutex().lock();
	Span* span = GetOneSpan(_spanLists[index],byte_size);
	assert(span);
	assert(span->_freeList);

	//从span中获取batchNum个对象
	//如果不后batchNum个，则有多少返回多少
	start = span->_freeList;
	end = start;
	size_t i = 0;
	size_t actualNum = 1;
	while (NextObj(end) && i < batchNum - 1)
	{
		end = NextObj(end);
		++i;
		++actualNum;
	}
	span->_freeList = NextObj(end);
	NextObj(end) = nullptr;


	_spanLists[index].GetMutex().unlock();
	return actualNum;
}


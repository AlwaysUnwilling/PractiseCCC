#include"ThreadCache.h"
#include"CentralCache.h"


void* ThreadCache::FetchFromCenTralCache(size_t index, size_t size)
{
	//慢开始反馈调节算法
	//1、慢开始不会一次向centralcache批量要太多，因为要太多可能会用不完浪费掉
	//2、如果你不要这个size大小内存需求，那么batchNum就会不断增长，直到上限
	//3、size越大，一次向centralcache要的batchNum就越小
	//4、size越小，一次centralcache要的bachNum就越大
	size_t batchNum = std::min(_freeLists[index].MaxSize(),SizeClass::NumMoveSize(size));
	if (_freeLists[index].MaxSize() == batchNum)
	{
		_freeLists[index].MaxSize() += 1;
	}
	void* start = nullptr;
	void* end = nullptr;
	size_t actucalNum=CentralCache::GetInstance()->FetchRangeObj(start, end, batchNum, size);
	assert(actucalNum > 1);
	if (actucalNum == 1)  //只返回一个对象，则start和end一定相等
	{
		assert(start == end);
		//  or return end;
	}
	else  //返回了多个，则把第一次返回，其他的挂在threadcache的自由链表中
	{
		_freeLists[index].PushRange(NextObj(start), end);

	}
	return start;
}
void* ThreadCache::Allocate(size_t size)
{
	assert(size <= MAX_BYTES);
	size_t alignSize = SizeClass::RoundUp(size);
	size_t index = SizeClass::Index(size);

	if (!_freeLists[index].Empty())
	{
		return _freeLists[index].Pop();
	}
	else
	{
		return FetchFromCenTralCache(index, alignSize);
	}
}
void ThreadCache::Deallocate(void* ptr, size_t size)
{
	assert(ptr);
	assert(size <= MAX_BYTES);
	size_t index = SizeClass::Index(size);
	_freeLists[index].Push(ptr);
}
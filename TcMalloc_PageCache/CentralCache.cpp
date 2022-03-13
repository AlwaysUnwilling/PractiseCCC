#include"CentralCache.h"
#include"PageCache.h"

CentralCache CentralCache::_sInst;

//获取一个非空的span
Span* CentralCache::GetOneSpan(SpanList& list, size_t byte_size)
{
	//先查看当前的spanlist中是否有还有未分配的对象的span
	Span* it = list.Begin();
	while (it != list.End())
	{
		if (it->_freeList != nullptr)
		{ 
			return it;
		}
		it = it->_next;
	}
	//先把central cache的桶锁解掉。这样如果其他线程释放内存对象回来，不会阻塞。
	list.GetMutex().unlock();
	//向pagecache索取,加锁获取
	PageCache::GetPageInstance()->GetPageMutex().lock();
	Span* span=PageCache::GetPageInstance()->NewSpan(SizeClass::NumMovePage(byte_size));
	//解锁
	PageCache::GetPageInstance()->GetPageMutex().unlock();
	//对获取的span切分，不需要加锁，因为其他线程访问不到这个span
	char* start = (char*)(span->_pageId << PAGE_SHIFT); //计算span的起始地址（页号*一页的大小）
	//计算span大块内存的大小（字节数）
	size_t bytes = span->_n << PAGE_SHIFT;
	char* end = start + bytes;
	//把大块内存切成自由链表连接起来
	span->_freeList = start;
	start += byte_size;
	void* tail = span->_freeList; 
	while (start < end)
	{
		NextObj(tail) = start;
		tail = NextObj(tail);
		start += byte_size;
	}
	//切好后的span挂到list中时需要再加锁，当返回centralcache后会解锁
	list.GetMutex().lock();
	list.PushFront(span);
	return span;
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


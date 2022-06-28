#include"CentralCache.h"
#include"PageCache.h"

CentralCache CentralCache::_sInst;

//��ȡһ���ǿյ�span
Span* CentralCache::GetOneSpan(SpanList& list, size_t byte_size)
{
	//�Ȳ鿴��ǰ��spanlist���Ƿ��л���δ����Ķ����span
	Span* it = list.Begin();
	while (it != list.End())
	{
		if (it->_freeList != nullptr)
		{ 
			return it;
		}
		it = it->_next;
	}
	//�Ȱ�central cache��Ͱ�������������������߳��ͷ��ڴ�������������������
	list.GetMutex().unlock();
	//��pagecache��ȡ,������ȡ
	PageCache::GetPageInstance()->GetPageMutex().lock();
	Span* span=PageCache::GetPageInstance()->NewSpan(SizeClass::NumMovePage(byte_size));
	span->_isUse = true;
	span->ObjectSize = byte_size;
	//����
	PageCache::GetPageInstance()->GetPageMutex().unlock();
	//�Ի�ȡ��span�з֣�����Ҫ��������Ϊ�����̷߳��ʲ������span
	//����span����ʼ��ַ��ҳ��*һҳ�Ĵ�С��:ͨ��ҳ�ż���ҳ����ʼ��ַ��ҳ��<<PAGE_SHIFT��ҳ��*ÿҳ�Ĵ�С��
	char* start = (char*)(span->_pageId << PAGE_SHIFT); 
	//����span����ڴ�Ĵ�С���ֽ�����
	size_t bytes = span->_n << PAGE_SHIFT;
	char* end = start + bytes;
	//�Ѵ���ڴ��г�����������������
	span->_freeList = start;
	start += byte_size;
	void* tail = span->_freeList; 
	while (start < end)
	{
		NextObj(tail) = start;
		tail = NextObj(tail);
		start += byte_size;
	}
	NextObj(tail) = nullptr;
	//�кú��span�ҵ�list��ʱ��Ҫ�ټ�����������centralcache������
	list.GetMutex().lock();
	list.PushFront(span);
	return span;
}
//�����Ļ����ȡһ�������Ķ����threadcache
size_t CentralCache::FetchRangeObj(void*& start, void*& end, size_t batchNum, size_t byte_size)
{
	size_t index = SizeClass::Index(byte_size);

	_spanLists[index].GetMutex().lock();
	Span* span = GetOneSpan(_spanLists[index],byte_size);
	assert(span);
	assert(span->_freeList); 

	//��span�л�ȡbatchNum������
	//�������batchNum�������ж��ٷ��ض���
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
	span->_useCount += actualNum;

	_spanLists[index].GetMutex().unlock();
	return actualNum;
}

void CentralCache::ReleaseListTOSpans(void* start, size_t size)
{
	size_t index = SizeClass::Index(size);
	//Ͱ��
	_spanLists[index].GetMutex().lock();
	while (start)
	{
		void* next = NextObj(start);
		Span* span = PageCache::GetPageInstance()->MapObjectToSpan(start);
		NextObj(start) = span->_freeList;
		span->_freeList = start;
		span->_useCount--;
		if (span->_useCount == 0)   //˵��span���зֳ�ȥ������С���ڴ涼��������
		{                           //���span�Ϳ����ٻ���pagecache�ˣ�pagecache�����ٳ���ȥ��ǰ��ҳ�ϲ�
			_spanLists[index].erase(span);
			span->_freeList = nullptr;
			span->_next = nullptr;
			span->_prev = nullptr;

			_spanLists[index].GetMutex().unlock();

			//ҳ�ź�ҳ�������ÿ�
			PageCache::GetPageInstance()->GetPageMutex().lock();
			PageCache::GetPageInstance()->ReleaseSpanToPageCache(span);
			PageCache::GetPageInstance()->GetPageMutex().unlock();

			_spanLists[index].GetMutex().lock();
		}
		start = next;
	}
	_spanLists[index].GetMutex().unlock();
}


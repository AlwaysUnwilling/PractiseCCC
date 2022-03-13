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
	//����
	PageCache::GetPageInstance()->GetPageMutex().unlock();
	//�Ի�ȡ��span�з֣�����Ҫ��������Ϊ�����̷߳��ʲ������span
	char* start = (char*)(span->_pageId << PAGE_SHIFT); //����span����ʼ��ַ��ҳ��*һҳ�Ĵ�С��
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


	_spanLists[index].GetMutex().unlock();
	return actualNum;
}


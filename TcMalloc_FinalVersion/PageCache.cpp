#include"PageCache.h"

PageCache PageCache::_sInstan;

Span* PageCache::NewSpan(size_t k)
{
	assert(k > 0);
	//����128ҳ��ֱ���������
	if (k > NPAGES - 1)
	{
		void* ptr = SystemAlloc(k);
		//Span* span = new Span;
		Span* span = spanPool.New();
		span->_pageId = (PAGE_ID)ptr >> PAGE_SHIFT;
		span->_n = k;
		//_idSpanMap[span->_pageId] = span;
		_idSpanMap.set(span->_pageId, span);
		return span; 
	}
	if (!_spanLists[k].Empty())
	{
		Span* kSpan =_spanLists[k].PopFront();
		for (PAGE_ID i = 0; i < kSpan->_n; ++i)
		{
			//_idSpanMap[kSpan->_pageId + i] = kSpan;
			_idSpanMap.set(kSpan->_pageId + i,kSpan);
		}
		return kSpan;
	}
	//�������Ͱ������û��span������п��԰��������з�
	for (size_t i = k + 1; i < NPAGES; ++i)
	{
		if (!_spanLists[i].Empty())
		{
			//ֻҪ�в�Ϊ�յ�Ͱ���ͽ����з�:��nҳ��span�зֳ�kҳ��span��n-kҳ��span��kҳ��
			//span���ظ�centralcache��n-kҲ��span�ҵ���n-kͰ��ȥ
			Span* nSpan = _spanLists[i].PopFront();
			//Span* kSpan = new Span;
			Span* kSpan = spanPool.New();
			//��nSpan��ͷ����һ��kҳ����
			kSpan->_pageId = nSpan->_pageId;
			kSpan->_n = k;

			nSpan->_pageId += k;
			nSpan->_n -= k;

			_spanLists[nSpan->_n].PushFront(nSpan);
			//�洢nSpan����βҳ�Ÿ�nSpan��ӳ�䣬����page cache�����ڴ�ʱ���кϲ�����
			//_idSpanMap[nSpan->_pageId] = nSpan;
			_idSpanMap.set(nSpan->_pageId,nSpan);
			//_idSpanMap[nSpan->_pageId + nSpan->_n - 1] = nSpan;
			_idSpanMap.set(nSpan->_pageId + nSpan->_n - 1,nSpan);

			//����id��span��ӳ�䣬����centralcache����С���ڴ�ʱ���Ҷ�Ӧ��span
			for (PAGE_ID i = 0; i < kSpan->_n; ++i)
			{
				//_idSpanMap[kSpan->_pageId + i] = kSpan;
				_idSpanMap.set(kSpan->_pageId + i,kSpan);
			}
			return kSpan;
		}
	}
	//����û�д�ҳ��span->�Ҷ�Ҫһ��128ҳ��span
	//Span* bigSpan = new Span;
	Span* bigSpan = spanPool.New();
	void* ptr = SystemAlloc(NPAGES - 1);
	//��ҳ�ڴ��ҳ��=��ҳ�ڴ����ʼ��ַ/��ҳ�Ĵ�С
	bigSpan->_pageId = (PAGE_ID)ptr >> PAGE_SHIFT;
	bigSpan->_n = NPAGES - 1;

	_spanLists[bigSpan->_n].PushFront(bigSpan);
	return NewSpan(k);
}
Span* PageCache::MapObjectToSpan(void* obj)
{
	PAGE_ID id = ((PAGE_ID)obj >> PAGE_SHIFT);

	//std::unique_lock<std::mutex> lock(PageCache::GetPageMutex());
	//auto ret = _idSpanMap.find(id);
	auto ret =(Span*) _idSpanMap.get(id);
	//if (ret != _idSpanMap.end())
	//{
		//return ret->second;
	//}
	if (ret) 
	{
		return ret;
	}
	else
	{
		assert(false);
		return nullptr;
	}
}

void PageCache::ReleaseSpanToPageCache(Span* span)
{
	//����128page��ֱ�ӻ�����
	if (span->_n > NPAGES - 1) {
		void* ptr = (void*)(span->_pageId << PAGE_SHIFT);
		SystemFree(ptr);
		//delete span;
		spanPool.Delete(span);
		return ;
	}
	//��spanǰ���ҳ�����Խ��кϲ��������ڴ���Ƭ����
	while (true)
	{
		PAGE_ID prevId = span->_pageId - 1;
		//auto ret = _idSpanMap.find(prevId);
		//spanǰ���ҳ��û�У����ϲ�
		/*if (ret == _idSpanMap.end())
		{
			break;
		}*/
		auto ret = (Span*)_idSpanMap.get(prevId);
		if (ret == nullptr)
		{
			break;
		}
		//ǰ�����ڵ�ҳ��span�ڱ�ʹ�ã����ϲ�
		//Span* prevSpan = ret->second;
		Span* prevSpan = ret;
		if (prevSpan->_isUse)
		{
			break;
		}
		//�ϲ�����ҳ������NPAGES-1�����ϲ�
		if (prevSpan->_n + span->_n > NPAGES - 1)
		{
			break;
		}
		span->_pageId = prevSpan->_pageId;
		span->_n += prevSpan->_n;
		_spanLists[prevSpan->_n].erase(prevSpan);
		//delete prevSpan;
		spanPool.Delete(prevSpan);
	}
	//���ϲ�
	while (true)
	{
		PAGE_ID nextId = span->_pageId +span->_n;
		//auto ret = _idSpanMap.find(nextId);
		//spanǰ���ҳ��û�У����ϲ�
		//if (ret == _idSpanMap.end())
		//{
		//	break;
		//}
		auto ret = (Span*)_idSpanMap.get(nextId);
		if (ret == nullptr)
		{
			break;
		}
		//ǰ�����ڵ�ҳ��span�ڱ�ʹ�ã����ϲ�
		Span* nextSpan = ret;
		//Span* nextSpan = ret->second;
		if (nextSpan->_isUse)
		{
			break;
		}
		//�ϲ�����ҳ������NPAGES-1�����ϲ�
		if (nextSpan->_n + span->_n > NPAGES - 1)
		{
			break;
		}
		span->_n += nextSpan->_n;
		_spanLists[nextSpan->_n].erase(nextSpan);
		//delete nextSpan;
		spanPool.Delete(nextSpan);
	}
	//���ڶ�Ӧ��spanlists������_idSpanMap�����ӳ�����
	_spanLists[span->_n].PushFront(span);
	span->_isUse = false;
	//_idSpanMap[span->_pageId] = span;
	_idSpanMap.set(span->_pageId, span);
	//_idSpanMap[span->_pageId + span->_n - 1] = span;
	_idSpanMap.set(span->_pageId + span->_n - 1,span);
}
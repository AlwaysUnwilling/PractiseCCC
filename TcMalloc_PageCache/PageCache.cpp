#include"Common.h"
#include"PageCache.h"

PageCache PageCache:: _sInstan;
Span* PageCache::NewSpan(size_t k)
{
	assert(k > 0 && k < NPAGES);
	if (!_spanLists[k].Empty())
	{
		return _spanLists[k].PopFront();
	}
	//�������Ͱ������û��span������п��԰��������з�
	for (size_t i = k + 1; i < NPAGES; ++i)
	{
		if (!_spanLists[i].Empty())
		{
			//ֻҪ�в�Ϊ�յ�Ͱ���ͽ����з�:��nҳ��span�зֳ�kҳ��span��n-kҳ��span��kҳ��
			//span���ظ�centralcache��n-kҲ��span�ҵ���n-kͰ��ȥ
			Span* nSpan = _spanLists[i].PopFront();
			Span* kSpan = new Span;
			//��nSpan��ͷ����һ��kҳ����
			kSpan->_pageId = nSpan->_pageId;
			nSpan->_n = k;

			nSpan->_pageId += k;
			nSpan->_n -= k;

			_spanLists[nSpan->_n].PushFront(nSpan);
			return kSpan;
		}
	}
	//����û�д�ҳ��span->�Ҷ�Ҫһ��128ҳ��span
	Span* bigSpan = new Span;
	void* ptr = SystemAlloc(NPAGES - 1);
	bigSpan->_pageId = (PAGE_ID)ptr >> PAGE_SHIFT;
	bigSpan->_n = NPAGES - 1;

	_spanLists[bigSpan->_n].PushFront(bigSpan);
	return NewSpan(k);
}
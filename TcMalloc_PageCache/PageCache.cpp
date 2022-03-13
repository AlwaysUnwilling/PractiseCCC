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
	//检查后面的桶里面有没有span。如果有可以把他进行切分
	for (size_t i = k + 1; i < NPAGES; ++i)
	{
		if (!_spanLists[i].Empty())
		{
			//只要有不为空的桶，就进行切分:把n页的span切分成k页的span和n-k页的span；k页的
			//span返回给centralcache；n-k也的span挂到第n-k桶中去
			Span* nSpan = _spanLists[i].PopFront();
			Span* kSpan = new Span;
			//在nSpan的头部切一个k页下来
			kSpan->_pageId = nSpan->_pageId;
			nSpan->_n = k;

			nSpan->_pageId += k;
			nSpan->_n -= k;

			_spanLists[nSpan->_n].PushFront(nSpan);
			return kSpan;
		}
	}
	//后面没有大页的span->找堆要一个128页的span
	Span* bigSpan = new Span;
	void* ptr = SystemAlloc(NPAGES - 1);
	bigSpan->_pageId = (PAGE_ID)ptr >> PAGE_SHIFT;
	bigSpan->_n = NPAGES - 1;

	_spanLists[bigSpan->_n].PushFront(bigSpan);
	return NewSpan(k);
}
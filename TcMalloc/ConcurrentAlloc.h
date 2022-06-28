#pragma once

#include"Common.h"
#include"ThreadCache.h"
#include"PageCache.h"
#include"ObjectPool.h"

static void* ConcurrentAlloc(size_t size)
{
	if (size > MAX_BYTES) 
	{
		size_t alignSize = SizeClass::RoundUp(size); 
		size_t kpage = alignSize >> PAGE_SHIFT;
		PageCache::GetPageInstance()->GetPageMutex().lock();
		Span* span=PageCache::GetPageInstance()->NewSpan(kpage);
		span->ObjectSize = size;
		PageCache::GetPageInstance()->GetPageMutex().unlock();
		void* ptr = (void*)(span->_pageId << PAGE_SHIFT);
		return ptr;
	}
	else
	{
		if (pTLSThreadCache == nullptr)
		{
			//pTLSThreadCache = new ThreadCache;
			static ObjectPool<ThreadCache> tcPool;
			pTLSThreadCache = tcPool.New();
		}
		//cout << "pTLSThreadCache:" << std::this_thread::get_id() << "::" << pTLSThreadCache << endl;
		return pTLSThreadCache->Allocate(size);
	}

}

//static void ConcurrentFree(void* ptr, size_t size)
static void ConcurrentFree(void* ptr)
{
	Span* span = PageCache::GetPageInstance()->MapObjectToSpan(ptr);
	size_t size = span->ObjectSize;
	if (size > MAX_BYTES)
	{
		//µ¥¶À¼ÓËø
		Span* span = PageCache::GetPageInstance()->MapObjectToSpan(ptr);

		//¼ÓËø
		PageCache::GetPageInstance()->GetPageMutex().lock();
		PageCache::GetPageInstance()->ReleaseSpanToPageCache(span);
		PageCache::GetPageInstance()->GetPageMutex().unlock();
	}
	else
	{
		assert(pTLSThreadCache);
		pTLSThreadCache->Deallocate(ptr, size);
	}
}
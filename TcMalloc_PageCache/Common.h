#pragma once

#include<iostream>
#include<vector>
#include<thread>
#include<mutex>
#include<time.h>
#include<assert.h>
#include<algorithm>


using std::cout;
using std::endl;

static const size_t MAX_BYTES = 256 * 1024;
static const size_t NFREELIST = 208;
static const size_t NPAGES = 129;
static const size_t PAGE_SHIFT = 13;

#ifdef _WIN64  //WIN32下只有WIN32定义，没有WIN64定义 ;要想在WIN64下执行64标准,需要先执行WIN64
	typedef unsigned long long PAGE_ID;
#elif _WIN32    //在WIN64下既有WIN32定义，也有WIN64定义
	typedef size_t PAGE_ID;
#elif 
    //linux
#endif 

#ifdef _WIN32
#include<windows.h>
#else
// 
#endif

// 直接去堆上按页申请空间
inline static void* SystemAlloc(size_t kpage)
{
#ifdef _WIN32
	void* ptr = VirtualAlloc(0, kpage << 13, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
#else
	// linux下brk mmap等
#endif

	if (ptr == nullptr)
		throw std::bad_alloc();

	return ptr;
}

static void*& NextObj(void* obj)
{
	return *(void**)obj;
}
//管理切分好的小对象的自由链表
class FreeList
{
private:
	void* _freeList=nullptr;
	size_t _maxSize = 1;
public:
	size_t& MaxSize()
	{
		return _maxSize;
	}
	void Push(void* obj)  //把还回来的内存块头插到自由链表中
	{
		assert(obj);
		//*(void**)obj = _freeList;
		//_freeList = obj;
		NextObj(obj) = _freeList;
		_freeList = obj;
	}
	void PushRange(void* start, void* end)
	{
		NextObj(end) = _freeList;
		_freeList = start;
	}
	void* Pop()    //   弹出一个内存块    头删     
	{
		assert(_freeList);
		void* ret = _freeList;
		_freeList = NextObj(_freeList);
		return ret;
	}
	bool Empty()
	{
		return _freeList == nullptr;
	}
};

//管理对象大小的对齐映射规则
//静态内联函数可以直接使用类直接调用，不需要使用对象去调
class SizeClass
{
private:
      //整体控制在最多10%左右的内存碎片浪费
	  // 内存范围              内存对齐标准      自由链表中桶的个数范围
	  //[1,128]               8byte对齐        freeList[0,16)
	  //[128+1,1024]          16byte对齐       freeList[16,72)
	  //[1024+1,8*1024]       128byte对齐      freeList[72,128)
	  //[8*1024+1,64*1024]    1024byte对齐     freeList[128,184)
	  //[64*1024+1,256*1024]  8*1024byte对齐   freeList[184,208)
	//static inline size_t _RoundUp(size_t size, size_t alignNum)
	//{
	//	size_t alignSize = size;
	//	if (size % alignNum)
	//	{
	//		alignSize = (size / alignNum + 1) * alignNum;
	//	}
	//	return alignSize;
	//}
	static inline size_t _RoundUp(size_t size, size_t alignNum)
	{
		return ((size+alignNum-1) & ~(alignNum - 1));
	}
	//static inline size_t _Index(size_t bytes, size_t alignNum)
	//{
	//	if (bytes % alignNum)
	//	{
	//		return bytes / alignNum - 1;
	//	}
	//	return bytes / alignNum;
	//}
	static inline size_t _Index(size_t bytes, size_t alignNum_shift)
	{
		return ((bytes + (1 << alignNum_shift) - 1) >> alignNum_shift) - 1;
	}
public:
	//获取bytes内存块在自由链表数组对应的索引
	static inline size_t Index(size_t bytes)
	{
		assert(bytes <= MAX_BYTES);
		//每个区间有多少个自由链表
		static int group_array[4] = { 16,56,56,56 };
		if (bytes <= 128)
		{
			return _Index(bytes, 3);
		}
		else if (bytes <= 1024)
		{
			return _Index(bytes - 128, 4) + group_array[0];
		}
		else if (bytes <= 8 * 1024)
		{
			return _Index(bytes - 1024, 7) + group_array[1] + group_array[0];
		}
		else if (bytes <= 64 * 1024)
		{
			return _Index(bytes - 8 * 1024, 10) + group_array[2] + group_array[1] + group_array[0];
		}
		else if (bytes <= 256 * 1024)
		{
			return _Index(bytes - 64 * 1024, 13) + group_array[3] + group_array[2] + group_array[1] + group_array[0];
		}
		else {
			assert(false);
			return -1;
		}
	}
	//需求size大小的内存块，实际返回的内存块大小
	static inline size_t RoundUp(size_t size)
	{
		if (size <= 128) {
			return _RoundUp(size, 8);
		}
		else if (size <= 1024) {
			return _RoundUp(size, 16);
		}
		else if (size <= 8 * 1024) {
			return _RoundUp(size, 128);
		}
		else if (size <= 64 * 1024) {
			return _RoundUp(size, 1025);
		}
		else if (size <= 256 * 1024) {
			return _RoundUp(size, 8*1024);
		}
		else {
			assert(false);
			return -1;
		}
	}
	//一次threadcache从中心缓存中获取多少个对象
	static size_t NumMoveSize(size_t size)
	{
		assert(size > 0);
		//[2,512]一次批量移动多少个对象（慢启动）上限制
		//小对象一次批量上限高
		//小对象一次批量上限低
		int num = MAX_BYTES / size;
		if (num < 2) {
			num = 2;
		}
		if (num > 512) {
			num = 512;
		}
		return num;
	}
	static size_t NumMovePage(size_t size)
	{
		size_t num = NumMoveSize(size);
		size_t npage = num * size;
		npage >>= PAGE_SHIFT;
		if (npage == 0)
		{
			npage = 1;
		}
		return npage;
	}

};

//管理多个连续页大块内存跨度结构
struct Span
{
	PAGE_ID _pageId=0;  //大块内存起始页的页号
	size_t _n=0;     //页的数量
	Span* _next=nullptr;   //双向链表结构
	Span* _prev=nullptr;
	size_t _useCount=0;//切好小块内存，被分配给threadcache的计数
	void* _freeList=nullptr;//切好的小块内存的自由链表
};
//带头双向循环链表
class SpanList
{
private:
	Span* _head;
	std::mutex _mtx;  //桶锁
public:
	std::mutex& GetMutex()
	{
		return _mtx;
	}
	void PushFront(Span* span)
	{
		insert(Begin(), span);
	}
	Span* Begin()
	{
		return _head->_next;
	}
	Span* End()
	{
		return _head;
	}
	SpanList()
	{
		_head = new Span;
		_head->_next = _head;
		_head->_prev = _head;
	}
	void insert(Span* pos, Span* newSpan)
	{
		assert(pos);
		assert(newSpan);
		Span* prev = pos->_prev;
		prev->_next = newSpan;
		newSpan->_prev = prev;
		newSpan->_next = pos;
		pos->_prev = newSpan;
	}
	void erase(Span* pos)
	{
		assert(pos);
		assert(pos != _head);
		Span* prev = pos->_prev;
		Span* next = pos->_next;
		prev->_next = next;
		next->_prev = prev;
	}
	Span* PopFront()
	{
		Span* front = _head->_next;
		erase(front);
		return front;
	}
	bool Empty()
	{
		return _head->_next == nullptr;
	}
};
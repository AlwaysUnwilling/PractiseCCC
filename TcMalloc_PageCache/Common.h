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

#ifdef _WIN64  //WIN32��ֻ��WIN32���壬û��WIN64���� ;Ҫ����WIN64��ִ��64��׼,��Ҫ��ִ��WIN64
	typedef unsigned long long PAGE_ID;
#elif _WIN32    //��WIN64�¼���WIN32���壬Ҳ��WIN64����
	typedef size_t PAGE_ID;
#elif 
    //linux
#endif 

#ifdef _WIN32
#include<windows.h>
#else
// 
#endif

// ֱ��ȥ���ϰ�ҳ����ռ�
inline static void* SystemAlloc(size_t kpage)
{
#ifdef _WIN32
	void* ptr = VirtualAlloc(0, kpage << 13, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
#else
	// linux��brk mmap��
#endif

	if (ptr == nullptr)
		throw std::bad_alloc();

	return ptr;
}

static void*& NextObj(void* obj)
{
	return *(void**)obj;
}
//�����зֺõ�С�������������
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
	void Push(void* obj)  //�ѻ��������ڴ��ͷ�嵽����������
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
	void* Pop()    //   ����һ���ڴ��    ͷɾ     
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

//��������С�Ķ���ӳ�����
//��̬������������ֱ��ʹ����ֱ�ӵ��ã�����Ҫʹ�ö���ȥ��
class SizeClass
{
private:
      //������������10%���ҵ��ڴ���Ƭ�˷�
	  // �ڴ淶Χ              �ڴ�����׼      ����������Ͱ�ĸ�����Χ
	  //[1,128]               8byte����        freeList[0,16)
	  //[128+1,1024]          16byte����       freeList[16,72)
	  //[1024+1,8*1024]       128byte����      freeList[72,128)
	  //[8*1024+1,64*1024]    1024byte����     freeList[128,184)
	  //[64*1024+1,256*1024]  8*1024byte����   freeList[184,208)
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
	//��ȡbytes�ڴ�����������������Ӧ������
	static inline size_t Index(size_t bytes)
	{
		assert(bytes <= MAX_BYTES);
		//ÿ�������ж��ٸ���������
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
	//����size��С���ڴ�飬ʵ�ʷ��ص��ڴ���С
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
	//һ��threadcache�����Ļ����л�ȡ���ٸ�����
	static size_t NumMoveSize(size_t size)
	{
		assert(size > 0);
		//[2,512]һ�������ƶ����ٸ�������������������
		//С����һ���������޸�
		//С����һ���������޵�
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

//����������ҳ����ڴ��Ƚṹ
struct Span
{
	PAGE_ID _pageId=0;  //����ڴ���ʼҳ��ҳ��
	size_t _n=0;     //ҳ������
	Span* _next=nullptr;   //˫������ṹ
	Span* _prev=nullptr;
	size_t _useCount=0;//�к�С���ڴ棬�������threadcache�ļ���
	void* _freeList=nullptr;//�кõ�С���ڴ����������
};
//��ͷ˫��ѭ������
class SpanList
{
private:
	Span* _head;
	std::mutex _mtx;  //Ͱ��
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
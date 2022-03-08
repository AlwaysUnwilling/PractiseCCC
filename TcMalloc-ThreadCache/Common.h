#pragma once

#include<iostream>
#include<vector>
#include<thread>
#include<time.h>
#include<assert.h>


using std::cout;
using std::endl;

static const size_t MAX_BYTES = 256 * 1024;
static const size_t NFREELIST = 208;

static void*& NextObj(void* obj)
{
	return *(void**)obj;
}
//管理切分好的小对象的自由链表
class FreeList
{
private:
	void* _freeList=nullptr;
public:
	void Push(void* obj)  //把还回来的内存块头插到自由链表中
	{
		assert(obj);
		//*(void**)obj = _freeList;
		//_freeList = obj;
		NextObj(obj) = _freeList;
		_freeList = obj;
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
};
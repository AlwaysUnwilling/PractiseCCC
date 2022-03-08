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
//�����зֺõ�С�������������
class FreeList
{
private:
	void* _freeList=nullptr;
public:
	void Push(void* obj)  //�ѻ��������ڴ��ͷ�嵽����������
	{
		assert(obj);
		//*(void**)obj = _freeList;
		//_freeList = obj;
		NextObj(obj) = _freeList;
		_freeList = obj;
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
};
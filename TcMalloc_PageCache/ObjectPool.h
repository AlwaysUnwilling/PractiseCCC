#pragma once
#include"Common.h"
//
//template<size_t N>
//class ObjectPool
//{};

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

#define CAPCITY (128*1024)
template<class T>
class ObjectPool
{
private:
	char* _memory = nullptr;   //n内存块
	size_t _remainSize = 0;       //内存块剩余大小（bytes）
	void* _freelist = nullptr;    //还回的内存块链表头结点
public:
	T* New()
	{
		T* obj = nullptr;
		if (_freelist) {
			obj = (T*)_freelist;
			void* next = *(void**)_freelist;
			_freelist = next;
		}else {
			if (_remainSize < sizeof(T)) {
				_remainSize = CAPCITY;
				//_memory = (char*)malloc(_remainSize);
				//if (_memory == nullptr) {
				//	throw std::bad_alloc();
				//}
				_memory = (char*)SystemAlloc(_remainSize >> 13);
				if (_memory == nullptr)
				{
					throw std::bad_alloc();
				}
			}
			obj = (T*)_memory;
			size_t objSize = sizeof(T) < sizeof(void*) ? sizeof(void*) : sizeof(T);
			_memory += sizeof(T);
			_remainSize -= objSize;
		}
		new(obj)T;   //定位new。显示调用T的构造函数初始化
		return obj;
	}
	void Delete(T* obj)
	{
		obj->~T();        //显示调用obj的析构函数清理对象 并不是释放obj而是T对象里的析构函数清理资源
		*(void**)obj = nullptr;
		_freelist = obj;
	}
};

struct TreeNode
{
	int _val;
	TreeNode* _left;
	TreeNode* _right;

	TreeNode()
		:_val(0)
		, _left(nullptr)
		, _right(nullptr)
	{}
};
void TestObjectPool()
{
	// 申请释放的轮次
	const size_t Rounds = 5;

	// 每轮申请释放多少次
	const size_t N = 100000;

	std::vector<TreeNode*> v1;
	v1.reserve(N);

	size_t begin1 = clock();
	for (size_t j = 0; j < Rounds; ++j)
	{
		for (int i = 0; i < N; ++i)
		{
			v1.push_back(new TreeNode);
		}
		for (int i = 0; i < N; ++i)
		{
			delete v1[i];
		}
		v1.clear();
	}

	size_t end1 = clock();

	std::vector<TreeNode*> v2;
	v2.reserve(N);

	ObjectPool<TreeNode> TNPool;
	size_t begin2 = clock();
	for (size_t j = 0; j < Rounds; ++j)
	{
		for (int i = 0; i < N; ++i)
		{
			v2.push_back(TNPool.New());
		}
		for (int i = 0; i < N; ++i)
		{
			TNPool.Delete(v2[i]);
		}
		v2.clear();
	}
	size_t end2 = clock();

	cout << "new cost time:" << end1 - begin1 << endl;
	cout << "object pool cost time:" << end2 - begin2 << endl;
}
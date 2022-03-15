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

#define CAPCITY (128*1024)
template<class T>
class ObjectPool
{
private:
	char* _memory = nullptr;   //n�ڴ��
	size_t _remainSize = 0;       //�ڴ��ʣ���С��bytes��
	void* _freelist = nullptr;    //���ص��ڴ������ͷ���
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
		new(obj)T;   //��λnew����ʾ����T�Ĺ��캯����ʼ��
		return obj;
	}
	void Delete(T* obj)
	{
		obj->~T();        //��ʾ����obj����������������� �������ͷ�obj����T���������������������Դ
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
	// �����ͷŵ��ִ�
	const size_t Rounds = 5;

	// ÿ�������ͷŶ��ٴ�
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
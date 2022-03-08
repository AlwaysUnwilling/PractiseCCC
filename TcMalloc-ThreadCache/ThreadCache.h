#pragma once
#include"Common.h"


class ThreadCache
{
public:
	void* Allocate(size_t size);   //申请需要的空间大小 bytes
	void Deallocate(void* ptr, size_t size);  //size方便还回来的空间通过size打大小映射到对应的hash桶中挂起
	//从中心缓存获取对象
	void* FetchFromCenTralCache(size_t index, size_t size);
private:
	FreeList _freeLists[NFREELIST];
};

//Thread Local Storage（线程局部存储）TLS
//线程局部存储（TLS），是一种变量的存储方法，这个变量在它所在的线程内是全局可访问的，但
//是不能被其他线程访问到，这样就保持了数据的线程独立性。而熟知的全局变量，是所有线程都可
//以访问的，这样就不可避免需要锁来控制，增加了控制成本和代码复杂度。
static _declspec(thread) ThreadCache* pTLSThreadCache = nullptr;

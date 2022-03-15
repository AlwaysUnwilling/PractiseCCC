#include"ThreadCache.h"
#include"CentralCache.h"


void* ThreadCache::FetchFromCenTralCache(size_t index, size_t size)
{
	//����ʼ���������㷨
	//1������ʼ����һ����centralcache����Ҫ̫�࣬��ΪҪ̫����ܻ��ò����˷ѵ�
	//2������㲻Ҫ���size��С�ڴ�������ôbatchNum�ͻ᲻��������ֱ������
	//3��sizeԽ��һ����centralcacheҪ��batchNum��ԽС
	//4��sizeԽС��һ��centralcacheҪ��bachNum��Խ��
	size_t batchNum = min(_freeLists[index].MaxSize(),SizeClass::NumMoveSize(size));
	if (_freeLists[index].MaxSize() == batchNum)
	{
		_freeLists[index].MaxSize() += 1;
	}
	void* start = nullptr;
	void* end = nullptr;
	size_t actucalNum=CentralCache::GetInstance()->FetchRangeObj(start, end, batchNum, size);
	assert(actucalNum > 0);
	if (actucalNum == 1)  //ֻ����һ��������start��endһ�����
	{
		assert(start == end);
		//  or return end;
	}
	else  //�����˶������ѵ�һ�η��أ������Ĺ���threadcache������������
	{
		_freeLists[index].PushRange(NextObj(start), end, actucalNum-1);

	}
	return start;
}
void* ThreadCache::Allocate(size_t size)
{
	assert(size <= MAX_BYTES);
	size_t alignSize = SizeClass::RoundUp(size);
	size_t index = SizeClass::Index(size);

	if (!_freeLists[index].Empty())
	{
		return _freeLists[index].Pop();
	}
	else
	{
		return FetchFromCenTralCache(index, alignSize);
	}
}
void ThreadCache::ListTooLong(FreeList& list, size_t size)
{
	void* start = nullptr;
	void* end = nullptr;
	list.PopRange(start, end, list.MaxSize());
	CentralCache::GetInstance()->ReleaseListTOSpans(start,size);
}
void ThreadCache::Deallocate(void* ptr, size_t size)
{
	assert(ptr);
	assert(size <= MAX_BYTES);
	size_t index = SizeClass::Index(size);
	_freeLists[index].Push(ptr);
	//���_freeLists[index]�ĳ��ȣ��ڵ������>= ������һ�������������������Ҫ��
	//������ڴ滹��central cache
	if (_freeLists[index].Size() >= _freeLists[index].MaxSize())
	{
		ListTooLong(_freeLists[index], size);
	}
}
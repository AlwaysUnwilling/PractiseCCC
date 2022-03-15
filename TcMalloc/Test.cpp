#include"ConcurrentAlloc.h"



void Alloc1()
{
	for (size_t i = 0; i < 5; ++i)
	{
		void* ptr=ConcurrentAlloc(6);
	}
}
void Alloc2()
{
	for (size_t i = 0; i < 5; ++i)
	{
		void* ptr = ConcurrentAlloc(6);
	}
}
void TLSTest()
{
	std::thread t1(Alloc1);
	t1.join();
	cout << endl;
	std::thread t2(Alloc1);
	t2.join();
}
void TestConcurrentAlloc()
{
	void* p1 = ConcurrentAlloc(6);
	void* p2 = ConcurrentAlloc(8);
	void* p3 = ConcurrentAlloc(1);
	void* p4 = ConcurrentAlloc(7);
	void* p5 = ConcurrentAlloc(8);
	void* p6 = ConcurrentAlloc(8);
	void* p7 = ConcurrentAlloc(8);
	std::cout << p1 << std::endl;
	std::cout << p2 << std::endl;
	std::cout << p3 << std::endl;
	std::cout << p4 << std::endl;
	std::cout << p5 << std::endl;
	ConcurrentFree(p1, 6);
	ConcurrentFree(p2, 8);
	ConcurrentFree(p3, 1);
	ConcurrentFree(p4, 7);
	ConcurrentFree(p5, 8);
	ConcurrentFree(p6, 8);
	ConcurrentFree(p7, 8);
}
void MultiThreadAlloc1()
{
	std::vector<void*> v1;
	for (size_t i = 0; i < 5; ++i)
	{
		void* ptr = ConcurrentAlloc(6);
		v1.push_back(ptr);
	}
	for (auto e : v1)
	{
		ConcurrentFree(e, 6);
	}
}
void MultiThreadAlloc2()
{
	std::vector<void*> v2;
	for (size_t i = 0; i < 5; ++i)
	{
		void* ptr = ConcurrentAlloc(6);
		v2.push_back(ptr);
	}
	for (auto e : v2)
	{
		ConcurrentFree(e, 6);
	}
}
void TestMultiThread()
{
	std::thread t1(MultiThreadAlloc1);
	
	cout << endl;
	std::thread t2(MultiThreadAlloc2);
	t1.join();
	t2.join();
}
int main()
{
	//TLSTest();
	//TestConcurrentAlloc();
	TestMultiThread();
	return 0;
}
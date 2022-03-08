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
int main()
{
	TLSTest();
	return 0;
}
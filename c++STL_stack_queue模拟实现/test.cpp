#include<iostream>
using namespace std;
#include"stack_queue.h"
#include<deque>

void test_deque()  //双端队列
{
	deque<int> d;
	d.push_back(1);
	d.push_back(2);
	d.push_back(3);
	d.push_back(4);
	deque<int>::iterator it = d.begin();
	while (it != d.end())
	{
		cout << *it << " ";
		++it;
	}
	cout << endl;
	for (size_t i = 0; i < d.size(); ++i)
	{
		cout << d[i] << " ";
	}
	cout << endl;
	for (auto& e : d)
	{
		e += 1;
		cout << e << " ";
	}
	cout << endl;
	d.pop_front();
	d.pop_back();
	for (auto e : d)
	{
		cout << e << " ";
	}
	cout << endl;
}
int main()
{
	//my_stack_queue::test_stack();
	//my_stack_queue::test_queue();
	test_deque();
	return 0;
}
//双端队列可以解决vector和list的缺点，看似很完美，但是它也有它的不足：
//1.deque大量频繁的operator[]即随机访问效率不高；
//2.deque的迭代器遍历相对复杂，效率也相对不高。
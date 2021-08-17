#include<iostream>
using namespace std;
#include"SmartPtr.h"


//int main()
//{
//	//my_SmartPtr::shared_ptr<int> sp1(new int);
//	//my_SmartPtr::shared_ptr<int> sp2(sp1);
//	//my_SmartPtr::shared_ptr<int> sp3(sp1);
//	//my_SmartPtr::shared_ptr<int> sp4(new int);
//	//my_SmartPtr::shared_ptr<int> sp5(sp4);
//	//my_SmartPtr::shared_ptr<int> sp6(sp4);
//	//my_SmartPtr::shared_ptr<int> sp7(sp4);
//	//sp1 = sp4;
//
//	// shared_ptr的拷贝赋值时的线程安全问题
//	//shared_ptr是否是线程安全的？注意这里问题的shared_ptr对象拷贝和析构++/--引用计数(存放在堆上的)是否是安全的，库的实现中是安全的。
//	my_SmartPtr::shared_ptr<int> sp(new int);
//	cout << sp.use_count() << endl;
//	int n = 10000;
//
//	thread t1([&]() {
//		for (int i = 0; i < n; ++i)
//		{
//			my_SmartPtr::shared_ptr<int> sp1(sp);
//		}
//		});
//	thread t2([&]() {
//		for (int i = 0; i < n; ++i)
//		{
//			my_SmartPtr::shared_ptr<int> sp2(sp);
//		}
//		});
//	t1.join();
//	t2.join();
//	cout << sp.use_count() << endl;
//	return 0;
//}

//shared_ptr循环引用；
struct ListNode
{
	int val;
	//ListNode* _next;
	//ListNode* _prev;
	//my_SmartPtr::shared_ptr<ListNode> _spnext;
	//my_SmartPtr::shared_ptr<ListNode> _spprev;
	my_SmartPtr::weak_ptr<ListNode> _spnext;
	my_SmartPtr::weak_ptr<ListNode> _spprev;
	~ListNode()
	{
		cout << "~ListNode()" << endl;
	}
};

int main()
{
	//ListNode* n1 = new ListNode;
	//ListNode* n2 = new ListNode;

	//n1->_next = n2;
	//n2->_prev = n1;
	//delete n1;
	//delete n2;
	my_SmartPtr::shared_ptr<ListNode> spn1(new ListNode);
	my_SmartPtr::shared_ptr<ListNode> spn2(new ListNode);
	//spn1->_next = spn2;  //spn1->_next的类型是ListNode*，spn2的类型是my_SmartPtr::shared_ptr<ListNode>；不能互相赋值
	//spn2->_prev = spn1;  //将ListNode的_next和_prev类型全部用智能指针替换.

	//循环引用
	spn1->_spnext = spn2;  //解决方式：使用weak_ptr，不增加引用计数；
	spn2->_spprev = spn1;
	return 0;
}
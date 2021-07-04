//面试：为什么会有list？
//因为它是为了补充vector缺点菜存在的。
//vector的优缺点：
//缺点：
//1、头部和中间插入删除数据效率低，时间复杂度O(N)，因为要挪动数据。
//2、插入数据空间不够需要增容吗，增容需要开辟新空间、拷贝数据吗、释放旧空间，会付出巨大代价。
//优点：
//*支持下标随机访问。operator[];间接的就很好的支持排序，二分查找，对算法等等。
//list的优点：
//1、list的头部和中间插入删除不需要挪动数据，效率高。O(1)
//2、list插入数据是新增结点，不需要增容。
//缺点：
//*不支持随机访问
//总结：实际使用中vector和list是相辅相成的俩个容器。
#include<list>
#include<iostream>
using namespace std;
void test_list1()
{
	list<int> l;
	l.push_back(1);
	l.push_back(2);
	l.push_back(3);
	l.push_back(4);
	list<int>::iterator it = l.begin();  //迭代器，可读可写
	while (it != l.end())
	{
		cout << *it << " ";
		++it;
	}
	cout << endl;
	l.push_front(0);
	l.push_front(-1);
	for (auto e : l)   //范围for
	{
		cout << e << " ";
	}
	cout << endl;
	l.pop_back();
	l.pop_front();
	for (auto e : l)
	{
		cout << e << " ";
	}
	cout << endl;
	list<int>::const_iterator conit = l.begin();   //只读
	while (conit != l.end())
	{
		cout << *conit << " ";
		++conit;
	}
	cout << endl;
	list<int>::reverse_iterator rit = l.rbegin();   //反向迭代器
	while (rit != l.rend())
	{
		cout << *rit << " ";
		++rit;
	}
	cout << endl;
}
void test_list2()
{
	list<int> l;
	l.push_back(1);
	l.push_back(2);
	l.push_back(3);
	l.push_back(4);
	l.push_back(5);
	l.push_back(6);
	for (auto e : l)   //范围for
	{
		cout << e << " ";
	}
	cout << endl;
	list<int>::iterator pos = find(l.begin(), l.end(), 3);   //insert()的插入位置pos需要通过算法函数find()进行查找，然后判断是否存在该位置，然后进行插入
	if (pos != l.end())                          //list<int>的迭代器是指针，但和vector的指针不一样。
	{
		l.insert(pos, 30);//这里的插入后list的迭代器并没有失效，而vector/string迭代器在插入删除后迭代器会失效（因为插入删除会挪动数据和涉及增容问题）
		l.erase(pos);//而list的erase()后会失效，因为该节点已经被删除。
	}
	for (auto e : l)   //范围for
	{
		cout << e << " ";
	}
	cout << endl;
}
void test_list3()
{
	list<int> l1;
	l1.push_back(1);
	l1.push_back(2);
	l1.push_back(3);
	l1.push_back(4);
	l1.push_back(5);
	l1.push_back(6);
	list<int> l2;
	l2.push_back(7);
	l2.push_back(8);
	l2.push_back(9);
	l2.push_back(10);
	l2.push_back(11);
	l2.push_back(12);
	//std::list::splice   //将俩个链表合并
	//entire list(1)
	//	void splice(iterator position, list & x);
	//single element(2)
	//	void splice(iterator position, list & x, iterator i);
	//element range(3)
	//	void splice(iterator position, list & x, iterator first, iterator last);
	// splicing lists
//#include <iostream>
//#include <list>
//
//	int main()
//	{
//		std::list<int> mylist1, mylist2;
//		std::list<int>::iterator it;
//
//		// set some initial values:
//		for (int i = 1; i <= 4; ++i)
//			mylist1.push_back(i);      // mylist1: 1 2 3 4
//
//		for (int i = 1; i <= 3; ++i)
//			mylist2.push_back(i * 10);   // mylist2: 10 20 30
//
//		it = mylist1.begin();
//		++it;                         // points to 2
//
//		mylist1.splice(it, mylist2); // mylist1: 1 10 20 30 2 3 4
//									  // mylist2 (empty)
//									  // "it" still points to 2 (the 5th element)
//
//		mylist2.splice(mylist2.begin(), mylist1, it);
//		// mylist1: 1 10 20 30 3 4
//		// mylist2: 2
//		// "it" is now invalid.
//		it = mylist1.begin();
//		std::advance(it, 3);           // "it" points now to 30
//
//		mylist1.splice(mylist1.begin(), mylist1, it, mylist1.end());
//		// mylist1: 30 3 4 1 10 20
//
//		std::cout << "mylist1 contains:";
//		for (it = mylist1.begin(); it != mylist1.end(); ++it)
//			std::cout << ' ' << *it;
//		std::cout << '\n';
//
//		std::cout << "mylist2 contains:";
//		for (it = mylist2.begin(); it != mylist2.end(); ++it)
//			std::cout << ' ' << *it;
//		std::cout << '\n';
//
//		return 0;
//	}
	l1.splice(l1.end(), l2);
	for (auto e : l1)   //范围for
	{
		cout << e << " ";
	}
	cout << endl;
	for (auto e : l2)   //范围for   //转接完后l2变为空了
	{
		cout << e << " ";
	}
	cout << endl;
}
void test_list4()
{
	list<int> l1;
	l1.push_back(1);
	l1.push_back(2);
	l1.push_back(3);
	l1.push_back(4);
	l1.push_back(5);
	l1.push_back(6);
	l1.reverse();     //逆置
	for (auto e : l1)   //范围for
	{
		cout << e << " ";
	}
	cout << endl;
}
void test_list5()  //list<int>  调用erase()后迭代器失效问题
{
	list<int> l1;
	l1.push_back(1);
	l1.push_back(7);
	l1.push_back(8);
	l1.push_back(4);
	l1.push_back(5);
	l1.push_back(6);
	l1.push_back(10);
	l1.push_back(6);
	l1.push_back(11);
	l1.push_back(14);
	for (auto e : l1)   //范围for
	{
		cout << e << " ";
	}
	cout << endl;
	list<int>::iterator it = l1.begin();
	while (it != l1.end())
	{
		if (*it % 2 == 0)
		{
			it=l1.erase(it); //list迭代器如果调用了erase()删除了数据，那么它的迭代器也会失效，所以要用it来接受它的下个结点的位置。
		}
		else
		{
			++it;
		}
	}
	for (auto e : l1)   //范围for
	{
		cout << e << " ";
	}
	cout << endl;
}
int main()
{
	//test_list1();
	//test_list2();
	//test_list3();
	//test_list4();
	test_list5();

	return 0;
}
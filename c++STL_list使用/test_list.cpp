//���ԣ�Ϊʲô����list��
//��Ϊ����Ϊ�˲���vectorȱ��˴��ڵġ�
//vector����ȱ�㣺
//ȱ�㣺
//1��ͷ�����м����ɾ������Ч�ʵͣ�ʱ�临�Ӷ�O(N)����ΪҪŲ�����ݡ�
//2���������ݿռ䲻����Ҫ������������Ҫ�����¿ռ䡢�����������ͷžɿռ䣬�Ḷ���޴���ۡ�
//�ŵ㣺
//*֧���±�������ʡ�operator[];��ӵľͺܺõ�֧�����򣬶��ֲ��ң����㷨�ȵȡ�
//list���ŵ㣺
//1��list��ͷ�����м����ɾ������ҪŲ�����ݣ�Ч�ʸߡ�O(1)
//2��list����������������㣬����Ҫ���ݡ�
//ȱ�㣺
//*��֧���������
//�ܽ᣺ʵ��ʹ����vector��list���ศ��ɵ�����������
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
	list<int>::iterator it = l.begin();  //���������ɶ���д
	while (it != l.end())
	{
		cout << *it << " ";
		++it;
	}
	cout << endl;
	l.push_front(0);
	l.push_front(-1);
	for (auto e : l)   //��Χfor
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
	list<int>::const_iterator conit = l.begin();   //ֻ��
	while (conit != l.end())
	{
		cout << *conit << " ";
		++conit;
	}
	cout << endl;
	list<int>::reverse_iterator rit = l.rbegin();   //���������
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
	for (auto e : l)   //��Χfor
	{
		cout << e << " ";
	}
	cout << endl;
	list<int>::iterator pos = find(l.begin(), l.end(), 3);   //insert()�Ĳ���λ��pos��Ҫͨ���㷨����find()���в��ң�Ȼ���ж��Ƿ���ڸ�λ�ã�Ȼ����в���
	if (pos != l.end())                          //list<int>�ĵ�������ָ�룬����vector��ָ�벻һ����
	{
		l.insert(pos, 30);//����Ĳ����list�ĵ�������û��ʧЧ����vector/string�������ڲ���ɾ�����������ʧЧ����Ϊ����ɾ����Ų�����ݺ��漰�������⣩
		l.erase(pos);//��list��erase()���ʧЧ����Ϊ�ýڵ��Ѿ���ɾ����
	}
	for (auto e : l)   //��Χfor
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
	//std::list::splice   //����������ϲ�
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
	for (auto e : l1)   //��Χfor
	{
		cout << e << " ";
	}
	cout << endl;
	for (auto e : l2)   //��Χfor   //ת�����l2��Ϊ����
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
	l1.reverse();     //����
	for (auto e : l1)   //��Χfor
	{
		cout << e << " ";
	}
	cout << endl;
}
void test_list5()  //list<int>  ����erase()�������ʧЧ����
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
	for (auto e : l1)   //��Χfor
	{
		cout << e << " ";
	}
	cout << endl;
	list<int>::iterator it = l1.begin();
	while (it != l1.end())
	{
		if (*it % 2 == 0)
		{
			it=l1.erase(it); //list���������������erase()ɾ�������ݣ���ô���ĵ�����Ҳ��ʧЧ������Ҫ��it�����������¸�����λ�á�
		}
		else
		{
			++it;
		}
	}
	for (auto e : l1)   //��Χfor
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
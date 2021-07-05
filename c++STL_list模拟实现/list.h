#pragma once

namespace my_list
{
	template<class T>
	struct _list_Node
	{
		_list_Node<T>* _next;
		_list_Node<T>* _prev;
		T _data;
		_list_Node(const T& x=T())
			:_data(x)
			,_next(nullptr)
			,_prev(nullptr)
		{}
	};

	//正向  可读、可写迭代器
	//_list_iterator<T, T&, T*> -> iterator
	//_list_iterator<T, const T&, const T*> -> const_iterator
	template<class T,class Ref,class Ptr>
	struct _list_iterator            //迭代器封装     
	{
		typedef _list_Node<T> Node;
		typedef _list_iterator<T, Ref, Ptr> Self;
		Node* _Node;
		_list_iterator (Node* node)  //迭代器构造函数
			:_Node(node)
		{}
		//*it
		Ref operator*()
		{
			return _Node->_data;
		}
		// it->
		Ptr operator->()     // 对于自定义类型的访问  重载operator->()；
		{
			return &_Node->_data;
		}
		//++it;
		Self& operator++()  //前置++
		{
			_Node = _Node->_next;
			return *this;
		}
		//it++;
		Self operator++(int)  //后置++
		{
			Self tmp(*this);
			//_Node = _Node->_next;
			++(*this);
			return tmp;
		}
		//--it;
		Self& operator--()  //前置--
		{
			_Node = _Node->_prev;
			return *this;
		}
		//it--;
		Self operator--(int)  //后置--
		{
			Self tmp(*this);
			//_Node = _Node->_prev;
			--(*this);
			return *this;
		}
		//*it != end()
		bool operator!=(const Self& it)
		{
			return _Node != it._Node;
		}
		//*it==end()
		bool operator==(const Self& it)
		{
			return _Node == it._Node;
		}
	};
	template<class T>
	class list
	{
		typedef _list_Node<T> Node;
	public:
		typedef _list_iterator<T, T&, T*> iterator;   //可读可写迭代器
		typedef _list_iterator<T, const T&, const T*> const_iterator;   //const_iterator  只读迭代器
		void clear()
		{
			iterator it = begin();
			while (it != end())
			{
				erase(it++);
			}
		}
		iterator begin()
		{
			return iterator(_head->_next);
		}
		const_iterator begin()const
		{
			return const_iterator(_head->_next);
		}
		iterator end()
		{
			return iterator(_head);
		}
		const_iterator end()const
		{
			return const_iterator(_head);
		}
		//带头双向循环链表
		list()                              //构造函数
		{
			_head = new Node;
		    _head->_next = _head;
		     _head->_prev = _head;
		}
		list(const list<T>& lt)         //拷贝构造
		{
			//建立新的头
			_head = new Node;
			_head->_next = _head;
			_head->_prev = _head;
			// 赋值它的有效结点的值链接到新的_head；
			//const_iterator it = lt.begin();
			//while (it != lt.end())
			//{
			//	push_back(*it);
			//	++it;
			//}
			for (auto e : lt)
			{
				push_back(e);
			}
		}
		//list<T>& operator=(const list<T>& lt)  //赋值    传统写法
		//{
		//	if (this != &lt)
		//	{
		//		clear();
		//		for (auto e : lt)
		//		{
		//			push_back(e);
		//		}
		//	}
		//	return *this;
		//}
		list<T>& operator=(list<T> lt)  //赋值     现代写法
		{
			swap(lt._head, _head);
			return *this;
		}
		~list()                            // 析构函数
		{
			clear();
			delete _head;
			_head = nullptr;
		}
		void push_back(const T& x)
		{
			//Node* tail = _head->_prev;
			//Node* newnode = new Node(x);
			//
			//tail->_next = newnode;
			//newnode->_prev = tail;
			//newnode->_next = _head;
			//_head->_prev = newnode;
			insert(end(), x);
		}
		void pop_back()
		{
			erase(--end());
		}
		void push_front(const T& x)
		{
			insert(begin(), x);
		}
		void pop_front()
		{
			erase(begin());
		}
		void insert(iterator pos, const T& x)
		{
			// prev  cur  newnode;
			Node* cur= pos._Node;
			Node* prev = cur->_prev;
			Node* newnode = new Node(x);
			prev->_next = newnode;
			newnode->_prev = prev;
			newnode->_next = cur;
			cur->_prev = newnode;
		}
		iterator erase(iterator pos)
		{
			//assert(pos._Node->_next != pos._Node);
			assert(pos != end());
			Node* cur = pos._Node;
			Node* prev = cur->_prev;
			Node* next = cur->_next;
			delete cur;
			prev->_next = next;
			next->_prev = prev;
			return pos++;
		}
	private:
		Node* _head;
	};
	//说明：Node* cur和iterator it 当他们都指向同一个结点是，那么他们在物理内存中都存的是这个结点的地址，物理上可以说是一样的；
	//      但是他们的类型是不一样的，所以他们的意义也就不一样： 比如，*cur是一个指针的解引用，取到的是该节点[(*cur).成员对象/cur->成员对象]；而*it是去调用迭代器的operator*()，
	//      返回值是结点中存的值[*it==cur->_data]。                                                     
	void test_list1()
	{
		list<int> lt;
		lt.push_back(1);
		lt.push_back(2);
		lt.push_back(3);
		lt.push_back(4);
		list<int>::iterator it = lt.begin();
		while (it != lt.end())
		{
			cout << *it << " ";
			++it;
		}
		cout << endl;
	}


	struct Date
	{
		int _year = 0;
		int _month = 1;
		int _day = 1;
	};
	void test_list2()
	{
		list<Date> lt;
		lt.push_back(Date());
		lt.push_back(Date());

		list<Date>::iterator it = lt.begin();
		while (it != lt.end())
		{
			//cout << *it << " ";  //对于自定义类型Date ,Date如果本身没有重载operator<<()输出的话， 这里的cout << *it也是不能输出的，但是it被封装成了一个类似指针的功能，
			                   //我们可以实现一个迭代器的operator->()来实现自定义类型的成员访问。
			cout << it->_year << "-" << it->_month << "-" << it->_day << endl;//这里的it->_year的实际过程应该是(it->)->_year,括号里的it->是调用了重载函数it.operator->(),
			                  //然后该函数的返回类型是T*(即Date*),然后对象指针（T*）用访问符->去访问该对象自己的成员。但是为了可读性，编译器进行了特殊处理。
			//cout << (*it)._year << "-" << (*it)._month << "-" << (*it)._day << endl;//当然也可以用(*it).对象成员  去访问。
			++it;
		}
		cout << endl;
	}
	void list_Print(const list<int>& lt)
	{
		list<int>::const_iterator it = lt.begin();
		while (it != lt.end())
		{
			cout << *it << " ";
			++it;
		}
		cout << endl;
	}
	void test_list3()
	{
		list<int> lt;
		lt.push_back(1);
		lt.push_back(2);
		lt.push_back(3);
		lt.push_back(4);
		list_Print(lt);
	}
	void test_list4()
	{
		list<int> lt;
		lt.push_back(1);
		lt.push_back(2);
		lt.push_back(3);
		lt.push_back(4);
		list_Print(lt);
		lt.insert(lt.begin(), 0);
		lt.insert(lt.begin(), -1);
		lt.insert(lt.begin(), -2);
		list_Print(lt);
	}
	void test_list5()
	{
		list<int> lt;
		lt.push_back(1);
		lt.push_back(2);
		lt.push_back(3);
		lt.push_back(4);
		lt.push_back(5);
		lt.push_back(6);
		lt.insert(lt.begin(), 0);
		lt.insert(lt.begin(), -1);
		lt.insert(lt.begin(), -2);
		list_Print(lt);
		lt.pop_back();
		lt.pop_back();
		lt.pop_front();
		lt.pop_front();
		list_Print(lt);
	}
	void test_list6()
	{
		list<int> lt;
		lt.push_back(1);
		lt.push_back(2);
		lt.push_back(3);
		lt.push_back(4);
		lt.push_back(5);
		lt.push_back(6);
		list_Print(lt);
		list<int> lt1(lt);
		list_Print(lt1);
	}
	void test_list7()
	{
		list<int> lt;
		lt.push_back(1);
		lt.push_back(2);
		lt.push_back(3);
		lt.push_back(4);
		lt.push_back(5);
		lt.push_back(6);
		list_Print(lt);
		list<int> lt1;
		lt1.push_back(10);
		lt1.push_back(20);
		lt1.push_back(30);
		lt1.push_back(40);
		lt1.push_back(50);
		lt1.push_back(60);
		lt1.push_back(70);
		lt1.push_back(80);
		lt1.push_back(90);
		lt1.push_back(100);
		list_Print(lt1);
		lt1 = lt;
		list_Print(lt1);
	}
}

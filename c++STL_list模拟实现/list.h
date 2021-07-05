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

	//����  �ɶ�����д������
	//_list_iterator<T, T&, T*> -> iterator
	//_list_iterator<T, const T&, const T*> -> const_iterator
	template<class T,class Ref,class Ptr>
	struct _list_iterator            //��������װ     
	{
		typedef _list_Node<T> Node;
		typedef _list_iterator<T, Ref, Ptr> Self;
		Node* _Node;
		_list_iterator (Node* node)  //���������캯��
			:_Node(node)
		{}
		//*it
		Ref operator*()
		{
			return _Node->_data;
		}
		// it->
		Ptr operator->()     // �����Զ������͵ķ���  ����operator->()��
		{
			return &_Node->_data;
		}
		//++it;
		Self& operator++()  //ǰ��++
		{
			_Node = _Node->_next;
			return *this;
		}
		//it++;
		Self operator++(int)  //����++
		{
			Self tmp(*this);
			//_Node = _Node->_next;
			++(*this);
			return tmp;
		}
		//--it;
		Self& operator--()  //ǰ��--
		{
			_Node = _Node->_prev;
			return *this;
		}
		//it--;
		Self operator--(int)  //����--
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
		typedef _list_iterator<T, T&, T*> iterator;   //�ɶ���д������
		typedef _list_iterator<T, const T&, const T*> const_iterator;   //const_iterator  ֻ��������
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
		//��ͷ˫��ѭ������
		list()                              //���캯��
		{
			_head = new Node;
		    _head->_next = _head;
		     _head->_prev = _head;
		}
		list(const list<T>& lt)         //��������
		{
			//�����µ�ͷ
			_head = new Node;
			_head->_next = _head;
			_head->_prev = _head;
			// ��ֵ������Ч����ֵ���ӵ��µ�_head��
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
		//list<T>& operator=(const list<T>& lt)  //��ֵ    ��ͳд��
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
		list<T>& operator=(list<T> lt)  //��ֵ     �ִ�д��
		{
			swap(lt._head, _head);
			return *this;
		}
		~list()                            // ��������
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
	//˵����Node* cur��iterator it �����Ƕ�ָ��ͬһ������ǣ���ô�����������ڴ��ж������������ĵ�ַ�������Ͽ���˵��һ���ģ�
	//      �������ǵ������ǲ�һ���ģ��������ǵ�����Ҳ�Ͳ�һ���� ���磬*cur��һ��ָ��Ľ����ã�ȡ�����Ǹýڵ�[(*cur).��Ա����/cur->��Ա����]����*it��ȥ���õ�������operator*()��
	//      ����ֵ�ǽ���д��ֵ[*it==cur->_data]��                                                     
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
			//cout << *it << " ";  //�����Զ�������Date ,Date�������û������operator<<()����Ļ��� �����cout << *itҲ�ǲ�������ģ�����it����װ����һ������ָ��Ĺ��ܣ�
			                   //���ǿ���ʵ��һ����������operator->()��ʵ���Զ������͵ĳ�Ա���ʡ�
			cout << it->_year << "-" << it->_month << "-" << it->_day << endl;//�����it->_year��ʵ�ʹ���Ӧ����(it->)->_year,�������it->�ǵ��������غ���it.operator->(),
			                  //Ȼ��ú����ķ���������T*(��Date*),Ȼ�����ָ�루T*���÷��ʷ�->ȥ���ʸö����Լ��ĳ�Ա������Ϊ�˿ɶ��ԣ����������������⴦��
			//cout << (*it)._year << "-" << (*it)._month << "-" << (*it)._day << endl;//��ȻҲ������(*it).�����Ա  ȥ���ʡ�
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

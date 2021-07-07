#pragma once
#include<vector>
#include<list>
namespace my_stack_queue
{
	template<class T,class Container>
	class stack
	{
	public:
		void push(const T& x)
		{
			_con.push_back(x);
		}
		void pop()
		{
			_con.pop_back();
		}
		size_t Size()
		{
			return _con.size();
		}
		bool empty()
		{
			return _con.empty();
		}
		T& top()
		{
			return _con.back();
		}
	private:
		Container _con;
	};
	void test_stack()
	{
		stack<int, vector<int>> st;
		st.push(1);
		st.push(2);
		st.push(3);
		st.push(4);
		while (!st.empty())
		{
			cout << st.top() << " ";
			st.pop();
		}
		cout << endl;
		stack<int, list<int>> st1;
		st1.push(5);
		st1.push(6);
		st1.push(7);
		st1.push(8);
		while (!st1.empty())
		{
			cout << st1.top() << " ";
			st1.pop();
		}
		cout << endl;
	}
	template<class T, class Container>
	class queue
	{
	public:
		void push(const T& x)
		{
			_con.push_back(x);
		}
		void pop()
		{
			_con.pop_front();
		}
		size_t Size()
		{
			return _con.size();
		}
		T& front()
		{
			return _con.front();
		}
		T& back()
		{
			return _con.back();
		}
		bool empty()
		{
			return _con.empty();
		}
	private:
		Container _con;
	};
	void test_queue()
	{
		queue<int, list<int>> q;
		q.push(1);
		q.push(2);
		q.push(3);
		q.push(4);
		while (!q.empty())
		{
			cout << q.front() << " ";
			q.pop();
		}
		cout << endl;
		//queue<int, vector<int>> q1;   //不能用vector。vector没有提供pop_front()接口
		//q1.push(5);
		//q1.push(6);
		//q1.push(7);
		//q1.push(8);
		//while (!q.empty())
		//{
		//	cout << q1.front() << " ";
		//	q1.pop();
		//}
		//cout << endl;
	}
}

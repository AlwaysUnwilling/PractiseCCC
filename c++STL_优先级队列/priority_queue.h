#pragma once
#include<vector>




namespace my_priority_queue
{
	// 仿函数 :它的对象可以像函数一样去使用
	template<class T>
	struct less
	{
		bool operator()(const T& x1, const T& x2)
		{
			return x1 < x2;
		}
	};
	template<class T>
	struct greater
	{
		bool operator()(const T& x1, const T& x2)  //重载operator()
		{
			return x1 > x2;
		}
	};
	//模拟实现优先级队列
	template<class T, class Container = vector<T>,class Compare = less<T>>
	class priority_queue
	{
	public:
		void AdjustUP(int child)
		{
			int parent = (child - 1) / 2;
			Compare com;
			while (child > 0)
			{
				//if (_con[child] > _con[parent])
				if (com(_con[parent], _con[child]))
				{
					swap(_con[child], _con[parent]);
					child = parent;
					parent = (child - 1) / 2;
				}
				else
					break;
			}
		}
		void AdjustDown(int parent)
		{
			int child = 2 * parent + 1;
			Compare com;
			while (child < _con.size())
			{
				//if (child+1<_con.size() && _con[child + 1] > _con[child])
				if (child+1<_con.size() && com(_con[child], _con[child + 1]))
				{
					++child;
				}
				//if (_con[child] > _con[parent])
				if (com(_con[parent], _con[child]))
				{
					swap(_con[parent], _con[child]);
					parent = child;
					child = 2 * parent + 1;
				}
				else
					break;
			}
		}
		void push(const T& x)
		{
			_con.push_back(x);
			//O(logN)
			AdjustUP(_con.size()-1);//默认是大堆
		}
		void pop()
		{
			swap(_con[0], _con[_con.size() - 1]);
			_con.pop_back();
			//O(logN)
			AdjustDown(0);
		}
		T& top()
		{
			return _con[0];
		}
		size_t size()
		{
			return _con.size();
		}
		bool empty()
		{
			return _con.empty();
		}
	private:
		Container _con;
	};

	void test_priority_queue()
	{
		priority_queue<int> pq;
		pq.push(4);
		pq.push(2);
		pq.push(3);
		pq.push(1);
		pq.push(7);
		while (!pq.empty())
		{
			cout << pq.top() << " ";
			pq.pop();
		}
		cout << endl;
		priority_queue<int,vector<int>,greater<int>> pq1;
		pq1.push(4);
		pq1.push(2);
		pq1.push(3);
		pq1.push(1);
		pq1.push(7);
		while (!pq1.empty())
		{
			cout << pq1.top() << " ";
			pq1.pop();
		}
		cout << endl;
	}
}


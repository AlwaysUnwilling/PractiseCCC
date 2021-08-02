#pragma once
#include"RBTree.h"

namespace MySet
{
	template<class K>
	class set
	{
		struct SetKOfK
		{
			const K& operator()(const K& key)
			{
				return key;
			}
		};
	public:
		typedef typename RBTree<K, K, SetKOfK>::iterator iterator;//typename 修饰RBTree<K, K, SetKOfK>::iterator 表示这是类型声明
		iterator begin()
		{
			return _t.begin();
		}
		iterator end()
		{
			return _t.end();
		}
		pair<iterator, bool> Insert(const K& key)
		{
			return _t.Insert(key);
		}
	private:
		RBTree<K, K, SetKOfK> _t;
	};
	void Test_Set()
	{
		set<int> s;
		s.Insert(3);
		s.Insert(4);
		s.Insert(1);
		s.Insert(2);
		s.Insert(5);
		set<int>::iterator it = s.begin();
		while (it != s.end())
		{
			cout << *it << " ";
			++it;
		}
		cout << endl;
		for (auto key : s)
		{
			cout << key << " ";
		}
		cout << endl;
	}
}

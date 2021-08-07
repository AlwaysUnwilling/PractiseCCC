#pragma once
#include"HashTable.h"
using namespace my_OPOEN_Hash;

namespace MyUnorderedSet
{
	template<class K,class Hash=_Hash<K>>
	class unordered_set
	{
		struct SetKOfT
		{
			const K& operator()(const K& key)
			{
				return key;
			}
		};
	public:
		typedef typename HashTable<K, K, SetKOfT, Hash>::iterator iterator;
		iterator begin()
		{
			return _ht.begin();
		}
		iterator end()
		{
			return _ht.end();
		}
		pair<iterator, bool> insert(const K& k)
		{
			return _ht.Insert(k);
		}

	private:
		HashTable<K, K, SetKOfT,Hash> _ht;
	};
	void Test_Unordered_Set()
	{
		unordered_set<int> s;
		s.insert(1);
		s.insert(5);
		s.insert(4);
		s.insert(2);
		unordered_set<int>::iterator it = s.begin();
		while (it != s.end())
		{
			cout << *it << " ";
			++it;
		}
		cout << endl;
	}
}

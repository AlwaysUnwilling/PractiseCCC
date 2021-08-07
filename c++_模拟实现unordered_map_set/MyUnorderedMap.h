#pragma once
#include"HashTable.h"
using namespace my_OPOEN_Hash;

namespace MyUnorderedMap
{
	template<class K, class V,class Hash=_Hash<K>>
	class unordered_map
	{
		struct MapKOfT
		{
			const K& operator()(const pair<K, V>& kv)
			{
				return kv.first;
			}
		};
	public:
		typedef typename HashTable<K, pair<K, V>, MapKOfT, Hash>::iterator iterator;
		iterator begin()
		{
			return _ht.begin();
		}
		iterator end()
		{
			return _ht.end();
		}
		pair<iterator,bool> insert(const pair<K, V>& kv)
		{
			return _ht.Insert(kv);
		}
		V& operator[](const K& key)
		{		
			pair<iterator,bool> ret = _ht.Insert(make_pair(key, V()));
			return ret.first->second;
		}
	private:
		HashTable<K, pair<K, V>, MapKOfT,Hash> _ht; 
	};
	void Test_Unordered_Map()
	{
		unordered_map<int, int> m;
		m.insert(make_pair(1, 1));
		m.insert(make_pair(2, 2));
		m.insert(make_pair(3, 3));
		m.insert(make_pair(4, 4));
		unordered_map<int, int>::iterator it = m.begin();
		while (it != m.end())
		{
			cout << it->first << ":" << it->second << endl;
			++it;
		}
		cout << endl;
		unordered_map<string, string> dict;
		dict.insert(make_pair("sort", "排序"));
		dict.insert(make_pair("string", "字符串"));
		dict.insert(make_pair("hello", "你好"));
		dict.insert(make_pair("world", "世界"));
		dict["int"] = "整型";
		unordered_map<string, string>::iterator dit = dict.begin();
		while (dit != dict.end())
		{
			cout << dit->first << ":" << dit->second << endl;
			++dit;
		}
		cout << endl;
	}
}

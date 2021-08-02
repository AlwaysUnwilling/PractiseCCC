#pragma once
#include"RBTree.h"
namespace MyMap
{
	template<class K,class V>
	class map
	{
		struct MapKeyOfT
		{
			const K& operator()(const pair<K, V>& kv)
			{
				return kv.first;
			}
		};
	public:
		typedef typename RBTree<K, pair<K, V>, MapKeyOfT>::iterator iterator;
		iterator begin()
		{
	        return _t.begin();
		}
		iterator end()
		{
			return _t.end();
		}
		pair<iterator,bool> Insert(const pair<K, V>& kv)
		{
			return _t.Insert(kv);
		}
		V& operator[](const K& key)
		{
			pair<iterator,bool> ret= _t.Insert(make_pair(key,V()));
			return ret.first->second;
		}
	private:
		RBTree<K, pair<K, V>, MapKeyOfT> _t;
	};
	void Test_Map()
	{
		map<int, int> m;
		m.Insert(make_pair(1, 1));
		m.Insert(make_pair(3, 3));
		m.Insert(make_pair(10, 10));
		m.Insert(make_pair(5, 5));
		m.Insert(make_pair(6, 6));
		map<int, int>::iterator it = m.begin();
		while (it != m.end())
		{
			cout << it->first << ":" << it->second << endl;
			++it;
		}
		cout << endl;
		for (auto kv : m)
		{
			cout << kv.first << ":" << kv.second << endl;
		}

		string strs[] = { "����" ,"���" ,"ƻ��" ,"����" ,"ƻ��" ,"�㽶" ,"�㽶" ,"�㽶" ,"����" ,"ӣ��" ,"����" ,"����" };
		map<string, int> countMap;
		for (auto& e : strs)
		{
		 	   //1.���ˮ������map�У���operator[]�����pair<e,0>,����ӳ����󣨴����������ý������޸�(++);ע�������0��int()��ȱʡֵ��
		 	   //2.���ˮ����map�У���operator[]����ˮ����Ӧ��ӳ����󣨴����������ã����������޸�(++);
			countMap[e]++;
		}
		for (auto& e : countMap)
		{
			cout << e.first << ":" << e.second << endl;
		}
	}
}

#pragma once
#include<vector>
#include<iostream>

using namespace std;

template<class K>
struct SetKeyOfT
{
	const K& operator()(const K& key)
	{
		return key;
	}
};

namespace my_CLOSE_Hash
{
	//unordered_set<K>  ->HashTable<K,K>
    //unordered_map<K,V>  ->HashTable<K,pair<K,V>>
	enum State
	{
		EMPTY,
		EXIST,
		DELETE
	};
	template<class T>
	struct HashData
	{
		T _data;
		State _state;
	};
	template<class K, class T, class KeyOfT>
	class HashTable
	{
	public:
		bool Insert(const T& d)
		{
			//��������=��������/��Ĵ�С==��������ϣ�����ĳ̶�
			//��Խ�ӽ�������������Խ���׳�ͻ����ͻԽ�࣬Ч��Խ��
			//��ϣ���������˲����ݣ����Ŷ��Ʒ��У�һ�㸺�����ӵ���0.7���ҾͿ�ʼ����
			//��������ԽС����ͻ����Խ�ͣ�����Ч��Խ�ߣ����Ǹ�������ԽС���˷ѵĿռ�Խ��
			//���Ը�������һ��ȡһ������ֵ0.7
			if (_tables.size() == 0 || _num * 10 / _tables.size() >= 7)
			{
				// 1.��2����С���±�
				// 2.�����ɱ�����ݣ����¼������±���λ��
				// 3.�ͷžɱ�
				//vector<HashData> newtables;
				//size_t newsize = _tables.size() == 0 ? 10 : _tables.size() * 2;
				//newtables.resize(newsize);
				//for (size_t i = 0; i < _tables.size(); ++i)
				//{
				//	if (_tables[i]._state == EXITS)
				//	{
				//		// �������±��е�λ�ò������ͻ
				//		size_t index = koft(_tables[i]._data) % newtables.size();
				//		while (newtables[index]._state == EXITS)
				//		{
				//			++index;
				//			if (index == _tables.size())
				//			{
				//				index = 0;
				//			}
				//		}

				//		newtables[index] = _tables[i];
				//	}
				//}
				//_tables.swap(newtables);

				HashTable<K, T, KeyOfT> newht;
				size_t newsize = _tables.size() == 0 ? 10 : _tables.size() * 2;
				newht._tables.resize(newsize);
				for (size_t i = 0; i < _tables.size(); ++i)
				{
					if (_tables[i]._state == EXITS)
					{
						newht.Insert(_tables[i]._data);
					}
				}

				_tables.swap(newht._tables);
			}
			// ����̽��
				//// ����d�е�key�ڱ���ӳ���λ��
				//size_t  index = koft(d) % _tables.size();
				//while (_tables[index]._state == EXITS)
				//{
				//	if (koft(_tables[index]._data) == koft(d))
				//	{
				//		return false;
				//	}

				//	++index;
				//	if (index == _tables.size())
				//	{
				//		index = 0;
				//	}
				//}

				//_tables[index]._data = d;
				//_tables[index]._state = EXITS;
				//_num++;

				// ����̽��
				// ����d�е�key�ڱ���ӳ���λ��
			size_t  start = koft(d) % _tables.size();
			size_t index = start;
			int i = 1;
			KeyOfT koft;
			//����d��key�ڱ���ӳ���λ��
			size_t index = koft(d) % _tables.size();
			while (_tables[index]._state == EXIST)
			{
				//if (koft(_tables[index]._data) ==koft(d))
				//{
				//	return false;
				//}
				//++index;
				//if (index == _tables.size())
				//{
				//	index = 0;
				//}
				if (koft(_tables[index]._data) == koft(d))
				{
					return false;
				}

				index = start + i * i;
				++i;
				index %= _tables.size();
			}

			_tables[index]._data == d;
			_tables[index]._state = EXIST;
			_num++;
			return true;
		}
		HashData* Find(const K& key)
		{
			KeyOfT koft;
			//����d��key�ڱ���ӳ���λ��
			size_t index = koft(d) % _tables.size();
			while (_tables[index]._state != EMPTY)
			{
				if (koft(_tables[index]._data) == key)
				{
					if (_tables[index]._state == EXIST)
					{
						return &_tables[index];
					}
					else if (_tables[index]._state == DELETE)
					{
						return nullptr;
					}
				}
				++index;
				if (index == _tables.size())
				{
					index = 0;
				}
			}
			return nullptr;
		}
		bool Erase(const K& key)
		{
			HashData* ret = Find(key);
			if (ret)
			{
				ret->_state = DELETE;
				--_num;
				return true;
			}
			return false;
		}
	private:
		vector<HashData> _tables;
		size_t _num = 0;  //��Ч���ݵĸ���
	};
	void TestHashTable()
	{
		HashTable<int, int, SetKeyOfT<int>> ht;
		ht.Insert(4);
		ht.Insert(14);
		ht.Insert(24);
		ht.Insert(5);
		ht.Insert(15);
		ht.Insert(25);
		ht.Insert(6);
		ht.Insert(16);
	}
}

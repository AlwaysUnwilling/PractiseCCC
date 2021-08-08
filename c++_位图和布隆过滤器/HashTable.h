#pragma once
#include<vector>

namespace my_OPOEN_Hash
{
	template<class K>
	struct SetKOfT
	{
		const K& operator()(const K& key)
		{
			return key;
		}
	};
	template<class T>
	struct HashNode
	{
		HashNode(const T& data)
			:_data(data)
			,_next(nullptr)
		{}
		T _data;
		HashNode* _next;
	};
	//默认仿函数直接返回key，因为有些类型的key直接就可以取模
	template<class K>
	struct _Hash
	{
		const K& operator()(const K& key)
		{
			return key;
		}
	};
	//特化将string作为K的场景
	template<>
	struct _Hash<string>
	{
		size_t operator()(const string& key)
		{
			size_t hash = 0;
			for (size_t i = 0; i < key.size(); ++i)
			{
				//BKDR Hash
				hash *= 131;
				hash += key[i];
			}
			return hash;
		}
	};
	//将string转成可以取模的仿函数
	//struct _HashString
	//{
	//	size_t operator()(const string& key)
	//	{
	//		size_t hash = 0;
	//		for (size_t i = 0; i < key.size(); ++i)
	//		{
	//			//BKDR Hash
	//			hash *= 131;
	//			hash += key[i];
	//		}
	//		return hash;
	//	}
	//};
	
	//前置声明
	template<class K, class T, class KOfT, class Hash> //仿函数Hash将对应的key转成可以取模的整型
	class HashTable;
	//迭代器
	template<class K,class T,class KOfT,class Hash>
	struct __HashTableIterator
	{
		typedef __HashTableIterator<K, T, KOfT,Hash> Self;
		typedef HashNode<T> Node;
		typedef HashTable<K, T, KOfT, Hash> HT;
		HT* _pht;
		Node* _node;
		__HashTableIterator(Node* node,HT* pht)
			:_node(node)
			,_pht(pht)
		{}
		T& operator*()
		{
			return _node->_data;
		}
		T* operator->()
		{
			return &_node->_data;
		}
		Self& operator++()
		{
			if (_node->_next)
			{
				_node = _node->_next;
			}
			else
			{
				//如果一个桶走完了，找到下一个桶继续遍历
				KOfT koft;
				size_t i = _pht->HashFunc(koft(_node->_data)) % _pht->_tables.size();
				++i;
				for (; i < _pht->_tables.size(); ++i)
				{
					Node* cur = _pht->_tables[i];
					if (cur)
					{
						_node = cur;
						return *this;
					}
				}
				_node = nullptr;
			}
			return *this;
		}
		bool operator!=(const Self& s)
		{
			return _node != s._node;
		}
		bool operator==(const Self& s)
		{
			return _node == s._node;
		}
	};
	template<class K,class T,class KOfT,class Hash=_Hash<K>> //仿函数Hash将对应的key转成可以取模的整型
	class HashTable
	{
		typedef HashNode<T> Node;
	public:
		friend struct __HashTableIterator<K, T, KOfT, Hash>;//_tables是HashTable的私有，别的类需要访问可以设置友元
		typedef __HashTableIterator<K, T, KOfT,Hash> iterator;
		iterator begin()
		{
			for (size_t i = 0; i < _tables.size(); ++i)
			{
				if (_tables[i])
				{
					return iterator(_tables[i],this);
				}
			}
			return end();
		}
		iterator end()
		{
			return iterator(nullptr,this);
		}
		~HashTable()
		{
			Clear();
		}
		void Clear()
		{
			for (size_t i = 0; i < _tables.size(); ++i)
			{
				Node* cur = _tables[i];
				while (cur)
				{
					Node* next = cur->_next;
					delete cur;
					cur = next;
				}
				_tables[i] = nullptr;
			}
		}
		pair<iterator,bool> Insert(const T& data)
		{
			KOfT koft;
			// 如果负载因子等于1，则增容，避免大量的哈希冲突
			if (_tables.size() == _num)
			{
				// 1.开2倍大小的新表（不一定是2倍）
				// 2.遍历旧表的数据，重新计算在新表中位置
				// 3.释放旧表
				vector<Node*> newtables;
				size_t newsize = _tables.size() == 0 ? 10 : _tables.size() * 2;
				newtables.resize(newsize);//开空间并初始化为nullptr
				for (auto& e : _tables)
				{
					// 将旧表中的节点取下来重新计算在新表中的位置，并插入进去
					Node* cur = e;
					while (cur)
					{
						Node* next = cur->_next;
						size_t index = HashFunc(koft(cur->_data)) % newtables.size();
						cur->_next = newtables[index];
						newtables[index] = cur;
						cur = next;
					}
					e = nullptr;
				}
				_tables.swap(newtables);
			}
			size_t index = HashFunc(koft(data)) % _tables.size();
			//判断这个值在表中在不在
			Node* cur = _tables[index];
			while (cur)
			{
				if (koft(cur->_data) == koft(data))
				{
					return make_pair(iterator(cur,this),false);
				}
				else
				{
					cur = cur->_next;
				}
			}
			Node* newnode = new Node(data);
			newnode->_next=_tables[index];
			_tables[index]=newnode;
			++_num;
			return make_pair(iterator(newnode, this), true);
		}
		size_t HashFunc(const K& key)
		{
			Hash hash;
			return hash(key);
		}
		Node* Find(const K& key)
		{
			KOfT koft;
			size_t index = HashFunc(key) % _tables.size();
			Node* cur = _tables[index];
			while (cur)
			{
				if (koft(cur->_data) == key)
				{
					return cur;
				}
				else
				{
					cur = cur->_next;
				}
			}
			return nullptr;
		}
		bool Erase(const K& key)
		{
			KOfT koft;
			size_t index = HashFunc(key) % _tables.size();
			Node* prev = nullptr;
			Node* cur = _tables[index];
			while (cur)
			{
				if (koft(cur->_data) == key)
				{
					//找到，并删除
					if (prev)
					{
						prev->_next = cur->_next;
					}
					else
					{
						_tables[index] = cur->_next;
					}
					delete cur;
					return true;
				}
				else
				{
					prev = cur;
					cur = cur->_next;
				}
			}
			return false;
		}
	private:
		vector<Node*> _tables;
		size_t _num = 0;//记录表中数据个数
	};
	void TestHashTable()
	{
		HashTable<int, int,SetKOfT<int>> ht;
		ht.Insert(4);
		ht.Insert(14);
		ht.Insert(24);
		ht.Insert(5);
		ht.Insert(15);
		ht.Insert(25);
		ht.Insert(6);
		ht.Insert(16);
		ht.Insert(26);
		ht.Insert(36);
		ht.Insert(33);
	}
	void TestHashTable1()
	{
		//HashTable<string, string, SetKOfT<string>, _HashString> ht;
		HashTable<string, string, SetKOfT<string>> ht;  //特化string作为K的场景
		ht.Insert("sort");
		ht.Insert("string");
		ht.Insert("left");
		cout << ht.HashFunc("abcd") << endl;
		cout << ht.HashFunc("aadd") << endl;
	}
}

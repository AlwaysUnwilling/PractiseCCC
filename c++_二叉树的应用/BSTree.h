#pragma once
#include<iostream>
#include<string>
using namespace std;

//搜索二叉树的应用：1、K的模型---判断K在不在？；2、K / Value的模型---通过key找对应的value;
//K/Value的实现
template<class K,class V>
struct BSTreeNode
{
	BSTreeNode<K, V>* _left;
	BSTreeNode<K, V>* _right;
	K _key;
	V _value;
	BSTreeNode(const K& key,const V& value)
		:_left(nullptr)
		,_right(nullptr)
		,_key(key)
		,_value(value)
	{}
};

template<class K,class V>
class BSTree
{
	typedef BSTreeNode<K, V> Node;
public:
	bool Insert(const K& key, const V& value)
	{
		if (_root == nullptr)
		{
			_root = new Node(key,value);
			return true;
		}
		Node* cur = _root;
		Node* parent = nullptr;
		while (cur)
		{
			if (cur->_key < key)
			{
				parent = cur;
				cur = cur->_right;
			}
			else if (cur->_key > key)
			{
				parent = cur;
				cur = cur->_left;
			}
			else
			{
				return false;
			}
		}
		cur = new Node(key, value);
		if (key > parent->_key)
		{
			parent->_right = cur;
		}
		else
		{
			parent->_left = cur;
		}
		return true;
	}
	Node* Find(const K& key)
	{
		Node* cur = _root;
		while (cur)
		{
			if (key > cur->_key)
			{
				cur = cur->_right;
			}
			else if (key < cur->_key)
			{
				cur = cur->_left;
			}
			else
			{
				return cur;
			}
		}
		return nullptr;
	}
	bool Erase(const K& key)
	{
		Node* cur = _root;
		Node* parent = nullptr;
		while (cur)
		{
			if (key > cur->_key)
			{
				parent = cur;
				cur = cur->_right;
			}
			else if (key < cur->_key)
			{
				parent = cur;
				cur = cur->_left;
			}
			else
			{
				if (cur->_left==nullptr)
				{
					if (cur == _root)
					{
						_root = cur->_right;
					}
					else
					{
						if (parent->_left == cur)
						{
							parent->_left = cur->_right;
						}
						else
						{
							parent->_right = cur->_right;
						}
					}
					delete cur;
				}
				else if (cur->_right == nullptr)
				{
					if (cur == _root)
					{
						_root = cur->_left;
					}
					else
					{
						if (parent->_left == cur)
						{
							parent->_left = cur->_left;
						}
						else
						{
							parent->_right = cur->_left;
						}
						delete cur;
					}
				}
				else
				{
					Node* leftMax = cur->_left;
					Node* leftMaxParent = cur;
					while (leftMax->_right)
					{
						leftMaxParent = leftMax;
						leftMax = leftMax->_right;
					}
					cur->_key = leftMax->_key;
					if (leftMaxParent->_left == leftMax)
					{
						leftMaxParent->_left = leftMax->_left;
					}
					else
					{
						leftMaxParent->_right = leftMax->_left;
					}
					delete leftMax;
				}
				return true;
			}
		}
		return false;
	}
	void _InOrder(Node* root)
	{
		if (root == nullptr)
		{
			return;
		}
		_InOrder(root->_left);
		cout << root->_key << " " << root->_value << endl;;
		_InOrder(root->_right);
	}
	void InOrder()
	{
		_InOrder(_root);
		cout << endl;
	}
private:
	Node* _root=nullptr;
};

void TestBSTree1()
{
	BSTree<int,int> t;
	int a[] = { 5,3,4,1,7,8,2,6,0,9 };
	for (auto e : a)
	{
		t.Insert(e,0);
	}
	t.InOrder();
	t.Erase(7);
	t.InOrder();
	t.Erase(5);
	t.InOrder();
}
void TestBSTree2()   //中英文翻译
{
	BSTree<string, string> dict;
	dict.Insert("sort", "排序");
	dict.Insert("string", "字符串");
	dict.Insert("hello", "你好");
	dict.Insert("tree", "树");
	dict.Insert("insert", "插入");

	string str;
	while (cin >> str)
	{
		BSTreeNode<string, string>* ret = dict.Find(str);
		if (ret)
		{
			cout << ret->_value<<endl;
		}
		else
		{
			cout << "无此单词" << endl;
		}
	}
}
//假设有一堆水果，如何统计各种水果出现的次数？
void TestBSTree3()
{
	string strs[] = { "西瓜","苹果","西瓜","苹果","西瓜","香蕉","西瓜","樱桃","西瓜","西瓜" };
	BSTree<string, int> countTree;
	for (auto str : strs)
	{
		BSTreeNode<string, int>* ret = countTree.Find(str);
		if (ret == nullptr)  //如果要找的水果在countTree中没有，就插入进去，并把它的_value改为1；
		{
			countTree.Insert(str, 1);
		}
		else   //如果要找的水果有，那么久让它的_value++；
		{
			ret->_value++;
		}
	}
	countTree.InOrder();
}
//小结:使用搜索二叉树进行统计次数一般情况下它的效率很高，但是如果插入的数据是有序的，或者接近有序的，那么搜索树的效率就
//     完全没办法保障了O(N),这也是搜索树的局限性。 所以搜索树的效率最坏的情况下是O(N)。
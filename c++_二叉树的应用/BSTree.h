#pragma once
#include<iostream>
#include<string>
using namespace std;

//������������Ӧ�ã�1��K��ģ��---�ж�K�ڲ��ڣ���2��K / Value��ģ��---ͨ��key�Ҷ�Ӧ��value;
//K/Value��ʵ��
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
void TestBSTree2()   //��Ӣ�ķ���
{
	BSTree<string, string> dict;
	dict.Insert("sort", "����");
	dict.Insert("string", "�ַ���");
	dict.Insert("hello", "���");
	dict.Insert("tree", "��");
	dict.Insert("insert", "����");

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
			cout << "�޴˵���" << endl;
		}
	}
}
//������һ��ˮ�������ͳ�Ƹ���ˮ�����ֵĴ�����
void TestBSTree3()
{
	string strs[] = { "����","ƻ��","����","ƻ��","����","�㽶","����","ӣ��","����","����" };
	BSTree<string, int> countTree;
	for (auto str : strs)
	{
		BSTreeNode<string, int>* ret = countTree.Find(str);
		if (ret == nullptr)  //���Ҫ�ҵ�ˮ����countTree��û�У��Ͳ����ȥ����������_value��Ϊ1��
		{
			countTree.Insert(str, 1);
		}
		else   //���Ҫ�ҵ�ˮ���У���ô��������_value++��
		{
			ret->_value++;
		}
	}
	countTree.InOrder();
}
//С��:ʹ����������������ͳ�ƴ���һ�����������Ч�ʺܸߣ�����������������������ģ����߽ӽ�����ģ���ô��������Ч�ʾ�
//     ��ȫû�취������O(N),��Ҳ���������ľ����ԡ� ������������Ч������������O(N)��
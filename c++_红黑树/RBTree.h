#pragma once
#include<iostream>

using namespace std;
enum Colour
{
	BLACK,
	RED,
};
template<class K, class V>
struct RBTreeNode
{
	RBTreeNode<K, V>* _left;
	RBTreeNode<K, V>* _right;
	RBTreeNode<K, V>* _parent;
	pair<K, V> _kv;
	Colour _col;
	RBTreeNode(const pair<K,V>& kv)
		:_left(nullptr)
		,_right(nullptr)
		,_parent(nullptr)
		,_kv(kv)
		,_col(RED)
	{}
};
template<class K,class V>
class RBTree
{
	typedef RBTreeNode<K, V> Node;
public:
	bool Insert(const pair<K, V>& kv)
	{
		//1.���������Ĺ������
		if (_root == nullptr)
		{
			_root = new Node(kv);
			_root->_col = BLACK;
			return true;
		}
		Node* cur = _root;
		Node* parent = nullptr;
		while (cur)
		{
			if (cur->_kv.first > kv.first)
			{
				parent = cur;
				cur = cur->_left;
			}
			else if (cur->_kv.first < kv.first)
			{
				parent = cur;
				cur = cur->_right;
			}
			else
			{
				return false;
			}
		}
		cur = new Node(kv);
		if (kv.first > parent->_kv.first)
		{
			parent->_right=cur;
			cur->_parent = parent;
		}
		else
		{
			parent->_left=cur;
			cur->_parent = parent;
		}
		
		//����������ɫ
		cur->_col = RED;
		//2.���¸��ڵ����ɫʹ��������������
		while (parent && parent->_col == RED)
		{
			//���ɫ�������ؼ�������
			Node* grandfather = parent->_parent;
			if (grandfather->_left == parent)
			{
				Node* uncle = grandfather->_right;
				//���1��uncle���ڣ���Ϊ��
				if (uncle && uncle->_col == RED)
				{
					parent->_col = uncle->_col = BLACK;
					grandfather->_col = RED;
					//�������ϴ���
					cur = grandfather;
					parent = cur->_parent;
				}
				//���2/���3��uncle�����ڣ����ߴ�����Ϊ��
				else
				{
					//���3:˫��->��Ϊ����
					if (cur == parent->_right)
					{
						RotateL(parent);
						swap(cur, parent);
					}
					//���2(ps:�п����ǵ���������仯������)
					RotateR(grandfather);
					grandfather->_col = RED;
					parent->_col = BLACK;
					break;
				}
			}
			else //�游�����Ǹ���
			{
				Node* uncle = grandfather->_left;
				//���1��uncle���ڣ���Ϊ��
				if (uncle && uncle->_col == RED)
				{
					parent->_col = uncle->_col = BLACK;
					grandfather->_col = RED;
					//������������
					cur = grandfather;
					parent = cur->_parent;
				}
				//���2/���3��uncle�����ڣ����ߴ�����Ϊ��
				else
				{
					//���3��˫��->����
					if (cur == parent->_left)
					{
						RotateR(parent);
						swap(cur, parent);
					}
					//���2(ps:�п��������3�仯����)
					RotateL(grandfather);
					grandfather->_col = RED;
					parent->_col = BLACK;
					break;
				}
			}
		}
		_root->_col = BLACK;
		return true;
	}
	void RotateL(Node* parent)
	{
		Node* subR = parent->_right;
		Node* ppNode = parent->_parent;
		Node* subRL = subR->_left;
		parent->_right = subRL;
		if (subRL)
		{
			subRL->_parent = parent;
		}
		parent->_parent = subR;
		subR->_left = parent;
		//1.ԭ��parent��������ĸ�������subR�Ǹ�
		//2.parentΪ������ֻ���������е��������ı����ӹ�ϵ����ôsubRҪ��������λ�á�
		if (_root == parent)
		{
			_root = subR;
			subR->_parent = nullptr;
		}
		else
		{
			if (ppNode->_left == parent)
			{
				ppNode->_left = subR;
			}
			else
			{
				ppNode->_right = subR;
			}
			subR->_parent = ppNode;
		}
	}
	void RotateR(Node* parent)
	{
		Node* subL = parent->_left;
		Node* subLR = subL->_right;
		Node* ppNode = parent->_parent;
		parent->_left = subLR;
		if (subLR)
		{
			subLR->_parent = parent;
		}
		parent->_parent = subL;
		subL->_right = parent;
		//1.ԭ��parent��������ĸ�������subR�Ǹ�
	    //2.parentΪ������ֻ���������е��������ı����ӹ�ϵ����ôsubRҪ��������λ�á�				
		if (_root == parent)
		{
			_root = subL;
			subL->_parent = nullptr;
		}
		else
		{
			if (ppNode->_left == parent)
			{
				ppNode->_left = subL;
			}
			else
			{
				ppNode->_right = subL;
			}
			subL->_parent = ppNode;
		}
	}
	void _InOrder(Node* root)
	{
		if (root == nullptr)
		{
			return;
		}
		_InOrder(root->_left);
		cout << root->_kv.first << ":" << root->_kv.second << endl;
		_InOrder(root->_right);
	}
	void InOrder()
	{
		_InOrder(_root);
	}
private:
	Node* _root=nullptr;
};
void TestRBTree()
{
	int a[] = { 16,3,7,11,9,26,18,14,15 };
	//int a[] = { 4,2,6,1,3,5,15,7,16,14 };
	RBTree<int, int> t;
	for (auto e : a)
	{
		t.Insert(make_pair(e, e));
	}
	t.InOrder();
	//cout << t.IsBalance() << endl;

}
   
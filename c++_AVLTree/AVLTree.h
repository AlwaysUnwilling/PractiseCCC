#pragma once
#include<iostream>

using namespace std;

template<class K,class V>
struct AVLTreeNode
{
	AVLTreeNode<K, V>* _left;
	AVLTreeNode<K, V>* _right;
	AVLTreeNode<K, V>* _parent;
	int _bf;   //balance factor  ƽ������
	pair<K, V> _kv;
	AVLTreeNode(const pair<K,V>& kv)
		:_left(nullptr)
		,_right(nullptr)
		,_parent(nullptr)
		,_bf(0)
		,_kv(kv)
	{}
};
template<class K, class V>
class AVLTree
{
	typedef AVLTreeNode<K, V> Node;
public:
	bool Insert(const pair<K, V> kv)
	{
		if (_root == nullptr)
		{
			_root = new Node(kv);
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
		if (parent->_kv.first < kv.first)
		{
			parent->_right = cur;
			cur->_parent = parent;
		}
		else
		{
			parent->_left = cur;
			cur->_parent = parent;
		}
		//����ƽ������
		while (parent)
		{
			if (cur == parent->_right)
			{
				parent->_bf++;
			}
			else 
			{
				parent->_bf--;
			}
			//���ƽ�������Ƿ���Ҫ��������
			if (parent->_bf == 0)
			{
				//parent���������ĸ߶�û�䡣ֹͣ���¡�
				break;
			}
			else if (parent->_bf == 1 || parent->_bf == -1)
			{
				//�����߶ȱ���ˡ��������ϸ���
				cur = parent;
				parent = parent->_parent;
			}
			else if (parent->_bf == 2 || parent->_bf == -2)
			{
				//parent�����������ֲ�ƽ�⣬��Ҫ��ת����һ�¡�
				//1����תǰ���Ǳ���������������������
				//2����ת��ƽ����
				if (parent->_bf == 2)
				{
					if (cur->_bf == 1)
					{
						//����  ����
						RotateL(parent);
					}
					else if (cur->_bf == -1)
					{
						//˫��
						RotateRL(parent);
					}
				}
				else if (parent->_bf == -2)
				{
					if (cur->_bf == -1)
					{
						//����  ����
						RotateR(parent);
					}
					else if (cur->_bf == 1)
					{
						//˫��
						RotateLR(parent);
					}
				}
				//��ת��ɺ�parent���ڵ����ĸ߶Ȼָ����˲�����ǰ�ĸ߶�
				//��������������ϲ�û��Ӱ�죬ѭ������
				break;
			}
		}
		return true;
	}
	void RotateL(Node* parent)
	{
		Node* subR = parent->_right;
		Node* subRL = subR->_left;
		subR->_left = parent;
		parent->_right = subRL;
		if (subRL)
		{
			subRL->_parent = parent;
		}
		Node* ppNode = parent->_parent;
		parent->_parent = subR;
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
		parent->_bf = subR->_bf = 0;
	}
	void RotateR(Node* parent)
	{
		Node* subL = parent->_left;
		Node* ppNode = parent->_parent;
		Node* subLR = subL->_right;
		parent->_left = subLR;
		if (subLR)
		{
			subLR->_parent = parent;
		}
		subL->_right = parent;
		parent->_parent = subL;
		if (parent == _root)
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
		subL->_bf = parent->_bf = 0;
	}
	void RotateRL(Node* parent)
	{
		Node* subR = parent->_right;
		Node* subRL = subR->_left;
		int bf = subRL->_bf;

		RotateR(parent->_right);
		RotateL(parent);
		//����subRL��subR��parent��ƽ������
		if (bf == -1)
		{
			parent->_bf = 0;
			subR->_bf = 1;
			subRL->_bf = 0;
		}
		else if (bf == 1)
		{
			parent->_bf = 0;
			subR->_bf = -1;
			subRL->_bf = 0;
		}
		else if (bf == 0)   //subRL�����²���Ľ��
		{
			parent->_bf = 0;
			subR->_bf = 0;
			subRL->_bf = 0;
		}
	}
	void RotateLR(Node* parent)
	{
		Node* subL = parent->_left;
		Node* subLR = subL->_right;
		int bf = subLR->_bf;

		RotateL(subL);
		RotateR(parent);

		if (bf == 1)
		{
			parent->_bf = 0;
			subL->_bf = -1;
			subLR->_bf = 0;
		}
		else if (bf == -1)
		{
			parent->_bf = 1;
			subL->_bf = 0;
			subLR->_bf = 0;
		}
		else if (bf == 0)  //subLR����������� 
		{
			parent->_bf = 0;
			subL->_bf = 0;
			subLR->_bf = 0;
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
	int Height(Node* root)
	{
		if (root == nullptr)
		{
			return 0;
		}
		int leftHeight = Height(root->_left);
		int rightHeight = Height(root->_right);
		return leftHeight > rightHeight ? leftHeight + 1 : rightHeight + 1;
	}
	bool _IsBalance(Node* root)
	{
		if (root == nullptr)
		{
			return true;
		}
		int leftHeight = Height(root->_left);
		int rightHeight = Height(root->_right);
		return abs(leftHeight - rightHeight) < 2
			&& _IsBalance(root->_left)
			&& _IsBalance(root->_right);
	}
	bool IsBalance()
	{
		return _IsBalance(_root);
	}
private:
	Node* _root=nullptr;
};

void TestAVLTree()
{
	int a[] = { 16,3,7,11,9,26,18,14,15 };
	AVLTree<int, int> t;
	for (auto e : a)
	{
		t.Insert(make_pair(e, e));
	}
	t.InOrder();
	cout << t.IsBalance() << endl;
}
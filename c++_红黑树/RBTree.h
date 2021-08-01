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
		//1.按搜索树的规则插入
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
		
		//新增结点的颜色
		cur->_col = RED;
		//2.更新各节点的颜色使满足红黑树的性质
		while (parent && parent->_col == RED)
		{
			//红黑色的条件关键看叔叔
			Node* grandfather = parent->_parent;
			if (grandfather->_left == parent)
			{
				Node* uncle = grandfather->_right;
				//情况1：uncle存在，且为红
				if (uncle && uncle->_col == RED)
				{
					parent->_col = uncle->_col = BLACK;
					grandfather->_col = RED;
					//继续往上处理
					cur = grandfather;
					parent = cur->_parent;
				}
				//情况2/情况3：uncle不存在，或者存在且为黑
				else
				{
					//情况3:双旋->变为单旋
					if (cur == parent->_right)
					{
						RotateL(parent);
						swap(cur, parent);
					}
					//情况2(ps:有可能是第三种情况变化过来的)
					RotateR(grandfather);
					grandfather->_col = RED;
					parent->_col = BLACK;
					break;
				}
			}
			else //祖父的右是父亲
			{
				Node* uncle = grandfather->_left;
				//情况1：uncle存在，且为红
				if (uncle && uncle->_col == RED)
				{
					parent->_col = uncle->_col = BLACK;
					grandfather->_col = RED;
					//继续迭代处理
					cur = grandfather;
					parent = cur->_parent;
				}
				//情况2/情况3：uncle不存在，或者存在且为黑
				else
				{
					//情况3：双旋->单旋
					if (cur == parent->_left)
					{
						RotateR(parent);
						swap(cur, parent);
					}
					//情况2(ps:有可能是情况3变化来的)
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
		//1.原来parent是这棵树的根，现在subR是根
		//2.parent为根的树只是整棵树中的子树，改变链接关系，那么subR要顶替它的位置。
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
		//1.原来parent是这棵树的根，现在subR是根
	    //2.parent为根的树只是整棵树中的子树，改变链接关系，那么subR要顶替它的位置。				
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
   
#pragma once
#include<iostream>

using namespace std;
enum Colour
{
	BLACK,
	RED,
};
template<class T>
struct RBTreeNode
{
	RBTreeNode<T>* _left;
	RBTreeNode<T>* _right;
	RBTreeNode<T>* _parent;
	T _data;   
	Colour _col;
	RBTreeNode(const T& data)
		:_left(nullptr)
		,_right(nullptr)
		,_parent(nullptr)
		,_data(data)
		,_col(RED)
	{}
};

//迭代器
template<class T,class Ref,class Ptr>
struct __TreeIterator
{
	typedef RBTreeNode<T> Node;
	typedef __TreeIterator<T,Ref,Ptr> Self;
	Node* _node;
	__TreeIterator(Node* node)
		:_node(node)
	{}
	Ref operator*()
	{
		return _node->_data;
	}
	Ptr operator->()
	{
		return &_node->_data;
	}
	Self& operator++()
	{
		//1.如果右不为空，中序的下一个就是右子树的最左结点
		//2.如果右为空，表示_node所在的子树已经访问完成，下一个结点在他的祖先中找
		// 沿着路径往上找孩子是它的左的那个祖先
		if (_node->_right)
		{
			//中序的下一个就是右子树的最左结点
			Node* subLeft = _node->_right;
			while (subLeft->_left)
			{
				subLeft = subLeft->_left;
			}
			_node = subLeft;
		}
		else
		{
			Node* cur = _node;
			Node* parent = cur->_parent;
			while (parent && cur==parent->_right)
			{
				cur = cur->_parent;
				parent = parent->_parent;
			}
			_node = parent;
		}
		return *this;
	}
	Self& operator--() 
	{
		if (_node->_left)
		{
			Node* subRight = _node->_left;
			while (subRight->_right)
			{
				subRight = subRight->_right;
			}
			_node = subRight;
		}
		else
		{
			Node* cur = _node;
			Node* parent = cur->_parent;
			while (parent && cur == parent->_left)
			{
				cur = cur->_parent;
				parent = parent->_parent;
			}
			_node = parent;
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

template<class K,class T,class KOfT>
class RBTree
{
	typedef RBTreeNode<T> Node;
public:
	typedef __TreeIterator<T,const T&,const T*> const_iterator;
	typedef __TreeIterator<T,T&,T*> iterator;
	iterator begin()
	{
		Node* cur=_root;
		while (cur && cur->_left)
		{
			cur = cur->_left;
		}
		return iterator(cur);
	}
	const_iterator begin()const
	{
		Node* cur = _root;
		while (cur && cur->_left)
		{
			cur = cur->_left;
		}
		return const_iterator(cur);
	}
	iterator end()
	{
		return iterator(nullptr);
	}
	const_iterator end()const
	{
		return const_iterator(nullptr);
	}
	pair<iterator,bool> Insert(const T& data)
	{
		//1.按搜索树的规则插入
		KOfT koft;//仿函数
		if (_root == nullptr)
		{
			_root = new Node(data);
			_root->_col = BLACK;
			return make_pair(iterator(_root),true);
		}
		Node* cur = _root;
		Node* parent = nullptr;
		while (cur)
		{
			if (koft(cur->_data) > koft(data))
			{
				parent = cur;
				cur = cur->_left;
			}
			else if (koft(cur->_data) < koft(data))
			{
				parent = cur;
				cur = cur->_right;
			}
			else
			{
				return make_pair(iterator(cur), false);
			}
		}
		cur = new Node(data);
		Node* newnode = cur;
		if (koft(cur->_data) > koft(parent->_data))
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
		return make_pair(iterator(newnode), true);
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

private:
	Node* _root=nullptr;
};

   
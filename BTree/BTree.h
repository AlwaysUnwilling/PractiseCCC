#pragma once

//B 树又叫平衡多路查找树。一棵M阶的B树(M叉树)的特性如下：
//B树中所有节点的孩子节点数中的最大值称为B树的阶，记为M（重点）
//树中的每个节点至多有M棵子树，即：如果定了M，则这个B树中任何节点的子节点数量都不能超过M
//若根节点不是终端节点，则至少有两棵子树
//除根节点和叶节点外，所有点至少有M/2棵子树（上溢）
//所有的叶子结点都位于同一层。
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//1. 根节点至少有两个孩子
//2. 每个非根节点至少有M / 2(上取整)个孩子, 至多有M个孩子
//3. 每个非根节点至少有M / 2 - 1(上取整)个关键字, 至多有M - 1个关键字，并且以升序排列
//4. key[i]和key[i + 1]之间的孩子节点的值介于key[i]、key[i + 1]之间
//5. 所有的叶子节点都在同一层

//B树的优点：
//数据结构管理数据：1、简单地把数据存起来；2、除了存储数据，还需要快速地搜索数据
//搜索：
//    1.搜索二叉树：极端场景下退化成类似单支，效率由O(logN)降低到O(N)；
//    2.为了解决上面的问题。提出了平衡树的概念：AVL树和红黑树。虽然基本上保证了效率O(logN)；
//      但是当再进行外查询（硬盘IO）时，O(logN)的效率也会由于N的次数增加而导致IO次数变多，效率下降
//      不能稳定第保证效率。外搜索时IO的时间消耗很大，需要尽量减少IO次数，即O(logN)的值尽量稳定的
//      小而且不会随N的增加而明显变化。
//    3.为了让搜索次数尽量小而不随N的数量增加而变化，提出了哈希/散列表(O(1))--但是当某些场景(哈希冲突严重)
//      下，哈希桶的某一个桶连接过长时也会导致搜索效率的下降。
// 小结： 以上数据结构在内存中搜索时效率都还不错。但是当进行外搜索时，由于IO次数的不可控，导致外搜索时
//       IO次数增加导致效率降低。而B树的出现，可以有效的控制外搜索时对IO次数的控制，保证了IO次数的少且
//       稳定！
#include<iostream>

//  B树的时间复杂度O(logM（N）)   ----[log(M/2)N,log(M)N]

template<class K,class V,size_t M>
struct BTreeNode
{
	std::pair<K, V> _kvs[ M ];    //关键字数组 ---多开一个关键字空间方便插入
	BTreeNode<K, V, M>* _subs[ M + 1 ];   //孩子节点指针数组  -----多开一个孩子节点方便插入
	BTreeNode<K, V, M>* _parent;	//父节点指针
	size_t _kvSize;                 //孩子节点数组中的有效个数 
	BTreeNode():_parent(nullptr),_kvSize(0)
	{
		for (size_t i=0;i<M+1;++i)
		{
			_subs[i] = nullptr;
		}
	}
};

template<class K,class V,size_t M>
class BTree
{
	typedef BTreeNode<K, V, M> Node;
private:
	Node* _root=nullptr;
private:
	//往父节点中插入一个kv值和一个孩子sub
	void insertkv(Node* cur, const std::pair<K, V> kv, Node* sub)
	{
		size_t index = cur->_kvSize;
		while (index)
		{
			if (cur->_kvs[index-1].first > kv.first)
			{
				cur->_kvs[index] = cur->_kvs[index - 1];//挪动父节点的kv值
				cur->_subs[index + 1] = cur->_subs[index];//挪动父节点kv值对应的右孩子
				index--;
			}
			else
			{
				break;
			}
		}
		cur->_kvs[index] = kv;
		cur->_subs[index + 1] = sub;
		if (sub)
		{
			sub->_parent = cur;
		}
		cur->_kvSize++;
	}
	//中序遍历----左根左根.....右
	void _inorder(Node* root)
	{
		if (root == nullptr)
		{
			return;
		}
		size_t i = 0;
		while (i < root->_kvSize)
		{
			_inorder(root->_subs[i]);
			std::cout << root->_kvs[i].first << ":" << root->_kvs[i].second << std::endl;
			++i;
		}
		//再访问最后一个右
		_inorder(root->_subs[i]);
	}
public:
	std::pair<Node*,int> find(const K& key)   //找到后返回该节点和对应的下标；失败返回父节点和-1;
	{	
		Node* cur = _root;
		Node* parent = nullptr;
		while (cur)
		{
			size_t index = 0;
			while (index < cur->_kvSize)    //如果M比较大，这里应该换用二分查找会块一些
			{
				if (cur->_kvs[index].first < key)  //key大于当前位置key，往右找
				{
					index++;
				}
				else if (cur->_kvs[index].first > key)//可以小于当前位置key，去往当前位置key的左孩子找
				{
					break;
				}
				else
				{
					return std::make_pair(cur, index);
				}
			}
			//左孩子的下标与当前key值下标相同，右孩子下标是当前key值的下标+1；
			parent = cur;
			cur = cur->_subs[index];
		}
		//没找到
		return { parent,-1 };
	}
	bool insert(const std::pair<K, V>& kv)
	{
		//空树
		if (_root == nullptr)   
		{
			_root = new Node;
			_root->_kvs[0] = kv;
			_root->_kvSize++;
		}
		//非空树
		std::pair<Node*, int> ret = find(kv.first);
		//已经存在，插入失败   (如果允许插入就是multi版本)
		if (ret.second >= 0)
		{
			return false;
		}
		Node* cur = ret.first;//找需要插入的节点
		auto newKV = kv;
		Node* sub = nullptr;  //分裂后产生的新节点
		while (true)
		{
			insertkv(cur, newKV, sub); //插入
		    //判断插入的合法性---需要符合B树的特性
			if (cur->_kvSize < M)
			{
				return true;
			}
			//插入后导致该节点的key值满了，需要自底向上分裂解决
			Node* newNode = new Node;  //生成兄弟节点
			//1、拷贝一半key值给生成的兄弟节点[0,mid-1] mid [mid+1,cur->_kvSize-1];
			size_t mid = M / 2;
			newKV = cur->_kvs[mid];
			cur->_kvs[mid] = std::pair<K,V>();
			size_t j = 0;
			size_t i = mid + 1;
			for (; i < M; ++i)
			{
				newNode->_kvs[j] = cur->_kvs[i];
				cur->_kvs[i]= std::pair<K, V>();  //清除
				//TODO  //拷贝左孩子
				newNode->_subs[j] = cur->_subs[i];
				cur->_subs[i] = nullptr;         //清除
				//拷贝后孩子的父亲需要重新跟新
				if (newNode->_subs[j])
				{
					newNode->_subs[j]->_parent = newNode;
				}
				j++;
				newNode->_kvSize++;
			}
			//拷贝最右一个kv值对应的右孩子
			newNode->_subs[j] = cur->_subs[i];
			cur->_subs[i] = nullptr;               //清除
			if (newNode->_subs[j])
			{
				newNode->_subs[j]->_parent = newNode;
			}
			cur->_kvSize = cur->_kvSize - newNode->_kvSize - 1;
			//cur->_kvSize = mid;
			//如果cur没有父亲，那么cur就是根，将产生新的根
			if (cur->_parent == nullptr)
			{
				_root = new Node;
				_root->_kvs[0] = newKV;
				_root->_kvSize++;
				_root->_subs[0] = cur;
				_root->_subs[1] = newNode;
				cur->_parent = _root;
				newNode->_parent = _root;
				return true;
			}
			//如果cur有父亲，那么就要转换成往cur的父亲中插入一个key和一个孩子（新分裂产生的兄弟节点）
			sub = newNode;      //  开始迭代
			cur = cur->_parent;
		}
		return true;
	}
	void inorder()
	{
		_inorder(_root);
	}
};

//B+树：
//B+树的规则和B树一样，除了一下几点变化：
//1、每个节点中，孩子的数量与关键字的数量一样---相当于在B树中取消了最左边的左孩子
//2、为所有叶子节点增加一个连接指针----方便查找
//3、所有关键字都出现在叶子节点---所有的值(K-V)都存在叶子，非叶子节点只存储关键字(K),方便找到kv在的叶子
//   每个节点存的就是孩子的最小值
//***所有的值都要存到叶子节点：如果是KV模型，非叶子节点只存K，叶子节点村KV；如果是K模型，非叶子节点存K，
//   叶子节点也存K。
//B+树的优缺点：a、B+树找任何一个值都要走到叶子节点（叶子节点存储所有的值）---缺点（由于B+树的高度很低，可以忽略此缺点）
//			 b、B+树非常方便遍历，所有的值都存储到叶子节点，而且叶子节点被连接起来了

//B* 树：
//B* 树是B + 树的变形，在B + 树的非根和非叶子节点再增加指向兄弟节点的指针；非根节点的关键字和孩子的数量利用率进行提高[2 * M / 3, M];
//     分裂更加滞后。
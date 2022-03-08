#pragma once

//B ���ֽ�ƽ���·��������һ��M�׵�B��(M����)���������£�
//B�������нڵ�ĺ��ӽڵ����е����ֵ��ΪB���Ľף���ΪM���ص㣩
//���е�ÿ���ڵ�������M�������������������M�������B�����κνڵ���ӽڵ����������ܳ���M
//�����ڵ㲻���ն˽ڵ㣬����������������
//�����ڵ��Ҷ�ڵ��⣬���е�������M/2�����������磩
//���е�Ҷ�ӽ�㶼λ��ͬһ�㡣
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//1. ���ڵ���������������
//2. ÿ���Ǹ��ڵ�������M / 2(��ȡ��)������, ������M������
//3. ÿ���Ǹ��ڵ�������M / 2 - 1(��ȡ��)���ؼ���, ������M - 1���ؼ��֣���������������
//4. key[i]��key[i + 1]֮��ĺ��ӽڵ��ֵ����key[i]��key[i + 1]֮��
//5. ���е�Ҷ�ӽڵ㶼��ͬһ��

//B�����ŵ㣺
//���ݽṹ�������ݣ�1���򵥵ذ����ݴ�������2�����˴洢���ݣ�����Ҫ���ٵ���������
//������
//    1.���������������˳������˻������Ƶ�֧��Ч����O(logN)���͵�O(N)��
//    2.Ϊ�˽����������⡣�����ƽ�����ĸ��AVL���ͺ��������Ȼ�����ϱ�֤��Ч��O(logN)��
//      ���ǵ��ٽ������ѯ��Ӳ��IO��ʱ��O(logN)��Ч��Ҳ������N�Ĵ������Ӷ�����IO������࣬Ч���½�
//      �����ȶ��ڱ�֤Ч�ʡ�������ʱIO��ʱ�����ĺܴ���Ҫ��������IO��������O(logN)��ֵ�����ȶ���
//      С���Ҳ�����N�����Ӷ����Ա仯��
//    3.Ϊ����������������С������N���������Ӷ��仯������˹�ϣ/ɢ�б�(O(1))--���ǵ�ĳЩ����(��ϣ��ͻ����)
//      �£���ϣͰ��ĳһ��Ͱ���ӹ���ʱҲ�ᵼ������Ч�ʵ��½���
// С�᣺ �������ݽṹ���ڴ�������ʱЧ�ʶ����������ǵ�����������ʱ������IO�����Ĳ��ɿأ�����������ʱ
//       IO�������ӵ���Ч�ʽ��͡���B���ĳ��֣�������Ч�Ŀ���������ʱ��IO�����Ŀ��ƣ���֤��IO����������
//       �ȶ���
#include<iostream>

//  B����ʱ�临�Ӷ�O(logM��N��)   ----[log(M/2)N,log(M)N]

template<class K,class V,size_t M>
struct BTreeNode
{
	std::pair<K, V> _kvs[ M ];    //�ؼ������� ---�࿪һ���ؼ��ֿռ䷽�����
	BTreeNode<K, V, M>* _subs[ M + 1 ];   //���ӽڵ�ָ������  -----�࿪һ�����ӽڵ㷽�����
	BTreeNode<K, V, M>* _parent;	//���ڵ�ָ��
	size_t _kvSize;                 //���ӽڵ������е���Ч���� 
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
	//�����ڵ��в���һ��kvֵ��һ������sub
	void insertkv(Node* cur, const std::pair<K, V> kv, Node* sub)
	{
		size_t index = cur->_kvSize;
		while (index)
		{
			if (cur->_kvs[index-1].first > kv.first)
			{
				cur->_kvs[index] = cur->_kvs[index - 1];//Ų�����ڵ��kvֵ
				cur->_subs[index + 1] = cur->_subs[index];//Ų�����ڵ�kvֵ��Ӧ���Һ���
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
	//�������----������.....��
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
		//�ٷ������һ����
		_inorder(root->_subs[i]);
	}
public:
	std::pair<Node*,int> find(const K& key)   //�ҵ��󷵻ظýڵ�Ͷ�Ӧ���±ꣻʧ�ܷ��ظ��ڵ��-1;
	{	
		Node* cur = _root;
		Node* parent = nullptr;
		while (cur)
		{
			size_t index = 0;
			while (index < cur->_kvSize)    //���M�Ƚϴ�����Ӧ�û��ö��ֲ��һ��һЩ
			{
				if (cur->_kvs[index].first < key)  //key���ڵ�ǰλ��key��������
				{
					index++;
				}
				else if (cur->_kvs[index].first > key)//����С�ڵ�ǰλ��key��ȥ����ǰλ��key��������
				{
					break;
				}
				else
				{
					return std::make_pair(cur, index);
				}
			}
			//���ӵ��±��뵱ǰkeyֵ�±���ͬ���Һ����±��ǵ�ǰkeyֵ���±�+1��
			parent = cur;
			cur = cur->_subs[index];
		}
		//û�ҵ�
		return { parent,-1 };
	}
	bool insert(const std::pair<K, V>& kv)
	{
		//����
		if (_root == nullptr)   
		{
			_root = new Node;
			_root->_kvs[0] = kv;
			_root->_kvSize++;
		}
		//�ǿ���
		std::pair<Node*, int> ret = find(kv.first);
		//�Ѿ����ڣ�����ʧ��   (�������������multi�汾)
		if (ret.second >= 0)
		{
			return false;
		}
		Node* cur = ret.first;//����Ҫ����Ľڵ�
		auto newKV = kv;
		Node* sub = nullptr;  //���Ѻ�������½ڵ�
		while (true)
		{
			insertkv(cur, newKV, sub); //����
		    //�жϲ���ĺϷ���---��Ҫ����B��������
			if (cur->_kvSize < M)
			{
				return true;
			}
			//������¸ýڵ��keyֵ���ˣ���Ҫ�Ե����Ϸ��ѽ��
			Node* newNode = new Node;  //�����ֵܽڵ�
			//1������һ��keyֵ�����ɵ��ֵܽڵ�[0,mid-1] mid [mid+1,cur->_kvSize-1];
			size_t mid = M / 2;
			newKV = cur->_kvs[mid];
			cur->_kvs[mid] = std::pair<K,V>();
			size_t j = 0;
			size_t i = mid + 1;
			for (; i < M; ++i)
			{
				newNode->_kvs[j] = cur->_kvs[i];
				cur->_kvs[i]= std::pair<K, V>();  //���
				//TODO  //��������
				newNode->_subs[j] = cur->_subs[i];
				cur->_subs[i] = nullptr;         //���
				//�������ӵĸ�����Ҫ���¸���
				if (newNode->_subs[j])
				{
					newNode->_subs[j]->_parent = newNode;
				}
				j++;
				newNode->_kvSize++;
			}
			//��������һ��kvֵ��Ӧ���Һ���
			newNode->_subs[j] = cur->_subs[i];
			cur->_subs[i] = nullptr;               //���
			if (newNode->_subs[j])
			{
				newNode->_subs[j]->_parent = newNode;
			}
			cur->_kvSize = cur->_kvSize - newNode->_kvSize - 1;
			//cur->_kvSize = mid;
			//���curû�и��ף���ôcur���Ǹ����������µĸ�
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
			//���cur�и��ף���ô��Ҫת������cur�ĸ����в���һ��key��һ�����ӣ��·��Ѳ������ֵܽڵ㣩
			sub = newNode;      //  ��ʼ����
			cur = cur->_parent;
		}
		return true;
	}
	void inorder()
	{
		_inorder(_root);
	}
};

//B+����
//B+���Ĺ����B��һ��������һ�¼���仯��
//1��ÿ���ڵ��У����ӵ�������ؼ��ֵ�����һ��---�൱����B����ȡ��������ߵ�����
//2��Ϊ����Ҷ�ӽڵ�����һ������ָ��----�������
//3�����йؼ��ֶ�������Ҷ�ӽڵ�---���е�ֵ(K-V)������Ҷ�ӣ���Ҷ�ӽڵ�ֻ�洢�ؼ���(K),�����ҵ�kv�ڵ�Ҷ��
//   ÿ���ڵ��ľ��Ǻ��ӵ���Сֵ
//***���е�ֵ��Ҫ�浽Ҷ�ӽڵ㣺�����KVģ�ͣ���Ҷ�ӽڵ�ֻ��K��Ҷ�ӽڵ��KV�������Kģ�ͣ���Ҷ�ӽڵ��K��
//   Ҷ�ӽڵ�Ҳ��K��
//B+������ȱ�㣺a��B+�����κ�һ��ֵ��Ҫ�ߵ�Ҷ�ӽڵ㣨Ҷ�ӽڵ�洢���е�ֵ��---ȱ�㣨����B+���ĸ߶Ⱥܵͣ����Ժ��Դ�ȱ�㣩
//			 b��B+���ǳ�������������е�ֵ���洢��Ҷ�ӽڵ㣬����Ҷ�ӽڵ㱻����������

//B* ����
//B* ����B + ���ı��Σ���B + ���ķǸ��ͷ�Ҷ�ӽڵ�������ָ���ֵܽڵ��ָ�룻�Ǹ��ڵ�Ĺؼ��ֺͺ��ӵ����������ʽ������[2 * M / 3, M];
//     ���Ѹ����ͺ�
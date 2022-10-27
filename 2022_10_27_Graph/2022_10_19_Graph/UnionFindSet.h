#pragma once 
#include<iostream>
#include<vector>
#include<map>


/*template<class T>
class UnionFindSet
{
public:
	UnionFindSet(T* a,int n)
	{
		for (int i = 0; i < n; ++i)
		{
			_a.push_back(a[i]);
			_IndexMap[a[i]] = i;
		}
	}
private:
	std::vector<T> _a;   //编号找人
	std::map<T, int> _IndexMap; //人找编号
};*/

template<typename T>
class UnionFindSet
{
private:
	std::vector<T> _ufs;
public:
	UnionFindSet(size_t n)
		:_ufs(n,-1)
	{}
	void Union(const T& x1,const T& x2)
	{
		int root1 = FindRoot(x1);
		int root2 = FindRoot(x2);
		if (root1 == root2)
		{
			break;
		}
		//数据量小的合并到数据量大的上，在路径压缩中会减少需要压缩的数据
		if (abs(_ufs[root1]) < abs(_ufs[root2]))
		{
			swap(root1, root2);
		}
		_ufs[root1] += _ufs[root2];
		_ufs[root2] = root1;
	}
	int FindRoot(const T& x)
	{
		int root = x;
		while (_ufs[root] >= 0)
		{
			root = _ufs[root];
		}
		
		//压缩路径
		while (_ufs[x] >= 0)
		{
			int parent = _ufs[x];
			_ufs[x] = root;
			x = parent;
		}
		return root;
	}
	bool IsInSet(const T& x1, const T& x2)
	{
		int root1 = FindRoot(x1);
		int root2 = FindRoot(x2);
		return root1 == root2;
	}
	size_t SetSize()
	{
		size_t cnt = 0;
		for (auto e : _ufs)
		{
			if (e < 0)
			{
				cnt++;
			}
		}
		return cnt;
	}
};


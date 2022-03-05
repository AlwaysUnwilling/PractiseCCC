#pragma once

#include<iostream>
#include<vector>
#include<assert.h>
#include<string>
#include<math.h>


class UnionFindSet
{
private:
	std::vector<int> _ufs;
public:
	UnionFindSet(int n)
	{
		_ufs.resize(n, -1);   //n表示最开始有多少个独立的集合（即多少个元素，每个元素单独看作
							  // 一个集合，他们的的值--父节点都是-1，表示他们都是根		
	}
	//元素x1和x2所在的集合合并
	void Union(int x1, int x2)
	{
		int root1 = FindRoot(x1);
		int root2 = FindRoot(x2);
		if (root1 != root2) {            //root1==root2 表示俩个值本身就在一个集合中，不需要再合并
			_ufs[root1] += _ufs[root2];  //选root1作为新集合的根
			_ufs[root2] = root1;
		}
	}
	//查找x所在集合的根
	int FindRoot(int x)
	{
		assert(x < _ufs.size());
		while (_ufs[x]>=0) {
			x = _ufs[x];
		}
		return x;
	}
	size_t SetSize()    //总共有多少个集合
	{
		size_t count = 0;
		for (auto e : _ufs) {
			if (e < 0) {
				count++;
			}
		}
		return count;
	}
	size_t SetMemberSize(int x)  //x所在集合中的元素个数---根的绝对值是多少就是该集合中的元素个数（根的-1的个数）
	{
		int root = FindRoot(x);
		return abs(_ufs[root]);
	}
};

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
		_ufs.resize(n, -1);   //n��ʾ�ʼ�ж��ٸ������ļ��ϣ������ٸ�Ԫ�أ�ÿ��Ԫ�ص�������
							  // һ�����ϣ����ǵĵ�ֵ--���ڵ㶼��-1����ʾ���Ƕ��Ǹ�		
	}
	//Ԫ��x1��x2���ڵļ��Ϻϲ�
	void Union(int x1, int x2)
	{
		int root1 = FindRoot(x1);
		int root2 = FindRoot(x2);
		if (root1 != root2) {            //root1==root2 ��ʾ����ֵ�������һ�������У�����Ҫ�ٺϲ�
			_ufs[root1] += _ufs[root2];  //ѡroot1��Ϊ�¼��ϵĸ�
			_ufs[root2] = root1;
		}
	}
	//����x���ڼ��ϵĸ�
	int FindRoot(int x)
	{
		assert(x < _ufs.size());
		while (_ufs[x]>=0) {
			x = _ufs[x];
		}
		return x;
	}
	size_t SetSize()    //�ܹ��ж��ٸ�����
	{
		size_t count = 0;
		for (auto e : _ufs) {
			if (e < 0) {
				count++;
			}
		}
		return count;
	}
	size_t SetMemberSize(int x)  //x���ڼ����е�Ԫ�ظ���---���ľ���ֵ�Ƕ��پ��Ǹü����е�Ԫ�ظ���������-1�ĸ�����
	{
		int root = FindRoot(x);
		return abs(_ufs[root]);
	}
};

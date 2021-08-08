#pragma once
#include<vector>

namespace My_BitSet
{
	class bitset
	{
	public:
		bitset(size_t N)
		{
			_bits.resize(N / 32 + 1, 0);
			_num = 0;
		}
		void set(size_t x)
		{
			size_t index = x / 32;//算出映射位置在第几个整型
			size_t pos = x % 32;//算出x在整型的第几个位
			_bits[index] |= (1 << pos);//第pos个位置成1
			++_num;
		}
		void reset(size_t x)
		{
			size_t index = x / 32;
			size_t pos = x % 32;
			//_bits[index] ^= (1 << pos);//将第pos个位置成0    **如果第pos位本来就是0，这样就就会置成1
			_bits[index] &= ~(1 << pos);//将第pos个位置成0
			--_num;
		}
		//判断x在不在(即x映射的位置的位是否为1)
		bool test(size_t x)
		{
			size_t index = x / 32;
			size_t pos = x % 32;
			//int tmp = _bits[index];
			//tmp &= (1 << pos);
			//if (tmp != 0)
			//{
			//	return true;
			//}
			//else
			//	return false;
			return _bits[index] & (1 << pos);
		}
	private:
		std::vector<int> _bits;
		size_t _num;//映射存储的数据个数
	};
	void test_bitset()
	{
		bitset b(101);
		b.set(100);
		b.set(98);
		b.set(10);
		b.set(97);
		b.set(5);
		b.reset(98);
		for (size_t i = 0; i < 101; i++)
		{
			printf("[%d]:%d\n", i, b.test(i));
		}
		//bitset b1(-1);//无符号整型最大值
	}
}

//位图的应用
//1. 快速查找某个数据是否在一个集合中
//2. 排序
//3. 求两个集合的交集、并集等
//4. 操作系统中磁盘块标记
//位图的优点：节省空间，效率高；缺点：只能处理整型。
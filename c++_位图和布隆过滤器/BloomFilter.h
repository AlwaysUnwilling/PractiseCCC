#pragma once
#include"BitSet.h"
#include<string>

namespace My_BloomFilter
{
	struct HashStr1
	{
		size_t operator()(const std::string& str)
		{
			//BKDR
			size_t hash = 0;
			for (size_t i = 0; i < str.size(); ++i)
			{
				hash *= 131;
				hash += str[i];
			}
			return hash;
		}
	};
	struct HashStr2
	{
		size_t operator()(const std::string& str)
		{
			//RSHash
			size_t hash = 0;
			size_t magic = 63689;//魔数
			for (size_t i = 0; i < str.size(); ++i)
			{
				hash *= magic;
				hash += str[i];
				magic *= 378551;
			}
			return hash;
		}
	};
	struct HashStr3
	{
		size_t operator()(const std::string& str)
		{
			//SDBMHash
			size_t hash = 0;
			for (size_t i = 0; i < str.size(); ++i)
			{
				hash *= 65599;
				hash += str[i];
			}
			return hash;
		}
	};
	template<class K = std::string,
		     class Hash1 = HashStr1,
		     class Hash2 = HashStr2,
		     class Hash3 = HashStr3>
	class bloomfilter
	{
	public:
		bloomfilter(size_t num)
			:_bs(5*num)
			,_N(5*num)
		{}
		void set(const K& key)
		{
			size_t index1 = Hash1()(key) % _N;
			size_t index2 = Hash2()(key) % _N;
			size_t index3 = Hash3()(key) % _N;
			_bs.set(index1);
			_bs.set(index2);
			_bs.set(index3);
		}
		bool test(const K& key)
		{
			size_t index1 = Hash1()(key) % _N;
			if (_bs.test(index1) == false)
				return false;

			size_t index2 = Hash2()(key) % _N;
			if (_bs.test(index2) == false)
				return false;

			size_t index3 = Hash3()(key) % _N;
			if (_bs.test(index3) == false)
				return false;

			return true;//但是这里也不一定是真的在，还是存在误判
			//判断在，是不准确的，可能存在误判
			//判断不在，是准确的
		}
	private:
		My_BitSet::bitset _bs;//位图
		size_t _N;
	};
	void test_bloomfilter()
	{
		bloomfilter<std::string> bf(100);
		bf.set("abcd");
		bf.set("aadd");
		bf.set("bcad");
		
		std::cout << bf.test("abcd") << std::endl;
		std::cout << bf.test("aadd") << std::endl;
		std::cout << bf.test("bcad") << std::endl;
	}
}

//布隆过滤器的删除：
//布隆过滤器不能直接支持删除工作，因为在删除一个元素时，可能会影响其他元素。
//比如：删除上图中"tencent"元素，如果直接将该元素所对应的二进制比特位置0，“baidu”元素也被删除了，
//因为这两个元素在多个哈希函数计算出的比特位上刚好有重叠。
//一种支持删除的方法：将布隆过滤器中的每个比特位扩展成一个小的计数器，插入元素时给k个计数器(k个哈
//	希函数计算出的哈希地址)加一，删除元素时，给k个计数器减一，通过多占用几倍存储空间的代价来增加删
//	除操作。
//	缺陷：
//	1. 无法确认元素是否真正在布隆过滤器中
//	2. 存在计数回绕
//优点：节省空间，高效，可以标记存储任意类型
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
			size_t index = x / 32;//���ӳ��λ���ڵڼ�������
			size_t pos = x % 32;//���x�����͵ĵڼ���λ
			_bits[index] |= (1 << pos);//��pos��λ�ó�1
			++_num;
		}
		void reset(size_t x)
		{
			size_t index = x / 32;
			size_t pos = x % 32;
			//_bits[index] ^= (1 << pos);//����pos��λ�ó�0    **�����posλ��������0�������;ͻ��ó�1
			_bits[index] &= ~(1 << pos);//����pos��λ�ó�0
			--_num;
		}
		//�ж�x�ڲ���(��xӳ���λ�õ�λ�Ƿ�Ϊ1)
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
		size_t _num;//ӳ��洢�����ݸ���
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
		//bitset b1(-1);//�޷����������ֵ
	}
}

//λͼ��Ӧ��
//1. ���ٲ���ĳ�������Ƿ���һ��������
//2. ����
//3. ���������ϵĽ�����������
//4. ����ϵͳ�д��̿���
//λͼ���ŵ㣺��ʡ�ռ䣬Ч�ʸߣ�ȱ�㣺ֻ�ܴ������͡�
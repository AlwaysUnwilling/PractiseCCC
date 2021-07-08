#include<iostream>
#include<vector>
#include<list>
#include<queue>
#include<stack>
#include<functional>   //�º���ͷ�ļ�

using namespace std;
#include"priority_queue.h"
void test_priority_queue()  //��֧�ֵ���������
{
	//priority_queue<int> pq;  //Ĭ���Ǵ�����ȼ���
	priority_queue<int,vector<int>,greater<int>> pq;  //Ĭ���Ǵ�����ȼ���,�����ҪС�����ȼ�����β����� �º���
	pq.push(3);
	pq.push(1);
	pq.push(9);
	pq.push(4);
	pq.push(2);
	while (!pq.empty())
	{
		cout << pq.top()<<" ";
		pq.pop();
	}
	cout << endl;
}
//�º���������Ӧ��
void test_sort()
{
	vector<int> v;
	v.push_back(2);
	v.push_back(7);
	v.push_back(1);
	v.push_back(6);
	v.push_back(0);
	for (auto e : v)
	{
		cout << e << " ";
	}
	cout << endl;
	sort(v.begin(), v.end());   //Ĭ���ĵ�������(less)
	for (auto e : v)
	{
		cout << e << " ";
	}
	cout << endl;
	//�����Ҫ�Ľ���  
	//default (1)	
	//template <class RandomAccessIterator>
	//void sort(RandomAccessIterator first, RandomAccessIterator last);
	//custom(2)
	//	template <class RandomAccessIterator, class Compare>
	//void sort(RandomAccessIterator first, RandomAccessIterator last, Compare comp);        �����Compare comp Ҳ�Ƿº���,�����ﴫ���Ƿº����Ķ��󣬼���less<T> le ���� greater<T> gt,
	// 	                                                                                  �������ȼ������ﴫ���Ƿº�������less<T>����greater<T>
	//����
	//greater<int> gt;
	//sort(v.begin(), v.end(), gt);  ʵ�������Ǹ�ϲ��������÷�
	sort(v.begin(), v.end(), greater<int>());
	for (auto e : v)
	{
		cout << e << " ";
	}
	cout << endl;
}
int main()
{
	//test_priority_queue();
	//my_priority_queue::test_priority_queue();
	/*my_priority_queue::less<int> lessFunc;   
	cout << lessFunc(1, 2) << endl;*/
	test_sort();
	return 0;
}



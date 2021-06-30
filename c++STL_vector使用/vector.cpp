#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

void test_vector1()  //�������졢��ֵ
{
	vector<int> v1;  //β������
	v1.push_back(1);
	v1.push_back(2);
	v1.push_back(3);
	v1.push_back(4);
	for (size_t i = 0; i < v1.size(); ++i)  //����
	{
		cout << v1[i] << " ";
	}
	cout << endl;
	vector<int> v2(v1); //��������
	for (size_t i = 0; i < v2.size(); ++i)
	{
		cout << v2[i] << " ";
	}
	cout << endl;
	vector<int> v3;
	v3.push_back(10);
	v3.push_back(20);
	v3.push_back(30);
	v3.push_back(40);
	v1 = v3;     //��ֵ
	for (size_t i = 0; i < v1.size(); ++i)
	{
		cout << v1[i] << " ";
	}
	cout << endl;
}
void test_vector2()  //������д
{
	vector<int> v;
	v.push_back(1);
	v.push_back(2);
	v.push_back(3);
	v.push_back(4);
	for (size_t i = 0; i < v.size(); ++i)  //д
	{
		v[i] += 1;
	}
	cout << endl;
	for (size_t i = 0; i < v.size(); ++i)  //����
	{
		cout << v[i] << " ";
	}
	cout << endl;
	//������ vector<int>::iterator
	vector<int>::iterator it = v.begin();
	while (it != v.end())
	{
		*it += 1;
		++it;
	}
	it = v.begin();
	while (it != v.end())
	{
		cout << *it << " ";
		++it;
	}
	cout << endl;
	//��Χfor(auto e:v)
	for (auto& e : v)
	{
		e += 1;
	}
	for (auto e : v)
	{
		cout << e << " ";
	}
	cout << endl;
}
void print_vector(const vector<int> vt)
{
	vector<int>::const_iterator it = vt.begin();
	while (it != vt.end())
	{
		cout << *it << " ";
		++it;
	}
	cout << endl;
}
void test_vector3()  //�������͵ĵ�����
{
	vector<int> v;
	v.push_back(1);
	v.push_back(2);
	v.push_back(3);
	v.push_back(4);
	//��ͨ����ش���  �ɶ���д
	vector<int>::iterator it = v.begin();
	while (it != v.end())
	{
		*it += 1;
		++it;
	}
	it = v.begin();
	while (it != v.end())
	{
		cout << *it << " ";
		++it;
	}
	cout << endl;
	//const_iterator  �ɶ�  ����д
	print_vector(v);
	//���������  �ɶ���д��Ҳ��vector<int>::const_reverse_iterator it = vt.rbegin() ��������ֻ����
	vector<int>::reverse_iterator rit = v.rbegin();
	while (rit != v.rend())
	{
		cout << *rit << " ";
		++rit;
	}
	cout << endl;
}
void test_vector4()
{
	vector<int> v;
	v.push_back(1);
	v.push_back(2);
	v.push_back(3);
	v.push_back(4);
	cout << v.capacity() << endl;
	cout << v.size() << endl;

	size_t sz;
	vector<int> foo;
	sz = foo.capacity();
	cout << "making foo grow:" << endl;
	for (int i = 0; i < 100; ++i)
	{
		foo.push_back(i);
		if (sz != foo.capacity())
		{
			sz = foo.capacity();
			cout << "capacity changed:" << sz << endl;
		}
	}

}
void test_vector5()
{
	vector<int> v;
	v.push_back(1);
	v.push_back(2);
	v.push_back(3);
	v.push_back(4);
	//v[4]=5;  //[]����Խ��ֱ����ֹ����assert����ʵ��
	v.at(4) = 5;  //at����Խ������쳣��
}
void test_vector6()
{
	vector<int> v;
	v.push_back(1);
	v.push_back(2);
	v.push_back(3);
	v.push_back(4);
	v.insert(v.begin(), 0);   //ͷ��    ��ͷ(v.begin())��λ�ò���0��
	v.insert(v.begin(), -1);
	for (auto e : v)
	{
		cout << e << " ";
	}
	cout << endl;
	v.erase(v.begin());   //ͷɾ    ��ͷ(v.begin())��λ��ɾ������
	for (auto e : v)
	{
		cout << e << " ";
	}
	cout << endl;
	v.insert(v.end(), -1);  //����Ҳ����ʵ��β��
	for (auto e : v)
	{
		cout << e << " ";
	}
	cout << endl;
}
void test_vector7()
{
	vector<int> v;
	v.push_back(10);
	v.push_back(20);
	v.push_back(50);
	v.push_back(7);
	v.push_back(2);
	v.push_back(7);
	v.push_back(1);
	//Ҫ��ɾ�����е�7��
	//����1��֪��7���±�3
	v.erase(v.begin() + 3);
	for (auto e : v)
	{
		cout << e << " ";
	}
	cout << endl;
	//����2�����ң�����vector��û���ṩ���ҽӿ�(find());�������ʹ���㷨��find();
	// #include<algorithm>  �㷨ͷ�ļ�
	vector<int>::iterator pos = find(v.begin(), v.end(), 7); //��������ҵ�ֵ�ж����findֻ�᷵���ҵ��ĵ�һ����ֵ���±�
	if (pos != v.end()) 
	{
		v.erase(pos);
	}
	//��ʵ�㷨��algorithm�����find��һ������ģ�壬ע�⣺find(first,last,val)�е��������������ҿ������������������ʹ����ҿ��������޷��Ƚϣ�
	//��[first,last);  listҲ����ʹ�ø��㷨find()���㷨�л����Կ���ʵ�ֵ�sort(v.begin(),v.end())������
	for (auto e : v)
	{
		cout << e << " ";
	}
	cout << endl;
	sort(v.begin(), v.end());
	for (auto e : v)
	{
		cout << e << " ";
	}
	cout << endl;
}

//������ʧЧ
void test_vector8()
{
	vector<int> v;
	v.push_back(1);
	v.push_back(2);
	v.push_back(3);
	v.push_back(4);
	v.push_back(5);
	//vector<int>::iterator it = v.begin();
	//��һ��ʧЧ��push_back,insert,resize,reserve�ȿ��ܻ����ݵĽӿڶ��ᵼ�µش���ʧЧ��
	//�������ݵ������ݣ������¿ռ䣬�ͷ��˾ɿռ䣬����������ָ�룩��Ȼָ��ɿռ䣬�ͻᵼ�µ�����ʧЧ
	//v.push_back(6);
	/*v.push_back(7);
	v.push_back(8);*/
	//while (it != v.end())
	//{
	//	cout << *it << " ";
	//	++it;
	//}
	//cout << endl;
	//�ڶ��ֵ�����ʧЧ��ɾ�����ݵ��µ�����ʧЧ
	//Ҫ��:ɾ�������е�����ż��
	vector<int>::iterator it = v.begin();
	while (it != v.end())
	{
		if (*it % 2 == 0)
		{
			//v.erase(it);  //����ĵ�����ʧЧ����Ϊ��ɾ��it֮��it��λ�þ�ʧЧ��
			it = v.erase(it);
	    } //vs�±������Ǳ������������ģ�gcc�¿��ܻᱨ����������л����ǻᵼ�½������
	           //������iterator erase();erase()�����и�����ֵ,���ķ���ֵ�Ǹ�������ָ��ָ��ɾ����itλ�õ���һ��λ��
		else    //���Կ�����itȥ����������һ��λ�ü����������С�
	    ++it;
	}                   
	cout << endl;
	for (auto e : v)
	{
		cout << e << " ";
	}
	cout << endl;
}
int main()
{
	//test_vector1();
	//test_vector2();
	//test_vector3();
	//test_vector4();
	//test_vector5();
	//test_vector6();
	//test_vector7();
	test_vector8();
	return 0;
} 
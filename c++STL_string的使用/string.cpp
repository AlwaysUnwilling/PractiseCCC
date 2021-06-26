#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
#include<assert.h>
#include<string>
using namespace std;
//
////��ģ���ʵ�����������[]������ operator[]();
//template<class T>
//class Vector
//{
//public:
//	Vector()
//		:_a(nullptr)
//		,_size(0)
//		,_capacity(0)
//	{}
//	~Vector()
//	{
//		delete[]_a;
//		_a = nullptr;
//		_size = _capacity = 0;
//	}
//	size_t Size()
//	{
//		return _size;
//	}
//	void PushBack(T x);
//	void PopBack();
//	/*T operator[](size_t i)
//	{
//		assert(i > 0)
//			return _a[i];
//	}*/
//	T& operator[](size_t i)          //�����[]������ operator[]();���ô�����ֵ�����޸ķ���ֵ�����ݡ�
//	{
//		assert(i < _size);
//		return _a[i];
//	}
//private:
//	T* _a;
//	size_t _size;
//	size_t _capacity;
//};
//
//template<class T>
//void Vector<T>:: PushBack(T x)
//{
//	if (_size == _capacity)
//	{
//		size_t _newcapacity = _capacity == 0 ? 2 : _capacity *= 2;
//		T* tmp = new T[_newcapacity];
//		if (_a)
//		{
//			memcpy(tmp, _a, sizeof(T) * _size);
//			delete[]_a;
//		}
//		_a = tmp;
//		_capacity = _newcapacity;
//	}
//	_a[_size] = x;
//	_size++;
//}
//template<class T>
//void Vector<T>::PopBack()
//{
//	assert(_size > 0);
//	_size--;
//}
//int main()
//{
//	Vector<int> v;
//	v.PushBack(1);
//	v.PushBack(2);
//	v.PushBack(3);
//	v.PushBack(4);
//	for (size_t i = 0; i < v.Size(); ++i)
//	{
//		cout << v[i] << " ";
//	}
//	cout << endl;
//	for (size_t i = 0; i < v.Size(); ++i)
//	{
//		v[i] *= 2;
//	}
//	for (size_t i = 0; i < v.Size(); ++i)
//	{
//		cout << v[i] << " ";
//	}
//	cout << endl;
//	cout << v.Size() << endl;
//	return 0;
//}

//npos Maximum value for size_t(public static member constant):size_t npos =-1;
//string��1.�ĸ����캯��
void test_string1()
{
	string s1; //default (1)	string();���ַ� --����
	string s2("hello");//from c-string (4)	string(const char* s);--����
	string s3("hello",2); //from sequence(5) string(const char* s, size_t n);--����
	string s4(s2);//copy (2)	string(const string & str);--��������
	string s5(s2,1,8); //substring(3) string(const string & str, size_t pos, size_t len = npos);
	string s6(s2,1,string::npos); 
	string s7(10,'a'); 
	cout << s1 << endl;
	cout << s2 << endl;
	cout << s3 << endl;
	cout << s4 << endl;
	cout << s5 << endl;
	cout << s6 << endl;
	cout << s7 << endl;
	s1 = s7; //��ֵ
	cout << s1<<endl;
}

int string2int(const string& nums) //�ַ���ת����
{                              ////const_iterator begin() const;ֻ�ܶ�������д
	int val = 0;
	////1.0   �÷�Χfor�����ַ���ת����
	//for (auto& ch : nums)
	//{
	//	val *= 10;
	//	val += (ch-'0');
	//}
	//2.1 ʹ�õ����������ַ���ת����   ����ת��
	//string::const_iterator it = nums.begin();
	//while (it != nums.end())
	//{
	//	val *= 10;
	//	val += (*it - '0');//�ַ�1��Ӧ�İ�˹��ֵ��49,�ַ�0�İ�˹��ֵ��48
	//	++it;
	//}
	//2.2 ʹ�õ����������ַ���ת����    ����ת��
	string::const_reverse_iterator rit = nums.rbegin();
	while (rit != nums.rend())
	{
		val *= 10;
		val += (*rit - '0');
		++rit;
	}
	return val;
}
//string��2.����
void test_string2()
{
	string s1("hello");
	s1 += ' ';    //string (1)	string& operator+= (const string & str); �ӵ�һ������
				  //c - string(2) string & operator+= (const char* s);�ӵ�һ���ַ���(��\0�������ַ���Ҳ��c��string)
				  //character(3)  string& operator+= (char c);	�ӵ�һ���ַ�
	s1 += "world";
	cout << s1 << endl;
	//1.forѭ������
	for (size_t i = 0; i < s1.size(); i++)  //��
	{
		cout << s1[i] << " ";
	}
	cout << endl;
	for (size_t i = 0; i < s1.size(); i++)  //д
	{
		s1[i] += 1;  //ÿ���ַ�����1��
	}
	for (size_t i = 0; i < s1.size(); i++)  //��
	{
		cout << s1[i] << " ";
	}
	cout << endl;
	//2.������ string::iterator
	//  2.1 ������� iterator begin();�ɶ���д  
	//auto it = s1.begin();//auto �Զ�ʶ��s1.begin()������
	string::iterator it = s1.begin(); //��������� it(������԰�it���Ϊһ��ָ�룬����������һ����ָ�룬����ָ��һ���Ķ���)
	while (it != s1.end())  //д
	{                      //�����s1.end()��string s1ĩβ���һ���ַ�����һ��λ�ã��������һ���ַ�
		*it -= 1;          //s1.begin()��string s1�ĵ�һ���ַ�
		++it;
	}
	it = s1.begin();
	while (it != s1.end())  //��
	{
		cout << *it << " ";
		++it;
	}
	cout << endl;
	/*2.2 ������� reverse_iterator rit = rbegin()*/
	string::reverse_iterator rit = s1.rbegin();
	while (rit != s1.rend())  //д
	{
		*rit += 1;
		++rit;
	}
	rit = s1.rbegin();
	while (rit != s1.rend())  //��
	{
		cout << *rit << " ";
		++rit;
	}
	cout << endl;
	
	//3.��Χfor����  (c++11֧��->ԭ���滻�ɵ�����)
	for (auto& ch : s1) //д  ��Χfor��������ָ�룬��Ҫдʱ����ʹ��������ʵ���޸Ķ���
	{
		ch -= 1;
	}
	for (auto ch : s1) //��
	{
		cout << ch << " ";
	}
	cout << endl;
}
void test_string3()
{
	string s1("hello world");
	string s2("hello");
	cout << s1.size() << endl;
	cout << s2.size() << endl;
	cout << s1.length() << endl;  //����ʹ�ã����Ϊsize�����Ƽ�ʹ�ã��Ƽ�ʹ��size
	cout << s2.length() << endl;

	cout << s1.max_size() << endl;  //���Ƽ�ʹ�ã�������
	cout << s2.max_size() << endl;

	cout << s1.capacity() << endl; //�Զ�����
	cout << s2.capacity() << endl;

	s1.clear();// ����ַ�������capacity���ᱻ�ͷ�
	cout << s1 << endl;
	cout << s1.capacity() << endl;
}
void test_string4()
{
	string s1;
	//s1.reserve(100);  //reserve(size_t n)  ���ֱ���ܹ���Ҫ���ٿռ��ֽ��ô˽ӿ����룬�Ͳ�����Ƶ����ȥ���ݡ�
	                 // ������Ҫ100�Ŀռ䣬���ǿ��������ռ䣨�ռ��������ʵ�ʿ��Ŀռ�����100)������һ���������࿪һ���ռ䣨����101��������'\0'��
	//s1.resize(100); //void resize (size_t n); void resize(size_t n, char c);
	               //resize(size_t n) ����������100�Ŀռ䣬����ʹ��s1��sizeҲ�����100�������ȫ�����'0'����
	//s1.resize(100, 'x');//void resize(size_t n, char c);//����100���ռ䣬���Ҵ����ַ���x��������ٲ����ַ�����뵽��x���ĺ��档
	size_t sz = s1.capacity();
	cout << "making s1 grow:"<<endl;
	for (size_t i = 0; i < 100; ++i)
	{
		s1.push_back('c');
		if (sz != s1.capacity())
		{
			sz = s1.capacity();
			cout << "capacity changed:" << sz << endl;
		}
	}
	string s2("hello world");//����s2���조hello world��
	s2.resize(5);//����resize(5);���s2��size��С��ʹ��s2��ֻʣǰ5���ַ�������capacity����䡣
	s2.resize(20,'x');//����resize(20);������ı�s2��sizeΪ20��ʵ�ʲ�һ����20����Ϊ��Ҫȡ���������һ�ʹ��s2.capacity()���ݣ����һ���s2ԭ�����ַ�����ȫ����Ϊ�ַ���x����
}
void test_string5()
{
	string s;
	s.push_back('x');  //���뵥���ַ�
	s.append("1111"); //�����ַ���   β��
	                  //string (1)	
	                     /* string& append(const string & str); 
						  string& append(const string & str, size_t subpos, size_t sublen);
                          string & append(const char* s);
	                      string& append(const char* s, size_t n);
                          string& append(size_t n, char c);
                          template <class InputIterator>
                          string& append(InputIterator first, InputIterator last);*/
	s += 'x';
	s += "eeeeee";
	cout << s << endl;

	s.insert(s.begin(), 0); //ͷ��
	cout << s << endl;
	s.insert(2, "2");  // string& insert (size_t pos, const string& str);
	
		                  /*string& insert(size_t pos, const string & str, size_t subpos, size_t sublen);

		                  string & insert(size_t pos, const char* s);

		                  string& insert(size_t pos, const char* s, size_t n);

		                  string& insert(size_t pos, size_t n, char c);
	                      void insert(iterator p, size_t n, char c);
	
		                  iterator insert(iterator p, char c);

		                  template <class InputIterator>
	                      void insert(iterator p, InputIterator first, InputIterator last);*/
	cout << s << endl;
	s.erase(2, 3); //�ӵڶ���λ��ɾ����3���ַ�
	              //string& erase(size_t pos = 0, size_t len = npos);
		         /*  iterator erase(iterator p);
		           iterator erase(iterator first, iterator last);*/
	cout << s << endl;
}
int main()
{
	//test_string1();
	//test_string2();
	/*string nums("12345");
	cout << string2int(nums) << endl;*/
	//test_string3();
	//test_string4();
	test_string5();
	return 0;
}
//�ܽ᣺��������������ʽ����������ͷ���  ���ԣ���ͨ���ɶ���д����const���Σ��ɶ�����д����
#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
#include<assert.h>
#include<string>
using namespace std;
//
////类模板简单实践，及运算符[]的重载 operator[]();
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
//	T& operator[](size_t i)          //运算符[]的重载 operator[]();引用传返回值可以修改返回值的数据。
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
//string：1.四个构造函数
void test_string1()
{
	string s1; //default (1)	string();空字符 --构造
	string s2("hello");//from c-string (4)	string(const char* s);--构造
	string s3("hello",2); //from sequence(5) string(const char* s, size_t n);--构造
	string s4(s2);//copy (2)	string(const string & str);--拷贝构造
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
	s1 = s7; //赋值
	cout << s1<<endl;
}

int string2int(const string& nums) //字符串转整型
{                              ////const_iterator begin() const;只能读，不能写
	int val = 0;
	////1.0   用范围for进行字符串转整型
	//for (auto& ch : nums)
	//{
	//	val *= 10;
	//	val += (ch-'0');
	//}
	//2.1 使用迭代器进行字符串转整型   正向转换
	//string::const_iterator it = nums.begin();
	//while (it != nums.end())
	//{
	//	val *= 10;
	//	val += (*it - '0');//字符1对应的阿斯玛值是49,字符0的阿斯玛值是48
	//	++it;
	//}
	//2.2 使用迭代器进行字符串转整型    反向转换
	string::const_reverse_iterator rit = nums.rbegin();
	while (rit != nums.rend())
	{
		val *= 10;
		val += (*rit - '0');
		++rit;
	}
	return val;
}
//string：2.遍历
void test_string2()
{
	string s1("hello");
	s1 += ' ';    //string (1)	string& operator+= (const string & str); 加等一个对象
				  //c - string(2) string & operator+= (const char* s);加等一个字符串(以\0结束的字符串也叫c—string)
				  //character(3)  string& operator+= (char c);	加等一个字符
	s1 += "world";
	cout << s1 << endl;
	//1.for循环遍历
	for (size_t i = 0; i < s1.size(); i++)  //读
	{
		cout << s1[i] << " ";
	}
	cout << endl;
	for (size_t i = 0; i < s1.size(); i++)  //写
	{
		s1[i] += 1;  //每个字符加了1；
	}
	for (size_t i = 0; i < s1.size(); i++)  //读
	{
		cout << s1[i] << " ";
	}
	cout << endl;
	//2.迭代器 string::iterator
	//  2.1 正序遍历 iterator begin();可读可写  
	//auto it = s1.begin();//auto 自动识别s1.begin()的类型
	string::iterator it = s1.begin(); //定义迭代器 it(这里可以把it理解为一个指针，但迭代器不一定是指针，是像指针一样的东西)
	while (it != s1.end())  //写
	{                      //这里的s1.end()是string s1末尾最后一个字符的下一个位置，不是最后一个字符
		*it -= 1;          //s1.begin()是string s1的第一个字符
		++it;
	}
	it = s1.begin();
	while (it != s1.end())  //读
	{
		cout << *it << " ";
		++it;
	}
	cout << endl;
	/*2.2 反向遍历 reverse_iterator rit = rbegin()*/
	string::reverse_iterator rit = s1.rbegin();
	while (rit != s1.rend())  //写
	{
		*rit += 1;
		++rit;
	}
	rit = s1.rbegin();
	while (rit != s1.rend())  //读
	{
		cout << *rit << " ";
		++rit;
	}
	cout << endl;
	
	//3.范围for遍历  (c++11支持->原理被替换成迭代器)
	for (auto& ch : s1) //写  范围for不能用于指针，需要写时可以使用引用来实现修改对象
	{
		ch -= 1;
	}
	for (auto ch : s1) //读
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
	cout << s1.length() << endl;  //早起使用，后改为size，不推荐使用，推荐使用size
	cout << s2.length() << endl;

	cout << s1.max_size() << endl;  //不推荐使用，无意义
	cout << s2.max_size() << endl;

	cout << s1.capacity() << endl; //自动增容
	cout << s2.capacity() << endl;

	s1.clear();// 清空字符，但是capacity不会被释放
	cout << s1 << endl;
	cout << s1.capacity() << endl;
}
void test_string4()
{
	string s1;
	//s1.reserve(100);  //reserve(size_t n)  如果直到总共需要多少空间字节用此接口申请，就不会再频繁的去增容。
	                 // 这里需要100的空间，都是开整数倍空间（空间对齐后可能实际开的空间会大于100)，而且一般编译器会多开一个空间（比如101）：留给'\0'。
	//s1.resize(100); //void resize (size_t n); void resize(size_t n, char c);
	               //resize(size_t n) 不仅开辟了100的空间，而且使得s1的size也变成了100（多余的全部填充'0'）。
	//s1.resize(100, 'x');//void resize(size_t n, char c);//开辟100个空间，并且存入字符‘x’；如果再插入字符会插入到‘x’的后面。
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
	string s2("hello world");//对象s2构造“hello world”
	s2.resize(5);//这里resize(5);会吧s2的size变小，使得s2中只剩前5个字符，容量capacity不会变。
	s2.resize(20,'x');//这里resize(20);不仅会改变s2的size为20（实际不一定是20，因为需要取整），而且会使得s2.capacity()扩容，并且会在s2原来的字符串后全部改为字符‘x’。
}
void test_string5()
{
	string s;
	s.push_back('x');  //插入单个字符
	s.append("1111"); //插入字符串   尾插
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

	s.insert(s.begin(), 0); //头插
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
	s.erase(2, 3); //从第二个位置删除掉3个字符
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
//总结：迭代器的四种形式：方向：正向和反向；  属性：普通（可读可写）和const修饰（可读不可写）。
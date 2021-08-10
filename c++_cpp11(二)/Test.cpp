#include<iostream>
#include<vector>
#include<list>
#include<string>
#include<map>
#include <initializer_list>
using namespace std;
//  右值引用应用：右值引用的移动构造和移动赋值,可以减少拷贝
class String
{
public:
	String(const char* str = "")
	{
		_str = new char[strlen(str) + 1];
		strcpy(_str, str);
	}

	// s2(s1)
	String(const String& s)
	{
		cout << "String(const String& s)-拷贝构造-效率低" << endl;

		_str = new char[strlen(s._str) + 1];
		strcpy(_str, s._str);
	}

	// s3(右值-将亡值)
	String(String&& s)
		:_str(nullptr)
	{
		// 传过来的是一个将亡值，反正你都要亡了，我的目的是跟你有一样大的空间，一样的值
		// 不如把你的控制和只给我
		cout << "String(String&& s)-移动构造-效率高" << endl;
		swap(_str, s._str);
	}

	// s3 = s4
	String& operator=(const String& s)
	{
		cout << "String& operator=(const String& s)-拷贝赋值-效率低" << endl;

		if (this != &s)
		{
			char* newstr = new char[strlen(s._str) + 1];
			strcpy(newstr, s._str);

			delete[] _str;
			_str = newstr;
		}

		return *this;
	}

	// s3 = 右值-将亡值
	String& operator=(String&& s)
	{
		cout << "String& operator=(String&& s)-移动赋值-效率高" << endl;
		swap(_str, s._str);

		return *this;
	}


	~String()
	{
		delete[] _str;
	}

	// s1 + s2
	String operator+(const String& s2)
	{
		String ret(*this);
		//ret.append(s2);

		return ret;  // 返回的是右值
	}

	// s1 += s2
	String& operator+=(const String& s2)
	{
		//this->append(s2);
		return *this; // 返回是左值
	}

private:
	char* _str;
};

//String f(const char* str)
//{
//	String tmp(str);
//	return tmp; // 这里返回实际是拷贝tmp的临时对象
//}

//int main()
//{
//	String s1("左值");
//	String s2(s1);                      // 参数是左值
//	String s3(f("右值-将亡值"));        // 参数是右值-将亡值(传递给你用，用完我就析构了)
//	//String s4(move(s1));
//
//	String s5("左值");
//	s5 = s1;
//	s5 = f("右值-将亡值");
//
//	return 0;
//}

////////////////////////////////////////////////////////////////////////////////
// 右值引用应用：当传值返回值，返回是右值，结合前面学的移动构造和移动赋值，可以拷贝拷贝
class Solution1 {
public:
	vector<string> letterCombinations(string digits) {
		vector<string> v;

		return v;
	}
};

class Solution2 {
public:
	// 核心思想：找出杨辉三角的规律，发现每一行头尾都是1，中间第[j]个数等于上一行[j-1]+[j]
	vector<vector<int>> generate(int numRows) {
		vector<vector<int>> vv;
		// 先开辟杨辉三角的空间
		vv.resize(numRows);
		// ...

		return vv;
	}
};

int x1()
{
	String s1("s1");
	String s2("s2");

	String s3 = s1 += s2; // 拷贝构造
	String s4 = s1 + s2;  // 移动构造

	// 现实中不可避免存在传值返回的场景，传值返回的拷贝返回对象的临时对象。
	// 如果vector只实现参数为const左值引用深拷贝，那么下面的代价就很大
	// vector(const vector<T>& v)->深拷贝

	// 但是如果vector实现了参数右值引用的移动拷贝，那么这里效率就会很高
	// vector(vector<T>&& v) ->移动拷贝
	// 结论：右值引用本身没太多意义，右值引用的实现了移动构造和移动赋值
	// 那么面对接收函数传值返回对象(右值)等等场景，可以提高效率
	vector<string> v = Solution1().letterCombinations("abcd");
	vector<vector<int>> vv = Solution2().generate(5);

	return 0;
}

//////////////////////////////////////////////////////////////////////////////
//右值引用去做函数的参数,减少拷贝

//std::vector::push_back
//void push_back(const value_type& val);
//void push_back(value_type&& val);
//
//std::list::push_back
//void push_back(const value_type& val);
//void push_back(value_type&& val);
//
//std::set::insert
//pair<iterator, bool> insert(const value_type& val);
//pair<iterator, bool> insert(value_type&& val);

//std::vector::emplace_back
//template <class... Args>
//void emplace_back(Args&&... args);   // 模板的可变参数 （了解）
// 网上有人说：emplace版本表push和insert高效。这句话不准确，没有深入去分析。

// ... 其他容器也插入数据结构也基本都是两个重载实现，一个左值引用，一个右值引用
int x2()
{
	vector<string> v;
	string s1("左值");
	string s2("左值");

	int val = 1234;

	// push_back中调用的是string的拷贝构造
	v.push_back(move(s2));             // void push_back(const value_type& val);

	// push_back中调用的是string的移动构造
	v.push_back("右值");         //void push_back(value_type&& val);
	v.push_back(to_string(val)); // void push_back(value_type&& val);

	v.emplace_back(s1); // v.emplace_back(move(s1)); 
	v.emplace_back("右值");

	vector<pair<string, string>> vp;
	vp.push_back(make_pair("右值", "右值"));

	pair<string, string> kv("左值", "左值");
	vp.push_back(kv);

	vp.emplace_back(make_pair("右值", "右值"));
	vp.emplace_back(kv);
	vp.emplace_back("右值", "右值"); // 体现emplace_back模板可变参数特点的地方

	return 0;
}

// 总结
// 右值引用做参数和作返回值减少拷贝的本质是利用了移动构造和移动赋值
// 左值引用和右值引用本质的作用都是减少拷贝，右值引用本质可以认为是弥补左值引用不足的地方, 他们两相辅相成

// 左值引用：解决的是传参过程中和返回值过程中的拷贝
// 做参数：void push(T x) -> void push(const T& x)  解决的是传参过程中减少拷贝
// 做返回值：T f2() -> T& f2()  解决的返回值过程中的拷贝
// ps:但是要注意这里有限制，如果返回对象出了作用域不在了就不能用传引用, 这个左值引用无法解决，等待C++11右值引用解决

// 右值引用：解决的是传参后，push/insert函数内部将对象移动到容器空间上的问题.
// + 传值返回接收返回值的拷贝
// 做参数： void push(T&& x)  解决的push内部不再使用拷贝构造x到容器空间上，而是移动构造过去
// 做返回值：T f2();  解决的外面调用接收f2()返回对象的拷贝，T ret = f2(),这里就是右值引用的移动构造，减少了拷贝

void Fun(int& x) { cout << "lvalue ref" << endl; }
void Fun(const int& x) { cout << "const lvalue ref" << endl; }
void Fun(int&& x) { cout << "rvalue ref" << endl; }
void Fun(const int&& x) { cout << "const rvalue ref" << endl; }

/////////////////////////////////////////
//完美转发:
template<typename T>
void PerfectForward(T&& t)
{
	// 右值引用会第二次之后的参数传递过程中右值属性丢失,下一层调用会全部识别为左值
	// 完美转发解决
	Fun(std::forward<T>(t));
}

int x3()
{
	PerfectForward(10); // rvalue ref

	int a;
	PerfectForward(a); // lvalue ref
	PerfectForward(std::move(a)); // rvalue ref

	const int b = 8;
	PerfectForward(b); // const lvalue ref
	PerfectForward(std::move(b)); // const rvalue ref

	string s0("hello");
	string s1 = to_string(11111);

	/*basic_string(_Myt&& _Right) _NOEXCEPT
		: _Mybase(_Right._Getal())
	{	// construct by moving _Right
		_Tidy();
		_Assign_rv(_STD forward<_Myt>(_Right));
	}*/

	return 0;
}
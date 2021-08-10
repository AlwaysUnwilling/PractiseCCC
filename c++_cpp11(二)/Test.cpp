#include<iostream>
#include<vector>
#include<list>
#include<string>
#include<map>
#include <initializer_list>
using namespace std;
//  ��ֵ����Ӧ�ã���ֵ���õ��ƶ�������ƶ���ֵ,���Լ��ٿ���
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
		cout << "String(const String& s)-��������-Ч�ʵ�" << endl;

		_str = new char[strlen(s._str) + 1];
		strcpy(_str, s._str);
	}

	// s3(��ֵ-����ֵ)
	String(String&& s)
		:_str(nullptr)
	{
		// ����������һ������ֵ�������㶼Ҫ���ˣ��ҵ�Ŀ���Ǹ�����һ����Ŀռ䣬һ����ֵ
		// �������Ŀ��ƺ�ֻ����
		cout << "String(String&& s)-�ƶ�����-Ч�ʸ�" << endl;
		swap(_str, s._str);
	}

	// s3 = s4
	String& operator=(const String& s)
	{
		cout << "String& operator=(const String& s)-������ֵ-Ч�ʵ�" << endl;

		if (this != &s)
		{
			char* newstr = new char[strlen(s._str) + 1];
			strcpy(newstr, s._str);

			delete[] _str;
			_str = newstr;
		}

		return *this;
	}

	// s3 = ��ֵ-����ֵ
	String& operator=(String&& s)
	{
		cout << "String& operator=(String&& s)-�ƶ���ֵ-Ч�ʸ�" << endl;
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

		return ret;  // ���ص�����ֵ
	}

	// s1 += s2
	String& operator+=(const String& s2)
	{
		//this->append(s2);
		return *this; // ��������ֵ
	}

private:
	char* _str;
};

//String f(const char* str)
//{
//	String tmp(str);
//	return tmp; // ���ﷵ��ʵ���ǿ���tmp����ʱ����
//}

//int main()
//{
//	String s1("��ֵ");
//	String s2(s1);                      // ��������ֵ
//	String s3(f("��ֵ-����ֵ"));        // ��������ֵ-����ֵ(���ݸ����ã������Ҿ�������)
//	//String s4(move(s1));
//
//	String s5("��ֵ");
//	s5 = s1;
//	s5 = f("��ֵ-����ֵ");
//
//	return 0;
//}

////////////////////////////////////////////////////////////////////////////////
// ��ֵ����Ӧ�ã�����ֵ����ֵ����������ֵ�����ǰ��ѧ���ƶ�������ƶ���ֵ�����Կ�������
class Solution1 {
public:
	vector<string> letterCombinations(string digits) {
		vector<string> v;

		return v;
	}
};

class Solution2 {
public:
	// ����˼�룺�ҳ�������ǵĹ��ɣ�����ÿһ��ͷβ����1���м��[j]����������һ��[j-1]+[j]
	vector<vector<int>> generate(int numRows) {
		vector<vector<int>> vv;
		// �ȿ���������ǵĿռ�
		vv.resize(numRows);
		// ...

		return vv;
	}
};

int x1()
{
	String s1("s1");
	String s2("s2");

	String s3 = s1 += s2; // ��������
	String s4 = s1 + s2;  // �ƶ�����

	// ��ʵ�в��ɱ�����ڴ�ֵ���صĳ�������ֵ���صĿ������ض������ʱ����
	// ���vectorֻʵ�ֲ���Ϊconst��ֵ�����������ô����Ĵ��۾ͺܴ�
	// vector(const vector<T>& v)->���

	// �������vectorʵ���˲�����ֵ���õ��ƶ���������ô����Ч�ʾͻ�ܸ�
	// vector(vector<T>&& v) ->�ƶ�����
	// ���ۣ���ֵ���ñ���û̫�����壬��ֵ���õ�ʵ�����ƶ�������ƶ���ֵ
	// ��ô��Խ��պ�����ֵ���ض���(��ֵ)�ȵȳ������������Ч��
	vector<string> v = Solution1().letterCombinations("abcd");
	vector<vector<int>> vv = Solution2().generate(5);

	return 0;
}

//////////////////////////////////////////////////////////////////////////////
//��ֵ����ȥ�������Ĳ���,���ٿ���

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
//void emplace_back(Args&&... args);   // ģ��Ŀɱ���� ���˽⣩
// ��������˵��emplace�汾��push��insert��Ч����仰��׼ȷ��û������ȥ������

// ... ��������Ҳ�������ݽṹҲ����������������ʵ�֣�һ����ֵ���ã�һ����ֵ����
int x2()
{
	vector<string> v;
	string s1("��ֵ");
	string s2("��ֵ");

	int val = 1234;

	// push_back�е��õ���string�Ŀ�������
	v.push_back(move(s2));             // void push_back(const value_type& val);

	// push_back�е��õ���string���ƶ�����
	v.push_back("��ֵ");         //void push_back(value_type&& val);
	v.push_back(to_string(val)); // void push_back(value_type&& val);

	v.emplace_back(s1); // v.emplace_back(move(s1)); 
	v.emplace_back("��ֵ");

	vector<pair<string, string>> vp;
	vp.push_back(make_pair("��ֵ", "��ֵ"));

	pair<string, string> kv("��ֵ", "��ֵ");
	vp.push_back(kv);

	vp.emplace_back(make_pair("��ֵ", "��ֵ"));
	vp.emplace_back(kv);
	vp.emplace_back("��ֵ", "��ֵ"); // ����emplace_backģ��ɱ�����ص�ĵط�

	return 0;
}

// �ܽ�
// ��ֵ������������������ֵ���ٿ����ı������������ƶ�������ƶ���ֵ
// ��ֵ���ú���ֵ���ñ��ʵ����ö��Ǽ��ٿ�������ֵ���ñ��ʿ�����Ϊ���ֲ���ֵ���ò���ĵط�, �������ศ���

// ��ֵ���ã�������Ǵ��ι����кͷ���ֵ�����еĿ���
// ��������void push(T x) -> void push(const T& x)  ������Ǵ��ι����м��ٿ���
// ������ֵ��T f2() -> T& f2()  ����ķ���ֵ�����еĿ���
// ps:����Ҫע�����������ƣ�������ض���������������˾Ͳ����ô�����, �����ֵ�����޷�������ȴ�C++11��ֵ���ý��

// ��ֵ���ã�������Ǵ��κ�push/insert�����ڲ��������ƶ��������ռ��ϵ�����.
// + ��ֵ���ؽ��շ���ֵ�Ŀ���
// �������� void push(T&& x)  �����push�ڲ�����ʹ�ÿ�������x�������ռ��ϣ������ƶ������ȥ
// ������ֵ��T f2();  �����������ý���f2()���ض���Ŀ�����T ret = f2(),���������ֵ���õ��ƶ����죬�����˿���

void Fun(int& x) { cout << "lvalue ref" << endl; }
void Fun(const int& x) { cout << "const lvalue ref" << endl; }
void Fun(int&& x) { cout << "rvalue ref" << endl; }
void Fun(const int&& x) { cout << "const rvalue ref" << endl; }

/////////////////////////////////////////
//����ת��:
template<typename T>
void PerfectForward(T&& t)
{
	// ��ֵ���û�ڶ���֮��Ĳ������ݹ�������ֵ���Զ�ʧ,��һ����û�ȫ��ʶ��Ϊ��ֵ
	// ����ת�����
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
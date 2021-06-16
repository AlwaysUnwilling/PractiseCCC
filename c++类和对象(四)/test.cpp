#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
using namespace std;
//class Date
//{
//public:
//	int GetMonthDay(int year, int month)
//	{
//		static int MonthDays[13] = { 0,31,28,31,30,31,30,31,31,30,31,30,31 };
//		if (month == 2 && ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0))
//			return 29;
//		else
//		{
//			return MonthDays[month];
//		}
//	}
//	Date(int year = 0, int month = 1, int day = 1)
//	{
//		if (year >= 0 && month >= 1 && month <= 12 && day >= 1 && day <= GetMonthDay(year, month))
//		{
//			_year = year;
//			_month = month;
//			_day = day;
//		}
//		else
//		{
//			cout << "非法日期" << endl;
//		}
//
//
//	}
//	Date(const Date& d)  //引用权限缩小使用const 避免d1被误改
//	{
//		_year = d._year;
//		_month = d._month;
//		_day = d._day;
//	}
//	inline bool operator==(const Date& d)
//	{
//		return _year == d._year     //这里相当于 d1._year==d.year  ==>  this->_year==d.year;
//			&& _month == d._month
//			&& _day == d._day;
//	}
//	bool operator<(const Date& d)
//	{
//		if (_year < d._year) return true;
//		else if (_year == d._year && _month < d._month) return true;
//		else if (_year == d._year && _month == d._month && _day < d._day) return true;
//		else return false;
//	}
//	bool operator>(const Date& d)
//	{
//		return !(*this <= d);
//	}
//	bool operator<=(const Date& d)
//	{
//		return *this < d || *this == d;//复用上面的来实现；
//	}
//	bool operator>=(const Date& d)
//	{
//		return !(*this < d);
//	}
//	bool operator!=(const Date& d)
//	{
//		return !(*this == d);
//	}
//	Date operator+(int day)
//	{
//		//Date ret = d2;
//		Date ret(*this);
//		ret._day += day;    // ==> ret.operator+=(int day);
//		return ret;
//	}
//	Date& operator+=(int day)
//	{
//		if (day < 0)
//		{
//			return *this -= -day;
//		}
//		_day += day;
//		while (_day > GetMonthDay(_year, _month))
//		{
//			_day -= GetMonthDay(_year, _month);
//			_month++;
//			if (_month == 13)
//			{
//				_year++;
//				_month = 1;
//			}
//		}
//		return *this;
//	}
//	Date& operator-=(int day)   //d3-=day
//	{
//		if (day < 0)
//		{
//			return *this += -day;
//		}
//		_day -= day;
//		while (_day <= 0)
//		{
//			_month--;
//			if (_month == 0)
//			{
//				_year--;
//				_month = 12;
//			}
//			_day += GetMonthDay(_year, _month);
//		}
//		return *this;
//	}
//	Date operator-(int day)    //d3-=10
//	{
//		Date ret = *this;
//		ret._day -= day;   // ==> ret.operator-=(int day);
//		return ret;
//	}
//	Date& operator--()   //--d3    默认是前置--
//	{
//		* this -= 1;
//		return *this;
//	}
//	Date operator--(int)  //后置--   为了构成重载函数
//	{
//		Date tmp = (*this);
//		*this -= 1;
//		return tmp;   //返回减之前的
//	}
//	Date& operator++()  //++ d3  //++d3    默认是前置++
//	{
//		* this += 1;
//		return *this;
//	}
//	Date operator++(int)  //d3++   后置++   为了构成重载函数
//	{
//		Date tmp = (*this);
//		*this += 1;
//		return tmp;   //返回加之前的
//	}
//	Date& operator=(const Date& d)  //在自定义类型传参和返回值时，在可以的情况下尽量使用引用。可以减少拷贝构造函数的调用
//	{
//		if (this != &d)  //防止自己给自己赋值  无意义
//		{
//			_year = d._year;
//			_month = d._month;
//			_day = d._day;
//		}
//		return *this;
//	}
//	int operator-(const Date& d)  //日期减日期
//	{
//		int flag = -1;//判断相减完后相差天数的正负
//		int n = 0;
//		Date smaller = *this;  //拷贝构造
//		Date Greater = d;
//		if (*this > d)
//		{
//			smaller = d;    //赋值 Date& operator=(const Date& d)
//			Greater = *this;
//			flag = 1;
//		}
//		while (smaller != Greater)
//		{
//			++smaller;
//			n++;
//		}
//		return n * flag;
//	}
//	void Print()const  //==》void Print(const Date* this)这样写完，之后*this就不能在修改成员变量了
//	{
//		cout << _year << "-" << _month << "-" << _day << endl;
//	}
//	const Date* operator&()const
//	{
//		return this;
//	}
//	Date* operator&()
//	{
//		return this;
//	}
//private:
//	int _year;
//	int _month;
//	int _day;
//};
//void f(const Date& d)//对象调用const成员函数
//{
//	d.Print();    //d.Print(const Date& d) 这里传参被const修饰，Print(Date* this)中*this的权限被放大
//	            // 所以无法编译，但是*this是隐藏的，所以Print函数应改为Print()const;这里const修饰的
//	            //是this指向的对象
//
//}
//int main()
//{
//	Date d(2021, 4, 18);
//	f(d);
//	return 0;
//}

//初始化链表： 构造函数体赋值:在创建对象时，编译器通过调用构造函数，给对象中各个成员变量一个合适的初始值；
            //构造函数体中的语句只能将其称作为赋初值，而不能称作初始化。因为初始化只能初始化一次，而构造函数体内可以多次赋值。
            /* 初始化列表：以一个冒号开始，接着是一个以逗号分隔的数据成员列表，每个"成员变量"后面跟一个放在括
             号中的初始值或表达式。注意：1. 每个成员变量在初始化列表中只能出现一次(初始化只能初始化一次)
                                       2. 类中包含以下成员，必须放在初始化列表位置进行初始化：引用成员变量、const成员变量、自定义类型成员(该类没有默认构造函数)*/
class A
{
public:
    A(int a)
        :_a(a)
    {}
private:
    int _a;
};
class B
{
public:
    B(int a, int ref)
        :_aobj(a)
        , _ref(ref)
        , _n(10)
    {}
private:
    A _aobj; // 没有默认构造函数
    int& _ref; // 引用
    const int _n; // const
};
//总结： 1.尽量使用初始化列表初始化，因为不管你是否使用初始化列表，对于自定义类型成员变量，一定会先使
//用初始化列表初始化。 2.成员变量在类中声明次序就是其在初始化列表中的初始化顺序，与其在初始化列表中的先后次序无关，只与成员变量被调用的顺序有关


//static成员
//设计出一个类A，可以计算出这个类总共产生了多少个对象？
//思路：对象都是构造函数或者拷贝构造函数产生的
//class A
//{
//public:
//	A()  //构造函数
//	{
//		n++;
//	}
//	A(const A& a)//拷贝构造函数
//	{
//		n++;
//	}
//	static int GetN()//static修饰的成员函数没有this指针，该函数中不能访问非静态区的成员(如：_a)
//	{
//		//_a = 10;//这里没有this指针  所以不能访问
//		return n;
//	}
//private:
//	static int n;//声明；这里被static修饰以后就不属于某个对象，是属于类的所有对象，属于这个类。
//	           //但会受到public和private权限限制  n在静态区
//	int _a;
//};
//int A::n = 0;//n的定义
//A f1(A a) //传值传参  拷贝构造
//{
//	return a;//传值返回 拷贝构造一个
//}
//int main()
//{
//	A a1;//构造
//	A a2;//构造
//	f1(a1);
//	f1(a2);
//	cout << a1.GetN() << endl;
//	cout << a2.GetN() << endl;
//	cout << A::GetN() << endl;
//	return 0;
//}

 //explicit  1.构造函数不仅可以构造与初始化对象，对于单个参数的构造函数，还具有类型转换的作用
class Date
{
public:
	Date(int year) //如果不使用explicit，d1 = 2019;可以执行。执行逻辑（隐式转换）：
		:_year(year)             // 生成临时Date tmp，调用构造函数把tmp初始化为2019即tmp(2019) ,然后d1=tmp进行拷贝构造
	{}

	//explicit Date(int year)  //被explicit修饰后会禁止d1 = 2019这个这种赋值编译
	//	:_year(year)
	//{}
    Date(int year,int month,int day)  //被explicit修饰后会禁止d1 = 2019这个这种赋值编译
		:_year(year)
		,_month(month)
		,_day(day)
	{}

private:
	int _year;
	int _month;
	int _day;
};
void TestDate()
{
	Date d1(2018);

	// 用一个整形变量给日期类型对象赋值
	// 实际编译器背后会用2019构造一个无名对象，最后用无名对象给d1对象进行赋值
    d1 = 2019;//可读性差  //如果不使用explicit，d1 = 2019;可以执行。执行逻辑（隐式转换）：
             // 生成临时Date tmp，调用构造函数把tmp初始化为2019即tmp(2019) ,然后d1=tmp进行拷贝构造  最后优化为构造函数
	        // 
	const Date& d1 = 2019;//因为临时变量具有常性，所以这里如果写成Date& d1=2019是不能编译的（权限放大），但是加上const修饰就可以用引用
                        //但是，此时就没有优化，这里引用的就是临时变量tmp(2019)
	Date d2 = { 2018,4,18 }; //c++11才支持此种操作，与单个参数构造函数类似，不想这种发生可以加explicit限制
}
int main()
{
	TestDate();
	return 0;
}



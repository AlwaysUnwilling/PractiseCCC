#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
#include<stdio.h>
using namespace std;
//类里面可以定义：1.成员变量；2.成员方法
//class Person
//{
//	void Print()//定义在类里面的函数默认是内联函数  若果申明在.h，定义在.cpp是就不再是内联函数
//	{
//
//	}
//	char _name[10];
//	int _age;
//};
//
//class Student //c++中class和struct都可以用来定义类。class默认访问限定是私有的，struct默认是公有的
//{
//public:
//	void ShowInfo()
//	{
//		cout << _name << endl;
//		cout << _age << endl;
//		cout << _stuid << endl;
//	}
//	int GerAge()
//	{
//		return _age;
//	}
////private://一半情况下成员变量都是比较隐私的，都会定义为私有或保护的
//	const char* _name;
//	int _age;
//	int _stuid;
//};
//int main()
//{
//	Student s1;
//	Student s2;
//	s1._name = "peter";
//	s1._age = 18;
//	s1._stuid = 1;
//	s1.ShowInfo();
//	return 0;
//}

//封装：1.将数据和方法放到一起；2.把向给你看的数据给你看（public），不想不给你看的封装起来（protected/private）
//class Stack
//{
//public:
//	void Push(int x);
//	void Pop();
//	bool Empty();
//private:
//	int* _a;
//	int _size;
//	int _capacity;
//};
////没有成员变量的类的大小是1，而不是0：开一个字节的空间不是为了存数据，而是为了占位
//
//class Date
//{
//public:
//	void Init(int year,int month,int day)//void Init(Date* this,int year,int month,int day)
//	{
//		_year = year;
//		_month = month;
//		_day = day;
//	}
//	void Print()//void Print(Date* this)  这里不需要指针是因为，编译器自动添加了指向Date的类指针this
//	{
//		cout << _year << "-"<<_month << "-"<<_day << endl;
//		cout << this->_year << "-" << this->_month << "-" << this->_day << endl;//这里可以这样写
//	}
//private:
//	int _year;
//	int _month;
//	int _day;
//};
//int main()
//{
//	Date d1;
//	d1.Init(2021, 06, 13);//d1.Init(&d1,2021, 06, 13)
//	d1.Print();  //	d1.Print(&d1)
//	return 0;
//}
//面试：1.this指针存在进程地址空间的哪个区域： 存在栈上的，因为它是一个形参（ps：vs下在ecx这个寄存器来传递）
//      2.下面p->PrintA（）和p->Show（）,运行会发生什么？：
//        成员函数存在公共代码段，所以p->Show（）这里虽然this指针是NULL，但是this指针没有去访问成员对象
//class A
//{
//public:
//	void PrintA()
//	{
//		cout << _a << endl;//这里相当于cout <<this-> _a << endl 这里的this指针已经是NULL，它再访问成员_a会崩溃
//	}
//	void Show()
//	{
//		cout << "Show()" << endl;
//	}
//private:
//	int _a;
//};
//int main()
//{
//	A* p = NULL;
//	p->PrintA();//运行这里程序会崩溃
//	p->Show();//这里运行程序正常；
//	return 0;
//}

//构造函数：函数名和类名相同；可以构成重载；实例化时自动调用
//         如果我们没有显示定义构造函数，编译器会自动生成无参默认构造函数：
//              1.针对内置类型成员变量不做处理；
//              2.针对自定义类型成员变量，调用它的构造函数进行初始化
//         #一旦用户显示了构造函数，系统就不会生成默认构造函数（无参不会生成）


//class Time
//{
//public:
//	Time()                         //构造函数（进行初始化）
//	{
//		_hour = 0;
//		_minute = 0;
//		_second = 0;
//	}
//private:
//	int _hour;
//	int _minute;
//	int _second;
//};
//class Date
//{
//public:
//	//Date(int year, int month, int day) //构造函数（进行初始化）
//	//{
//	//	_year = year;
//	//	_month = month;
//	//	_day = day;
//	//}
//	//Date()                         //构造函数（进行初始化）
//	//{
//	//	_year = 2021;
//	//	_month = 4;
//	//	_day = 18;
//	//}
//
//	//更好的解决方法->缺省函数
//	Date(int year=0, int month=1, int day=1)
//	{
//		_year = year;
//		_month = month;
//		_day = day;
//	}
//	void Print()
//	{
//		cout << _year << "-" << _month << "-" << _day << endl;
//	}
//private:
//	int _year;
//	int _month;
//	int _day;
//	Time _t;   
//};
//int main()
//{
//	Date d1(2021,6,13);//自动调用Date(int year, int month, int day)
//	d1.Print();
//
//	Date d2;//Date d2无参调用构造函数时不能Date d2()这样写。调用无参直接Date d2;就好了
//	d2.Print();//自动调用Date()
//	return 0;
//}

//析构函数：对象生命周期到了后自动调用  （~类型名），完成清理工作；但不是对对象的销毁，是对对象开辟的空间（malloc出来的）等进行销毁
class Stack
{
public:
	Stack(int n = 10)
	{
		_a = (int*)malloc(sizeof(int) * n);
		if (_a == nullptr)
		{
			cout << "mallco fail" << endl;
			exit(-1);
		}
		cout << "Stack(int n = 10) malloc:" << _a << endl;
		_size = 0;
		_capacity = 10;
	}
	~Stack()//析构函数
	{
		if (_a)
		{
			free(_a);
			cout << "~Stack() malloc:" << _a << endl;
            _a= nullptr;
			_size = _capacity = 0;
		}
	}
private:
	int* _a;
	int _size;
	int _capacity;
};
int main()
{
	//调用时先调用st1,然后st2；析构时先析构st2，然后st1
	Stack st1; 
	Stack st2;

	return 0;
}


#include<iostream>
#include<string>
using namespace std;

//继承的定义格式：
//派生类（子类） 继承方式  基类（父类）
//class Student :public Person
//{
//public:
//	int _stuid;
//};
class Person
{
public:
	void Print()
	{
		cout << "name:" << _name << endl;
		cout << "age:" << _age << endl;
	 }
protected:
	string _name = "peter"; //姓名
	int _age = 18;  //年龄
};
//继承后父类的Person的成员（成员函数和成员变量）都会编程之类的一部分。这里体现了Student和Teacher复用了Person的成员
class Student:public Person
{
protected:
	int _stuid;//学号
};
class Teacher :public Person
{
protected:
	int _jobid; //工号
};

int main()
{
	Student s;
	Teacher t;
	s.Print();
	t.Print();
	return 0;
}
////继承关系和访问限定符
//继承方式：1.public继承；2.protected继承；3.private继承；
//访问限定符：1.public访问；2.protected访问；3.private访问；

////继承基类成员访问方式
//1. 基类private成员在派生类中无论以什么方式继承都是不可见的。这里的不可见是指基类的私有成员还是
//被继承到了派生类对象中，但是语法上限制派生类对象不管在类里面还是类外面都不能去访问它。
//2. 基类private成员在派生类中是不能被访问，如果基类成员不想在类外直接被访问，但需要在派生类中能
//访问，就定义为protected。可以看出保护成员限定符是因继承才出现的。
//3<重点>.基类的私有成员在子类都是不可见。基类的其他成员在子类的访问方式 == Min(成员在基类的访问限定符，继承方式)，public > protected > private。
//4. 使用关键字class时默认的继承方式是private，使用struct时默认的继承方式是public，不过最好显示的
//写出继承方式。
//5. 在实际运用中一般使用都是public继承，几乎很少使用protetced / private继承，也不提倡使用
//protetced / private继承，因为protetced / private继承下来的成员都只能在派生类的类里面使用，实际中
//扩展维护性不强。
class Person
{
public:
	void Print()
	{
		cout << _name << endl;
	}
protected:
	string _name; // 姓名
private:
	int _age; // 年龄
};
//class Student : protected Person
//class Student : private Person
class Student : public Person
{
public:
	void f()
	{
		cout << _stunum << endl;
		//cout << _age << endl;//_age是基类的私有成员，继承后子类不可用
	}
protected:
	int _stunum; // 学号
};

int main()
{
	Student s;
	return 0;
}

//基类和派生类对象赋值转换:
//1.派生类对象 可以赋值给 基类的对象 / 基类的指针 / 基类的引用。这里有个形象的说法叫切片或者切
//割。寓意把派生类中父类那部分切来赋值过去。
//2.基类对象不能赋值给派生类对象
//3.基类的指针可以通过强制类型转换赋值给派生类的指针。但是必须是基类的指针是指向派生类对象时才
//是安全的。这里基类如果是多态类型，可以使用RTTI(Run - Time Type Information)的dynamic_cast 来
//进行识别后进行安全转换。
class Person
{
protected:
	string _name; // 姓名
	string _sex; // 性别
	int _age; // 年龄
};
class Student : public Person
{
public:
	int _No; // 学号
};
void Test()
{
	Student sobj;
	// 1.子类对象可以赋值给父类对象/指针/引用
	Person pobj = sobj;
	Person* pp = &sobj;
	Person& rp = sobj;

	//2.基类对象不能赋值给派生类对象
	//sobj = pobj;

	// 3.基类的指针可以通过强制类型转换赋值给派生类的指针
	pp = &sobj;
		Student * ps1 = (Student*)pp; // 这种情况转换时可以的。
	ps1->_No = 10;

	pp = &pobj;
	Student* ps2 = (Student*)pp; // 这种情况转换时虽然可以，但是会存在越界访问的问题
	ps2->_No = 10;
}

//继承的作用域：
//1. 在继承体系中基类和派生类都有独立的作用域。
//2. 子类和父类中有同名成员，子类成员将屏蔽父类对同名成员的直接访问，这种情况叫隐藏，也叫重定
//义。（在子类成员函数中，可以使用 基类::基类成员 显示访问）
//3. 需要注意的是如果是成员函数的隐藏，只需要函数名相同就构成隐藏。
//4. 注意在实际中在继承体系里面最好不要定义同名的成员。
// Student的_num和Person的_num构成隐藏关系，可以看出这样代码虽然能跑，但是非常容易混淆
class Person
{
protected:
	string _name = "小李子"; // 姓名
	int _num = 111; // 身份证号
};
class Student : public Person
{
public:
	void Print()
	{
		cout << " 姓名:" << _name << endl;
		cout << " 身份证号:" << Person::_num << endl;  //在子类成员函数中，可以使用 基类::基类成员 显示访问
		cout << " 学号:" << _num << endl;
	}
protected:
	int _num = 999; // 学号
};
void Test()
{
	Student s1;
	s1.Print();
};

// B中的fun和A中的fun不是构成重载，因为不是在同一作用域
// B中的fun和A中的fun构成隐藏，成员函数满足函数名相同就构成隐藏。
class A {
public:
	void fun()
	{
		cout << "func()" << endl;
	}
};
class B : public A {
public:
	void fun(int i)   //子类成员函数与子类继承下来的基类成员函数fun() 函数名相同(尽管参数不同)就构成了隐藏或者叫重定义
	{                 //在子类成员函数中，可以使用 基类::基类成员 显示访问
		A::fun();
		cout << "func(int i)->" << i << endl;
	}
};
void Test()
{
	B b;
	b.fun(10);
};
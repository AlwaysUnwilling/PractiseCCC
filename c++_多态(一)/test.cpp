#include<iostream>
using namespace std;

//多态的概念:通俗来说，就是多种形态，具体点就是去完成某个行为，当不同的对象去完成时会产生出不同的状态。
//多态的构成条件:多态是在不同继承关系的类对象，去调用同一函数，产生了不同的行为。
//构成多态还有两个条件：1.必须通过基类的指针或者引用调用虚函数
//                      2. 被调用的函数必须是虚函数，且派生类必须对基类的虚函数进行重写
//虚函数：虚函数：即被virtual修饰的类成员函数。
class Person {
public:
	virtual void BuyTicket() { cout << "买票-全价" << endl; }
};
//虚函数的重写：虚函数的重写(覆盖)：派生类中有一个跟基类完全相同的虚函数(即派生类虚函数与基类虚函数的返回值类型、函数名字、参数列表完全相同)，称子类的虚函数重写了基类的虚函数
class Person {
public:
	virtual void BuyTicket() { cout << "买票-全价" << endl; }
};
class Student : public Person {
public:
	virtual void BuyTicket() { cout << "买票-半价" << endl; }
	/*注意：在重写基类虚函数时，派生类的虚函数在不加virtual关键字时，虽然也可以构成重写(因为继
承后基类的虚函数被继承下来了在派生类依旧保持虚函数属性),但是该种写法不是很规范，不建议这样使用
*/
/*void BuyTicket() { cout << "买票-半价" << endl; }*/
};
void Func(Person& p)
{
	p.BuyTicket();
}
int main()
{
	Person ps;
	Student st;

	Func(ps);
	Func(st);
	return 0;
}

//虚函数重写的两个例外：
//1. 协变(基类与派生类虚函数返回值类型不同)
//派生类重写基类虚函数时，与基类虚函数返回值类型不同。即基类虚函数返回基类对象的指针或者引
//用，派生类虚函数返回派生类对象的指针或者引用时，称为协变。
class A {};
class B : public A {};
class Person {
public:
	virtual Person& f1()
	{
		return *this;
	}
	virtual A* f() 
	{
		return new A; 
	}
};
class Student : public Person {
public:
	virtual Student& f1()
	{
		return *this;
	}
	virtual B* f()
	{ 
		return new B;   //这里的B和A必须是继承关系
	}
};
//2. 析构函数的重写(基类与派生类析构函数的名字不同)
//如果基类的析构函数为虚函数，此时派生类析构函数只要定义，无论是否加virtual关键字，都与基类的
//析构函数构成重写，虽然基类与派生类析构函数名字不同。虽然函数名不相同，看起来违背了重写的规
//则，其实不然，这里可以理解为编译器对析构函数的名称做了特殊处理，编译后析构函数的名称统一处
//理成destructor。
class Person {
public:
	virtual ~Person() { cout << "~Person()" << endl; }
};
class Student : public Person {
public:
	virtual ~Student() { cout << "~Student()" << endl; }
};
// 只有派生类Student的析构函数重写了Person的析构函数，下面的delete对象调用析构函数，才能构成多态，才能保证p1和p2指向的对象正确的调用析构函数。
int main()
{
	Person* p1 = new Person;
	Person* p2 = new Student;
	delete p1;
	delete p2;  //这里如果没有把析构函数定义为虚函数，而student类中恰有需要释放的资源，那么会造成内存泄漏。
	return 0;
}

// C++11 override 和 final
//final 修饰虚函数，表示该虚函数不能再被继承
class Car
{
public:
	virtual void Drive() final {}
};
class Benz :public Car
{
public:
	virtual void Drive() { cout << "Benz-舒适" << endl; }
};
//override : 检查派生类虚函数是否重写了基类某个虚函数，如果没有重写编译报错。
class Car {
public:
	virtual void Drive() {}
};
class Benz :public Car {
public:
	virtual void Drive() override { cout << "Benz-舒适" << endl; }
};


//重载、覆盖(重写)、隐藏(重定义)的对比:
//重载：俩个函数在同一作用域，且函数名相同，参数不同。
//重写（覆盖）：俩个函数分别在基类和派生类的作用域中；函数名、参数、返回值均相同（协变例外）；俩个函数必须是虚函数。
//重定义（隐藏）：俩个函数分别在基类和派生类的作用域中；函数名相同；俩个基类和派生类的同名函数不构成重写就是重定义。

//抽象类
//在虚函数的后面写上 = 0 ，则这个函数为纯虚函数。包含纯虚函数的类叫做抽象类（也叫接口类），抽象类
//不能实例化出对象。派生类继承后也不能实例化出对象，只有重写纯虚函数，派生类才能实例化出对象。纯
//虚函数规范了派生类必须重写，另外纯虚函数更体现出了接口继承。
class Car
{
public:
	virtual void Drive() = 0;
};
class Benz :public Car
{
public:
	virtual void Drive()
	{
		cout << "Benz-舒适" << endl;
	}
};
class BMW :public Car
{
public:
	virtual void Drive()
	{
		cout << "BMW-操控" << endl;
	}
};
void Test()
{
	Car* pBenz = new Benz;
	pBenz->Drive();
	Car* pBMW = new BMW;
	pBMW->Drive();
}

//接口继承和实现继承:普通函数的继承是一种实现继承，派生类继承了基类函数，可以使用函数，继承的是函数的实现。虚函数的
//继承是一种接口继承，派生类继承的是基类虚函数的接口，目的是为了重写，达成多态，继承的是接口。所
//以如果不实现多态，不要把函数定义成虚函数。
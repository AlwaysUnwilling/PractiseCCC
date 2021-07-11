#include<iostream>

using namespace std;

//笔试面试题：
//1. 什么是菱形继承？菱形继承的问题是什么？
//2. 什么是菱形虚拟继承？如何解决数据冗余和二义性的
//3. 继承和组合的区别?什么时候用继承？什么时候用组合？

//class Person
//{
//public:
//	Person(const char* name = "Peter")
//		:_name(name)
//	{
//		cout << "Person()" << endl;
//	}
//	Person(const Person& p)
//		:_name(p._name)
//	{
//		cout << "Person(const Person& p)" << endl;
//	}
//	Person& operator=(const Person& p)
//	{
//		cout << "Person& operator=(const Person& p)" << endl;
//		if (this != &p)
//		{
//			_name = p._name;
//		}
//		return *this;
//	}
//	~Person()
//	{
//		cout << "~Person()" << endl;
//	}
//protected:
//	string _name;
//};
//
////派生类的六个默认成员函数
//class Student :public Person
//{
//public:
//	Student(const char* name, int studid)   // 构造函数(带参)
//		//:_name(name)      // 基类的成员必须由基类的构造函数来初始化，派生类里不能自己构造初识化。
//		:Person(name)       //如果派生类里面向要显示构造基类的成员可以调用基类的构造函数来显示
//		, _studid(studid)
//	{
//		cout << "Student()" << endl;
//	}
//	Student(const Student& s)   //拷贝构造
//		//:_name(s._name)      //派生类的拷贝构造函数中有基类的成员，必须要调用基类的构造函数完成，而不能自己去实现。
//		:Person(s)        //派生类的拷贝构造函数中需要显示基类的成员的拷贝构造。
//		,_studid(s._studid)
//	{
//		cout << "Student(const Student& s)" << endl;
//	}
//	Student& operator=(const Student& s)   //赋值
//	{
//		if (this != &s)
//		{
//			//operator=(s);//调用基类的赋值  (this->operator=(s))  ，这里的s被赋值给Person;但是基类的operator=()和派生类的operator=()是同名函数，所以
//			//            //基类的同名函数在派生类中被影藏了，如果在派生类中要调用基类的同名函数需要制定作用域，否则这里会出现栈溢出（operator=(s)会在这里递归调用派生类的operator=(s)）
//			Person::operator=(s);   //正确的调用基类的赋值函数 :this->Person::operator=(s)
//			_studid = s._studid;
//		}
//		cout << "Student& operator=(const Student& s)" << endl;
//		return *this;
//	}
//	~Student()
//	{
//		//Person::~Person();  //基类的析构函数和派生类的析构函数随便表面开来函数名不同，但是他俩也是同名函数构成了隐藏，因为编译器把他俩的名字统一处理成destructor(跟多态有关)
//		               //所以也需要指定作用域
//		//而在派生类中的析构函数不需要调用基类的析构函数，因为派生类的析构函数完成后，会自动调用基类的析构函数。即：不需要显示基类的析构函数的调用
//		cout << "~Student()" << endl;
//	}
//protected:
//	int _studid;
//};
//int main()
//{
//	Student s1("Tom",1);
//	//Student s2(s1);
//	//Student s3("Jack",3);
//	//s1 = s3;
//	return 0;
//}

//如何设计一个不能被继承的类？
//把基类的构造函数私有化，它的派生类就不能继承基类。因为派生类继承了基类后，基类的私有成员会不可见，不能被派生类使用。而派生类创建对象后必须调用基类的构造函数，基类的构造函数私有
//后，派生类不能调用，派生类的对象就不能生成。
//class A
//{
//private:
//	A()
//	{}
//};
//class B:public A
//{};
//int main()
//{
//	//B b;  //不能生成对象
//	return 0;
//}

//继承与友元:友元关系不能继承，也就是说基类友元不能访问派生类（子类）私有和保护成员；如果需要访问，可以在派生类中再增加一次友元关系即可访问

//class Student;
//class Person
//{
//public:
//	friend void Display(const Person& p, const Student& s);
//protected:
//	string _name; // 姓名
//};
//class Student : public Person
//{
//	friend void Display(const Person& p, const Student& s);
//protected:
//	int _stuNum; // 学号
//};
//void Display(const Person& p, const Student& s) {
//	cout << p._name << endl;
//	cout << s._stuNum << endl;
//}
//void main()
//{
//	Person p;
//	Student s;
//	Display(p, s);
//}

//继承与静态成员:基类定义了static静态成员，则整个继承体系里面只有一个这样的成员。无论派生出多少个子类，都只有一个static成员实例 。
//class Person
//{
//public:
//	Person()
//	{
//		++_count;
//	}
//	string _name;
//	static int _count;
//};
//int Person::_count = 0;
//class Student:public Person
//{
//protected:
//	int _stuNum;
//};
//int main()
//{
//	Person p;
//	Student s;
//	p._name = "jack";
//	s._name = "rose";
//
//	p._count = 1;
//	s._count = 2;
//
//	Person::_count++;
//	cout << p._name << endl;
//	cout << s._name << endl;
//	cout << p._count << endl;
//	cout << s._count << endl;
//	return 0;
//}

//********<重点>  复杂的菱形继承及菱形模拟继承 
//菱形继承的问题：造成数据的冗余和二义性。解决方法：制定类域去访问。
//单继承：一个子类只有一个直接父类时称这个继承关系为单继承
//多继承：一个子类有两个或以上直接父类时称这个继承关系为多继承
//菱形继承：菱形继承是多继承的一种特殊情况
//菱形继承的问题：从下面的对象成员模型构造，可以看出菱形继承有数据冗余和二义性的问题。在Assistant
//的对象中Person成员会有两份。
//class Person
//{
//public:
//	string _name; // 姓名
//};
//class Student : public Person
//{
//protected:
//	int _num; //学号
//};
//class Teacher : public Person
//{
//protected:
//	int _id; // 职工编号
//};
//class Assistant : public Student, public Teacher
//{
//protected:
//	string _majorCourse; // 主修课程
//};
//void Test()
//{
//	// 这样会有二义性无法明确知道访问的是哪一个
//	Assistant a;
//	//a._name = "peter";
//
//	// 需要显示指定访问哪个父类的成员可以解决二义性问题，但是数据冗余问题无法解决
//	a.Student::_name = "xxx";
//	a.Teacher::_name = "yyy";
//}
////虚拟继承可以解决菱形继承的二义性和数据冗余的问题。如上面的继承关系，在Student和Teacher的继承
////Person时使用虚拟继承(virtual)，即可解决问题。需要注意的是：虚拟继承不要再其他地方去使用。
//class Person
//{
//public:
//	string _name; // 姓名
//};
//class Student : virtual public Person
//{
//protected:
//	int _num; //学号
//};
//class Teacher : virtual public Person
//{
//protected:
//	int _id; // 职工编号
//};
//class Assistant : public Student, public Teacher
//{
//protected:
//	string _majorCourse; // 主修课程
//};
//void Test()
//{
//	Assistant a;
//	a._name = "peter";
//}

//面试题：c++有哪些缺陷：多继承就是其中之一。多继承可能导致菱形继承，要解决菱形继承引入了虚继承，虚继承的底层结构的对象模型非常复杂，且有一定的效率损失。

//虚继承是如何实现的呢？
//对象模型（对象再内存中是怎么存的）
//菱形继承：
//class A
//{
//public:
//	int _a;
//};
//class B :public A
//{
//public:
//	int _b;
//};
//class C :public A
//{
//public:
//	int _c;
//};
//class D :public B, public C
//{
//public:
//	int _d;
//};
//int main()
//{
//	D d;
//	cout << sizeof(d) << endl;  //d继承了B和C，B和C分别继承了A，A的大小是4，B和C的大小分别是8，d的大小就是8+8+4=20;
//	d.B::_a = 1;
//	d.C::_a = 2;
//	d._b = 3;
//	d._c = 4;
//	d._d = 5;
//	return 0;
//}
//菱形虚继承：这里是通过了B和C的两个指针，指向的一张表。这两个指针叫虚基表指针，这两个表叫虚基表。虚基表中存的偏移量。通过偏移量可以找到下面的A。
class A
{
public:
	int _a;
};
class B :virtual public A
{
public:
	int _b;
};
class C :virtual public A
{
public:
	int _c;
};
class D :public B, public C
{
public:
	int _d;
};
int main()
{
	D d;
	cout << sizeof(d) << endl;  //虚拟继承中，d继承了B和C，B和C分别继承了A，但是B和C并没有存储A中成员_a,而是存储了_a相对它俩的偏移量地址（指针）。8+8+4++4=24；
	                          //而A中的对象存在公共部分
	d.B::_a = 1;
	d.C::_a = 2;
	d._b = 3;
	d._c = 4;
	d._d = 5;
	return 0;
}

//继承的总结和反思：继承和组合
//1.public继承是一种is - a的关系。也就是说每个派生类对象都是一个基类对象。
//2.组合是一种has - a的关系。假设B组合了A，每个B对象中都有一个A对象。
//3.优先使用对象组合，而不是类继承 。
//4.继承允许你根据基类的实现来定义派生类的实现。这种通过生成派生类的复用通常被称为白箱复用
//(white - box reuse)。术语“白箱”是相对可视性而言：在继承方式中，基类的内部细节对子类可见 。
//继承一定程度破坏了基类的封装，基类的改变，对派生类有很大的影响。派生类和基类间的依赖关
//系很强，耦合度高。
//5.对象组合是类继承之外的另一种复用选择。新的更复杂的功能可以通过组装或组合对象来获得。对
//象组合要求被组合的对象具有良好定义的接口。这种复用风格被称为黑箱复用(black - box reuse)，
//因为对象的内部细节是不可见的。对象只以“黑箱”的形式出现。 组合类之间没有很强的依赖关系，
//耦合度低。优先使用对象组合有助于你保持每个类被封装。
//6.实际尽量多去用组合。组合的耦合度低，代码维护性好。不过继承也有用武之地的，有些关系就适
//合继承那就用继承，另外要实现多态，也必须要继承。类之间的关系可以用继承，可以用组合，就
//用组合。
 

// Car和BMW Car和Benz构成is-a的关系
class Car {
protected:
	string _colour = "白色"; // 颜色
	string _num = "陕ABIT00"; // 车牌号
};
class BMW : public Car {
public:
	void Drive() { cout << "好开-操控" << endl; }
};

class Benz : public Car {
public:
	void Drive() { cout << "好坐-舒适" << endl; }
};

// Tire和Car构成has-a的关系

class Tire {
protected:
	string _brand = "Michelin"; // 品牌
	size_t _size = 17; // 尺寸

};

class Car {
protected:
	string _colour = "白色"; // 颜色
	string _num = "陕ABIT00"; // 车牌号
	Tire _t; // 轮胎
};
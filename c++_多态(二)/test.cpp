#include<iostream>
using namespace std;

//多态的原理
//虚函数表
// 这里常考一道笔试题：sizeof(Base)是多少？
class Base
{
public:
	virtual void Func1()
	{
		cout << "Func1()" << endl;
	}
private:
	int _b = 1;
};
//通过观察测试我们发现b对象是8bytes，除了_b成员，还多一个__vfptr放在对象的前面(注意有些平台可能会
//	放到对象的最后面，这个跟平台有关)，对象中的这个指针我们叫做虚函数表指针(v代表virtual，f代表
//		function)。一个含有虚函数的类中都至少都有一个虚函数表指针，因为虚函数的地址要被放到虚函数表中，
//	虚函数表也简称虚表。
// 针对上面的代码我们做出以下改造
// 1.我们增加一个派生类Derive去继承Base
// 2.Derive中重写Func1
// 3.Base再增加一个虚函数Func2和一个普通函数Func3
class Base
{
public:
	virtual void Func1()
	{
		cout << "Base::Func1()" << endl;
	}
	virtual void Func2()
	{
		cout << "Base::Func2()" << endl;
	}
	void Func3()
	{
		cout << "Base::Func3()" << endl;
	}
private:
	int _b = 1;
};
class Derive : public Base
{
public:
	virtual void Func1()
	{
		cout << "Derive::Func1()" << endl;
	}
private:
	int _d = 2;
};
int main()
{
	Base b;
	Derive d;
	return 0;
}
//通过观察和测试，我们发现了以下几点问题：
//1. 派生类对象d中也有一个虚表指针，d对象由两部分构成，一部分是父类继承下来的成员，虚表指针也就
//是存在部分的另一部分是自己的成员。
//2. 基类b对象和派生类d对象虚表是不一样的，这里我们发现Func1完成了重写，所以d的虚表中存的是重
//写的Derive::Func1，所以虚函数的重写也叫作覆盖，覆盖就是指虚表中虚函数的覆盖。重写是语法的
//叫法，覆盖是原理层的叫法。
//3. 另外Func2继承下来后是虚函数，所以放进了虚表，Func3也继承下来了，但是不是虚函数，所以不会
//放进虚表。
//4. 虚函数表本质是一个存虚函数指针的指针数组，这个数组最后面放了一个nullptr。
//5. 总结一下派生类的虚表生成：a.先将基类中的虚表内容拷贝一份到派生类虚表中 b.如果派生类重写了基
//类中某个虚函数，用派生类自己的虚函数覆盖虚表中基类的虚函数 c.派生类自己新增加的虚函数按其在
//派生类中的声明次序增加到派生类虚表的最后。
//6. 这里还有一个童鞋们很容易混淆的问题：虚函数存在哪的？虚表存在哪的？ 答：虚函数存在虚表，虚表
//存在对象中。注意上面的回答的错的。但是很多童鞋都是这样深以为然的。注意虚表存的是虚函数指
//针，不是虚函数，虚函数和普通函数一样的，都是存在代码段的，只是他的指针又存到了虚表中。另外
//对象中存的不是虚表，存的是虚表指针。

//多态的原理:满足多态多态以后的函数调用，不是在编译时确定的，是运行起来以后到对象中去找的。不满足多态函数调用时是编译时确定好的。
class Person {
public:
	virtual void BuyTicket() { cout << "买票-全价" << endl; }
};
class Student : public Person {
public:
	virtual void BuyTicket() { cout << "买票-半价" << endl; }
};
void Func(Person& p) {
	p.BuyTicket();
}
int main()
{
	Person Mike;
	Func(Mike);

	Student Johnson;
	Func(Johnson);
	return 0;
}

// 动态绑定与静态绑定:1. 静态绑定又称为前期绑定(早绑定)，在程序编译期间确定了程序的行为，也称为静态多态，比如：函数重载
//2. 动态绑定又称后期绑定(晚绑定)，是在程序运行期间，根据具体拿到的类型确定程序的具体行为，调用
//具体的函数，也称为动态多态。

//单继承中的虚函数表
class Base {
public:
	virtual void func1() { cout << "Base::func1" << endl; }
	virtual void func2() { cout << "Base::func2" << endl; }
private:
	int a;
};
class Derive :public Base {
public:
	virtual void func1() { cout << "Derive::func1" << endl; }
	virtual void func3() { cout << "Derive::func3" << endl; }
	virtual void func4() { cout << "Derive::func4" << endl; }
private:
	int b;
};


typedef void(*VFPTR) ();
void PrintVTable(VFPTR vTable[])
{
	// 依次取虚表中的虚函数指针打印并调用。调用就可以看出存的是哪个函数
	cout << " 虚表地址>" << vTable << endl;
	for (int i = 0; vTable[i] != nullptr; ++i)
	{
		printf(" 第%d个虚函数地址 :0X%x,->", i, vTable[i]);
		VFPTR f = vTable[i];
		f();
	}
	cout << endl;
}
int main()
{
	Base b;
	Derive d;
	// 思路：取出b、d对象的头4bytes，就是虚表的指针，前面我们说了虚函数表本质是一个存虚函数指针的指针数组，这个数组最后面放了一个nullptr
		// 1.先取b的地址，强转成一个int*的指针
		// 2.再解引用取值，就取到了b对象头4bytes的值，这个值就是指向虚表的指针
		// 3.再强转成VFPTR*，因为虚表就是一个存VFPTR类型(虚函数指针类型)的数组。
		// 4.虚表指针传递给PrintVTable进行打印虚表
		// 5.需要说明的是这个打印虚表的代码经常会崩溃，因为编译器有时对虚表的处理不干净，虚表最后面没有放nullptr，导致越界，这是编译器的问题。我们只需要点目录栏的 - 生成 - 清理解决方案，再编译就好了。
		VFPTR * vTableb = (VFPTR*)(*(int*)&b);
	PrintVTable(vTableb);
	VFPTR* vTabled = (VFPTR*)(*(int*)&d);
	PrintVTable(vTabled);
	return 0;
}

//多继承中的虚函数表: 多继承派生类的末尾写的函数放在第一个继承基类部分的虚函数表中。
class Base1 {
public:
	virtual void func1() { cout << "Base1::func1" << endl; }
	virtual void func2() { cout << "Base1::func2" << endl; }
private:
	int b1;
};
class Base2 {
public:
	virtual void func1() { cout << "Base2::func1" << endl; }
	virtual void func2() { cout << "Base2::func2" << endl; }
private:
	int b2;
};
class Derive : public Base1, public Base2 {
public:
	virtual void func1() { cout << "Derive::func1" << endl; }
	virtual void func3() { cout << "Derive::func3" << endl; }
private:
	int d1;
};
typedef void(*VFPTR) ();
void PrintVTable(VFPTR vTable[])
{
	cout << " 虚表地址>" << vTable << endl;
	for (int i = 0; vTable[i] != nullptr; ++i)
	{
		printf(" 第%d个虚函数地址 :0X%x,->", i, vTable[i]);
		VFPTR f = vTable[i];
		f();
	}
	cout << endl;
}
int main()
{
	Derive d;
	VFPTR* vTableb1 = (VFPTR*)(*(int*)&d);
	PrintVTable(vTableb1);
	VFPTR* vTableb2 = (VFPTR*)(*(int*)((char*)&d + sizeof(Base1)));
	PrintVTable(vTableb2);
	return 0;
}
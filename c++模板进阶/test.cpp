#include<iostream>
using namespace std;


//非类型模板参数
//template<class T,int N>    //实际中，费类型的模板参数的类型一般都是int，这些也可以char/short/long/long long/
//class A                   //但是自定义类型不可以用作费类型的模板参数的类型（string,vector等）
//{
//public:
//
//private:
//	T _a[N];
//};
//int main()
//{
//	A<int,10> a1;
//	A<int, 100> a2;
//	
//	return 0;
//}

//模板的特化
//1.函数模板的特化
//template<class T>
//bool IsEqual(T& left, T& right)
//{
//	return left == right;
//}
////模板的特化:针对某些类型的特殊化处理
//template<>
//bool IsEqual<char*>(char*& left, char*& right)
//{
//	//return left == right;
//	return strcmp(left, right) == 0;
//}
////2.类模板的特化
//template<class T1,class T2>
//class Data
//{
//public:
//	Data()
//	{
//		cout << "Data<T1,T2>" << endl;
//	}
//private:
//	T1 _d1;
//	T2 _d2;
//};
////类模板特化
//template<>
//class Data<int, char>   //全特化
//{
//public:
//	Data()
//	{
//		cout << "全特化：Data<int,char>" << endl;
//	}
//private:
//};
//template<class T1>
//class Data<T1, int>   //偏特化
//{
//public:
//	Data()
//	{
//		cout << "偏特化：Data<int,char>" << endl;
//	}
//private:
//};
//template<class T1,class T2>
//class Data<T1*, T2*>   //偏特化   指针
//{
//public:
//	Data()
//	{
//		cout << "偏特化：Data<T1*,T2*>" << endl;
//	}
//private:
//};
//template<class T1, class T2>
//class Data<T1&, T2&>   //偏特化   引用
//{
//public:
//	Data()
//	{
//		cout << "偏特化：Data<T1&,T2&>" << endl;
//	}
//private:
//};
//int main()
//{ 
//	int a = 0;
//	int b = 1;
//	cout << IsEqual(a, b) << endl;
//
//	const char* p1 = "hello";  //如果需要比较字符串，如果用上面的模板函数是无法实现正确的比较的，因为T类型是char*，这里实际比较的是
//	const char* p2 = "world";  // 俩个指针的大小，而我们需要的是比较指针指向的字符串的大小。
//	cout << IsEqual(p1, p2) << endl;
//
//	Data<int, double> d1;
//	Data<int, char> d2;
//	Data<string, int> d3;
//	Data<char*, int*> d4;
//	Data<int&, short&> d5;
//	return 0;
//}
//模板的分离编译
//分离编译：项目工程中一半将函数或者类的申明放到.h，将函数或者类的定义放到.cpp中。
//为什么要分离编译？方便查看和维护。

#include"Func.h"

int main()
{
	Func1();//Func1()可以编译通过执行。
	Func2(10);//Func2(10)会报链接失败
	Func2(10.11);
	return 0;
}
//同样是分离编译，普通函数/类可以，函数类模板/类模板为什么不行？
//因为在链接时Func.o文件中被没有对函数模板的类型T进行实例化，没有实例化就不能生成Func2()的地址（Func.cpp和test.cpp在链接之前分别走的是各自的单线，直到链接时才会合到一起）。
//Func.h         Func.cpp     test.cpp
//1、预处理：展开头文件（模板）、宏替换、条件编译、去掉注释
//生成：         Func.i        test.i   （Func.h 已经被展开）
//2、编译：检查语法，生成汇编代码
//生成：         Func.s        test.s
//3、汇编：将汇编代码转换成二进制机器码
//生成：         Func.o        test.o
//4、链接：将目标文件合到一起，编译时Func1()和Func2()函数有声明，所以编译通过了。链接时要去Func.o中找Func1()和Func2()
//         的地址，这里Func1()找到了，Func2()没有找到，所以报了链接错误。
//生成：a.out


// 如何解决模板的分离编译问题？
//1.显示实例化(放在Func.cpp即放在模板定义的地方):不推荐使用，累赘，不方便。
template
void Func2<int>(const int& x);
template
void Func2<double>(const double& x);
//2.不要分离编译模板(牺牲了可维护性)：模板的定义和声明都放在.h文件中。

//总结：模板的优点：1.模板复用了代码，节省资源，更快的迭代开发，c++的标准模板库（STL）因此而产生；
//                  2.增强了代码的灵活性
//      模板的缺点：1.模板会袋子代码膨胀问题，也会袋子编译时间边长；
//                  2.出现模板编译错误时，错误信息非常凌乱，不易定位错误。
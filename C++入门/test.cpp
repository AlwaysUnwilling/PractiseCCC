#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
//using namespace std;//c++所有东西都是放到std命名空间中
//
//int main()
//{
//	int a = 10;
//	cout << "a="<<a<< endl;
//	std:: cout << "a=" << a << std::endl;
//	return 0;
//}

//在工程中推荐使用部分展开使用
//using std::cout;//从屏幕输出
//using std::endl;
//using std::cin;//从屏幕输入
//int main()
//{
//	int i=1;
//	int a = 10;
//	double d = 1.1;
//	cout << "a=" << a << endl;
//	std::cout << "a=" << a << std::endl;
//	cout << "a=" << a << endl << "d=" << d << endl;//可以自动识别类型
//	cin >> i;
//	//std::cin >> i;
//	cout << "i=" << i << endl;
//	return 0;
//}

using namespace std;
//void Func(int a = 0)//缺省参数
//{
//	cout << a << endl;
//}
//int main()
//{
//	Func();//缺省函数
//	Func(1);
//	return 0;
//}

//void Func1(int a = 0, int b = 10,int c=20)//半缺省参数：必须从右往左连续缺省
//{
//	cout << a <<" "<< b <<" "<< c <<endl;
//}
//void Func2(int a , int b , int c = 20)
//{
//	cout << a << " " << b << " " << c << endl;
//}
//int main()
//{
//	Func1();//全缺省
//	Func1(1);
//	Func1(1,2);
//	Func1(1,2,3);
//	Func2(7,8);//调用时，如果要传参，必须从左往右依次传参，不能空缺
//	Func2(7,8,9);
//	return 0;
//}

//重载函数:函数名相同，参数不同（类型 or 个数 or 顺序不同）
//对返回值没有要求
//int Add(int left, int right)
//{
//	return right + left;
//}
//double Add(double left, double right)
//{
//	return right + left;
//}
//long Add(long left, long right)
//{
//	return right + left;
//}
//int Add(int left, int right,int mid)
//{
//	return left + right + mid;
//}
//double Add(int left, double right, int mid)
//{
//	return left + right + mid;
//}
//double Add(double left, int right, int mid)
//{
//	return left + right + mid;
//}
//int main()
//{
//	Add(2, 3);
//	Add(2.0, 3.1);
//	Add(2L, 3L);
//	Add(2, 3,4);
//	Add(2, 3.2,5);
//	Add(2.1, 3,6);
//	return 0;
//}
//函数重载面试问题：1.什么是函数重载；2.c++是如何支持函数重载的？为什么c语言不支持？
//回答2.：在链接时c语言遇到相同的函数名不会生成相应的.o文件（因为c语言中函数名在机器码中保存的就是函数名本身）；
//        而c++中，函数名在机器码中会修饰它的函数名（不仅仅保留函数名，还会保留函数的参数类型等相关信息），从而可以区分
//        开相同的函数名。<函数名修饰规则>

//引用
//int main()
//{
//	int a = 1;
//	int& ra = a;//ra是a的引用，即a的别名。对a的别名或者自己改变，那么a的值就会改变
//	            //引用特性：1.在定义时必须初始化。（int& ra；是错误的）
//
//	int d = 2;
//	ra = d;  //这里是将d的值赋值给ra，这会导致a的值也会变为2
//	return 0;
//}
int main()
{
	int a = 1;
	int& b = a;//b的类型仍然是int
	const int c = 2;
	//int& rc = c;//这里就会编译不通过，因为：c被const修饰变成了只可以读，rc是int类型是可读可写的。
	const int& rc = c;//这样就可以编译了

	int d = 3;
    int& e = d;
	const int& f = d;//这样也是可以的：c是可读可写的，f变成别名只读
	//总结：引用取别名时，权限可以缩小，但不能放大

	int i = 5;
	double db = i;//隐士类型转换
	//double& ri = i;//这样引用是错误的
	const double& ri = i;//这样是可以的：这里ri引用的其实不是i本身，首先i变为一个double的一个临时变量，临时变量具有常性。
	return 0;
}
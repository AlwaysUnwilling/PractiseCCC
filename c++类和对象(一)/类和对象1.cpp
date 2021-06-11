#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
using namespace std;

//引用做参数
void swap(int* p1, int* p2)//参数传地址
{
	int tmp = *p1;
	*p1 = *p2;
	*p2 = tmp;
}
//参数传引用：优点：1.输出型参数；2.提高效率
void swap1(int& r1, int& r2)  //此处是c++中交换参数的写法：r1和r2分别是a和b的别名，交换r1和r2即交换了a和b
{                             //此处的r1和r2并没有开辟空间
	int tmp = r1;
	r1 = r2;
	r2 = tmp;
}
int Count1()
{
	static int n = 0;
	n++;
	return n;//传值返回：相当于返回了n的拷贝，会产生临时空间
}
int& Count2()
{
	static int n = 0;
	n++;
	return n;//传引用返回：相当于返回了n的别名，不会产生空间
	        //如果n变成局部变量，引用返回时是不安全的
}
//int& Count3(int a,int b)   //c的定义只会执行一次：1.
//{
//	static int c = 0;//静态变量只有在第一次定义时才会执行，后续再调用该函数时，此句代码不会在执行；
//	c = a + b;
//	return c;//传引用返回：相当于返回了n的别名，不会产生空间
//			//如果n变成局部变量，引用返回时是不安全的
//}
int& Count3(int a, int b)//c的定义只会执行一次：2.
{
	static int c = a+b;//静态变量只有在第一次定义时才会执行，后续再调用该函数时，此句代码不会在执行；
	                   //如果改为这样，c的值就只是第一次执行c的定义时的值；后续调用该函数不会修改c的值；
	return c;//传引用返回：相当于返回了n的别名，不会产生空间
			//如果n变成局部变量，引用返回时是不安全的
}
int main()
{
	int a = 0;
	int b = 1;
	swap(&a, &b);
	cout << "a=" << a << endl << "b=" << b << endl;
	swap1(a, b);
	cout << "a=" << a << endl << "b=" << b << endl;
	//int& r1 = Count1();//这里编译不通过：因为Count1()函数是传值返回，产生的临时变量具有常性（只读不可写）,int& r1是可读可写权限放大了
	const int& r1 = Count1();//加上const修饰就可以
	int& r2 = Count2();//这里可以编译：因为Count2()函数是传引用返回，返回的是n的别名，即返回的就是n本身，所以r2也是n的别名；

	int& r3 = Count3(4,5);
	cout << "r3=" << r3 << endl;

	int& r4 = Count3(4, 6);
	Count3(7, 8);
	cout << "r4=" << r4 << endl;
	return 0;
}
//总结：一个函数如果要使用引用返回，返回变量除了这个函数的作用域还存在，就可以 使用引用返回，否则就不安全。 
//     那么函数使用引用返回的优点是：可以少创建拷贝一个临时对象，可以提高效率；还有一个优点...
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
//int main()
//{
//	int a = 0;
//	int b = 1;
//	swap(&a, &b);
//	cout << "a=" << a << endl << "b=" << b << endl;
//	swap1(a, b);
//	cout << "a=" << a << endl << "b=" << b << endl;
//	//int& r1 = Count1();//这里编译不通过：因为Count1()函数是传值返回，产生的临时变量具有常性（只读不可写）,int& r1是可读可写权限放大了
//	const int& r1 = Count1();//加上const修饰就可以
//	int& r2 = Count2();//这里可以编译：因为Count2()函数是传引用返回，返回的是n的别名，即返回的就是n本身，所以r2也是n的别名；
//
//	int& r3 = Count3(4,5);
//	cout << "r3=" << r3 << endl;
//
//	int& r4 = Count3(4, 6);
//	Count3(7, 8);
//	cout << "r4=" << r4 << endl;
//	return 0;
//}
//总结：一个函数如果要使用引用返回，返回变量除了这个函数的作用域还存在，就可以 使用引用返回，否则就不安全。 
//     那么函数使用引用返回的优点是：可以少创建拷贝一个临时对象，可以提高效率；还有一个优点


//指针和引用的区别：1.语法概念上引用不需要开辟空间，指针需要开辟空间；
//                  2.引用需要初始化，指针没有要求；
//                  3.引用在初始化一个实体后，就不能再引用其他实体；而指针可以在任何时候指向任意一个同类型的实体；
//                  4.没有NULL引用，但有NULL指针；
//                  5.在sizeof中含义不同：引用结果是引用实体类型的大小；但指针始终是地址空间所占字节个数（4个字节或8个字节）；
//                  6.引用自加即引用实体+1；指针自加即指针向后偏移一个类型的大小；
//                  7.有多级指针，但没有多级引用；
//                  8.访问实体的方式不同。指针需要显示解引用，引用编译器自己处理；
//                  9.引用比指针使用起来相对安全些；

//int main()
//{
//	int a = 10;
//	int& b = a;  //语法概念上这里b（引用）不需要开空间，但是在底层实现时和指针实现方式相似
//	int* p = &a;//需要开空间
//	return 0;
//}

//内联函数:代码量少的小函数可以用；递归函数或代码量多的函数不建议用   
//         以空间换时间的做法
//         内联函数是申明和定义不能分离的（因为内敛函数没有地址，在调用的地方直接展开）
//         c++中内联函数是用来替代宏函数的  宏常量是用（const int N = 10）来替代的 <面试题>
int Add(int left, int right)
{
	return left + right;
}
inline void swap(int& x1, int& x2)
{
	int tmp = x1;
	x1 = x2;
	x2 = tmp;
}
//频繁调用swap（），调用函数需要建立栈帧，是有消耗的
//如何解决：c语言使用宏函数；c++使用内敛函数
//int main()
//{
//	int ret = Add(1, 2);
//	int a = 0, b = 2;
//	swap(a, b);
//	return 0;
//}

//auto：自动推导变量
//int main()
//{
//	int a = 0;
//	auto b = a;  //b的类型是根据a的类型推导出来的
//	int& c = a;
//	auto& d = a;
//
//	auto* e = &a;
//	auto f = &a;
//
//	cout << typeid(a).name() << endl;
//	cout << typeid(b).name() << endl;
//	cout << typeid(c).name() << endl;
//	cout << typeid(d).name() << endl;
//	cout << typeid(e).name() << endl;
//	cout << typeid(f).name() << endl;
//
//	////找同一行定义多个变量时，这些变量的类型必须相同，否则编译器会报错。因为编译器只对第一个类型进行推导，然后用推导出来的类型定义其他变量
//	//auto g = 1, h = 1.1;//编译错误
//	//auto i = 2, j = 3;//正确使用auto
//	return 0;
//}

///*1*/.//auto不能用来做函数的参数
//void testauto(auto a) {    //err
//
//}
//2.auto不能直接用来申明数组
//void testauto() {
//	int a[] = { 1,2,3 };
//	auto b[] = { 4,5,6 };//err
//}

//基于范围的for循环

void fun(int n)
{
	cout << "整型" << endl;
}
void fun(int* n)
{
	cout << "整型指针" << endl;
}
int main()
{
	int arr[] = { 1,2,3,4,5 };
	//要求将数组中的值乘2倍，再打印
	//c语言
	for (int i = 0; i < sizeof(arr) / sizeof(int); i++)
		arr[i] *= 2;
	for (int i = 0; i < sizeof(arr) / sizeof(int); i++)
		cout << arr[i] << " ";
	cout << endl;

	//c++->范围for特点：写起来简洁
	//for (auto e : arr)//这里是把arr数组中的每个值取出来*2赋值给e；实际数组的值并未改变；
	//	e *= 2;
	//for (auto e : arr)
	//	cout << e << " ";


	for (auto& e : arr)//这样就可以改变数组的值   但是范围for不能用于指针
		e *= 2;
	for (auto e : arr)
		cout << e << " ";
	cout << endl;

	//c++中的指针
	int* p1 = NULL;
	int* p2 = nullptr;//c++ 推荐的空指针
	fun(0);
	fun(NULL);//c++中的NULL实际是定义了个宏 #define NULL 0；字面量是0；
	fun(nullptr);//nullptr定义是(void*)0 是个指针
}

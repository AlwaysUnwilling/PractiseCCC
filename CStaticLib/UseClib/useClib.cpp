#include<iostream>

#pragma comment(lib,"../Debug/CStaticLib.lib")

// extern "C" int Clib_add(int, int);   如果使用的是C语言库函数声明时记得加extern "C"；
// extern "C" int Clib_sub(int, int);   因为C语言和C++的函数名命名规则不同
int Clib_sub(int, int);    
int Clib_add(int, int);
// TODO: 这是一个库函数示例
//C语言静态库的创建：1、创建静态库文件；2、添加库程序，源文件使用C文件
//C语言静态库的使用：库路径设置：可以使用pragma关键字设置 #pragma comment(lib,"../Debug/clib.lib")
int main()
{
	int sum = 0;
	int sub = 0;
	printf("sum=%d, sub=%d\n", Clib_add(5, 3), Clib_sub(5, 3));
	return 0;
}
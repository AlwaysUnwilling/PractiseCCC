#include<iostream>


//声明导出---隐士链接:导出来的时经过CPP换名后的函数名(经过了c++的函数命名规则修饰)
_declspec(dllimport) int Cdll_add(int, int);
_declspec(dllimport) int Cdll_sub(int, int);
_declspec(dllimport) int Cdll_mul(int, int);

#pragma comment(lib,"../Debug/DLL.lib")  //注意这里不能直接写成../Debug/DLL.dll。因为在windows中不允许链接器直接
										//到.dll中抓取函数地址,只能在.lib文件抓取信息（编号和动态库文件名.dll）。也就是说链接完成后
										//调用动态库函数的地方存的是该函数在动态库中的编号。

int main()
{
	int sum = Cdll_add(5, 3);
	int sub = Cdll_sub(5, 3);
	int mul = Cdll_mul(5, 3);
	
	std::cout << "sum = " << sum << std::endl;
	std::cout << "sub = " << sub << std::endl;
	std::cout << "mul = " << mul << std::endl;
	return 0;
}
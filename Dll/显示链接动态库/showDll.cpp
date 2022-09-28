#include<iostream>
#include<windows.h>

typedef int(*ADD)(int, int);
typedef int(*SUB)(int, int);
typedef int(*MUL)(int, int);



int main()
{
	HMODULE hDll = LoadLibrary(L"Dll.dll");          //HMODULE==HINSTANCE
	ADD myAdd=(ADD)GetProcAddress(hDll, "Cdll_add");  //要想写不被c++命名规则修饰后的函数名需要使用显示链接的方式导出动态库
	std::cout << myAdd(5, 4) << std::endl;				//即：模块定义文件.def
	SUB mySub = (SUB)GetProcAddress(hDll, "Cdll_sub");
	std::cout << mySub(5, 4) << std::endl;
	MUL myMul = (MUL)GetProcAddress(hDll, "Cdll_mul");
	std::cout << myMul(5, 4) << std::endl;
	return 0;
}


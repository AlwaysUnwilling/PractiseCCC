#include<windows.h>
#include<iostream>



typedef int(*ADD)(int, int);
typedef int(*SUB)(int, int);
typedef int(*MUL)(int, int);

int main()
{
	HINSTANCE hIns = LoadLibrary("Win32DLL.dll");
	std::cout << "hIns:" << hIns << std::endl;
// 	ADD myAdd=(ADD)GetProcAddress(hIns, "?CppDll_sum@@YAHHH@Z");
// 	SUB mySub= (SUB)GetProcAddress(hIns, "?CppDll_sub@@YAHHH@Z");
// 	MUL myMul= (MUL)GetProcAddress(hIns, "?CppDll_mul@@YAHHH@Z");
	ADD myAdd = (ADD)GetProcAddress(hIns, "CppDll_sum");
	SUB mySub = (SUB)GetProcAddress(hIns, "CppDll_sub");
	MUL myMul = (MUL)GetProcAddress(hIns, "CppDll_mul");

	int sum = myAdd(5, 4);
	int sub = mySub(5, 4);
	int mul = myMul(5, 4);
	std::cout << "sum=" << sum << ",sub=" << sub << ",mul=" << mul << std::endl;

	FreeLibrary(hIns);
	return 0;
}
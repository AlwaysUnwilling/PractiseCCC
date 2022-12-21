#include<iostream>


_declspec(dllimport)int CppDll_sum(int, int);
_declspec(dllimport)int CppDll_sub(int, int);
_declspec(dllimport)int CppDll_mul(int, int);

#pragma comment(lib,"../Debug/Win32Dll.lib")
int main()
{
	int sum = CppDll_sum(5, 4);
	int sub = CppDll_sub(5, 4);
	int mul = CppDll_mul(5, 4);

	std::cout << "sum=" << sum << ",sub=" << sub << ",mul=" << mul << std::endl;
	return 0;
}
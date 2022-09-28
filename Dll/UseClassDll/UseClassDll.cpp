#include<iostream>
#include"../ClassDll/myClassdll.h"

#pragma comment(lib,"../Debug/ClassDll.lib")

int main()
{
	CMath math;

	int sum = math.Add(5, 6);
	int sub = math.Sub(6, 5);
	std::cout << "sum= " << sum << std::endl;
	std::cout << "sub= " << sub << std::endl;
	return 0;
}
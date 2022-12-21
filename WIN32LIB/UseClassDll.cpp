#include<iostream>
#include"../ClassDll/ClassDll.h"

#pragma comment(lib,"../Debug/ClassDll.lib")

int main()
{
	CMath math;
	int sum = math.Add(5, 4);
	int sub = math.Sub(5, 4);

	std::cout << "sum=" << sum << ",sub=" << sub << std::endl;
	return 0;
}
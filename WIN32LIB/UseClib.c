#include<stdio.h>

#pragma comment(lib,"../Debug/Win32StaticLib.lib")

//int Clib_add(int, int);
//int Clib_sub(int, int);

int main()
{
	int sum, sub;
	sum = Clib_add(5, 3);
	sub = Clib_sub(5, 3);
	printf("sum=%d,sub=%d\n", sum, sub);
	return 0;
}
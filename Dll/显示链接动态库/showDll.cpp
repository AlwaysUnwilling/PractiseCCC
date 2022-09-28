#include<iostream>
#include<windows.h>

typedef int(*ADD)(int, int);
typedef int(*SUB)(int, int);
typedef int(*MUL)(int, int);



int main()
{
	HMODULE hDll = LoadLibrary(L"Dll.dll");          //HMODULE==HINSTANCE
	ADD myAdd=(ADD)GetProcAddress(hDll, "Cdll_add");  //Ҫ��д����c++�����������κ�ĺ�������Ҫʹ����ʾ���ӵķ�ʽ������̬��
	std::cout << myAdd(5, 4) << std::endl;				//����ģ�鶨���ļ�.def
	SUB mySub = (SUB)GetProcAddress(hDll, "Cdll_sub");
	std::cout << mySub(5, 4) << std::endl;
	MUL myMul = (MUL)GetProcAddress(hDll, "Cdll_mul");
	std::cout << myMul(5, 4) << std::endl;
	return 0;
}


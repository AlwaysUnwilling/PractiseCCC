#include<iostream>


//��������---��ʿ����:��������ʱ����CPP������ĺ�����(������c++�ĺ���������������)
_declspec(dllimport) int Cdll_add(int, int);
_declspec(dllimport) int Cdll_sub(int, int);
_declspec(dllimport) int Cdll_mul(int, int);

#pragma comment(lib,"../Debug/DLL.lib")  //ע�����ﲻ��ֱ��д��../Debug/DLL.dll����Ϊ��windows�в�����������ֱ��
										//��.dll��ץȡ������ַ,ֻ����.lib�ļ�ץȡ��Ϣ����źͶ�̬���ļ���.dll����Ҳ����˵������ɺ�
										//���ö�̬�⺯���ĵط�����Ǹú����ڶ�̬���еı�š�

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
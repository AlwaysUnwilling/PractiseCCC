#include<iostream>

#pragma comment(lib,"../Debug/CStaticLib.lib")

// extern "C" int Clib_add(int, int);   ���ʹ�õ���C���Կ⺯������ʱ�ǵü�extern "C"��
// extern "C" int Clib_sub(int, int);   ��ΪC���Ժ�C++�ĺ�������������ͬ
int Clib_sub(int, int);    
int Clib_add(int, int);
// TODO: ����һ���⺯��ʾ��
//C���Ծ�̬��Ĵ�����1��������̬���ļ���2����ӿ����Դ�ļ�ʹ��C�ļ�
//C���Ծ�̬���ʹ�ã���·�����ã�����ʹ��pragma�ؼ������� #pragma comment(lib,"../Debug/clib.lib")
int main()
{
	int sum = 0;
	int sub = 0;
	printf("sum=%d, sub=%d\n", Clib_add(5, 3), Clib_sub(5, 3));
	return 0;
}
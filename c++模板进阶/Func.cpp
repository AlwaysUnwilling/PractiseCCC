#include"Func.h"
void Func1()
{
	cout << "Func1()" << endl;
}
template<class T>
void Func2(const T& x)
{
	cout << "Func2(const T& x)" << endl;
}
//ģ�������봦����ʾʵ����
template
void Func2<int>(const int& x);
template
void Func2<double>(const double& x);

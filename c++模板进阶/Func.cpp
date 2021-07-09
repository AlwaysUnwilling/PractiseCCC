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
//模板分离编译处理：显示实例化
template
void Func2<int>(const int& x);
template
void Func2<double>(const double& x);

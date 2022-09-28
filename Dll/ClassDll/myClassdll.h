#pragma once
#include"pch.h"
/*
动态库中封装类
1、在类名称前增加_declspec(dllexport)定义 eg.            //一般使用申明导出，不推荐使用模块定义文件.def方法导出类(虽然可以),因为：
	class _declspec(dllexport)CMath					//一般我们导出动态库中的类，其实是想把类中的成员函数的相对地址导出去，在动态库中封装的类，
	{												//其实就是个类型(和int、double等无差别),类型是不具有地址的。
		...
	};
2、通常使用预编译开关切换类的导入导出定义 eg.
	#ifdef DLLCLASS_EXPORT            //决定定义DLLCLASS_EXPORT 最好放在.cpp中
	#define EXT_CLASS _declspec(dllexport) //DLL
	#else
	#define EXT_CLASS _declspec(dllimport) //使用者
	#endif

	class EXT_CLASS CMath
	{
		...
	};
*/

//在动态库中封装类，一般需要.h文件进行申明，否则使用动态库的人无法知道动态库中封装的类名，进而拿不到成员方法

#ifdef DLLCLASS_EXPORT
#define EXT_CLASS _declspec(dllexport) //DLL
#else
#define EXT_CLASS _declspec(dllimport) //使用者
#endif


// template<class T>
// class  EXT_CLASS CMath       //申明导出，最终导出去的是类的成员函数的地址；
// {									//_declspec(dllexport)是制作动态库 _declspec(dllimport)是使用动态库时的申明
// public:
// 	T Add(T x, T y);
// 	T Sub(T x, T y);
/*};*/

class  EXT_CLASS CMath       //申明导出，最终导出去的是类的成员函数的地址；
{									//_declspec(dllexport)是制作动态库 _declspec(dllimport)是使用动态库时的申明
public:
	int Add(int x, int y);
	int Sub(int x, int y);
};
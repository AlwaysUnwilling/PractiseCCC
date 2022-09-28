// dllmain.cpp : 定义 DLL 应用程序的入口点。
#include "pch.h"

//windows动态库的创建：添加库程序；
//                   库程序导出--提供给使用者库中的函数等信息，俩种方法:1、声明导出：使用_declspec(dllexport)导出函数，注意动态库编译链接后，也会有lib
                                                                    //文件，是作为动态库函数映射使用，与静态库不完全相同
//                                                         2、模块定义文件.def导出:LIBRARY DLLFunc  //库;EXPORTS //库导出表
//                                                                              DLL_Mul @1  //导出函数
//库程序的导出指的是导出动态库函数的地址，提供给使用动态库者函数地址。

/*
* 在生成的动态库.dll文件中包含了俩部分信息，文件头上包含了所有动态库的函数的地址表(编号-函数名-函数地址)；后半部分包含了所有的动态库函数源码。
* 与.dll配套生成(同名)的.lib文件存放的是动态库函数名与它在动态库前半部分的编号的对应关系；还存放了动态库名（.dll文件名）。
*/
BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}
//导出方法1:声明导出
// _declspec(dllexport) int Cdll_add(int x, int y)
// {
//     return x + y;
// }
// _declspec(dllexport) int Cdll_sub(int x, int y)
// {
//     return x - y;
// }
// _declspec(dllexport) int Cdll_mul(int x, int y)
// {
//     return x * y;
// }

//导出方法2:模块定义文件.def
int Cdll_add(int x, int y)
{
    return x + y;
}
int Cdll_sub(int x, int y)
{
    return x - y;
}
int Cdll_mul(int x, int y)
{
    return x * y;
}
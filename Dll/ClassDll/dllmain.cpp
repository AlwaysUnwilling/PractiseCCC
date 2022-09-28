// dllmain.cpp : 定义 DLL 应用程序的入口点。

#include "pch.h"
#define DLLCLASS_EXPORT
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

#include"myClassdll.h"


/*template<class T>
T CMath<T>::Add(T x, T y)
{
	return x + y;
}

template<class T>
T CMath<T>::Sub(T x, T y)
{
	return x - y;
}*/


int CMath::Add(int x, int y)
{
    return x + y;
}


int CMath::Sub(int x, int y)
{
    return x - y;
}
#pragma once


#ifdef DLLCLASS_EXPORTS
#define EXT_CLASS _declspec(dllexport)   //DLL
#else
#define EXT_CLASS _declspec(dllimport)  //USER
#endif
class EXT_CLASS CMath
{
public:
	int Add(int x, int y);
	int Sub(int x, int y);
};

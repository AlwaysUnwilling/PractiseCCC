#include<afxwin.h>
#include<iostream>

class CAnimal :public CObject
{
	DECLARE_DYNAMIC(CAnimal)
};
IMPLEMENT_DYNAMIC(CAnimal,CObject)

class CDog :public CAnimal
{
	//DECLARE_DYNCREATE(CDog)
	DECLARE_DYNAMIC(CDog)
	static CObject* PASCAL CreateObject();
};
//IMPLEMENT_DYNCREATE(CDog,CAnimal)
CObject* PASCAL CDog::CreateObject()
{
	return new CDog; 
}
IMPLEMENT_RUNTIMECLASS(CDog, CAnimal, 0xFFFF,CDog::CreateObject, NULL)


int main()
{
	CObject* pob = RUNTIME_CLASS(CDog)->CreateObject();
	if (pob)
		std::cout << pob << std::endl;
	else
		std::cout << "NULL" << std::endl;
	return 0;
}
#include<afxwin.h>
#include<iostream>

class CAnimal :public CObject
{
	//DECLARE_DYNAMIC(CAnimal)
public: 
	static const CRuntimeClass classCAnimal;
	virtual CRuntimeClass* GetRuntimeClass() const; 
};

//IMPLEMENT_DYNAMIC(CAnimal,CObject)
	//IMPLEMENT_RUNTIMECLASS(CAnimal, CObject, 0xFFFF, NULL, NULL)
AFX_COMDAT const CRuntimeClass CAnimal::classCAnimal = 
		{ 
		"CAnimal",
		sizeof(class CAnimal),
		0xFFFF,
		NULL, 
		//RUNTIME_CLASS(CObject), 
		((CRuntimeClass*)(&CObject::classCObject)),
		NULL,
		NULL 
		}; 
CRuntimeClass* CAnimal::GetRuntimeClass() const 
{
	return RUNTIME_CLASS(CAnimal);
}

class CDog :public CAnimal
{
	DECLARE_DYNAMIC(CDog)
};

IMPLEMENT_DYNAMIC(CDog,CAnimal)

int main()
{
	CDog yellowdog;
	if (yellowdog.IsKindOf(RUNTIME_CLASS(CDog)))
		std::cout << "yes" << std::endl;
	else
		std::cout << "no" << std::endl;
	return 0;
}
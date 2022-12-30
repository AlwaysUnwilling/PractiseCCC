
// 职业调查.h: PROJECT_NAME 应用程序的主头文件
//

#pragma once

#ifndef __AFXWIN_H__
	#error "在包含此文件之前包含 'pch.h' 以生成 PCH"
#endif

#include "resource.h"		// 主符号


// C职业调查App:
// 有关此类的实现，请参阅 职业调查.cpp
//

class C职业调查App : public CWinApp
{
public:
	C职业调查App();

// 重写
public:
	virtual BOOL InitInstance();

// 实现

	DECLARE_MESSAGE_MAP()
};

extern C职业调查App theApp;

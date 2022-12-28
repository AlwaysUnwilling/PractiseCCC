// CMyButton.cpp: 实现文件
//

#include "pch.h"
#include "RunningButton.h"
#include "CMyButton.h"


// CMyButton

IMPLEMENT_DYNAMIC(CMyButton, CButton)

CMyButton::CMyButton()
{
	m_pButton = nullptr;
}

CMyButton::~CMyButton()
{
	m_pButton = nullptr;
}


BEGIN_MESSAGE_MAP(CMyButton, CButton)
	ON_WM_MOUSEMOVE()
END_MESSAGE_MAP()



// CMyButton 消息处理程序




void CMyButton::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	ShowWindow(SW_HIDE);
	if(m_pButton)
		m_pButton->ShowWindow(SW_SHOW);
	CButton::OnMouseMove(nFlags, point);
}

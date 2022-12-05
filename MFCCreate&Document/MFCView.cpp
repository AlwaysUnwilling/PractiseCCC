#include<afxwin.h>
#include"resource.h"

class CMyView :public CView
{
	DECLARE_MESSAGE_MAP()
public:
	virtual void OnDraw(CDC* pCDC)
	{
		pCDC->TextOut(100,100,"OnDraw");
	}
	afx_msg void OnPaint()
	{
		PAINTSTRUCT pcs = { 0 };
		HDC hdc = ::BeginPaint(this->m_hWnd, &pcs);
		::TextOut(hdc, 200, 200, "CMyView",7);
		EndPaint(&pcs);
	}
	afx_msg void OnNew()
	{
		AfxMessageBox(_T("view处理了OnCommand"));
	}
};
BEGIN_MESSAGE_MAP(CMyView,CView)
	ON_COMMAND(ID_NEW,OnNew)
	ON_WM_PAINT()
END_MESSAGE_MAP()


class CMyFrameWnd :public CFrameWnd
{
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnPaint()
	{
		PAINTSTRUCT ps = { 0 };
		HDC hdc = ::BeginPaint(this->m_hWnd,&ps);
		::TextOut(hdc, 100, 100, "我是框架窗口客户区",strlen("我是框架窗口客户区"));
		EndPaint(&ps);
	}
	afx_msg int OnCreate(LPCREATESTRUCT pcs)
	{
		pView = new CMyView;
		pView->Create(NULL, "View", WS_CHILD | WS_VISIBLE | WS_BORDER, CRect(0, 0, 200, 200), this, AFX_IDW_PANE_FIRST);
		m_pViewActive = pView;
		pMenu = new CMenu;
		pMenu->LoadMenu(IDR_MENU1);
		SetMenu(pMenu);
		return CFrameWnd::OnCreate(pcs);
	}
private:
	CMyView* pView = NULL;
	CMenu* pMenu = NULL;
};
BEGIN_MESSAGE_MAP(CMyFrameWnd,CFrameWnd)
	ON_WM_PAINT()
	ON_WM_CREATE()
END_MESSAGE_MAP()



class CMyWinApp :public CWinApp
{
public:
	virtual BOOL InitInstance()
	{
		CMyFrameWnd* pFrame = new CMyFrameWnd;
		m_pMainWnd = pFrame;
		pFrame->Create(NULL, "MFCView");
		pFrame->ShowWindow(SW_SHOW);
		pFrame->UpdateWindow();


		return TRUE;
	}
};

CMyWinApp theApp;
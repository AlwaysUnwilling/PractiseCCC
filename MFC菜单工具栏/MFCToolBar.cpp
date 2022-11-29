#include<afxwin.h>
#include<afxext.h>
#include"resource.h"

class CMyFrameWnd :public CFrameWnd
{
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnNew()
	{
		AfxMessageBox(_T("新建菜单项被点击"));
	}
	afx_msg void OnOpen()
	{
		AfxMessageBox(_T("打开菜单项被点击"));
	}
	afx_msg int OnCreate(LPCREATESTRUCT pcs)
	{
		toolbar = new CToolBar;
		toolbar->CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_ALIGN_TOP|CBRS_GRIPPER);
		toolbar->LoadToolBar(IDR_TOOLBAR1);
		toolbar->EnableDocking(CBRS_ORIENT_ANY);
		this->EnableDocking(CBRS_ORIENT_ANY);
		this->DockControlBar(toolbar, AFX_IDW_DOCKBAR_BOTTOM);
		return CFrameWnd::OnCreate(pcs);
	}
	afx_msg void OnButton()
	{
		AfxMessageBox(_T("菜单项按钮被点击"));
	}


	~CMyFrameWnd()
	{
		if (toolbar)
		{
			delete toolbar;
			toolbar = NULL;
		}
	}
private:
	CToolBar* toolbar = NULL;
};

BEGIN_MESSAGE_MAP(CMyFrameWnd, CFrameWnd)
	ON_WM_CREATE()
	ON_COMMAND(ID_NEW, OnNew)
	ON_COMMAND(ID_OPEN, OnOpen)
	ON_COMMAND(ID_BUTTON40007,OnButton)
END_MESSAGE_MAP()


class CMyWinApp :public CWinApp
{
public:
	virtual BOOL InitInstance()
	{
		CMyFrameWnd* pFrame = new CMyFrameWnd;
		m_pMainWnd = pFrame;
		pFrame->Create(NULL, "MFCCreate",WS_OVERLAPPEDWINDOW,CFrameWnd::rectDefault,NULL,
						(CHAR*)IDR_MENU1);
		pFrame->ShowWindow(SW_SHOW);
		pFrame->UpdateWindow();

		return TRUE;
	}
};

CMyWinApp theApp;
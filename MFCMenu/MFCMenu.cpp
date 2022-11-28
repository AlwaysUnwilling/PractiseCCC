#include<afxwin.h>
#include"resource.h"

class CMyFrameWnd:public CFrameWnd
{
	DECLARE_MESSAGE_MAP()
public:
	afx_msg int OnCreate(LPCREATESTRUCT pcs)
	{
		pMenu = new CMenu;
		pMenu->LoadMenu(IDR_MENU1);
		this->SetMenu(pMenu);
		return CFrameWnd::OnCreate(pcs);
	}
	afx_msg void OnNew()
	{
		AfxMessageBox(_T("新建菜单项被处理!"));
	}
	afx_msg void OnInitMenuPopup(CMenu* pPopup, UINT pos, BOOL i)
	{
		//pPopup->CheckMenuItem(ID_NEW, MF_CHECKED);
		::CheckMenuItem(pPopup->m_hMenu, ID_NEW, MF_CHECKED);
	}
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint pt)
	{
// 		HMENU hMenu=::GetSubMenu(pMenu->m_hMenu, 0);
// 		::TrackPopupMenu(hMenu, TPM_LEFTALIGN | TPM_TOPALIGN,pt.x,pt.y,0,this->m_hWnd,NULL);
		CMenu* pPopup = pMenu->GetSubMenu(0);
		pPopup->TrackPopupMenu(TPM_LEFTALIGN | TPM_TOPALIGN, pt.x, pt.y,this);
	}
private:
	CMenu* pMenu=NULL;
};
BEGIN_MESSAGE_MAP(CMyFrameWnd,CFrameWnd)
	ON_WM_CREATE()
	ON_COMMAND(ID_NEW,OnNew)
	ON_WM_INITMENUPOPUP()
	ON_WM_CONTEXTMENU()
END_MESSAGE_MAP()

class CMyWinApp :public CWinApp
{
public:
	virtual BOOL InitInstance()
	{
		CMyFrameWnd* pFrame = new CMyFrameWnd;
// 		pFrame->Create(NULL, "MFCCreate",WS_OVERLAPPEDWINDOW,CFrameWnd::rectDefault,NULL,
// 						(CHAR*)IDR_MENU1);
		pFrame->Create(NULL, "MFCCreate");
		m_pMainWnd = pFrame;
		pFrame->ShowWindow(SW_SHOW);
		pFrame->UpdateWindow();

		return TRUE;
	}
};

CMyWinApp theApp;
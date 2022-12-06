#include<afxwin.h>
#include"resource.h"

class CMyDoc :public CDocument
{
	DECLARE_DYNCREATE(CMyDoc)
	DECLARE_MESSAGE_MAP()
public:
};
IMPLEMENT_DYNCREATE(CMyDoc,CDocument)

BEGIN_MESSAGE_MAP(CMyDoc,CDocument)
END_MESSAGE_MAP()

class CMyView :public CView
{
	DECLARE_DYNCREATE(CMyView)
	DECLARE_MESSAGE_MAP()
public:
	virtual void OnDraw(CDC* pDC)
	{
		;
	}
};
IMPLEMENT_DYNCREATE(CMyView,CView)

BEGIN_MESSAGE_MAP(CMyView,CView)
END_MESSAGE_MAP()

class CMyFrame :public CFrameWnd
{
	DECLARE_DYNCREATE(CMyFrame)
	DECLARE_MESSAGE_MAP()
public:
};
IMPLEMENT_DYNCREATE(CMyFrame,CFrameWnd)

BEGIN_MESSAGE_MAP(CMyFrame,CFrameWnd)
END_MESSAGE_MAP()

class CMyWinApp :public CWinApp
{
	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL InitInstance()
	{
		CSingleDocTemplate* pTemplate = new CSingleDocTemplate(IDR_MENU1, 
			RUNTIME_CLASS(CMyDoc), 
			RUNTIME_CLASS(CMyFrame),
			RUNTIME_CLASS(CMyView));
		AddDocTemplate(pTemplate);
		OnFileNew();
		m_pMainWnd->ShowWindow(SW_SHOW);
		m_pMainWnd->UpdateWindow();

		return TRUE;
	}
};

BEGIN_MESSAGE_MAP(CMyWinApp,CWinApp)
END_MESSAGE_MAP()

CMyWinApp theApp;


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
	virtual void OnDraw(CDC* pCDC)
	{
		pCDC->TextOut(100, 100, "������ͼ����");
	}
};
IMPLEMENT_DYNCREATE(CMyView,CView)
BEGIN_MESSAGE_MAP(CMyView,CView)
END_MESSAGE_MAP()

//�����ӿ����
class CMyChild :public CMDIChildWnd
{
	DECLARE_DYNCREATE(CMyChild)
};
IMPLEMENT_DYNCREATE(CMyChild,CMDIChildWnd)

//��������ܴ����� ---�����Լ�������ܴ�����Ķ���
class CMyFrameWnd :public CMDIFrameWnd
{
};

class CMyWinApp :public CWinApp
{
	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL InitInstance()
	{
		CMyFrameWnd* pFrame = new CMyFrameWnd;
		pFrame->LoadFrame(IDR_MENU1);
		m_pMainWnd = pFrame;
		pFrame->ShowWindow(SW_SHOW);
		pFrame->UpdateWindow();

		CMultiDocTemplate* pTemplate = new CMultiDocTemplate(IDR_MENU2,
						RUNTIME_CLASS(CMyDoc),
						RUNTIME_CLASS(CMyChild),
						RUNTIME_CLASS(CMyView));
		AddDocTemplate(pTemplate);
		OnFileNew();
		OnFileNew();
		OnFileNew();

		return TRUE;
	}
};
BEGIN_MESSAGE_MAP(CMyWinApp,CWinApp)
END_MESSAGE_MAP()

CMyWinApp theApp;
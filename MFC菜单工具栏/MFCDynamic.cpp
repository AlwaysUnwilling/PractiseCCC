#include<afxwin.h>


class CMyFrameWnd :public CFrameWnd
{

};

class CMyWinApp :public CWinApp
{
public:
	virtual BOOL InitInstance()
	{
		CMyFrameWnd* pFrame = new CMyFrameWnd;
		m_pMainWnd = pFrame;
		pFrame->Create(NULL, "MFCCREATE");
		pFrame->ShowWindow(SW_SHOW);
		pFrame->UpdateWindow();

		return TRUE;
	}
};

CMyWinApp theApp;
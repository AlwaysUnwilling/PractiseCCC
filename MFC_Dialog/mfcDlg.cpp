#include <afxwin.h>
#include "resource.h"

class CMyDlg :public CDialog
{

};

class CMyWinApp :public CWinApp
{
public:
	virtual BOOL InitInstance()
	{
		CMyDlg* pdlg = new CMyDlg;
		pdlg->Create(IDD_DIALOG1);
		m_pMainWnd = pdlg;

		pdlg->ShowWindow(SW_SHOW);
		pdlg->UpdateWindow();

		return TRUE;
	}
};


CMyWinApp theApp;
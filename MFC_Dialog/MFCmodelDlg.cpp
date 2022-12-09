#include<afxwin.h>
#include"resource.h"


class CMyDlg :public CDialog
{
public:
	enum{IDD=IDD_DIALOG1};
	CMyDlg()
		:CDialog(IDD)
	{}
};

class CMyWinApp :public CWinApp
{
public:
	virtual BOOL InitInstance()
	{
// 		CMyDlg* pdlg = new CMyDlg;
// 		m_pMainWnd = pdlg;
// 		pdlg->DoModal();

		CMyDlg dlg;  //Õ»¿Õ¼ä£¿£¿£¿£¿
		m_pMainWnd = &dlg;
		dlg.DoModal();

		return TRUE;
	}
};

CMyWinApp theApp;

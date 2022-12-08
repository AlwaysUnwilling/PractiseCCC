#include<windows.h>
#include"resource.h"

static HINSTANCE hIns = 0;


int CALLBACK  NModelDlgProc(HWND hWnd,UINT msgID,WPARAM wParam,LPARAM lParam)
{
	switch (msgID)
	{
	case WM_SYSCOMMAND:
		if (wParam == SC_CLOSE)
		{
			EnableWindow(GetParent(hWnd), TRUE);
			DestroyWindow(hWnd); //������ģʽ�Ի����мǲ���EndDialog
			//EndDialog(hWnd,1100);  //err
		}
		break;
	case WM_DESTROY:
		MessageBox(NULL, "��Ҫ����", "Info", MB_OK);
		break;
	}
	return FALSE;  //�Ի������Ϣ���������ĶԻ��򴰿ڴ���������
}
void OnNDLG(HWND hWnd)
{
	EnableWindow(hWnd, FALSE);
	//HWND hDlg=CreateDialog(hIns, MAKEINTRESOURCE(IDD_DIALOG1), hWnd, NModelDlgProc);
	HRSRC hRsrc=FindResource(hIns,MAKEINTRESOURCE(IDD_DIALOG1),RT_DIALOG);
	HGLOBAL hGl=LoadResource(hIns, hRsrc);
	LPCDLGTEMPLATE pTemplate=(LPCDLGTEMPLATE)LockResource(hGl);
	HWND hDlg=CreateDialogIndirect(hIns, pTemplate, hWnd, NModelDlgProc);
	ShowWindow(hDlg, SW_SHOW);
}
void OnCommand(HWND hWnd,WPARAM wParam)
{
	switch (LOWORD(wParam))
	{
	case ID_NDLG:
		OnNDLG(hWnd);
		break;
	}
}
//���ڴ�����(�Զ���,������Ϣ��)
LRESULT CALLBACK WindProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_COMMAND:
		OnCommand(hWnd,wParam);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}
	return DefWindowProc(hWnd, message, wParam, lParam);
}

int CALLBACK WinMain(HINSTANCE hInstance, HINSTANCE hPreIns, LPSTR lpCmdLine, int nCmdShow)
{

	hIns = hInstance;
	//ע�ᴰ����
	WNDCLASS wc = { 0 };
	wc.cbClsExtra = 0;                         //���ڿ�������(��λ�ֽ�)��
	wc.cbWndExtra = 0;                         //���ڿ�������(��λ�ֽ�)
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);   //���ڱ���ɫ   COLOR_WINDOW+3---��ɫ����
	wc.hCursor = NULL;                 //��ꣻ��ֵΪNULL ָ����ϵͳĬ�Ϲ��
	wc.hIcon = NULL;              //ͼ�꣬��ֵΪNULL ָ����ϵͳĬ��ͼ��(���������Ͻǵ�СͼƬ)
	wc.hInstance = hIns;         //����ǰʵ�����
	wc.lpfnWndProc = WindProc;      //���ڴ�����(�Զ���)
	wc.lpszClassName = "Main";             //�����������   ������������Զ���ûʲô�ã�������Щ���������Ѿ���ϵͳע���ˣ�һ����֮��ͻ��ᰴ��ϵͳ
											//ϵͳ�����������������磬��ť�������Ϊ"button",�༭�������"edit"����ϵͳ�Ѿ�ע��ŵĴ�������
	wc.lpszMenuName = MAKEINTRESOURCE(IDR_MENU1);//(CHAR*)IDR_MENU1;             //�˵�����ֵΪNULL ָ���ǲ�Ҫ�˵�
	wc.style = CS_HREDRAW | CS_VREDRAW;   //���ڷ��   CS_HREDRAW | CS_VREDRAW---�����ڵ�ˮƽ��ֱ�����б仯ʱ���»�����

	RegisterClass(&wc);     //ע�ᴰ��---���������и�ֵȫ��д�����ϵͳ

	//���ڴ洴������
	HWND hWnd = CreateWindow(
		"Main",        //����������� ������ע�ᴰ�ڵĴ���������һ��
		"MyWindow",    //���ڱ���   �ַ��������ڴ�������ʱ���Ͻ���ʾ�Ĵ�������
		WS_OVERLAPPEDWINDOW,         //���ڷ��WS_OVERLAPPEDWINDOWN--�����˴󲿷ִ��ڷ��
		100, 100, 500, 500,        //���ڵ�λ�úʹ�С
		NULL,                   //������  ��ֵΪNULL��ʾû�и�����
		NULL,                  //�˵�   ��ֵΪNULL��ʾ��Ҫ�˵�
		hIns,                   //��ǰ����ʵ�����
		NULL                    //���ڸ�����Ϣ   �ÿ�NULL��ʾ�޸�����Ϣ
	);

	//��ʾ����
	ShowWindow(
		hWnd,           //���ڵĲ������
		SW_SHOW         //��ʾ��� windows�д��ڵ���ʾ��񹲷������֣�SW_SHOW--ԭ����ʾ(����ǰ�洴�����ڵ�λ�úʹ�С������ʾ)�������ʾ����С����ʾ
	);
	UpdateWindow(hWnd);          //ˢ�´��ڣ����Բ����ã��������

	//��Ϣѭ��
	MSG msg = { 0 };
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	/*���ڹرղ������������˳�������*/
	return 0;
}
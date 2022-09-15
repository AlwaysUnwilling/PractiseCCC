#include<windows.h>
#include<iostream>


/*
 WINAPI  --�ǵ���Լ����һ������Լ��������һ�����������з����ܲ�����
			�磬�������˲����ڶ�ջ�ϳ��ֵ�˳��ֻ��Ҫȷ����������ʾ��������wWinMain�������ɡ�
int WINAPI WinMain(
_In_ ��ʾ���������  HINSTANCE hInstance,           //ʵ���ľ����windows��h��ͷ��һ�㶼�ǲ������handle����д
_In_opt_ HINSTANCE hPrevInstance,          //û���κ����壬����16λwindows��ʹ�ã�������ʼ�����㡣
_In_ LPSTR lpCmdLine,                   //���������в�����Ϊ	Unicode�ַ���
_In_ int nShowCmd)                      //��һ����־��ָʾ��Ӧ�ó��򴰿�����С������󻯻���������ʾ
                              //����ֵ��һ��intֵ������ϵͳ��ʹ�ø�ֵ������������ʹ�ø�ֵ��״̬�봫�͸���������
*/

LPCTSTR clsName = (LPCTSTR)"MyWindow";
LPCTSTR msgName = (LPCTSTR)"��ӭѧϰWindows���";
LRESULT CALLBACK MyWinProc(
	HWND hwnd,
	UINT uMsg,
	WPARAM wParam,
	LPARAM lParam)
{
	HDC hdc;
	int ret;
	switch (uMsg)
	{
	case WM_CHAR:
		char szChar[20];
		sprintf_s(szChar, "��ղŰ�����:%c", wParam);
		MessageBox(hwnd,szChar,"char",NULL);
		break;
	case WM_LBUTTONDOWN:
		MessageBox(hwnd, "��⵽��������������", "�����Ϣ", NULL);
		break;
	case WM_PAINT:
		PAINTSTRUCT ps;
		hdc = BeginPaint(hwnd, &ps);
		TextOut(hdc, 0, 0, "Congratulations!", strlen("Congratulations!"));
		EndPaint(hwnd, &ps);
		MessageBox(hwnd, "�ػ�", "msg", NULL);
		break;
	case WM_CLOSE:
		ret = MessageBox(hwnd, "�Ƿ���Ľ���?","msg", MB_YESNO);
		if (ret == IDYES)
		{
			DestroyWindow(hwnd);
		}
		break;
	case WM_DESTROY:
		PostMessage(hwnd, WM_CLOSE, NULL, NULL);
		//PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hwnd,uMsg,wParam,lParam);
		//break;
	}
	return LRESULT(0);
}
int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nShowCmd)
{
	//1����������ô��ڶ���
	WNDCLASS window;
	window.cbClsExtra = NULL;
	window.cbWndExtra = NULL;
	window.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	window.hCursor = LoadCursor(NULL, IDC_ARROW);
	window.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	window.hInstance = hInstance;

	//2�����彻����Ӧ
	window.lpfnWndProc = MyWinProc;   //���ڵĻص�����
	window.lpszClassName = clsName;
	window.lpszMenuName = NULL;
	window.style = CS_HREDRAW | CS_VREDRAW;

	//3��ע�ᴰ����
	RegisterClass(&window);
	//4����������
	HWND hwnd = CreateWindow(clsName,msgName,WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,CW_USEDEFAULT,CW_USEDEFAULT,CW_USEDEFAULT,NULL,NULL,hInstance, NULL);
	//5����ʾ��ˢ�´���
	ShowWindow(hwnd, SW_SHOWNORMAL);
	UpdateWindow(hwnd);
	MSG msg;
	while (GetMessage(&msg,NULL,NULL,NULL))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return 0;
}

//typedef struct tagWNDCLASSW {
//	UINT        style;                //���ͣ��ó�Ա������Class Style���κ����---ϵͳ�ࡢӦ�ó���ȫ���ࡢӦ�ó��򱾵���
									
//										
//	WNDPROC     lpfnWndProc;         //���ڹ��̺���---����ָ�룬����ʹ��CallWindowProc���������ô��ڹ��̺�����
//	int         cbClsExtra;          //���մ�����ṹ����Ķ����ֽ�����ϵͳ���ֽڳ�ʼ��Ϊ�㡣
//	int         cbWndExtra;          //�ڴ���ʵ��֮�����Ķ����ֽ�����ϵͳ���ֽڳ�ʼ��Ϊ�㡣���Ӧ�ó���ʹ��WNDCLASS����Դ
//										�ļ���ע��ʹ��CLASSָ����ĶԻ�������뽫�˳�Ա����ΪDLGWINDOWEXTRA.
//	HINSTANCE   hInstance;          //������Ĵ��ڹ���ʵ���ľ����
//	HICON       hIcon;                //��ͼ��ľ�����˳�Ա�������α���Դ�ľ��������˳�Ա��NULL����Ӧ�ó���������������Ӧ�ó���
//										����ʱ��ʾ���ù����״��
//	HCURSOR     hCursor;           //�౳�����ʾ�����ó�Ա���������ڻ��Ʊ����������ʵľ����Ҳ��������ɫֵ����ɫֵ������һ�±�׼ϵͳ��ɫ֮һ(���뽫
//										ֵ1��ӵ���ѡ��ɫ)�������������ɫֵ������뽫��ת��Ϊһ��HBRUSH����֮һ.
//									ʹ��UnregisterClass ע���༶ʱ��ϵͳ���Զ�ɾ���༶�������ʡ�Ӧ�ó���Ӧɾ����Щ���ʡ����˳�ԱΪNULLʱ��
//									Ӧ�ó�������ڱ���������ͻ������л���ʱ�����Լ��ı�����Ҫȷ���Ƿ������Ʊ�����Ӧ�ó�����Դ��� WM_ERASEBKGND��Ϣ�����
//									 ��BeginPaint��������PAINTSTRUCT�ṹ��fErase��Ա��
//	HBRUSH      hbrBackground;
//	LPCWSTR     lpszMenuName;      ��˵�����Դ���ƣ������Ƴ�������Դ�ļ��С������ʹ����������ʶ�˵���
//									��ʹ��MAKEINTRESOURCE�ꡣ����˳�ԱΪNULL�������ڴ���Ĵ���û��Ĭ�ϲ˵���
//	LPCWSTR     lpszClassName;		ָ���� null ��β���ַ�����ָ�룬������һ��ԭ�ӡ�����˲�����ԭ�ӣ���������������ǰ����RegisterClass��
//									RegisterClassEx������������ԭ�ӡ�ԭ�ӱ����� lpszClassName�ĵ�λ���У���λ�ֱ���Ϊ�㡣
//									���lpszClassName��һ���ַ�������ָ����������������������ʹ��RegisterClass��RegisterClassEx ע����κ����ƣ�Ҳ�������κ�Ԥ����Ŀؼ������ơ�
//									lpszClassName����󳤶�Ϊ256�����lpszClassName������󳤶ȣ�RegisterClass������ʧ��
//} WNDCLASSW, * PWNDCLASSW, NEAR* NPWNDCLASSW, FAR* LPWNDCLASSW;
//#ifdef UNICODE
//typedef WNDCLASSW WNDCLASS;
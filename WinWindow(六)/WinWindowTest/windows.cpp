#define  _CRT_SECURE_NO_WARNINGS

#include<Windows.h>
#include<stdio.h>
#include"resource.h"

HANDLE g_hOutput = 0;
static HINSTANCE hInstance;


void OnLButtonDbclk(HWND hwnd, WPARAM wparam, LPARAM lparam)
{
	const char* szText = "WM_LBUTTONDBCLK";
	WriteConsole(g_hOutput, szText, strlen(szText), NULL, NULL);
}
void OnMouseMove(HWND hwnd, WPARAM wparam, LPARAM lparam)
{
	char szText[256] = { 0 };
	sprintf(szText, "WM_MOUSEMOVE:��������״̬��%d,X=%d,Y=%d\n", wparam, LOWORD(lparam), HIWORD(lparam));
	WriteConsole(g_hOutput, szText, strlen(szText), NULL, NULL);
}
void OnLButtonDown(HWND hwnd, WPARAM wparam, LPARAM lparam)
{
	char szText[256] = { 0 };
	sprintf(szText, "WM_LBUTTONDOWN:��������״̬��%d,X=%d,Y=%d\n", wparam, LOWORD(lparam), HIWORD(lparam));
	WriteConsole(g_hOutput, szText, strlen(szText), NULL, NULL);
}
void OnLButtonUp(HWND hwnd, WPARAM wparam, LPARAM lparam)
{
	char szText[256] = { 0 };
	sprintf(szText, "WM_LBUTTONUP:��������״̬��%d,X=%d,Y=%d\n", wparam, LOWORD(lparam), HIWORD(lparam));
	WriteConsole(g_hOutput, szText, strlen(szText), NULL, NULL);
}
void TestCreate(HWND hwnd, LPARAM lparam)
{
	HMENU hMenu = LoadMenu(hInstance, (char*)IDR_MENU1);
	SetMenu(hwnd, hMenu);
	//MessageBox(hwnd, "ȷ����������", "Tips", MB_OK);
}
void OnMouseWheel(HWND hwnd, WPARAM wparam, LPARAM lparam)
{
	short nDelta = HIWORD(wparam);
	char szText[256] = { 0 };
	sprintf(szText, "WM_MOUSEWHEEL:offset=%d\n", nDelta);
	WriteConsole(g_hOutput, szText, strlen(szText), NULL, NULL);
}
void OnTimer(HWND hwnd, WPARAM wparam)
{
	char szText[256] = { 0 };
	sprintf(szText, "WM_TIMER:ID=%d\n", wparam);
	WriteConsole(g_hOutput, szText, strlen(szText), NULL, NULL);
}
void OnCommand(HWND hwnd, WPARAM wparam)
{
	switch (LOWORD(wparam))
	{
	case ID_NEW:
		MessageBox(hwnd,"�½������","Tips",MB_OK);
		break;
	case ID_OPEN:
		MessageBox(hwnd, "�򿪱����", "Tips", MB_OK);
		break;
	case ID_SAVE:
		MessageBox(hwnd, "���汻���", "Tips", MB_OK);
		break;
	case ID_SAVEAS:
		MessageBox(hwnd, "���Ϊ�����", "Tips", MB_OK);
		break;
	case ID_ABOUT:
		MessageBox(hwnd, "���ڱ����", "Tips", MB_OK);
		break;
	case ID_EXIT:
		MessageBox(hwnd, "�˳������", "Tips", MB_OK);
		break;
	default:
		break;
	}
}
void OnRButtonUp(HWND hwnd, LPARAM lparam)
{
	HMENU hmain = LoadMenu(hInstance, (char*)IDR_MENU1);
	HMENU hPopUp = GetSubMenu(hmain,0);
	TrackPopupMenu(hPopUp, TPM_CENTERALIGN | TPM_VCENTERALIGN,           //����lparam���������ǿͻ����µĹ��λ��
																//�����ǵ����Ի�����Ҫ��Ļ����ϵ�µĹ��λ��
		LOWORD(lparam), HIWORD(lparam), 0,hwnd, NULL);          //����ʹ��ClientToScreen����ȥת��
}
void OnCONTEXTMENU(HWND hwnd, WPARAM wparam, LPARAM lparam)
{
	HMENU hmain = LoadMenu(hInstance, (char*)IDR_MENU1);
	HMENU hPopUp = GetSubMenu(hmain, 0);
	TrackPopupMenu(hPopUp, TPM_LEFTALIGN|TPM_TOPALIGN,           //TPM_CENTERALIGN | TPM_VCENTERALIGN, ˮƽ���У���ֱ��							
		LOWORD(lparam), HIWORD(lparam), 0, hwnd, NULL);
}
void DrawnPit(HDC hdc)
{
	for (int i = 0; i < 256; i++)
	{
		for (int j = 0; j < 256; j++)
		{
			SetPixel(hdc, i, j, RGB(i, j, i+j));         //����
		}
	}
	//MoveToEx---ָ����ǰ���ڵ���ʼ���� (���һ���������Է���ԭ���ĵ�ǰ�㣬�����տ����ÿ�)
	//LineTo---��ָ���㻭��lineto��ָ���㣬����һ��ֱ��
	MoveToEx(hdc, 256, 256, NULL);
	for (int i = 256; i < 256*2; i++)
	{
		for (int j = 256; j < 256*2; j++)
		{
			LineTo(hdc, i, j);
		}
	}
	//���ͼ�Σ��ɵ����ߣ�һ��һ�ε�Χ�ǵġ���ա�ͼ�β��ܽз��ͼ��---�����û�ˢ���
	//Rectangtle/Ellipse     ���Σ�Բ
	Rectangle(hdc, 0, 256, 255, 256*2);
	Ellipse(hdc, 256, 0, 256*2, 256);
	//WINGDIAPI HPEN    WINAPI CreatePen(_In_ int iStyle,  //���ʵ���ʽ--PS_SOLIDʵ���ߣ�����֧�ֶԸ����ؿ�������������֧��1�����ؿ�
	//																��������ؿ�����>1����ô���ʵ���ʽ�Զ�ʹ��ʵ����
	// 										_In_ int cWidth,  //���ʵĴ�ϸ(��λ������)
	// 									_In_ COLORREF color   //���ʵ���ɫ
	// 							);
	HPEN hpen = CreatePen(PS_SOLID, 5, RGB(0, 0, 255));
	HGDIOBJ oldPen= SelectObject(hdc,hpen);   //���½��Ļ��ʽ�����ȥ ��ͼ
	MoveToEx(hdc, 256 * 2, 0,NULL);
	for (int i = 256 * 2; i < 256 * 3; ++i)
	{
		for (int j = 0; j < 256; ++j)
		{
			LineTo(hdc, i, j);
		}
	}
	SelectObject(hdc, oldPen); //�����ʽ�������
	BOOL ret = DeleteObject(hpen); //�ͷŴ����Ļ���

	//HBRUSH hBrush=CreateSolidBrush(RGB(0, 255, 0));
	HBRUSH hBrush = CreateHatchBrush(HS_CROSS, RGB(0, 255, 0));
	HGDIOBJ hOld = SelectObject(hdc, hBrush);
	Rectangle(hdc, 256 * 2, 256, 256 * 3, 256 * 2);

	SelectObject(hdc, hOld);
	DeleteObject(hBrush);

	//Drawn BMP
	//1�����λͼ��Դ
	//2������BitMap
	HBITMAP hBitmap = LoadBitmap(hInstance, (char*)IDB_BITMAP1);
	//3������һ��͵�ǰDC��hdc����ƥ����ڴ�DC
	HDC hMemDC=CreateCompatibleDC(hdc);  //�����ڴ�DC������һ��������������DC��hMemDC�������������л�ͼ
	//4������SelectObject�������ڴ�DC�͸���ͼDC
	HGDIOBJ hOldDC=SelectObject(hMemDC, hBitmap);//��λͼ�����͸��ڴ�DC���ڴ�DC�����������н�λͼ���Ƴ���
	//5��������������ƺõ�λͼ���񵽴�����  BitBlt������һ��һ�ĳ���
	BitBlt(hdc, 256 * 3+10, 0, 48, 48, hMemDC, 0, 0, SRCCOPY);   //SRCCOPY---ԭ������
	StretchBlt(hdc, 256 * 3 + 10, 48, 24 , 24, hMemDC, 0, 0, 48,48,SRCCOPY);  //����/�Ŵ����
	StretchBlt(hdc, 256 * 3 + 10, 96, 96 , 96, hMemDC, 0, 0, 48,48,SRCCOPY);  //����/�Ŵ����
	//6����hOldDC��hMemDC����
	SelectObject(hMemDC, hOldDC);
	//7���ͷ��ڴ�λͼ
	DeleteObject(hBitmap);
	//8���ͷ��ڴ�DC
	DeleteDC(hMemDC);

	//TextOut()---�����ֻ�����ָ����λ�ô�����֧�ֻ��С�û�ж��뷽ʽ
	//DrawText(HDC hdc,LPCTSTR lpString,int nCount(�ַ�����),LPRECT lpRECT(�������ֵľ���),UINT uFormat�����Ƶķ�ʽ��);
	//DrawText֧�ֻ��У�֧�ֻ��Ʒ�ʽ(�ھ�����������\�ұ�\��\��\��ֱ�ȵ�).
	RECT rc = {256 * 3,256,256 * 3 + 256,256 + 256};
	SetTextColor(hdc, RGB(255, 0, 0));        //ֻ�����ڲ�͸��ģʽ��
	//SetBkColor(hdc, RGB(0, 255, 0));   //�ַ�����Ĭ�ϱ���ɫ�ǰ�ɫ
	SetBkMode(hdc, TRANSPARENT);     //�����ַ����ı���ģʽ(͸��ģʽ(TRANSPARENT)|��͸��ģʽ(OPAQUE Ĭ��))
	//��������
	HFONT hFont = CreateFont(30,0,45,0,900,1,1,1,GB2312_CHARSET,0,0,0,0,"����");
	hOld = SelectObject(hdc, hFont);
	DrawText(hdc, "�Ұ����й�!", strlen("�Ұ����й�"), &rc, DT_LEFT | DT_TOP);

	SelectObject(hdc, hOldDC);
	DeleteObject(hFont);
}
void OnPaint(HWND hwnd)
{
	PAINTSTRUCT ps = { 0 };
	HDC hdc = BeginPaint(hwnd, &ps);
	DrawnPit(hdc);

	EndPaint(hwnd, &ps);
}
LRESULT CALLBACK MyWinPro(HWND hwnd,UINT msg,WPARAM wparam,LPARAM lparam)
{
	switch (msg)
	{
	case WM_TIMER:
		OnTimer(hwnd, wparam);
		break;
	case WM_SETCURSOR:
	{
		HCURSOR hcursor_new = LoadCursor(hInstance, (char*)IDC_CURSOR2);
		if (LOWORD(lparam) == HTCLIENT)
		{
			SetCursor(hcursor_new);
			return 0;
		}		
	}
		break;
	case WM_MOUSEWHEEL:
		OnMouseWheel(hwnd, wparam, lparam);
		break;
	case WM_COMMAND:
		OnCommand(hwnd,wparam);
		break;
	case WM_RBUTTONUP:
		//OnRButtonUp(hwnd,lparam);
		break;
	case WM_CONTEXTMENU:         //����Ҽ�����  �����Ի�����Ϣ��wparam--�Ҽ�����Ĵ��ھ��  lparam--��2�ֽ�����Ļx���꣬��2�ֽ�����Ļy����
		OnCONTEXTMENU(hwnd, wparam, lparam);
		break;
	case WM_LBUTTONDBLCLK:
		OnLButtonDbclk(hwnd, wparam, lparam);
		break;
	case WM_MOUSEMOVE:
		OnMouseMove(hwnd, wparam, lparam);
		break;
	case WM_LBUTTONDOWN:
		OnLButtonDown(hwnd,wparam,lparam);
		break;
	case WM_LBUTTONUP:
		OnLButtonUp(hwnd, wparam, lparam);
		break;
	case WM_CREATE:
			// 		WINUSERAPI
			// 			HMENU
			// 			WINAPI
			// 			LoadMenuA(
			// 				_In_opt_ HINSTANCE hInstance,
			// 				_In_ LPCSTR lpMenuName);
			// 		WINUSERAPI
			// 			HMENU
			// 			WINAPI
			// 			LoadMenuW(
			// 				_In_opt_ HINSTANCE hInstance,
			// 				_In_ LPCWSTR lpMenuName);
			// #ifdef UNICODE
			// #define LoadMenu  LoadMenuW
			// #else
			// #define LoadMenu  LoadMenuA
			// #endif // !UNICODE
		SetTimer(hwnd, 100, 1000, NULL);
		TestCreate(hwnd,lparam);
		break;
	case WM_SYSCOMMAND:
		
		if (wparam == SC_CLOSE)
		{
			auto ret=MessageBox(hwnd, "�Ƿ�Ҫ�˳�?", "Tips", MB_YESNO);
			if (ret == IDYES)
			{
				SendNotifyMessage(hwnd, WM_CLOSE, 0, 0);
				return 0;
			}
			else
			{
				return 0;
			}
		}
		break;
	case WM_PAINT:
		OnPaint(hwnd);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}
	return DefWindowProc(hwnd, msg, wparam, lparam);
}
int CALLBACK WinMain(_In_ HINSTANCE hInst, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nShowCmd)
{
	//AllocConsole();    //���dos����
	g_hOutput = GetStdHandle(STD_OUTPUT_HANDLE);  //��ȡ��׼������

	HICON hIcon = LoadIcon(hInstance, (char*)IDI_ICON1);
	hInstance = hInst;
	WNDCLASS ws;
	ws.hInstance = hInstance;
	ws.lpfnWndProc = MyWinPro;
	//ws.hIcon = nullptr;
	ws.hIcon = hIcon;
	//ws.hCursor = nullptr;
	ws.hCursor = LoadCursor(hInstance,(char*)IDC_CURSOR1);
	ws.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	ws.lpszClassName = "MyWin";
	ws.lpszMenuName = NULL;
	//ws.lpszMenuName = (char*)IDR_MENU1;          //1��ע�ᴰ����ʱ���ò˵�  2���������ڴ������ò˵�  3����������WM_CREATE��Ϣ������SetMenu()�������ò˵�
	ws.cbClsExtra = 0;
	ws.cbWndExtra = 0;
	ws.style = CS_HREDRAW | CS_VREDRAW|CS_DBLCLKS;
	RegisterClass(&ws);

	char szTitle[256] = { 0 };
	LoadString(hInstance, IDS_STR1, szTitle, 256);
	HWND hmainwnd = CreateWindow("MyWin", szTitle, WS_OVERLAPPEDWINDOW, 720, 360, 720+720, 540+360, nullptr, nullptr, hInstance, 0);
	//HMENU hMenu = LoadMenu(hInstance,(char*)IDR_MENU1);
	//HWND hmainwnd = CreateWindow("MyWin", nullptr, WS_OVERLAPPEDWINDOW, 0, 0, 1280, 720, nullptr,hMenu , hInstance, 0);

	/*//�����Ӵ���
	WNDCLASS wc;
	wc.hInstance = hInstance;
	wc.lpfnWndProc = DefWindowProc;   //windowsĬ���ṩ�Ĵ��ڴ�����
	wc.hIcon = nullptr;
	wc.hCursor = nullptr;
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wc.lpszClassName = "Child";
	wc.lpszMenuName = nullptr;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.style = CS_HREDRAW | CS_VREDRAW;
	RegisterClass(&wc);
	HWND hchild=CreateWindow("Child", "c1", WS_CHILD | WS_VISIBLE|WS_OVERLAPPEDWINDOW, 100, 100, 540, 270, hmainwnd, nullptr,hInstance , 0);
	*/

	HACCEL hAccel= LoadAccelerators(hInstance, (char*)IDR_ACCELERATOR1);
	ShowWindow(hmainwnd, SW_SHOW);
	UpdateWindow(hmainwnd);
	MSG msg;
	while (GetMessage(&msg, nullptr, 0, 0))
	{
		if (!TranslateAccelerator(hmainwnd, hAccel, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	//DestroyWindow(hmainwnd);
	return 0;
}
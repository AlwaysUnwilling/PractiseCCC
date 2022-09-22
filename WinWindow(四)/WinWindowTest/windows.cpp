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
	sprintf(szText, "WM_MOUSEMOVE:其他按键状态：%d,X=%d,Y=%d\n", wparam, LOWORD(lparam), HIWORD(lparam));
	WriteConsole(g_hOutput, szText, strlen(szText), NULL, NULL);
}
void OnLButtonDown(HWND hwnd, WPARAM wparam, LPARAM lparam)
{
	char szText[256] = { 0 };
	sprintf(szText, "WM_LBUTTONDOWN:其他按键状态：%d,X=%d,Y=%d\n", wparam, LOWORD(lparam), HIWORD(lparam));
	WriteConsole(g_hOutput, szText, strlen(szText), NULL, NULL);
}
void OnLButtonUp(HWND hwnd, WPARAM wparam, LPARAM lparam)
{
	char szText[256] = { 0 };
	sprintf(szText, "WM_LBUTTONUP:其他按键状态：%d,X=%d,Y=%d\n", wparam, LOWORD(lparam), HIWORD(lparam));
	WriteConsole(g_hOutput, szText, strlen(szText), NULL, NULL);
}
void TestCreate(HWND hwnd, LPARAM lparam)
{
	HMENU hMenu = LoadMenu(hInstance, (char*)IDR_MENU1);
	SetMenu(hwnd, hMenu);
	//MessageBox(hwnd, "确定后建立窗口", "Tips", MB_OK);
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
		MessageBox(hwnd,"新建被点击","Tips",MB_OK);
		break;
	case ID_OPEN:
		MessageBox(hwnd, "打开被点击", "Tips", MB_OK);
		break;
	case ID_SAVE:
		MessageBox(hwnd, "保存被点击", "Tips", MB_OK);
		break;
	case ID_SAVEAS:
		MessageBox(hwnd, "另存为被点击", "Tips", MB_OK);
		break;
	case ID_ABOUT:
		MessageBox(hwnd, "关于被点击", "Tips", MB_OK);
		break;
	case ID_EXIT:
		MessageBox(hwnd, "退出被点击", "Tips", MB_OK);
		break;
	default:
		break;
	}
}
void OnRButtonUp(HWND hwnd, LPARAM lparam)
{
	HMENU hmain = LoadMenu(hInstance, (char*)IDR_MENU1);
	HMENU hPopUp = GetSubMenu(hmain,0);
	TrackPopupMenu(hPopUp, TPM_CENTERALIGN | TPM_VCENTERALIGN,           //这里lparam传过来的是客户区下的光标位置
																//而我们弹出对话框需要屏幕坐标系下的光标位置
		LOWORD(lparam), HIWORD(lparam), 0,hwnd, NULL);          //可以使用ClientToScreen函数去转换
}
void OnCONTEXTMENU(HWND hwnd, WPARAM wparam, LPARAM lparam)
{
	HMENU hmain = LoadMenu(hInstance, (char*)IDR_MENU1);
	HMENU hPopUp = GetSubMenu(hmain, 0);
	TrackPopupMenu(hPopUp, TPM_LEFTALIGN|TPM_TOPALIGN,           //TPM_CENTERALIGN | TPM_VCENTERALIGN, 水平居中，垂直上							
		LOWORD(lparam), HIWORD(lparam), 0, hwnd, NULL);
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
	case WM_CONTEXTMENU:         //鼠标右键弹起  弹出对话框消息，wparam--右键点击的窗口句柄  lparam--低2字节是屏幕x坐标，高2字节是屏幕y坐标
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
			auto ret=MessageBox(hwnd, "是否要退出?", "Tips", MB_YESNO);
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
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}
	return DefWindowProc(hwnd, msg, wparam, lparam);
}
int CALLBACK WinMain(_In_ HINSTANCE hInst, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nShowCmd)
{
	//AllocConsole();    //添加dos窗口
	g_hOutput = GetStdHandle(STD_OUTPUT_HANDLE);  //获取标准输出句柄

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
	//ws.lpszMenuName = (char*)IDR_MENU1;          //1、注册窗口类时设置菜单  2、创建窗口传参设置菜单  3、在主窗口WM_CREATE消息中利用SetMenu()函数设置菜单
	ws.cbClsExtra = 0;
	ws.cbWndExtra = 0;
	ws.style = CS_HREDRAW | CS_VREDRAW|CS_DBLCLKS;
	RegisterClass(&ws);

	char szTitle[256] = { 0 };
	LoadString(hInstance, IDS_STR1, szTitle, 256);
	HWND hmainwnd = CreateWindow("MyWin", szTitle, WS_OVERLAPPEDWINDOW, 0, 0, 1280, 720, nullptr, nullptr, hInstance, 0);
	//HMENU hMenu = LoadMenu(hInstance,(char*)IDR_MENU1);
	//HWND hmainwnd = CreateWindow("MyWin", nullptr, WS_OVERLAPPEDWINDOW, 0, 0, 1280, 720, nullptr,hMenu , hInstance, 0);

	/*//创建子窗口
	WNDCLASS wc;
	wc.hInstance = hInstance;
	wc.lpfnWndProc = DefWindowProc;   //windows默认提供的窗口处理函数
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
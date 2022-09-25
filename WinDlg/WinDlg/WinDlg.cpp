#include<windows.h>
#include<stdio.h>
#include"resource.h"


static HINSTANCE hIns = 0;

int CALLBACK MyDlgProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_SYSCOMMAND:
		if (wParam == SC_CLOSE)
		{
			EndDialog(hDlg,100);
		}
		break;
	}
	return FALSE;
}
int CALLBACK MyNoModeDlgProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
// 	switch (message)
// 	{
// 	case WM_SYSCOMMAND:
// 		if (wParam == SC_CLOSE)
// 		{
// 			DestroyWindow(hDlg);
// 		}
// 		break;
// 	}
	return FALSE;
}
void OnCommand(HWND hWnd, WPARAM wParam)
{
	switch (LOWORD(wParam))
	{
	case ID_MODE:
	{
		auto ret=DialogBox(hIns, (char*)IDD_DIALOG1, hWnd, MyDlgProc);
		if(ret==100)
		{
			MessageBox(hWnd, "Close Dialog!", "Tips", MB_OK);
		}
	}
		break;
	case ID_NMODE:
	{
		HWND hNoDlg=CreateDialog(hIns, (char*)IDD_DIALOG2, hWnd, MyNoModeDlgProc);
		ShowWindow(hNoDlg,SW_SHOW);
		UpdateWindow(hNoDlg);
	}
		break;
	}
}
LRESULT CALLBACK MyWinProc(HWND hWnd,UINT message,WPARAM wParam,LPARAM lParam)
{
	switch (message)
	{
	case WM_COMMAND:
		OnCommand(hWnd, wParam);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	case WM_SYSCOMMAND:

		if (wParam == SC_CLOSE)
		{
			auto ret = MessageBox(hWnd, "是否要退出?", "Tips", MB_YESNO);
			if (ret == IDYES)
			{
				SendNotifyMessage(hWnd, WM_CLOSE, 0, 0);
				return 0;
			}
			else
			{
				return 0;
			}
		}
		break;
	}
	
	return DefWindowProc(hWnd, message, wParam, lParam);
}
int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nShowCmd)
{
	hIns = hInstance;
	WNDCLASS ws;
	ws.hInstance = hIns;
	ws.hIcon = NULL;
	ws.hCursor = NULL;
	ws.lpfnWndProc = MyWinProc;
	ws.lpszClassName = "MyWin";
	ws.lpszMenuName = (char*)IDR_MENU1;
	ws.style = CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS;
	ws.cbClsExtra = 0;
	ws.cbWndExtra = 0;
	ws.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	RegisterClass(&ws);
	HWND hWnd = CreateWindow("MyWin", "Win32编程", WS_OVERLAPPEDWINDOW, 100, 100, 1280 + 100, 700 + 100, NULL, NULL, hIns, 0);
	ShowWindow(hWnd, SW_SHOW);
	UpdateWindow(hWnd);

	MSG msg;
	while (GetMessage(&msg,hWnd,0,0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return 0;
}
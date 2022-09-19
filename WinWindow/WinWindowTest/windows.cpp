#include<Windows.h>


void TestCreate(HWND hwnd, LPARAM lparam)
{
	MessageBox(hwnd, "确定后建立窗口", "Tips", MB_OK);
}
LRESULT CALLBACK MyWinPro(HWND hwnd,UINT msg,WPARAM wparam,LPARAM lparam)
{
	switch (msg)
	{
	case WM_CREATE:
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
int CALLBACK WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nShowCmd)
{
	WNDCLASS ws;
	ws.hInstance = hInstance;
	ws.lpfnWndProc = MyWinPro;
	ws.hIcon = nullptr;
	ws.hCursor = nullptr;
	ws.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	ws.lpszClassName = "MyWin";
	ws.lpszMenuName = nullptr;
	ws.cbClsExtra = 0;
	ws.cbWndExtra = 0;
	ws.style = CS_HREDRAW | CS_VREDRAW;
	RegisterClass(&ws);

	HWND hmainwnd = CreateWindow("MyWin", nullptr, WS_OVERLAPPEDWINDOW, 0, 0, 1280, 720, nullptr, nullptr, hInstance, 0);

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
	ShowWindow(hmainwnd, SW_SHOW);
	MSG msg;
	while (GetMessage(&msg, nullptr, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	//DestroyWindow(hmainwnd);
	return 0;
}
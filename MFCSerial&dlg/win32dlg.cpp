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
			DestroyWindow(hWnd); //销毁无模式对话框，切记不能EndDialog
			//EndDialog(hWnd,1100);  //err
		}
		break;
	case WM_DESTROY:
		MessageBox(NULL, "我要死了", "Info", MB_OK);
		break;
	}
	return FALSE;  //对话框的消息交给真正的对话框窗口处理函数处理
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
//窗口处理函数(自定义,处理消息等)
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
	//注册窗口类
	WNDCLASS wc = { 0 };
	wc.cbClsExtra = 0;                         //用于开缓冲区(单位字节)，
	wc.cbWndExtra = 0;                         //用于开缓冲区(单位字节)
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);   //窗口背景色   COLOR_WINDOW+3---白色背景
	wc.hCursor = NULL;                 //光标；赋值为NULL 指的是系统默认光标
	wc.hIcon = NULL;              //图标，赋值为NULL 指的是系统默认图标(标题栏左上角的小图片)
	wc.hInstance = hIns;         //程序当前实例句柄
	wc.lpfnWndProc = WindProc;      //窗口处理函数(自定义)
	wc.lpszClassName = "Main";             //窗口类的名字   窗口类的名字自定义没什么用，但是有些窗口类名已经被系统注册了，一旦与之冲突则会按照系统
											//系统窗口类来创建。比如，按钮类的名称为"button",编辑框的类名"edit"都是系统已经注册号的窗口类名
	wc.lpszMenuName = MAKEINTRESOURCE(IDR_MENU1);//(CHAR*)IDR_MENU1;             //菜单。赋值为NULL 指的是不要菜单
	wc.style = CS_HREDRAW | CS_VREDRAW;   //窗口风格   CS_HREDRAW | CS_VREDRAW---当窗口的水平或垂直方向有变化时重新画窗口

	RegisterClass(&wc);     //注册窗口---将以上所有赋值全部写入操作系统

	//在内存创建窗口
	HWND hWnd = CreateWindow(
		"Main",        //窗口类的名称 与上面注册窗口的窗口类名称一致
		"MyWindow",    //窗口标题   字符串用于在窗口生成时左上角显示的窗口名字
		WS_OVERLAPPEDWINDOW,         //窗口风格WS_OVERLAPPEDWINDOWN--包含了大部分窗口风格
		100, 100, 500, 500,        //窗口的位置和大小
		NULL,                   //父窗口  赋值为NULL表示没有父窗口
		NULL,                  //菜单   赋值为NULL表示不要菜单
		hIns,                   //当前程序实例句柄
		NULL                    //窗口附加信息   置空NULL表示无附加信息
	);

	//显示窗口
	ShowWindow(
		hWnd,           //窗口的操作句柄
		SW_SHOW         //显示风格 windows中窗口的显示风格共分了三种：SW_SHOW--原样显示(按照前面创建窗口的位置和大小进行显示)；最大化显示；最小化显示
	);
	UpdateWindow(hWnd);          //刷新窗口，可以不调用，建议调用

	//消息循环
	MSG msg = { 0 };
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	/*窗口关闭并不代表程序的退出！！！*/
	return 0;
}
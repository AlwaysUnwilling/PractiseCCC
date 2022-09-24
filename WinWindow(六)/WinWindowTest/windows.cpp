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
void DrawnPit(HDC hdc)
{
	for (int i = 0; i < 256; i++)
	{
		for (int j = 0; j < 256; j++)
		{
			SetPixel(hdc, i, j, RGB(i, j, i+j));         //画点
		}
	}
	//MoveToEx---指明当前窗口的起始画点 (最后一个参数可以返回原来的当前点，不接收可以置空)
	//LineTo---从指定点画到lineto的指定点，绘制一条直线
	MoveToEx(hdc, 256, 256, NULL);
	for (int i = 256; i < 256*2; i++)
	{
		for (int j = 256; j < 256*2; j++)
		{
			LineTo(hdc, i, j);
		}
	}
	//封闭图形，由单条线，一次一次的围城的“封闭”图形不能叫封闭图形---不能用画刷填充
	//Rectangtle/Ellipse     矩形，圆
	Rectangle(hdc, 0, 256, 255, 256*2);
	Ellipse(hdc, 256, 0, 256*2, 256);
	//WINGDIAPI HPEN    WINAPI CreatePen(_In_ int iStyle,  //画笔的样式--PS_SOLID实心线，可以支持对个像素宽，其他线型智能支持1个像素宽
	//																如果将像素宽设置>1，那么画笔的样式自动使用实心线
	// 										_In_ int cWidth,  //画笔的粗细(单位：像素)
	// 									_In_ COLORREF color   //画笔的颜色
	// 							);
	HPEN hpen = CreatePen(PS_SOLID, 5, RGB(0, 0, 255));
	HGDIOBJ oldPen= SelectObject(hdc,hpen);   //将新建的画笔交换出去 画图
	MoveToEx(hdc, 256 * 2, 0,NULL);
	for (int i = 256 * 2; i < 256 * 3; ++i)
	{
		for (int j = 0; j < 256; ++j)
		{
			LineTo(hdc, i, j);
		}
	}
	SelectObject(hdc, oldPen); //将画笔交换回来
	BOOL ret = DeleteObject(hpen); //释放创建的画笔

	//HBRUSH hBrush=CreateSolidBrush(RGB(0, 255, 0));
	HBRUSH hBrush = CreateHatchBrush(HS_CROSS, RGB(0, 255, 0));
	HGDIOBJ hOld = SelectObject(hdc, hBrush);
	Rectangle(hdc, 256 * 2, 256, 256 * 3, 256 * 2);

	SelectObject(hdc, hOld);
	DeleteObject(hBrush);

	//Drawn BMP
	//1、添加位图资源
	//2、加载BitMap
	HBITMAP hBitmap = LoadBitmap(hInstance, (char*)IDB_BITMAP1);
	//3、创建一块和当前DC（hdc）相匹配的内存DC
	HDC hMemDC=CreateCompatibleDC(hdc);  //创建内存DC并构建一个虚拟区域，虚拟DC（hMemDC）在虚拟区域中绘图
	//4、利用SelectObject将虚拟内存DC送给绘图DC
	HGDIOBJ hOldDC=SelectObject(hMemDC, hBitmap);//将位图数据送给内存DC，内存DC在虚拟区域中将位图绘制出来
	//5、将虚拟区域绘制好的位图成像到窗口中  BitBlt函数是一比一的成像
	BitBlt(hdc, 256 * 3+10, 0, 48, 48, hMemDC, 0, 0, SRCCOPY);   //SRCCOPY---原样成像
	StretchBlt(hdc, 256 * 3 + 10, 48, 24 , 24, hMemDC, 0, 0, 48,48,SRCCOPY);  //缩放/放大成像
	StretchBlt(hdc, 256 * 3 + 10, 96, 96 , 96, hMemDC, 0, 0, 48,48,SRCCOPY);  //缩放/放大成像
	//6、将hOldDC和hMemDC还回
	SelectObject(hMemDC, hOldDC);
	//7、释放内存位图
	DeleteObject(hBitmap);
	//8、释放内存DC
	DeleteDC(hMemDC);

	//TextOut()---将文字绘制在指定的位置处，不支持换行、没有对齐方式
	//DrawText(HDC hdc,LPCTSTR lpString,int nCount(字符数量),LPRECT lpRECT(绘制文字的矩形),UINT uFormat（绘制的方式）);
	//DrawText支持换行，支持绘制方式(在矩形区域的左边\右边\上\下\垂直等等).
	RECT rc = {256 * 3,256,256 * 3 + 256,256 + 256};
	SetTextColor(hdc, RGB(255, 0, 0));        //只适用于不透明模式下
	//SetBkColor(hdc, RGB(0, 255, 0));   //字符串的默认背景色是白色
	SetBkMode(hdc, TRANSPARENT);     //设置字符串的背景模式(透明模式(TRANSPARENT)|不透明模式(OPAQUE 默认))
	//设置字体
	HFONT hFont = CreateFont(30,0,45,0,900,1,1,1,GB2312_CHARSET,0,0,0,0,"黑体");
	hOld = SelectObject(hdc, hFont);
	DrawText(hdc, "我爱你中国!", strlen("我爱你中国"), &rc, DT_LEFT | DT_TOP);

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
	HWND hmainwnd = CreateWindow("MyWin", szTitle, WS_OVERLAPPEDWINDOW, 720, 360, 720+720, 540+360, nullptr, nullptr, hInstance, 0);
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
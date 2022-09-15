#include<windows.h>
#include<iostream>


/*
 WINAPI  --是调用约定，一个调用约定定义了一个函数从主叫方接受参数。
			如，它定义了参数在堆栈上出现的顺序。只需要确保按如下所示声明您的wWinMain函数即可。
int WINAPI WinMain(
_In_ 表示是输入参数  HINSTANCE hInstance,           //实例的句柄，windows中h开头的一般都是操作句柄handle的缩写
_In_opt_ HINSTANCE hPrevInstance,          //没有任何意义，它在16位windows中使用，但现在始终是零。
_In_ LPSTR lpCmdLine,                   //包含命令行参数作为	Unicode字符串
_In_ int nShowCmd)                      //是一个标志，指示主应用程序窗口是最小化，最大化还是正常显示
                              //返回值是一个int值，操作系统不使用该值，但是您可以使用该值将状态码传送给其他程序
*/

LPCTSTR clsName = (LPCTSTR)"MyWindow";
LPCTSTR msgName = (LPCTSTR)"欢迎学习Windows编程";
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
		sprintf_s(szChar, "你刚才按下了:%c", wParam);
		MessageBox(hwnd,szChar,"char",NULL);
		break;
	case WM_LBUTTONDOWN:
		MessageBox(hwnd, "检测到您按下了鼠标左键", "鼠标消息", NULL);
		break;
	case WM_PAINT:
		PAINTSTRUCT ps;
		hdc = BeginPaint(hwnd, &ps);
		TextOut(hdc, 0, 0, "Congratulations!", strlen("Congratulations!"));
		EndPaint(hwnd, &ps);
		MessageBox(hwnd, "重绘", "msg", NULL);
		break;
	case WM_CLOSE:
		ret = MessageBox(hwnd, "是否真的结束?","msg", MB_YESNO);
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
	//1、定义个配置窗口对象
	WNDCLASS window;
	window.cbClsExtra = NULL;
	window.cbWndExtra = NULL;
	window.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	window.hCursor = LoadCursor(NULL, IDC_ARROW);
	window.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	window.hInstance = hInstance;

	//2、定义交互响应
	window.lpfnWndProc = MyWinProc;   //窗口的回调函数
	window.lpszClassName = clsName;
	window.lpszMenuName = NULL;
	window.style = CS_HREDRAW | CS_VREDRAW;

	//3、注册窗口类
	RegisterClass(&window);
	//4、创建窗口
	HWND hwnd = CreateWindow(clsName,msgName,WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,CW_USEDEFAULT,CW_USEDEFAULT,CW_USEDEFAULT,NULL,NULL,hInstance, NULL);
	//5、显示和刷新窗口
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
//	UINT        style;                //类型，该成员可以是Class Style的任何组合---系统类、应用程序全局类、应用程序本地类
									
//										
//	WNDPROC     lpfnWndProc;         //窗口过程函数---函数指针，必须使用CallWindowProc函数来调用窗口过程函数。
//	int         cbClsExtra;          //按照窗口类结构分配的额外字节数。系统将字节初始化为零。
//	int         cbWndExtra;          //在窗口实例之后分配的额外字节数。系统将字节初始化为零。如果应用程序使用WNDCLASS在资源
//										文件中注册使用CLASS指令创建的对话框，则必须将此成员设置为DLGWINDOWEXTRA.
//	HINSTANCE   hInstance;          //包含类的窗口过程实例的句柄。
//	HICON       hIcon;                //类图标的句柄。此成员必须是游标资源的句柄。如果此成员是NULL，则应用程序必须在鼠标移入应用程序
//										窗口时显示设置光标形状。
//	HCURSOR     hCursor;           //类背景画笔句柄。该成员可以是用于绘制背景的物理画笔的句柄，也可以是颜色值。颜色值必须是一下标准系统颜色之一(必须将
//										值1添加到所选颜色)。如果给定了颜色值，则必须将其转换为一下HBRUSH类型之一.
//									使用UnregisterClass 注销班级时，系统会自动删除班级背景画笔。应用程序不应删除这些画笔。当此成员为NULL时，
//									应用程序必须在被请求在其客户区域中绘制时绘制自己的背景。要确定是否必须绘制背景，应用程序可以处理 WM_ERASEBKGND消息或测试
//									 由BeginPaint函数填充的PAINTSTRUCT结构的fErase成员。
//	HBRUSH      hbrBackground;
//	LPCWSTR     lpszMenuName;      类菜单的资源名称，该名称出现在资源文件中。如果您使用整数来标识菜单，
//									请使用MAKEINTRESOURCE宏。如果此成员为NULL，则属于此类的窗口没有默认菜单。
//	LPCWSTR     lpszClassName;		指向以 null 结尾的字符串的指针，或者是一个原子。如果此参数是原子，则它必须是由先前调用RegisterClass或
//									RegisterClassEx函数创建的类原子。原子必须在 lpszClassName的低位词中；高位字必须为零。
//									如果lpszClassName是一个字符串，它指定窗口类名。类名可以是使用RegisterClass或RegisterClassEx 注册的任何名称，也可以是任何预定义的控件类名称。
//									lpszClassName的最大长度为256。如果lpszClassName大于最大长度，RegisterClass函数将失败
//} WNDCLASSW, * PWNDCLASSW, NEAR* NPWNDCLASSW, FAR* LPWNDCLASSW;
//#ifdef UNICODE
//typedef WNDCLASSW WNDCLASS;
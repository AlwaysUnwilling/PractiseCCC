//#include<windows.h>   //不能与#include<winsock2.h> 同时包含，胡重复包含

#include<winsock2.h>
#include<iostream>
#include <Ws2tcpip.h>


#pragma comment(lib,"ws2_32.lib")

int main()
{
	std::cout << "TcpServer!" << std::endl;

	//初始化网络库
	// 加载套接字库
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


	SOCKET listenSock = -1;
	listenSock	= socket(AF_INET, SOCK_STREAM, 0);
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
		char sendBuff[1024];
		/*错误    C4996    'inet_ntoa': Use inet_ntop() or InetNtop() instead or define _WINSOCK_DEPRECATED_NO_WARNINGS to disable deprecated API warnings    Server    c:\users\wh\desktop\server\server\server.cpp    55
		解决方法：将inetntoa改为inet_ntop()或者 InetNtop() #include <Ws2tcpip.h>  头文件*/
		sprintf_s(sendBuff, sizeof(sendBuff), "Welcome %s to Connect me!",inet_ntoa(peer.sin_addr));
		std::cout << "------sendBuff----" << sendBuff << std::endl;
		int sendLen = send(sock, sendBuff, strlen(sendBuff), 0);
		char revBuff[1024] = { 0 };
		int revLen = recv(sock, revBuff, sizeof(revBuff), 0);
		if (revLen > 0)
		{
			revBuff[revLen - 1] = 0;
		}
		std::cout << "Client # " << revBuff << std::endl;
		closesocket(sock);
	}

	system("pause");
	if (listenSock >= 0) {
		closesocket(listenSock);
	}
	WSACleanup();

	return 0;
}
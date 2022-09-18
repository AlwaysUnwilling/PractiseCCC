#include<iostream>
#include<windows.h>
#include<cstdio>
#include<cstring>
#include<string>
//#include<WinSock2.h>

#pragma comment(lib,"ws2_32.lib")


inline void ErrorHandling(const char* msg)
{
	std::cout << "´íÎóÐÅÏ¢£º" << std::endl;
	if (msg != nullptr)
	{
		fputs(msg, stderr);   //´òÓ¡´íÎóÂë
		fputc('\n', stderr);  //»»ÐÐ
	}
	else
	{
		std::cout << "Î´Öª´íÎó£¡" << std::endl;
	}
}
int main()
{
	std::cout << "TcpServer!" << std::endl;

	//³õÊ¼»¯ÍøÂç¿â
	// ¼ÓÔØÌ×½Ó×Ö¿â
	WORD wVersionRequested;
	WSADATA wsaData;
	int err;

	wVersionRequested = MAKEWORD(1, 1);
	// ³õÊ¼»¯Ì×½Ó×Ö¿â
	err = WSAStartup(wVersionRequested, &wsaData);
	if (err != 0)
	{
		ErrorHandling("WSAStartup error!");
		return err;
	}

	if (LOBYTE(wsaData.wVersion) != 1 || HIBYTE(wsaData.wVersion) != 1)
	{
		WSACleanup();
		ErrorHandling("LOBYTE or HIBYTE error!");
		return -1;
	}


	SOCKET listenSock = -1;
	listenSock = socket(AF_INET, SOCK_STREAM, 0);
	if (listenSock == INVALID_SOCKET)
	{
		ErrorHandling("socket error!");
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
		ErrorHandling("bind error!");
		return -3;
	}
	if (listen(listenSock, 5) < 0)
	{
		ErrorHandling("listen error!");
		return -4;
	}
	SOCKADDR_IN peer;
	int len = sizeof(peer);


	while (TRUE)
	{
		SOCKET sock = accept(listenSock, (SOCKADDR*)&peer, &len);
		if (sock == SOCKET_ERROR)
		{
			ErrorHandling("accept error!");
			continue;
		}
		std::cout << "get a link...." << std::endl;
		char revBuff[1024] = { 0 };
		int revLen = recv(sock, revBuff, sizeof(revBuff), 0);
		if (revLen > 0)
		{
			revBuff[revLen] = 0;
		}
		std::cout << "File Content # " << revBuff << std::endl;
		closesocket(sock);
	}

	system("pause");
	if (listenSock >= 0) {
		closesocket(listenSock);
	}
	WSACleanup();

	return 0;
}
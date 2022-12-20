#include<windows.h>

#include<iostream>

#pragma comment(lib,"ws2_32.lib")

int main()
{
	std::cout << "TCP Server..." << std::endl;

	WORD wVersionRequested;
	WSADATA wsaData;
	int err;
	wVersionRequested = MAKEWORD(2, 2);
	err = WSAStartup(wVersionRequested, &wsaData);
	if (err != 0)
	{
		std::cout << "WSAStartup errorNum=" << GetLastError() << std::endl;
		return err;
	}
	if (LOBYTE(wsaData.wVersion) != 2 || HIBYTE(wsaData.wVersion != 2))
	{
		std::cout << "LOBYTE errorNum=" << GetLastError() << std::endl;
		WSACleanup();
		return -3;
	}
	SOCKET sockSrv = socket(AF_INET, SOCK_STREAM, 0);
	SOCKADDR_IN local;
	local.sin_family = AF_INET;
	local.sin_port = htons(8080);
	local.sin_addr.S_un.S_addr = htonl(INADDR_ANY);

	int len = sizeof(local);
	if (bind(sockSrv, (SOCKADDR*)&local, len)<0)
	{
		std::cout << "bind error!" << std::endl;
		return -1;
	}

	if (listen(sockSrv, 5) < 0)
	{
		std::cout << "listen error!" << std::endl;
		return -2;
	}
	SOCKADDR_IN peer;
	len = sizeof(peer);
	

	
	while (TRUE)
	{
		SOCKET sock;
		if ( sock= accept(sockSrv, (SOCKADDR*)&peer, &len) < 0)
		{
			std::cout << "warning :accept fail!" << std::endl;
			continue;
		}
		std::cout << "connect success!" << std::endl;
		char buff[1024] = { 0 };
		sprintf_s(buff, 1024, "ID :%s", inet_ntoa(peer.sin_addr));
		std::cout << buff << std::endl;
		char buff1[1024] = {0};
		//Sleep(2000);
		//int recvSize = recv(sock, buff1, 1023, 0);
// 		while(recv(sock, buff1, 1023, 0)<=0)
// 		{
// 			std::cout << "recv fail!" << std::endl;
// 			//closesocket(sock);
// 			continue;
// 		}
		if (send(sock, buff,sizeof(buff), 0) < 0)
		{
			std::cout << "send fail!" << std::endl;
			closesocket(sock);
		}
	}
	WSACleanup();
	closesocket(sockSrv);

	return 0;
}
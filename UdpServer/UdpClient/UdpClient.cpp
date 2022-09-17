#include<WinSock2.h>
#include<iostream>
#include<cstdio>
#include<cstring>
#include<string>

#pragma comment(lib,"ws2_32.lib")

int main()
{
	//³õÊ¼»¯ÍøÂç¿â
	WORD wVersion;
	WSADATA wsaData;
	int err;

	wVersion = MAKEWORD(2, 2);
	err = WSAStartup(wVersion, &wsaData);
	if (err != 0)
	{
		return err;
	}

	if (LOBYTE(wsaData.wVersion) != 2 || HIBYTE(wsaData.wVersion) != 2)
	{
		WSACleanup();
		return -1;
	}

	SOCKET sock = socket(AF_INET, SOCK_DGRAM, 0);
	if (sock == INVALID_SOCKET)
	{
		std::cerr << "socket error!" << std::endl;
		return 1;
	}
	SOCKADDR_IN peer;
	peer.sin_family = AF_INET;
	peer.sin_addr.S_un.S_addr = inet_addr("192.168.2.2");
	peer.sin_port = htons(8888);

	std::string sendBuf;
	char recvBuf[1024] = { 0 };
	while (TRUE)
	{
		sendBuf.clear();
		std::cout << "Please Enter Message: ";
		fflush(stdout);
		getline(std::cin, sendBuf);
		if (sendto(sock, sendBuf.c_str(), sendBuf.size(), 0, (SOCKADDR*)&peer, sizeof(peer)) < 0)
		{
			std::cerr << "sendto error!" << std::endl;
			return 3;
		}
		*recvBuf = 0;
		int recvLen = recvfrom(sock, recvBuf, 1023, 0, NULL, NULL);
		if (recvLen > 0)
		{
			recvBuf[recvLen] = 0;
			std::cout << "Server echo # " << recvBuf << std::endl;
		}
		else
		{
			std::cerr << "recvfrom error!" << std::endl;
			return 4;
		}
	}

	system("pause");
	closesocket(sock);
	WSACleanup();
	return 0;
}
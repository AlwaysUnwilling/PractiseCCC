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
	std::cout << "Server running..." << std::endl;

	SOCKET sock = socket(AF_INET, SOCK_DGRAM, 0);
	if (sock == INVALID_SOCKET)
	{
		std::cerr << "socket error!" << std::endl;
		return 1;
	}

	SOCKADDR_IN local;
	local.sin_family = AF_INET;
	local.sin_addr.S_un.S_addr = htonl(INADDR_ANY);
	local.sin_port = htons(8888);

	if (bind(sock, (SOCKADDR*)&local, sizeof(local)) == SOCKET_ERROR)
	{
		std::cerr<<"bind error!"<<std::endl;
		return 2;
	}

	SOCKADDR_IN peer;
	peer.sin_family = AF_INET;
	int len = sizeof(peer);

	std::string sendBuf;
	char recvBuf[1024] = { 0 };
	while (TRUE)
	{
		*recvBuf = 0;
		int recvLen = recvfrom(sock, recvBuf, 1023, 0, (SOCKADDR*)&peer, &len);
		if (recvLen > 0)
		{
			recvBuf[recvLen] = 0;
			std::cout << "Client IP:" << inet_ntoa(peer.sin_addr)
				<< " Client Port: " << ntohs(peer.sin_port) << std::endl;
			std::cout << "Client # " << recvBuf << std::endl;
		}

		sendBuf = "Server recv your message!";
		if (sendto(sock, sendBuf.c_str(), sendBuf.size(),0,(SOCKADDR*)&peer, sizeof(peer)) < 0)
		{
			std::cerr << "sendto error!" << std::endl;
			return 3;
		}

	}

	system("pause");
	closesocket(sock);
	WSACleanup();
	return 0;
}
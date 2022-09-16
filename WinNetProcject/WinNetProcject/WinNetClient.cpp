#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include<winsock2.h>
#include <Ws2tcpip.h>
#include<iostream>
#include<cstdio>
#include<string>

#pragma comment(lib,"ws2_32.lib")

int main()
{
	std::cout << "TcpClient!" << std::endl;

	//³õÊ¼»¯ÍøÂç¿â
	//¼ÓÔØÌ×½Ó×Ö¿â

	WORD wVersionRequested;
	WSADATA wsaData;
	int err;

	wVersionRequested = MAKEWORD(1, -1);
	//³õÊ¼»¯Ì×½Ó×Ö¿â
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
	peer.sin_addr.S_un.S_addr =inet_addr(address.c_str()) ;
	peer.sin_port = htons(8888);

	if (connect(sock, (SOCKADDR*)&peer, sizeof(peer)) < 0)
	{
		std::cout << "connect fail !" << std::endl;
		return -3;
	}

	std::string sendMsg;
	while (TRUE)
	{
		char revMsg[1024] = { 0 };

		int revLen = recv(sock, revMsg, sizeof(revMsg), 0);

		if (revLen)
		{
			std::cout << "Server $ " << revMsg << std::endl;
		}
		else
		{
			std::cerr << "recv error!" << std::endl;
			break;
		}

		sendMsg.clear();
		std::cout << "Client # ";
		fflush(stdout);
		std::getline(std::cin, sendMsg);
		if (send(sock, sendMsg.c_str(), sendMsg.size(), 0) < 0)
		{
			std::cerr << "send error!" << std::endl;
			break;
		}
	}

	system("pause");
	closesocket(sock);
	WSACleanup();

	return 0;
}
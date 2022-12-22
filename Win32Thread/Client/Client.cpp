#include<windows.h>
#include<process.h>
#include<iostream>
#include<set>

#pragma comment(lib,"ws2_32.lib")

HANDLE hRecv;
HANDLE hSend;

int main(int argc,char* argv[])
{
	if (argc != 2)
	{
		std::cout << "you should input your netname..." << std::endl;
		return -1;
	}
	if (strlen(argv[1]) > 32)
	{
		std::cout << "your name too long ...." << std::endl;
		return -2;
	}
	char name[32] = { 0 };
	strcpy(name, argv[1]);
	std::cout << "This is Client...." << std::endl;
	WORD wVersionRequested;
	WSADATA wsaData;
	int err;
	wVersionRequested = MAKEWORD(1, 1);
	err = WSAStartup(wVersionRequested, &wsaData);
	if (err != 0)
	{
		std::cout << "WSAStartup errorNum=" << GetLastError() << std::endl;
		return err;
	}
	if (LOBYTE(wsaData.wVersion) != 1 || HIBYTE(wsaData.wVersion != 1))
	{
		std::cout << "LOBYTE errorNum=" << GetLastError() << std::endl;
		WSACleanup();
		return -3;
	}

	SOCKET sock = socket(AF_INET, SOCK_STREAM, 0);
	if (sock < 0)
	{
		std::cout << "socket err!" << std::endl;
		return -4;
	}
	SOCKADDR_IN server;
	server.sin_addr.S_un.S_addr = inet_addr("192.168.2.4");
	server.sin_family = AF_INET;
	server.sin_port = htons(8888);
	int len = sizeof(server);

	if (connect(sock, (SOCKADDR*)&server, len) < 0)
	{
		std::cout << "connect err!" << std::endl;
		return -5;
	}

	char buff[1024] = { 0 };
	char msg[1024] = { 0 };
	char recvMsg[1024] = { 0 };
	while (TRUE)
	{
		memset(buff, 0, sizeof(buff));
		fgets(buff, 1023, stdin);
		std::cout << "Client inputs:" << buff << std::endl;
		buff[strlen(buff)] = 0;
		if (strncmp(buff, "goodbye",strlen("goodbye")) == 0)
		{
			std::cout << "byebye" << std::endl;
			closesocket(sock);
			break;
		}
		sprintf_s(msg, "[%s]: %s", name, buff);
		std::cout << "Client msg:" << msg << std::endl;
		send(sock, msg, strlen(msg), 0);

		int rLen=recv(sock, recvMsg, 1023, 0);
		if(rLen>0)
			std::cout << recvMsg << std::endl;
	}
	closesocket(sock);
	return 0;
}
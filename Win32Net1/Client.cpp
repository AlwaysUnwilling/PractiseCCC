#include<windows.h>
#include<iostream>

#pragma comment(lib,"ws2_32.lib")


int main()
{
	std::cout << "TCP Client..." << std::endl;

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
	if (sockSrv < 0)
	{
		std::cout << "socket err!" << std::endl;
		return -1;
	}
	SOCKADDR_IN peer;
	peer.sin_family = AF_INET;
	peer.sin_addr.S_un.S_addr = inet_addr("192.168.2.4");
	peer.sin_port = htons(8080);

	if (connect(sockSrv, (SOCKADDR*)&peer, sizeof(peer)) < 0)
	{
		std::cout << "connect err!" << std::endl;
		return -2;
	}
	char buff[1024] = { 0 };
	std::string msg("hello");
	std::cout << "sockSrv=" << sockSrv << std::endl;
	while (TRUE)
	{
// 		int sendSize = 0;
// 		if (sendSize=send(sockSrv, msg.c_str(),msg.size(),0) < 0)
// 		{
// 			std::cout << "client send err!" << std::endl;
// 			closesocket(sockSrv);
// 			return -3;
// 		}
// 		std::cout << "sendSize=" << sendSize << std::endl;
		if (recv(sockSrv, buff, 1023, 0) < 0)
		{
			std::cout << "recv err!" << std::endl;
			closesocket(sockSrv);
			return -4;
		}
		std::cout << buff << std::endl;
	}
	WSACleanup();
	if (sockSrv >= 0)
		closesocket(sockSrv);
	return 0;
}
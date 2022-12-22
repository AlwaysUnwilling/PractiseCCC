#include<windows.h>
#include<process.h>
#include<iostream>
#include<set>
#include<vector>

#pragma comment(lib,"ws2_32.lib")

HANDLE hMutex;
std::set<SOCKET> st;
std::vector<HANDLE> vhandle;

UINT CALLBACK client_handle(void* arg)
{
	SOCKET sock = *((SOCKET*)arg);
	int rLen = 0;
	char buff[1024] = { 0 };
	while (TRUE)
	{
		rLen = recv(sock, buff, 1023, 0);
		if (rLen < 0)
		{
			std::cout << "client quit..." << std::endl;
			closesocket(sock);
			WaitForSingleObject(hMutex, INFINITE);
			st.erase(sock);
			ReleaseMutex(hMutex);
			break;
		}
		std::cout << buff << std::endl;
		WaitForSingleObject(hMutex, INFINITE);
		auto it = st.begin();
		while (it != st.end())
		{
			send(*it, buff, strlen(buff), 0);
			++it;
		}
		ReleaseMutex(hMutex);
	}

	return 0;
}
int main()
{
	std::cout << "This is Server...." << std::endl;
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

	hMutex = CreateMutex(NULL, FALSE, NULL);
	

	SOCKET listenSock = socket(AF_INET, SOCK_STREAM, 0);
	if (listenSock < 0)
	{
		std::cout << "socket err!" << std::endl;
		return -4;
	}
	SOCKADDR_IN server;
	server.sin_addr.S_un.S_addr = htonl(INADDR_ANY);
	server.sin_family = AF_INET;
	server.sin_port = htons(8888);

	if (bind(listenSock, (SOCKADDR*)&server, sizeof(server)) < 0)
	{
		std::cout << "bind err!" << std::endl;
		return -5;
	}
	if (listen(listenSock, 5) < 0)
	{
		std::cout << "listen err!" << std::endl;
		return -5;
	}
	SOCKET sock = -1;
	SOCKADDR_IN peer;
	int len = sizeof(peer);
	
	while (TRUE)
	{
		sock = accept(listenSock, (SOCKADDR*)&peer, &len);
		if (sock < 0)
		{
			continue;
		}
		std::cout << "a client link..." << std::endl;
		WaitForSingleObject(hMutex, INFINITE);
		st.insert(sock);
		ReleaseMutex(hMutex);
		HANDLE hThread=(HANDLE)_beginthreadex(NULL, 0, client_handle, &sock, 0, NULL);
		vhandle.push_back(hThread);
	}
	WaitForMultipleObjects(vhandle.size(), &vhandle[0], TRUE, INFINITE);
	return 0;
}
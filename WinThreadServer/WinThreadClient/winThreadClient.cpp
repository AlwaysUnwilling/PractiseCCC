#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include<winsock2.h>
#include<iostream>
#include <Ws2tcpip.h>
#include<vector>

/*�ͻ��ˣ� 1�������������ߣ�2������Ϣ��3���ȴ�����˷���Ϣ��4���ȴ��û��Լ��Ĺر�(����)*/
#pragma comment(lib,"ws2_32.lib")

#define NAME_SIZE 256
#define MAX_BUF_SIZE 1024

HANDLE hMutex = 0;
char szName[NAME_SIZE] = "[DEFAULT]";         //Ĭ���ǳ�
char szMsg[MAX_BUF_SIZE] = { 0 };       //�շ����ݵ�buf

DWORD CALLBACK Routine2SendMsg(LPVOID arg)
{
	SOCKET sock = (SOCKET)arg;
	char szNameMsg[NAME_SIZE + MAX_BUF_SIZE] = { 0 }; 
	while (TRUE)
	{
		WaitForSingleObject(hMutex, INFINITE);
		memset(szMsg, 0, MAX_BUF_SIZE);
		fgets(szMsg, MAX_BUF_SIZE, stdin);
		//�ж��Ƿ���������Ϣ
		if (!strcmp(szMsg, "Q\n") || !strcmp(szMsg, "q\n"))
		{
			ReleaseMutex(hMutex);
			closesocket(sock);
			return 0;
		}
		sprintf(szNameMsg, "%s%s", szName, szMsg);
		send(sock, szNameMsg, MAX_BUF_SIZE, 0);
		ReleaseMutex(hMutex);
	}
	return 0;
}
DWORD CALLBACK Routine2RecvMsg(LPVOID arg)
{
	SOCKET sock = (SOCKET)arg;
	char szNameMsg[NAME_SIZE + MAX_BUF_SIZE] = { 0 };
	while (TRUE)
	{
		WaitForSingleObject(hMutex, INFINITE);
		memset(szNameMsg, 0, NAME_SIZE + MAX_BUF_SIZE);
		int recvLen = recv(sock, szNameMsg, NAME_SIZE + MAX_BUF_SIZE,0);
		if (recvLen < 0)
		{
			ReleaseMutex(hMutex);
			return 2;
		}
		szNameMsg[recvLen] = 0;
		ReleaseMutex(hMutex);
		std::cout << szNameMsg << std::endl;
	}
	return 0;
}

int main(int argc,char* argv[])
{
	if (argc != 2)
	{
		std::cout << "Usage:\n\t";       //shift + ����Ҽ� ���� �������еķ�ʽ����power shell
		std::cout << "winThreadClient.exe szName" << std::endl;
		return -999;
	}
	sprintf(szName, "[%s]", argv[1]);
	std::cout << "TcpClient!" << std::endl;

	//��ʼ�������
	//�����׽��ֿ�

	WORD wVersionRequested;
	WSADATA wsaData;
	int err;

	wVersionRequested = MAKEWORD(1, -1);
	//��ʼ���׽��ֿ�
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
	peer.sin_addr.S_un.S_addr = inet_addr(address.c_str());
	peer.sin_port = htons(8888);

	if (connect(sock, (SOCKADDR*)&peer, sizeof(peer)) < 0)
	{
		std::cout << "connect fail !" << std::endl;
		return -3;
	}
	std::cout << "client has already connected." << std::endl;

	HANDLE hsendThr = CreateThread(NULL, 0, Routine2SendMsg, (LPVOID)sock,0,NULL);
	HANDLE hrecvThr = CreateThread(NULL, 0, Routine2RecvMsg, (LPVOID)sock, 0, NULL);
	std::vector<HANDLE> harr;
	harr.push_back(hsendThr);
	harr.push_back(hrecvThr);

	WaitForMultipleObjects(2, &harr[0], TRUE, INFINITE);
	CloseHandle(hMutex);
	if (sock >= 0)
	{
		closesocket(sock);
	}
	WSACleanup();
	return 0;
}
#include<winsock2.h>
#include<iostream>
#include <Ws2tcpip.h>


#pragma comment(lib,"ws2_32.lib")

int MySocketRecv(int sock, char* buf, int dataSize)
{
	//ѭ������
	int numsRecvSoFar = 0;             //Ŀǰ���ܵ������ݴ�С(�ֽ�)
	int numsRemainingToRecv = dataSize;     //ʣ��Ҫ���ܵ����ݴ�С(�ֽ�)
	std::cout << "enter MySocketRecv()" << std::endl;
	while (TRUE)
	{
		int bytesRead = recv(sock, &buf[numsRecvSoFar], numsRemainingToRecv, 0);
		if (bytesRead == numsRemainingToRecv)              //һ���Խ�����
		{
			return 0;
		}
		else if (bytesRead > 0)
		{
			numsRecvSoFar += bytesRead;
			numsRemainingToRecv -= bytesRead;
			continue;
		}
		else if (bytesRead < 0 && bytesRead == EAGAIN)
		{
			std::cout << "��ʱ�����ݿɶ����Ժ�..." << std::endl;
			continue;
		}
		else 
		{
			std::cout << "���ͷ��Ͽ�����!" << std::endl;
			return -1;
		}

	}
}

int MySocketsend(int sock, unsigned char* data, unsigned dataSize)
{
	unsigned numBytesSendSoFar = 0;                        //Ŀǰ�Ѿ����͵õ����ݴ�С
	unsigned numBytesRemainingToSend = dataSize;         //ʣ��Ҫ���͵����ݴ�С
	while (TRUE)
	{
		int bytesSend = send(sock, reinterpret_cast<char* const>(&data[numBytesSendSoFar]), numBytesRemainingToSend, 0);
		if (bytesSend == numBytesRemainingToSend)
		{
			return 0;
		}
		else if (bytesSend > 0)
		{
			numBytesSendSoFar += bytesSend;
			numBytesRemainingToSend -= bytesSend;
			continue;
		}
		else if (bytesSend < 0 && errno == 11)
		{
			std::cout << "����..." << std::endl;
			continue;
		}
		else
		{
			std::cout<< "����ʧ�ܣ�" << std::endl;
			return -1;
		}
	}
}

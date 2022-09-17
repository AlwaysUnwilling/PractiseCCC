#include<winsock2.h>
#include<iostream>
#include <Ws2tcpip.h>


#pragma comment(lib,"ws2_32.lib")

int MySocketRecv(int sock, char* buf, int dataSize)
{
	//循环接受
	int numsRecvSoFar = 0;             //目前接受到的数据大小(字节)
	int numsRemainingToRecv = dataSize;     //剩余要接受的数据大小(字节)
	std::cout << "enter MySocketRecv()" << std::endl;
	while (TRUE)
	{
		int bytesRead = recv(sock, &buf[numsRecvSoFar], numsRemainingToRecv, 0);
		if (bytesRead == numsRemainingToRecv)              //一次性接收完
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
			std::cout << "暂时无数据可读，稍后..." << std::endl;
			continue;
		}
		else 
		{
			std::cout << "发送方断开连接!" << std::endl;
			return -1;
		}

	}
}

int MySocketsend(int sock, unsigned char* data, unsigned dataSize)
{
	unsigned numBytesSendSoFar = 0;                        //目前已经发送得到数据大小
	unsigned numBytesRemainingToSend = dataSize;         //剩余要发送的数据大小
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
			std::cout << "重试..." << std::endl;
			continue;
		}
		else
		{
			std::cout<< "发送失败！" << std::endl;
			return -1;
		}
	}
}

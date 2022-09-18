#include<iostream>
#include<vector>
#include<windows.h>
#include<process.h>
#include<array>

int tickets = 1000;
#define THREAD_NUM 8

DWORD BuyTickets(LPVOID arg)
{
	while (TRUE)
	{
		if (tickets > 0)
		{
			Sleep(500);
			std::cout << "ThreadID:" << GetCurrentThreadId()
				<< " got a tickets..."
				<< "tickets left: " << (--tickets) << std::endl;
			
		}
		else 
		{
			break;
		}
	}
	return 0;
}
int main()
{
	std::vector<HANDLE> threadHandle(THREAD_NUM, 0);
	//HANDLE threadHandle[THREAD_NUM];
	//std::array<HANDLE ,THREAD_NUM> threadHandle;
	std::vector<DWORD> threadID(THREAD_NUM,0);
	for (int i = 0; i < THREAD_NUM; ++i)
	{
		threadHandle[i]=CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE)BuyTickets, &threadID, 0, &threadID[i]);
	}
	
	for (auto ID : threadID)
	{
		std::cout << "ID: " << ID << std::endl;
	}

	//windows��������̲߳�ȥ�ȴ��������߳����н�������ô������߳�ִ����Ϻ�ֱ���˳�
	//�ᵼ�������߳�ֱ�ӱ����������쳣
	//��linux�����̵߳ȴ����߳��˳���Ҫjoin;windows����Ҫʹ��
	// 
	// 	WaitForSingleObject(                //�ȴ������߳��˳�
	// 		_In_ HANDLE hHandle,  //��Ҫ���ȴ������̲߳������
	// 		_In_ DWORD dwMilliseconds       //�ȴ�ʱ��---INFINITE--���ĵȴ�ʱ��(0xFFFFFFFF)
	// 	);

	//�ȴ�������߳��˳�
	// 	DWORD
	// 		WINAPI
	// 		WaitForMultipleObjects(
	// 			_In_ DWORD nCount,        //�ȴ��ĸ���
	// 			_In_reads_(nCount) CONST HANDLE * lpHandles,     //��Ŷ�����̵߳Ĳ���������׵�ַ
	// 			_In_ BOOL bWaitAll,        //TRUE��ʾ�ȴ��������߳��˳���FALSE��ʾ�ȴ�����һ�����߳��˳�.
	// 			_In_ DWORD dwMilliseconds    //�ȴ���ʱ��
	// 		);
	/*ע�⣺�����������ȴ��Ľ���п���ʧ�ܣ�������ֵ�� WAIT_FAIL ��ȴ�ʧ��*/

	//DWORD ret = -1;
	//WaitForMultipleObjects(THREAD_NUM,threadHandle, FALSE, INFINITE);
	WaitForMultipleObjects(THREAD_NUM, &threadHandle[0], FALSE, INFINITE);
	// 	if ((ret = WaitForMultipleObjects(3, reinterpret_cast<CONST HANDLE*>(&threadHandle), TRUE, INFINITE)) == WAIT_FAILED)
	// 	{
	// 		std::cout << "WaitForMultipleObjects fail!" << std::endl;
	// 		return -1;
	// 	}

	// 	for (int i = 0; i < THREAD_NUM; ++i)
	// 	{
	// 		auto ret=WaitForSingleObject(threadHandle[i], INFINITE);
	// 		if (ret == WAIT_FAILED)
	// 		{
	// 			std::cout << "ThreadID: " << threadID[i] << " fail!" << std::endl;
	// 		}
	// 	}

	for (int i = 0; i < THREAD_NUM; ++i)
	{
		CloseHandle(threadHandle[i]);
	}
	return 0;
}
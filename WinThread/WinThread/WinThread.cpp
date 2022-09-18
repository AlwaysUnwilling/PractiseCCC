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

	//windows下如果主线程不去等待其他子线程运行结束，那么如果主线程执行完毕后直接退出
	//会导致其他线程直接崩溃，引发异常
	//在linux下主线程等待子线程退出需要join;windows下需要使用
	// 
	// 	WaitForSingleObject(                //等待单个线程退出
	// 		_In_ HANDLE hHandle,  //需要被等待的子线程操作句柄
	// 		_In_ DWORD dwMilliseconds       //等待时间---INFINITE--最大的等待时间(0xFFFFFFFF)
	// 	);

	//等待多个子线程退出
	// 	DWORD
	// 		WINAPI
	// 		WaitForMultipleObjects(
	// 			_In_ DWORD nCount,        //等待的个数
	// 			_In_reads_(nCount) CONST HANDLE * lpHandles,     //存放多个子线程的操作句柄的首地址
	// 			_In_ BOOL bWaitAll,        //TRUE表示等待所有子线程退出；FALSE表示等待任意一个子线程退出.
	// 			_In_ DWORD dwMilliseconds    //等待的时间
	// 		);
	/*注意：这俩个函数等待的结果有可能失败，若返回值是 WAIT_FAIL 则等待失败*/

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
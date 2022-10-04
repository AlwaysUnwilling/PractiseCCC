#include<stdio.h>
#include<windows.h>
#include<process.h>

int tickets = 5000;
CRITICAL_SECTION g_cs;


DWORD CALLBACK SellTicketsA(LPVOID arg)
{
	while (TRUE)
	{
		EnterCriticalSection(&g_cs);
		if (tickets > 0)
		{
			Sleep(1);
			tickets--;
			printf("A remain: %d\n", tickets);
			LeaveCriticalSection(&g_cs);
		}else{
			LeaveCriticalSection(&g_cs);
			break;
		}
	}
	return 0;
}
DWORD CALLBACK SellTicketsB(LPVOID arg)
{
	while (TRUE)
	{
		EnterCriticalSection(&g_cs);
		if (tickets > 0)
		{
			Sleep(1);
			tickets--;
			printf("B remain: %d\n", tickets);
			LeaveCriticalSection(&g_cs);
		}
		else {
			LeaveCriticalSection(&g_cs);
			break;
		}
	}
	return 0;
}
int main()
{
	HANDLE hThr1, hThr2;
	hThr1 = CreateThread(NULL, 0, SellTicketsA, NULL, 0, NULL);     //�߳����ü���Ϊ2==����֮��Ϊ1���߳�ʹ�ø��ڴ�+1
	hThr2 = CreateThread(NULL, 0, SellTicketsB, NULL, 0, NULL);     //�߳����ü���Ϊ2==����֮��Ϊ1���߳�ʹ�ø��ڴ�+1
	CloseHandle(hThr1);      //�߳̾���ͷŸ��ڴ棬���ڴ����ü���-1
	CloseHandle(hThr2);         //�߳̾���ͷŸ��ڴ棬���ڴ����ü���-1
	InitializeCriticalSection(&g_cs);     //��ʼ���ؼ������
// 	WaitForSingleObject(hThr1, INFINITE);
// 	WaitForSingleObject(hThr2, INFINITE);
	Sleep(40000);
	DeleteCriticalSection(&g_cs);         //ɾ���ٽ���
	system("pause");
	return 0;
}
#include<windows.h>
#include<iostream>
#include<process.h>
#include<synchapi.h>



CRITICAL_SECTION g_cs;
int tickets = 5000;

DWORD CALLBACK TicketsWindow1(LPVOID arg)
{
	while (TRUE)
	{
		EnterCriticalSection(&g_cs);
		if (tickets > 0)
		{
			tickets--;
			std::cout << "sellorA# tickets left: " << tickets << std::endl;
			LeaveCriticalSection(&g_cs);
		}
		else
		{
			std::cout << "tickets sold out..." << std::endl;
			LeaveCriticalSection(&g_cs);
			break;
		}
	}
	return 0;
}
DWORD CALLBACK TicketsWindow2(void* arg)
{
	while (TRUE)
	{
		EnterCriticalSection(&g_cs);
		if (tickets > 0)
		{
			tickets--;
			std::cout << "sellorB# tickets left: " << tickets << std::endl;
			LeaveCriticalSection(&g_cs);
		}
		else
		{
			std::cout << "tickets sold out..." << std::endl;
			LeaveCriticalSection(&g_cs);
			break;
		}
	}
	return 0;
}

int main()
{
	HANDLE ThreadArr[2] = { 0 };
	InitializeCriticalSection(&g_cs);
	ThreadArr[0] = CreateThread(NULL, 0, TicketsWindow1, NULL, 0, NULL);
	ThreadArr[1] = CreateThread(NULL, 0, TicketsWindow2, NULL, 0, NULL);

	WaitForMultipleObjects(2, ThreadArr, TRUE, INFINITE);
	DeleteCriticalSection(&g_cs);
	CloseHandle(ThreadArr[0]);
	CloseHandle(ThreadArr[1]);

	return 0;
}




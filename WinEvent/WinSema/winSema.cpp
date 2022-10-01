#include<windows.h>
#include<iostream>
#include<vector>

HANDLE g_hSema = 0;


DWORD CALLBACK RoutineThread(LPVOID arg)
{
	while (TRUE)
	{
		WaitForSingleObject(g_hSema, INFINITE);
		std::cout << "g_hSema set a signal ..." << std::endl;
	}
	return 0;
}
int main()
{
	DWORD nID = 1;
	g_hSema = CreateSemaphore(NULL, nID, 10, NULL);
	HANDLE hThr = CreateThread(NULL, 0, RoutineThread, NULL, 0, NULL);
	while (TRUE)
	{
		//Sleep(3000);
		getchar();
		ReleaseSemaphore(g_hSema, ++nID, NULL);
	}

	WaitForSingleObject(hThr, INFINITE);
	CloseHandle(g_hSema);
	return 0;
}
#include<windows.h>
#include<iostream>
#include<vector>

DWORD nID = 0;
HANDLE hMutex = 0;

DWORD CALLBACK RoutineThread1(LPVOID arg)
{	
	//WaitForSingleObject(HANDLE(arg), INFINITE);
	while (TRUE)
	{
		WaitForSingleObject(hMutex, INFINITE);
		nID++;
		SetEvent((HANDLE)arg);
		Sleep(1000);
		ReleaseMutex(hMutex);
	}
	return 0;
}
DWORD CALLBACK RoutineThread2(LPVOID arg)
{
	while (TRUE)
	{
		WaitForSingleObject(HANDLE(arg), INFINITE);
		WaitForSingleObject(hMutex, INFINITE);
		std::cout << "nID = " << nID << std::endl;
		ResetEvent((HANDLE)arg);
		ReleaseMutex(hMutex);
	}
	return 0;
}
int main()
{
	std::vector<HANDLE> harr;
	hMutex = CreateMutex(NULL, FALSE, NULL);
	HANDLE hEvent = CreateEvent(NULL, TRUE, FALSE, NULL);
	harr.push_back(CreateThread(NULL, 0, RoutineThread1, hEvent, 0, NULL));
	harr.push_back(CreateThread(NULL, 0, RoutineThread2, hEvent, 0, NULL));

	WaitForMultipleObjects(2, &harr[0], TRUE, INFINITE);
	CloseHandle(hEvent);
	CloseHandle(hMutex);
	return 0;
}
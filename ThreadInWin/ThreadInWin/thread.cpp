#include<windows.h>
#include<iostream>
#include<vector>

DWORD CALLBACK MyThreadProc(LPVOID arg)
{
	std::cout<< "ThreadID: " << GetCurrentThreadId() << std::endl;
	while (TRUE)
	{
		std::cout << "Thread Running... " << reinterpret_cast<const char*>(arg) << std::endl;
		Sleep(1000);
	}
	return 0;
}
DWORD CALLBACK MyThreadProc1(LPVOID arg)
{
	while (TRUE)
	{
		std::cout << "Thread1 Running... " << reinterpret_cast<const char*>(arg) << std::endl;
		Sleep(1000);
	}
	return 0;
}
int main()
{
	const char* pszText = "********";
	const char* pszText1 = "++++++++";
	DWORD threadID = 0;
	HANDLE hThrd=CreateThread(NULL, 0, MyThreadProc, (LPVOID)pszText, 0, &threadID);
	HANDLE hThrd1 = CreateThread(NULL, 0, MyThreadProc1, (LPVOID)pszText1, CREATE_SUSPENDED, NULL);
	std::cout << "Main Thread get ThreadID: " << threadID << std::endl;
	getchar();
	SuspendThread(hThrd);
	ResumeThread(hThrd1);
	//WaitForSingleObject(hThrd, -1);
	std::vector<HANDLE> hv;
	hv.push_back(hThrd);
	hv.push_back(hThrd1);
	WaitForMultipleObjects(2,&hv[0], TRUE, -1);
	return 0;
}
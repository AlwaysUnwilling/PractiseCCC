#include<windows.h>
#include<iostream>
#include<vector>


long g_value = 0;
HANDLE hMutex = 0;

DWORD CALLBACK InterLock1(LPVOID arg)
{
	for (int i = 0; i < 10; ++i)
	{
		//g_value++;   //直接++存在线程安全问题   
		//InterlockedIncrement(&g_value);   //使用原子锁++
		WaitForSingleObject(hMutex, INFINITE);       //互斥锁    ---等待成功后，互斥句柄变为无信号
		g_value++;
		ReleaseMutex(hMutex);     //释放互斥句柄，互斥句柄重新变为有信号
		Sleep(1000);
	}
	return 0;
}
DWORD CALLBACK InterLock2(LPVOID arg)
{
	for (int i = 0; i < 10; ++i)
	{
		//g_value++;
		//InterlockedIncrement(&g_value);
		WaitForSingleObject(hMutex, INFINITE);       //互斥锁
		g_value++;
		ReleaseMutex(hMutex);
		Sleep(1000);
	}
	return 0;
}
int main()
{
	std::vector<HANDLE> harray;
	hMutex = CreateMutex(NULL, FALSE, NULL); //此时互斥句柄有信号的
	HANDLE hThd1=CreateThread(NULL, 0, InterLock1, NULL, 0, NULL);
	HANDLE hThd2=CreateThread(NULL, 0, InterLock2, NULL, 0, NULL);
	harray.push_back(hThd1);
	harray.push_back(hThd2);


	WaitForMultipleObjects(2, &harray[0], TRUE, INFINITE);
	std::cout << "g_value= " << g_value << std::endl;
	CloseHandle(hMutex);
	return 0;
}
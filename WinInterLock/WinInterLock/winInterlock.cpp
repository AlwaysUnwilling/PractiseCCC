#include<windows.h>
#include<iostream>
#include<vector>


long g_value = 0;
HANDLE hMutex = 0;

DWORD CALLBACK InterLock1(LPVOID arg)
{
	for (int i = 0; i < 10; ++i)
	{
		//g_value++;   //ֱ��++�����̰߳�ȫ����   
		//InterlockedIncrement(&g_value);   //ʹ��ԭ����++
		WaitForSingleObject(hMutex, INFINITE);       //������    ---�ȴ��ɹ��󣬻�������Ϊ���ź�
		g_value++;
		ReleaseMutex(hMutex);     //�ͷŻ����������������±�Ϊ���ź�
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
		WaitForSingleObject(hMutex, INFINITE);       //������
		g_value++;
		ReleaseMutex(hMutex);
		Sleep(1000);
	}
	return 0;
}
int main()
{
	std::vector<HANDLE> harray;
	hMutex = CreateMutex(NULL, FALSE, NULL); //��ʱ���������źŵ�
	HANDLE hThd1=CreateThread(NULL, 0, InterLock1, NULL, 0, NULL);
	HANDLE hThd2=CreateThread(NULL, 0, InterLock2, NULL, 0, NULL);
	harray.push_back(hThd1);
	harray.push_back(hThd2);


	WaitForMultipleObjects(2, &harray[0], TRUE, INFINITE);
	std::cout << "g_value= " << g_value << std::endl;
	CloseHandle(hMutex);
	return 0;
}
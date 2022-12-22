#include<windows.h>
#include<iostream>
#include<process.h>

UINT CALLBACK thread_routine(void* arg)
{
	while (TRUE)
	{
		printf("thread running...\n");
		Sleep(1000);
	}
	return 0;
}
int main()
{

	_beginthreadex(NULL,0,thread_routine,NULL,0,NULL);
	system("pause");
	return 0;
}
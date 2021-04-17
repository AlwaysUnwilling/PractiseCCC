#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
#include<string.h>
#include"ͨѶ¼.h"

void menu()
{
	printf("***************************************************\n");
	printf("******* 1.ADD                   2.DEL ************\n");
	printf("******* 3.SEARCH               4.MODIFY ***********\n");
	printf("******* 5.SHOW                  6.SORT ************\n");
	printf("***************  0.EXIT    ************************\n");
	printf("***************************************************\n");

}
int main()
{
	int input = 0;
	//struct PeoInfo con1;//  ����ͨѶ¼
	struct Contact con;  //con ����ͨѶ¼�����а�����data ָ�롢size��capacity
	InitContact(&con);//��ʼ��ͨѶ¼

	do
	{
		menu();
		printf("Please make a choice:");
		scanf("%d", &input);
		switch (input)
		{
		case ADD:
			AddContact(&con);
			break;
		case DEL:
			DelContact(&con);
			break;
		case SEARCH:
			SearchContact(&con);
			break;
		case MODIFY:
			ModifyContact(&con);
			break;
		case SHOW:
			ShowContact(&con);
			break;
		case SORT:
			SortContact(&con);
			break;
		case EXIT:
			//����ͨѶ¼------�ͷŶ�̬�ڴ濪�ٵ��ڴ�
			DestroyContact(&con);
			printf("Exit the contact!");
			break;
		default:
				printf("Error input,please make a choice again:");
			break;
		}
	} while (input);
	return 0;
}
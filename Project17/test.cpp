#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
#include<string.h>
#include"通讯录.h"

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
	//struct PeoInfo con1;//  创建通讯录
	struct Contact con;  //con 就是通讯录，其中包含了data 指针、size和capacity
	InitContact(&con);//初始化通讯录

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
			//销毁通讯录------释放动态内存开辟的内存
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
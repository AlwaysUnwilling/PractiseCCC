#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
#include"������.h"
void menu()
{
	printf("************************************\n");
	printf("******** 1.Play   2.Exit ***********\n");
	printf("************************************\n");
}
void game1()
{
	char ret = 0;
	char board[ROW][COL] = { 0 };//ȫ��Ϊ�ո�
	//��ʼ������
	Initboard(board, ROW, COL);
	Displayboard(board, ROW, COL);
	while (1)
	{
		PlayerMove(board, ROW, COL);//�������
		Displayboard(board, ROW, COL);
		ret = IsWin(board, ROW,COL);
		if (ret != 'C')
		{
			break;
		}
		ComputerMove(board, ROW, COL);
		Displayboard(board, ROW, COL);
		ret = IsWin(board, ROW, COL);
		if (ret != 'C')
		{
			break;
		}
	}
	if (ret == '*')
	{
		printf("��ϲ��Ӯ�ˣ�\n");
	}
	else if (ret == '#')
	{
		printf("���ϧ�������ˣ�\n");
	}
	else if (ret == 'Q')
	{
		printf("ƽ�֣�\n");
	}
}
void test()
{
	int input = 0;
	srand((unsigned int)time(NULL));
	do
	{
		menu();
		printf("��ѡ��>");
		scanf("%d", &input);
		switch (input)
		{
		case 1:
			game1();
			break;
		case 2:
			printf("�˳���Ϸ\n");
			break;
		default:
			printf("�������������ѡ��>\n");
			break;
		}
	} while (input);
}
int main()
{
	test();
	return 0;
}
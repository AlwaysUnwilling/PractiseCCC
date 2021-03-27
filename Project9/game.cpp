#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
#include"三子棋.h"
void menu()
{
	printf("************************************\n");
	printf("******** 1.Play   2.Exit ***********\n");
	printf("************************************\n");
}
void game1()
{
	char ret = 0;
	char board[ROW][COL] = { 0 };//全部为空格
	//初始化棋盘
	Initboard(board, ROW, COL);
	Displayboard(board, ROW, COL);
	while (1)
	{
		PlayerMove(board, ROW, COL);//玩家下棋
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
		printf("恭喜你赢了！\n");
	}
	else if (ret == '#')
	{
		printf("真可惜，你输了！\n");
	}
	else if (ret == 'Q')
	{
		printf("平局！\n");
	}
}
void test()
{
	int input = 0;
	srand((unsigned int)time(NULL));
	do
	{
		menu();
		printf("请选择：>");
		scanf("%d", &input);
		switch (input)
		{
		case 1:
			game1();
			break;
		case 2:
			printf("退出游戏\n");
			break;
		default:
			printf("输入错误，请重新选择：>\n");
			break;
		}
	} while (input);
}
int main()
{
	test();
	return 0;
}
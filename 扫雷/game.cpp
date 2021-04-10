#define _CRT_SECURE_NO_WARNINGS 1
#include"saolei.h"
void InitBoard(char board[ROWS][COLS], int rows, int cols,char set)
{
	int i = 0;
	int j = 0;
	for (i = 0; i < rows; i++)
	{
		for (j = 0; j < cols; j++)
		{
			board[i][j] = set;
		}
	}
}
void DisplayBoard(char board[ROWS][COLS], int row, int col)
{
	int i = 0;
	int j = 0;
	for (i = 0; i <= col; i++)
	{
		printf(" %d ", i);
	}
	printf("\n");
	for (i = 1; i <= row; i++)
	{
		printf(" %d ", i);
		for (j = 1; j <= col; j++)
		{
			printf(" %c ", board[i][j]);
		}
		printf("\n");
	}
}
void SetMine(char board[ROWS][COLS], int row, int col)
{
	int count = EASY_COUNT;
	while (count)
	{
		int x = rand() % row+1;
		int y = rand() % col+1;
		if (board[x][y] == '0')
		{
			board[x][y] = '1';
			count--;
		}
	}
}
int get_mine_count(char mine[ROWS][COLS], int x, int y)
{
     int c =mine[x][y + 1] + mine[x - 1][y + 1] + mine[x - 1][y] + mine[x - 1][y - 1] + mine[x][y - 1] + mine[x + 1][y - 1] + mine[x+1][y] + mine[x + 1][y + 1] - 8 * '0';
	 return c;
}
void display(char mine[ROWS][COLS], char show[ROWS][COLS], int x, int y)
{
	if (get_mine_count(mine, x, y) == 0)
	{
		show[x][y] = ' ';
		int i = 0;
		int j = 0;
		for (i = x - 1; i <= x + 1; i++)
		{
			for (j = y - 1; j <= y + 1; j++)
			{
				if (show[i][j] == '*' && i > 0 && i < ROWS - 1 && y>0 && y < COLS - 1)
				{
					display(mine, show, i, j);
				}
			}
		}
	}
	else
	{
		show[x][y] = get_mine_count(mine, x, y) + '0';
	}
}
int judge(char show[ROWS][COLS])
{
	int i = 1;
	int j = 1;
	int n = 0;
	for (i = 1; i <= ROW; i++)
	{
		for (j = 1; j <= COL; j++)
		{
			if (show[i][j] == '*')
			{
				n++;
			}
		}
	}
	return n;
}
void FindMine(char mine[ROWS][COLS], char show[ROWS][COLS], int row, int col)
{
	while (1)
	{
		int x = 0;
		int y = 0;
		printf("请输入排雷的坐标：>");
		scanf("%d%d", &x, &y);
		if (x<1 || x>row || y<1 || y>col)
		{
			printf("坐标非法,请重新输入!\n");
			continue;
		}
		else if (mine[x][y] == '1')
		{
			printf("真可惜，你被炸死了！\n");
			DisplayBoard(mine, row,col);
			break;
		}
		display(mine, show, x, y);
		DisplayBoard(show, row, col);
		if (judge(show) == EASY_COUNT)
		{
			printf("恭喜你！扫雷成功！\n");
			DisplayBoard(mine, row, col);
			break;
		}
	}
}
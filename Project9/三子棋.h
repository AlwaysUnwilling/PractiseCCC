
#define ROW 3
#define COL 3
void Initboard(char board[ROW][COL],int row,int col);
void Displayboard(char board[ROW][COL],int row,int col);
void PlayerMove(char board[ROW][COL],int row,int col);
void ComputerMove(char board[ROW][COL],int row,int col);
#include<stdlib.h>
#include<time.h>
char IsWin(char board[ROW][COL],int row,int col);//判断游戏结果：玩家赢返回'*';电脑赢返回'#';平局返回'Q';继续返回'C';所以函数应该为char类型
int IsFull(char board[ROW][COL], int row, int col);
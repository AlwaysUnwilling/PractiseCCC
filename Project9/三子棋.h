
#define ROW 3
#define COL 3
void Initboard(char board[ROW][COL],int row,int col);
void Displayboard(char board[ROW][COL],int row,int col);
void PlayerMove(char board[ROW][COL],int row,int col);
void ComputerMove(char board[ROW][COL],int row,int col);
#include<stdlib.h>
#include<time.h>
char IsWin(char board[ROW][COL],int row,int col);//�ж���Ϸ��������Ӯ����'*';����Ӯ����'#';ƽ�ַ���'Q';��������'C';���Ժ���Ӧ��Ϊchar����
int IsFull(char board[ROW][COL], int row, int col);
#define _CRT_SECURE_NO_WARNINGS 1
//题目：链接：https://www.nowcoder.com/questionTerminal/cf24906056f4488c9ddb132f317e03bc
//来源：牛客网
//
//定义一个二维数组N* M（其中2 <= N <= 10; 2 <= M <= 10），如5 × 5数组下所示：
//
//
//int maze[5][5] = {
//0, 1, 0, 0, 0,
//0, 1, 1, 1, 0,
//0, 0, 0, 0, 0,
//0, 1, 1, 1, 0,
//0, 0, 0, 1, 0,
//};
//
//
//它表示一个迷宫，其中的1表示墙壁，0表示可以走的路，只能横着走或竖着走，不能斜着走，要求编程序找出从左上角到右下角的最短路线。入口点为[0, 0], 既第一格是可以走的路。
//
//
//本题含有多组数据。
//
//
//输入描述 :
//输入两个整数，分别表示二维数组的行数，列数。再输入相应的数组，其中的1表示墙壁，0表示可以走的路。数据保证有唯一解, 不考虑有多解的情况，即迷宫只有一条通道。
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<assert.h>
#include<stdbool.h >
typedef struct Posion
{
    int row;
    int col;
}PT;
typedef PT STDataType;
typedef struct Stack
{
    STDataType* a;
    int top;
    int capacity;
}ST;
void StackInit(ST* st)
{
    st->a = (STDataType*)malloc(sizeof(STDataType) * 4);
    if (st->a == NULL)
    {
        printf("malloc fail\n");
        exit(-1);
    }
    st->capacity = 4;
    st->top = 0;
}
void StackPush(ST* st, STDataType x)
{
    assert(st);
    if (st->top == st->capacity)
    {
        STDataType* tmp = (STDataType*)realloc(st->a, st->capacity * 2 * sizeof(STDataType));
        if (tmp == NULL)
        {
            printf("realloc fail\n");
            exit(-1);
        }
        st->a = tmp;
        st->capacity *= 2;
    }
    st->a[st->top] = x;
    st->top++;
}
void StackPop(ST* st)
{
    assert(st);
    assert(st->top > 0);
    st->top--;
}
STDataType StackTop(ST* st)
{
    assert(st);
    assert(st->top > 0);
    return st->a[st->top - 1];
}
bool StackEmpty(ST* st)
{
    assert(st);
    return st->top == 0;
}
int StackSize(ST* st)
{
    assert(st);
    return st->top;
}
void StackDestroy(ST* st)
{
    assert(st);
    free(st->a);
    st->a = NULL;
}

ST Path;
void PrintPath(Stack* ps)
{
    Stack rPath;
    StackInit(&rPath);
    while (!StackEmpty(&Path))
    {
        StackPush(&rPath, StackTop(&Path));
        StackPop(&Path);
    }
    while (!StackEmpty(&rPath))
    {
        PT top = StackTop(&rPath);
        StackPop(&rPath);
        printf("(%d,%d)\n", top.row, top.col);
    }
    StackDestroy(&rPath);
}
bool IsPass(int** maze, int N, int M, PT pos)  //判断是否为通路
{
    if (pos.row >= 0 && pos.row < N
        && pos.col >= 0 && pos.col < M
        && maze[pos.row][pos.col] == 0)
    {
        return true;
    }
    else
        return false;
}
bool GetMazePath(int** maze, int N, int M, PT cur)  //
{

    StackPush(&Path, cur);
    //找到出口
    if (cur.row == N - 1 && cur.col == M - 1)
        return true;
    //走过的坐标置为2，防止重复走
    maze[cur.row][cur.col] = 2;
    PT next;
    next = cur;
    next.row -= 1; //上
    if (IsPass(maze, N, M, next))
    {
        if (GetMazePath(maze, N, M, next))
            return true;
    }

    next = cur;
    next.row += 1; //下
    if (IsPass(maze, N, M, next))
    {
        if (GetMazePath(maze, N, M, next))
            return true;
    }
    next = cur;
    next.col -= 1; //左
    if (IsPass(maze, N, M, next))
    {
        if (GetMazePath(maze, N, M, next))
            return true;
    }
    next = cur;
    next.col += 1; //右
    if (IsPass(maze, N, M, next))
    {
        if (GetMazePath(maze, N, M, next))
            return true;
    }
    StackPop(&Path);
    return false;
}
int main()
{
    int N = 0, M = 0;
    StackInit(&Path);
    while (scanf("%d%d", &N, &M) != EOF)
    {
        int** maze = (int**)malloc(sizeof(int*) * N);
        for (int i = 0; i < N; i++)
        {
            maze[i] = (int*)malloc(sizeof(int) * M);
        }
        for (int i = 0; i < N; i++)
        {
            for (int j = 0; j < M; j++)
            {
                scanf("%d", &maze[i][j]);
            }
        }
        PT entry = { 0,0 };
        //GetMazePath(maze, N, M,{0,0});
        if (GetMazePath(maze, N, M, entry))
        {
            PrintPath(&Path);
        }
        else
            printf("没有找到通路\n");
        for (int i = 0; i < N; i++)
        {
            free(maze[i]);
        }
        free(maze);
    }
    StackDestroy(&Path);
    return 0;
}

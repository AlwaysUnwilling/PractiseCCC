#define _CRT_SECURE_NO_WARNINGS 1
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
ST minPath;
void PrintPath()
{
    Stack rPath;
    StackInit(&rPath);
    while (!StackEmpty(&minPath))
    {
        StackPush(&rPath, StackTop(&minPath));
        StackPop(&minPath);
    }
    while (StackSize(&rPath)>1)
    {
        PT top = StackTop(&rPath);
        StackPop(&rPath);
        printf("[%d,%d],", top.row, top.col);
    }
    printf("[%d,%d]\n", StackTop(&rPath).row, StackTop(&rPath).col);
    StackPop(&rPath);
    StackDestroy(&rPath);
}
bool IsPass(int** maze, int N, int M, PT pos)  //判断是否为通路
{
    if (pos.row >= 0 && pos.row < N
        && pos.col >= 0 && pos.col < M
        && maze[pos.row][pos.col] == 1)
    {
        return true;
    }
    else
        return false;
}
void Stackcopy(ST* pPath, ST* pminPath)
{
    StackInit(pminPath);
    pminPath->a = (STDataType*)malloc(sizeof(STDataType) * (pPath->capacity));
    if (pminPath->a == NULL)
    {
        printf("pminPath malloc fail\n");
        exit(-1);
    }
    memcpy(pminPath->a,pPath->a,sizeof(STDataType)*pPath->top);
    pminPath->top = pPath->top;
    pminPath->capacity = pPath->capacity;
}
void GetMazePath(int** maze, int N, int M, PT cur,int P)  //
{

    StackPush(&Path, cur);
    //找到出口
    if (cur.row == 0 && cur.col == M - 1)
    {
        if (P >= 0 && StackEmpty(&minPath)  //如果找到了更短的路径就更新更短的路径到minPath   (需要用深拷贝，不能直接minPath=Path，这样俩个指针指向同一空间会造成程序崩溃，内存泄漏等)
            || StackSize(&Path) < StackSize(&minPath))
        {
            StackDestroy(&minPath);
            Stackcopy(&Path, &minPath);
        }
    }
    //走过的坐标置为2，防止重复走
    maze[cur.row][cur.col] = 2;
    PT next;
    next = cur;
    next.row -= 1; //上
    if (IsPass(maze, N, M, next))
    {
        GetMazePath(maze, N, M, next, P - 3);
    }

    next = cur;
    next.row += 1; //下
    if (IsPass(maze, N, M, next))
    {
        GetMazePath(maze, N, M, next, P);
    }
    next = cur;
    next.col -= 1; //左
    if (IsPass(maze, N, M, next))
    {
        GetMazePath(maze, N, M, next, P - 1);
    }
    next = cur;
    next.col += 1; //右
    if (IsPass(maze, N, M, next))
    {
        GetMazePath(maze, N, M, next, P - 1);
    }
    maze[cur.row][cur.col] = 1;//恢复被标记的路
    StackPop(&Path);
}
int main()
{
    int N = 0, M = 0,P = 0;
    StackInit(&Path);
    StackInit(&minPath);
    while (scanf("%d%d%d", &N, &M, &P) != EOF)
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
        GetMazePath(maze, N, M, entry, P);
        if (!StackEmpty(&minPath))
        {
            PrintPath();
        }
        else
            printf("Can not escape!\n");
        for (int i = 0; i < N; i++)
        {
            free(maze[i]);
        }
        free(maze);
    }
    StackDestroy(&Path);
    StackDestroy(&minPath);
    return 0;
}
#define _CRT_SECURE_NO_WARNINGS 1
//��Ŀ�����ӣ�https://www.nowcoder.com/questionTerminal/cf24906056f4488c9ddb132f317e03bc
//��Դ��ţ����
//
//����һ����ά����N* M������2 <= N <= 10; 2 <= M <= 10������5 �� 5��������ʾ��
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
//����ʾһ���Թ������е�1��ʾǽ�ڣ�0��ʾ�����ߵ�·��ֻ�ܺ����߻������ߣ�����б���ߣ�Ҫ�������ҳ������Ͻǵ����½ǵ����·�ߡ���ڵ�Ϊ[0, 0], �ȵ�һ���ǿ����ߵ�·��
//
//
//���⺬�ж������ݡ�
//
//
//�������� :
//���������������ֱ��ʾ��ά�������������������������Ӧ�����飬���е�1��ʾǽ�ڣ�0��ʾ�����ߵ�·�����ݱ�֤��Ψһ��, �������ж�����������Թ�ֻ��һ��ͨ����
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
bool IsPass(int** maze, int N, int M, PT pos)  //�ж��Ƿ�Ϊͨ·
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
    //�ҵ�����
    if (cur.row == N - 1 && cur.col == M - 1)
        return true;
    //�߹���������Ϊ2����ֹ�ظ���
    maze[cur.row][cur.col] = 2;
    PT next;
    next = cur;
    next.row -= 1; //��
    if (IsPass(maze, N, M, next))
    {
        if (GetMazePath(maze, N, M, next))
            return true;
    }

    next = cur;
    next.row += 1; //��
    if (IsPass(maze, N, M, next))
    {
        if (GetMazePath(maze, N, M, next))
            return true;
    }
    next = cur;
    next.col -= 1; //��
    if (IsPass(maze, N, M, next))
    {
        if (GetMazePath(maze, N, M, next))
            return true;
    }
    next = cur;
    next.col += 1; //��
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
            printf("û���ҵ�ͨ·\n");
        for (int i = 0; i < N; i++)
        {
            free(maze[i]);
        }
        free(maze);
    }
    StackDestroy(&Path);
    return 0;
}

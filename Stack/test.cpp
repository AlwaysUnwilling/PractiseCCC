#define _CRT_SECURE_NO_WARNINGS 1
#include"Stack.h"
int main()
{
	ST st;
	StackInit(&st);
	StackPush(&st, 1);
	StackPush(&st, 2);
	StackPush(&st, 3);
	StackPush(&st, 4);
	StackPush(&st, 5);
	StackPop(&st);
	printf("%d\n", StackTop(&st));
	printf("%d\n", StackSize(&st));
	while (!StackEmpty(&st))
	{
		printf("%d ", StackTop(&st));
		StackPop(&st);
	}
	printf("\n");
	if (!StackEmpty(&st))
	{
		printf("Stack ²»Îª¿Õ\n");
	}
	else
		printf("Stack Empty\n");

	StackDestroy(&st);
	return 0;
}
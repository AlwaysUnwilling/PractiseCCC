#define _CRT_SECURE_NO_WARNINGS 1
#include<string.h>
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
////int main()
////{
////	char input[20] = { 0 };
////	//shutdown -s -t 60
////	//system()-ִ��ϵͳ����
////	system("shutdown -s -t 60");
////	while (1)
////	{
////		printf("��ע�⣬��ĵ��Խ���1���Ӻ�ػ�������ȡ��������:������\n������>:\n");
////		scanf("%s", &input);
////		if (strcmp(input, "������") == 0)//�Ƚ������ַ���-strcmp()
////		{
////			system("shutdown -a");
////			break;
////		}
////	}
////	return 0;
////}
////RAND_MAX   (0- 0x7fff)  [0-32767]
//void menu()
//{
//	printf("*************************************************");
//	printf("********       1.Play      0.Exit      **********");
//	printf("*************************************************");
//}
//void game()
//{
//	int ret = 0;
//	int guess = 0;
//	//��ʱ���������һ�������������ʼ��
//	//time_t  time(time_t *timer)
//	//time_t
//	ret= rand()%100+1;//1.����һ���������   ������rand������������һ�������
//	//printf("%d\n",ret); //2.������
//	while (1)
//	{
//		printf("�������>:");
//		scanf("%d", &guess);
//		if (guess > ret)
//			printf("�´���\n");
//		else if (guess < ret)
//			printf("��С��\n");
//		else
//		{
//			printf("��ϲ�㣬�¶��ˣ�\n");
//			break;
//		}
//	}
//}
//int main()
//{
//	int input = 0;
//	srand((unsigned int)time(NULL)); //ʱ�������������һ���仯������
//	do              //��Ϸ�ؽ����˽���һ�Σ�����do...while����ѭ��
//	{
//		menu();
//		printf("��ѡ��:>");
//		scanf("%d", &input);
//		switch (input)
//		{
//		case 1:
//			game();//��������Ϸ
//			break;
//		case 0:
//			printf("�˳���Ϸ\n");
//			break;
//		default:
//			printf("����������");
//			break; 
//		}
//	} while (input);
//	return 0;
//}
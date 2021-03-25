#define _CRT_SECURE_NO_WARNINGS 1
#include<string.h>
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
////int main()
////{
////	char input[20] = { 0 };
////	//shutdown -s -t 60
////	//system()-执行系统命令
////	system("shutdown -s -t 60");
////	while (1)
////	{
////		printf("请注意，你的电脑将在1分钟后关机，如需取消请输入:我是猪\n请输入>:\n");
////		scanf("%s", &input);
////		if (strcmp(input, "我是猪") == 0)//比较俩个字符串-strcmp()
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
//	//拿时间戳来设置一个随机数生成起始点
//	//time_t  time(time_t *timer)
//	//time_t
//	ret= rand()%100+1;//1.生成一个随机数字   “函数rand（）；”生成一个随机数
//	//printf("%d\n",ret); //2.猜数字
//	while (1)
//	{
//		printf("请猜数字>:");
//		scanf("%d", &guess);
//		if (guess > ret)
//			printf("猜大了\n");
//		else if (guess < ret)
//			printf("猜小了\n");
//		else
//		{
//			printf("恭喜你，猜对了！\n");
//			break;
//		}
//	}
//}
//int main()
//{
//	int input = 0;
//	srand((unsigned int)time(NULL)); //时间戳函数，产生一个变化的数字
//	do              //游戏必将先运进来一次，固用do...while（）循环
//	{
//		menu();
//		printf("请选择:>");
//		scanf("%d", &input);
//		switch (input)
//		{
//		case 1:
//			game();//猜数字游戏
//			break;
//		case 0:
//			printf("退出游戏\n");
//			break;
//		default:
//			printf("请重新输入");
//			break; 
//		}
//	} while (input);
//	return 0;
//}
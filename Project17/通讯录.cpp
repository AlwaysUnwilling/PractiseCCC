#define _CRT_SECURE_NO_WARNINGS 1
#include"通讯录.h"
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<search.h>

void InitContact(struct Contact* ps)
{
	//memset(ps->data, 0, sizeof(ps->data));
	//ps->size = 0;   //初始化通讯录 全部为 0
	ps->data = (struct PeoInfo*)malloc(3 * sizeof(struct PeoInfo));
	if (ps->data == NULL)
	{
		return;
	}
	ps->size = 0;
	ps->capacity = DEFAULT_SZ;
} 
void CheckCapacity(struct Contact* ps)
{
	if (ps->size == ps->capacity)
	{
		//增容
		struct PeoInfo* ptr=(struct PeoInfo*)realloc(ps->data, (ps->capacity + 2) * sizeof(struct PeoInfo));
		if (ptr != NULL)
		{
			ps->data = ptr;
			ps->capacity += 2;
			printf("增容成功！\n");
		}
		else
			printf("增容失败！\n");
	}
}
void AddContact(struct Contact* ps)
{
	//检测当前空间是否满了：如果满了，扩容；如果不满，退出，进行下一步
	CheckCapacity(ps);
	printf("请输入姓名：");
	scanf("%s", ps->data[ps->size].name);
	printf("请输入年龄：");
	scanf("%d", &(ps->data[ps->size].age));
	printf("请输入性别：");
	scanf("%s", ps->data[ps->size].sex);
	printf("请输入电话：");
	scanf("%s", ps->data[ps->size].tele);
	printf("请输入地址：");
	scanf("%s", ps->data[ps->size].addr);
	ps->size++;
	printf("添加成功！\n");
	/*if (ps->size == MAX)
	{
		printf("The Contact Is Full.\n");
	}
	else
	{
		printf("请输入姓名：");
		scanf("%s", ps->data[ps->size].name);
		printf("请输入年龄：");
		scanf("%d", &(ps->data[ps->size].age));
		printf("请输入性别：");
		scanf("%s", ps->data[ps->size].sex);
		printf("请输入电话：");
		scanf("%s", ps->data[ps->size].tele);
		printf("请输入地址：");
		scanf("%s", ps->data[ps->size].addr);
		ps->size++;
		printf("添加成功！\n");
	}*/
}
void ShowContact(const struct Contact* ps)
{
	if (ps->size == 0)
	{
		printf("通讯录为空！\n");
	}
	else
	{
		int i = 0;
		printf("%20s\t%4s\t%5s\t%12s\t%20s\n", "名字", "年龄", "性别", "电话", "地址");
		for (i = 0; i < ps->size; i++)
		{
			printf("%20s\t%4d\t%5s\t%12s\t%20s\n", ps->data[i].name,
				ps->data[i].age,
				ps->data[i].sex,
				ps->data[i].tele,
			    ps->data[i].addr);
		}
	}
}
static int Findbyname(const struct Contact* ps, char* name)
{
	int i = 0;
	for (i = 0; i < ps->size ; i++)
	{
		if (strcmp(ps->data[i].name, name) == 0)
			return i;
	}
	return -1;  //找不到
}
void DelContact(struct Contact* ps)
{
	char name[MAX_name] = { 0 };
	printf("请输入要删除人的名字：");
	scanf("%s", name);
	int pos=Findbyname(ps,name);
	if (pos == -1)
	{
		printf("要删除的人不存在！\n");
	}
	else
	{
		int i = 0;
		for (i = pos; i < ps->size-1; i++)
		{
			 ps->data[i] = ps->data[i + 1];
		}
		ps->size--;
		printf("删除成功！\n");
	}
}
void SearchContact(const struct Contact* ps)
{
	char name[MAX_name] = { 0 };
	printf("请输入要查找人的名字：");
	scanf("%s", name);
	int pos = Findbyname(ps, name);
	if (pos == -1)
	{
		printf("要查找人的信息不存在！");
	}
	else
	{
		printf("%20s\t%4s\t%5s\t%12s\t%20s\n", "名字", "年龄", "性别", "电话", "地址");
		printf("%20s\t%4d\t%5s\t%12s\t%20s\n", ps->data[pos].name,
			ps->data[pos].age,
			ps->data[pos].sex,
			ps->data[pos].tele,
			ps->data[pos].addr);
	}
}
void ModifyContact(struct Contact* ps)
{
	char name[MAX_name] = { 0 };
	printf("请输入要修改人的姓名：");
	scanf("%s", name);
	int pos = Findbyname(ps, name);
	if (pos == -1)
	{
		printf("被修改人的信息不存在");
	}
	else
	{
		printf("请输入姓名：");
		scanf("%s", ps->data[pos].name);
		printf("请输入年龄：");
		scanf("%d", &(ps->data[pos].age));
		printf("请输入性别：");
		scanf("%s", ps->data[pos].sex);
		printf("请输入电话：");
		scanf("%s", ps->data[pos].tele);
		printf("请输入地址：");
		scanf("%s", ps->data[pos].addr);
		printf("修改成功！\n");
	}
}

int cmp_by_name(const void* e1, const void* e2)
{
	//return strcmp(((struct Contact*)e1)->data.name, ((struct Contact*)e2)->data.name);
	//return strcmp(((struct Contact*)e1)->data->name, (((struct Contact*)e2)->data->name));
	return strcmp(((struct PeoInfo*)e1)->name, (((struct PeoInfo*)e2)->name));
}
void SortContact(struct Contact* ps)
{
	qsort(ps->data, ps->size, sizeof(PeoInfo), cmp_by_name);
	//qsort(ps->data, ps->size, sizeof(ps->data[0]), cmp_by_name);
}

void DestroyContact(struct Contact* ps)
{
	free(ps->data);
	ps->data = NULL;
}
#define _CRT_SECURE_NO_WARNINGS 1
#include"ͨѶ¼.h"
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<search.h>

void InitContact(struct Contact* ps)
{
	//memset(ps->data, 0, sizeof(ps->data));
	//ps->size = 0;   //��ʼ��ͨѶ¼ ȫ��Ϊ 0
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
		//����
		struct PeoInfo* ptr=(struct PeoInfo*)realloc(ps->data, (ps->capacity + 2) * sizeof(struct PeoInfo));
		if (ptr != NULL)
		{
			ps->data = ptr;
			ps->capacity += 2;
			printf("���ݳɹ���\n");
		}
		else
			printf("����ʧ�ܣ�\n");
	}
}
void AddContact(struct Contact* ps)
{
	//��⵱ǰ�ռ��Ƿ����ˣ�������ˣ����ݣ�����������˳���������һ��
	CheckCapacity(ps);
	printf("������������");
	scanf("%s", ps->data[ps->size].name);
	printf("���������䣺");
	scanf("%d", &(ps->data[ps->size].age));
	printf("�������Ա�");
	scanf("%s", ps->data[ps->size].sex);
	printf("������绰��");
	scanf("%s", ps->data[ps->size].tele);
	printf("�������ַ��");
	scanf("%s", ps->data[ps->size].addr);
	ps->size++;
	printf("��ӳɹ���\n");
	/*if (ps->size == MAX)
	{
		printf("The Contact Is Full.\n");
	}
	else
	{
		printf("������������");
		scanf("%s", ps->data[ps->size].name);
		printf("���������䣺");
		scanf("%d", &(ps->data[ps->size].age));
		printf("�������Ա�");
		scanf("%s", ps->data[ps->size].sex);
		printf("������绰��");
		scanf("%s", ps->data[ps->size].tele);
		printf("�������ַ��");
		scanf("%s", ps->data[ps->size].addr);
		ps->size++;
		printf("��ӳɹ���\n");
	}*/
}
void ShowContact(const struct Contact* ps)
{
	if (ps->size == 0)
	{
		printf("ͨѶ¼Ϊ�գ�\n");
	}
	else
	{
		int i = 0;
		printf("%20s\t%4s\t%5s\t%12s\t%20s\n", "����", "����", "�Ա�", "�绰", "��ַ");
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
	return -1;  //�Ҳ���
}
void DelContact(struct Contact* ps)
{
	char name[MAX_name] = { 0 };
	printf("������Ҫɾ���˵����֣�");
	scanf("%s", name);
	int pos=Findbyname(ps,name);
	if (pos == -1)
	{
		printf("Ҫɾ�����˲����ڣ�\n");
	}
	else
	{
		int i = 0;
		for (i = pos; i < ps->size-1; i++)
		{
			 ps->data[i] = ps->data[i + 1];
		}
		ps->size--;
		printf("ɾ���ɹ���\n");
	}
}
void SearchContact(const struct Contact* ps)
{
	char name[MAX_name] = { 0 };
	printf("������Ҫ�����˵����֣�");
	scanf("%s", name);
	int pos = Findbyname(ps, name);
	if (pos == -1)
	{
		printf("Ҫ�����˵���Ϣ�����ڣ�");
	}
	else
	{
		printf("%20s\t%4s\t%5s\t%12s\t%20s\n", "����", "����", "�Ա�", "�绰", "��ַ");
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
	printf("������Ҫ�޸��˵�������");
	scanf("%s", name);
	int pos = Findbyname(ps, name);
	if (pos == -1)
	{
		printf("���޸��˵���Ϣ������");
	}
	else
	{
		printf("������������");
		scanf("%s", ps->data[pos].name);
		printf("���������䣺");
		scanf("%d", &(ps->data[pos].age));
		printf("�������Ա�");
		scanf("%s", ps->data[pos].sex);
		printf("������绰��");
		scanf("%s", ps->data[pos].tele);
		printf("�������ַ��");
		scanf("%s", ps->data[pos].addr);
		printf("�޸ĳɹ���\n");
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
#pragma once
#define MAX 1000
#define MAX_name 20
#define MAX_sex  5
#define MAX_tele  15
#define MAX_addr  30

struct PeoInfo
{
	char name[MAX_name];
	int age;
	char sex[MAX_sex];
	char tele[MAX_tele];
	char addr[MAX_addr];
};
enum Option
{
	EXIT,
	ADD,
	DEL,
	SEARCH,
	MODIFY,
	SHOW,
	SORT
};

struct Contact    // ͨѶ¼������
{
	struct PeoInfo data[MAX];  //���1000���˵���Ϣ
	int size;   //  ��¼��ǰ�Ѿ��е�Ԫ�ظ���
};

void InitContact(struct Contact* ps);
void AddContact(struct Contact* ps);
void ShowContact(const struct Contact* ps);
void DelContact(struct Contact* ps);
void SearchContact(const struct Contact* ps);
void ModifyContact(struct Contact* ps);
void SortContact(struct Contact* ps);

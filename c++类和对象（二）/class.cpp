#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
#include<stdio.h>
using namespace std;
//��������Զ��壺1.��Ա������2.��Ա����
//class Person
//{
//	void Print()//������������ĺ���Ĭ������������  ����������.h��������.cpp�ǾͲ�������������
//	{
//
//	}
//	char _name[10];
//	int _age;
//};
//
//class Student //c++��class��struct���������������ࡣclassĬ�Ϸ����޶���˽�еģ�structĬ���ǹ��е�
//{
//public:
//	void ShowInfo()
//	{
//		cout << _name << endl;
//		cout << _age << endl;
//		cout << _stuid << endl;
//	}
//	int GerAge()
//	{
//		return _age;
//	}
////private://һ������³�Ա�������ǱȽ���˽�ģ����ᶨ��Ϊ˽�л򱣻���
//	const char* _name;
//	int _age;
//	int _stuid;
//};
//int main()
//{
//	Student s1;
//	Student s2;
//	s1._name = "peter";
//	s1._age = 18;
//	s1._stuid = 1;
//	s1.ShowInfo();
//	return 0;
//}

//��װ��1.�����ݺͷ����ŵ�һ��2.������㿴�����ݸ��㿴��public�������벻���㿴�ķ�װ������protected/private��
//class Stack
//{
//public:
//	void Push(int x);
//	void Pop();
//	bool Empty();
//private:
//	int* _a;
//	int _size;
//	int _capacity;
//};
////û�г�Ա��������Ĵ�С��1��������0����һ���ֽڵĿռ䲻��Ϊ�˴����ݣ�����Ϊ��ռλ
//
//class Date
//{
//public:
//	void Init(int year,int month,int day)//void Init(Date* this,int year,int month,int day)
//	{
//		_year = year;
//		_month = month;
//		_day = day;
//	}
//	void Print()//void Print(Date* this)  ���ﲻ��Ҫָ������Ϊ���������Զ������ָ��Date����ָ��this
//	{
//		cout << _year << "-"<<_month << "-"<<_day << endl;
//		cout << this->_year << "-" << this->_month << "-" << this->_day << endl;//�����������д
//	}
//private:
//	int _year;
//	int _month;
//	int _day;
//};
//int main()
//{
//	Date d1;
//	d1.Init(2021, 06, 13);//d1.Init(&d1,2021, 06, 13)
//	d1.Print();  //	d1.Print(&d1)
//	return 0;
//}
//���ԣ�1.thisָ����ڽ��̵�ַ�ռ���ĸ����� ����ջ�ϵģ���Ϊ����һ���βΣ�ps��vs����ecx����Ĵ��������ݣ�
//      2.����p->PrintA������p->Show����,���лᷢ��ʲô����
//        ��Ա�������ڹ�������Σ�����p->Show����������Ȼthisָ����NULL������thisָ��û��ȥ���ʳ�Ա����
//class A
//{
//public:
//	void PrintA()
//	{
//		cout << _a << endl;//�����൱��cout <<this-> _a << endl �����thisָ���Ѿ���NULL�����ٷ��ʳ�Ա_a�����
//	}
//	void Show()
//	{
//		cout << "Show()" << endl;
//	}
//private:
//	int _a;
//};
//int main()
//{
//	A* p = NULL;
//	p->PrintA();//���������������
//	p->Show();//�������г���������
//	return 0;
//}

//���캯������������������ͬ�����Թ������أ�ʵ����ʱ�Զ�����
//         �������û����ʾ���幹�캯�������������Զ������޲�Ĭ�Ϲ��캯����
//              1.����������ͳ�Ա������������
//              2.����Զ������ͳ�Ա�������������Ĺ��캯�����г�ʼ��
//         #һ���û���ʾ�˹��캯����ϵͳ�Ͳ�������Ĭ�Ϲ��캯�����޲β������ɣ�


//class Time
//{
//public:
//	Time()                         //���캯�������г�ʼ����
//	{
//		_hour = 0;
//		_minute = 0;
//		_second = 0;
//	}
//private:
//	int _hour;
//	int _minute;
//	int _second;
//};
//class Date
//{
//public:
//	//Date(int year, int month, int day) //���캯�������г�ʼ����
//	//{
//	//	_year = year;
//	//	_month = month;
//	//	_day = day;
//	//}
//	//Date()                         //���캯�������г�ʼ����
//	//{
//	//	_year = 2021;
//	//	_month = 4;
//	//	_day = 18;
//	//}
//
//	//���õĽ������->ȱʡ����
//	Date(int year=0, int month=1, int day=1)
//	{
//		_year = year;
//		_month = month;
//		_day = day;
//	}
//	void Print()
//	{
//		cout << _year << "-" << _month << "-" << _day << endl;
//	}
//private:
//	int _year;
//	int _month;
//	int _day;
//	Time _t;   
//};
//int main()
//{
//	Date d1(2021,6,13);//�Զ�����Date(int year, int month, int day)
//	d1.Print();
//
//	Date d2;//Date d2�޲ε��ù��캯��ʱ����Date d2()����д�������޲�ֱ��Date d2;�ͺ���
//	d2.Print();//�Զ�����Date()
//	return 0;
//}

//���������������������ڵ��˺��Զ�����  ��~��������������������������ǶԶ�������٣��ǶԶ��󿪱ٵĿռ䣨malloc�����ģ��Ƚ�������
class Stack
{
public:
	Stack(int n = 10)
	{
		_a = (int*)malloc(sizeof(int) * n);
		if (_a == nullptr)
		{
			cout << "mallco fail" << endl;
			exit(-1);
		}
		cout << "Stack(int n = 10) malloc:" << _a << endl;
		_size = 0;
		_capacity = 10;
	}
	~Stack()//��������
	{
		if (_a)
		{
			free(_a);
			cout << "~Stack() malloc:" << _a << endl;
            _a= nullptr;
			_size = _capacity = 0;
		}
	}
private:
	int* _a;
	int _size;
	int _capacity;
};
int main()
{
	//����ʱ�ȵ���st1,Ȼ��st2������ʱ������st2��Ȼ��st1
	Stack st1; 
	Stack st2;

	return 0;
}


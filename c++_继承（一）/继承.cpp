#include<iostream>
#include<string>
using namespace std;

//�̳еĶ����ʽ��
//�����ࣨ���ࣩ �̳з�ʽ  ���ࣨ���ࣩ
//class Student :public Person
//{
//public:
//	int _stuid;
//};
class Person
{
public:
	void Print()
	{
		cout << "name:" << _name << endl;
		cout << "age:" << _age << endl;
	 }
protected:
	string _name = "peter"; //����
	int _age = 18;  //����
};
//�̳к����Person�ĳ�Ա����Ա�����ͳ�Ա������������֮���һ���֡�����������Student��Teacher������Person�ĳ�Ա
class Student:public Person
{
protected:
	int _stuid;//ѧ��
};
class Teacher :public Person
{
protected:
	int _jobid; //����
};

int main()
{
	Student s;
	Teacher t;
	s.Print();
	t.Print();
	return 0;
}
////�̳й�ϵ�ͷ����޶���
//�̳з�ʽ��1.public�̳У�2.protected�̳У�3.private�̳У�
//�����޶�����1.public���ʣ�2.protected���ʣ�3.private���ʣ�

////�̳л����Ա���ʷ�ʽ
//1. ����private��Ա����������������ʲô��ʽ�̳ж��ǲ��ɼ��ġ�����Ĳ��ɼ���ָ�����˽�г�Ա����
//���̳е�������������У������﷨��������������󲻹��������滹�������涼����ȥ��������
//2. ����private��Ա�����������ǲ��ܱ����ʣ���������Ա����������ֱ�ӱ����ʣ�����Ҫ������������
//���ʣ��Ͷ���Ϊprotected�����Կ���������Ա�޶�������̳вų��ֵġ�
//3<�ص�>.�����˽�г�Ա�����඼�ǲ��ɼ��������������Ա������ķ��ʷ�ʽ == Min(��Ա�ڻ���ķ����޶������̳з�ʽ)��public > protected > private��
//4. ʹ�ùؼ���classʱĬ�ϵļ̳з�ʽ��private��ʹ��structʱĬ�ϵļ̳з�ʽ��public�����������ʾ��
//д���̳з�ʽ��
//5. ��ʵ��������һ��ʹ�ö���public�̳У���������ʹ��protetced / private�̳У�Ҳ���ᳫʹ��
//protetced / private�̳У���Ϊprotetced / private�̳������ĳ�Ա��ֻ�����������������ʹ�ã�ʵ����
//��չά���Բ�ǿ��
class Person
{
public:
	void Print()
	{
		cout << _name << endl;
	}
protected:
	string _name; // ����
private:
	int _age; // ����
};
//class Student : protected Person
//class Student : private Person
class Student : public Person
{
public:
	void f()
	{
		cout << _stunum << endl;
		//cout << _age << endl;//_age�ǻ����˽�г�Ա���̳к����಻����
	}
protected:
	int _stunum; // ѧ��
};

int main()
{
	Student s;
	return 0;
}

//��������������ֵת��:
//1.��������� ���Ը�ֵ�� ����Ķ��� / �����ָ�� / ��������á������и������˵������Ƭ������
//�Ԣ����������и����ǲ���������ֵ��ȥ��
//2.��������ܸ�ֵ�����������
//3.�����ָ�����ͨ��ǿ������ת����ֵ���������ָ�롣���Ǳ����ǻ����ָ����ָ�����������ʱ��
//�ǰ�ȫ�ġ������������Ƕ�̬���ͣ�����ʹ��RTTI(Run - Time Type Information)��dynamic_cast ��
//����ʶ�����а�ȫת����
class Person
{
protected:
	string _name; // ����
	string _sex; // �Ա�
	int _age; // ����
};
class Student : public Person
{
public:
	int _No; // ѧ��
};
void Test()
{
	Student sobj;
	// 1.���������Ը�ֵ���������/ָ��/����
	Person pobj = sobj;
	Person* pp = &sobj;
	Person& rp = sobj;

	//2.��������ܸ�ֵ�����������
	//sobj = pobj;

	// 3.�����ָ�����ͨ��ǿ������ת����ֵ���������ָ��
	pp = &sobj;
		Student * ps1 = (Student*)pp; // �������ת��ʱ���Եġ�
	ps1->_No = 10;

	pp = &pobj;
	Student* ps2 = (Student*)pp; // �������ת��ʱ��Ȼ���ԣ����ǻ����Խ����ʵ�����
	ps2->_No = 10;
}

//�̳е�������
//1. �ڼ̳���ϵ�л���������඼�ж�����������
//2. ����͸�������ͬ����Ա�������Ա�����θ����ͬ����Ա��ֱ�ӷ��ʣ�������������أ�Ҳ���ض�
//�塣���������Ա�����У�����ʹ�� ����::�����Ա ��ʾ���ʣ�
//3. ��Ҫע���������ǳ�Ա���������أ�ֻ��Ҫ��������ͬ�͹������ء�
//4. ע����ʵ�����ڼ̳���ϵ������ò�Ҫ����ͬ���ĳ�Ա��
// Student��_num��Person��_num�������ع�ϵ�����Կ�������������Ȼ���ܣ����Ƿǳ����׻���
class Person
{
protected:
	string _name = "С����"; // ����
	int _num = 111; // ���֤��
};
class Student : public Person
{
public:
	void Print()
	{
		cout << " ����:" << _name << endl;
		cout << " ���֤��:" << Person::_num << endl;  //�������Ա�����У�����ʹ�� ����::�����Ա ��ʾ����
		cout << " ѧ��:" << _num << endl;
	}
protected:
	int _num = 999; // ѧ��
};
void Test()
{
	Student s1;
	s1.Print();
};

// B�е�fun��A�е�fun���ǹ������أ���Ϊ������ͬһ������
// B�е�fun��A�е�fun�������أ���Ա�������㺯������ͬ�͹������ء�
class A {
public:
	void fun()
	{
		cout << "func()" << endl;
	}
};
class B : public A {
public:
	void fun(int i)   //�����Ա����������̳������Ļ����Ա����fun() ��������ͬ(���ܲ�����ͬ)�͹��������ػ��߽��ض���
	{                 //�������Ա�����У�����ʹ�� ����::�����Ա ��ʾ����
		A::fun();
		cout << "func(int i)->" << i << endl;
	}
};
void Test()
{
	B b;
	b.fun(10);
};
#include<iostream>
using namespace std;

//��̬�ĸ���:ͨ����˵�����Ƕ�����̬����������ȥ���ĳ����Ϊ������ͬ�Ķ���ȥ���ʱ���������ͬ��״̬��
//��̬�Ĺ�������:��̬���ڲ�ͬ�̳й�ϵ�������ȥ����ͬһ�����������˲�ͬ����Ϊ��
//���ɶ�̬��������������1.����ͨ�������ָ��������õ����麯��
//                      2. �����õĺ����������麯���������������Ի�����麯��������д
//�麯�����麯��������virtual���ε����Ա������
class Person {
public:
	virtual void BuyTicket() { cout << "��Ʊ-ȫ��" << endl; }
};
//�麯������д���麯������д(����)������������һ����������ȫ��ͬ���麯��(���������麯��������麯���ķ���ֵ���͡��������֡������б���ȫ��ͬ)����������麯����д�˻�����麯��
class Person {
public:
	virtual void BuyTicket() { cout << "��Ʊ-ȫ��" << endl; }
};
class Student : public Person {
public:
	virtual void BuyTicket() { cout << "��Ʊ-���" << endl; }
	/*ע�⣺����д�����麯��ʱ����������麯���ڲ���virtual�ؼ���ʱ����ȻҲ���Թ�����д(��Ϊ��
�к������麯�����̳������������������ɱ����麯������),���Ǹ���д�����Ǻܹ淶������������ʹ��
*/
/*void BuyTicket() { cout << "��Ʊ-���" << endl; }*/
};
void Func(Person& p)
{
	p.BuyTicket();
}
int main()
{
	Person ps;
	Student st;

	Func(ps);
	Func(st);
	return 0;
}

//�麯����д���������⣺
//1. Э��(�������������麯������ֵ���Ͳ�ͬ)
//��������д�����麯��ʱ��������麯������ֵ���Ͳ�ͬ���������麯�����ػ�������ָ�������
//�ã��������麯����������������ָ���������ʱ����ΪЭ�䡣
class A {};
class B : public A {};
class Person {
public:
	virtual Person& f1()
	{
		return *this;
	}
	virtual A* f() 
	{
		return new A; 
	}
};
class Student : public Person {
public:
	virtual Student& f1()
	{
		return *this;
	}
	virtual B* f()
	{ 
		return new B;   //�����B��A�����Ǽ̳й�ϵ
	}
};
//2. ������������д(�������������������������ֲ�ͬ)
//����������������Ϊ�麯������ʱ��������������ֻҪ���壬�����Ƿ��virtual�ؼ��֣���������
//��������������д����Ȼ�����������������������ֲ�ͬ����Ȼ����������ͬ��������Υ������д�Ĺ�
//����ʵ��Ȼ������������Ϊ�����������������������������⴦���������������������ͳһ��
//���destructor��
class Person {
public:
	virtual ~Person() { cout << "~Person()" << endl; }
};
class Student : public Person {
public:
	virtual ~Student() { cout << "~Student()" << endl; }
};
// ֻ��������Student������������д��Person�����������������delete��������������������ܹ��ɶ�̬�����ܱ�֤p1��p2ָ��Ķ�����ȷ�ĵ�������������
int main()
{
	Person* p1 = new Person;
	Person* p2 = new Student;
	delete p1;
	delete p2;  //�������û�а�������������Ϊ�麯������student����ǡ����Ҫ�ͷŵ���Դ����ô������ڴ�й©��
	return 0;
}

// C++11 override �� final
//final �����麯������ʾ���麯�������ٱ��̳�
class Car
{
public:
	virtual void Drive() final {}
};
class Benz :public Car
{
public:
	virtual void Drive() { cout << "Benz-����" << endl; }
};
//override : ����������麯���Ƿ���д�˻���ĳ���麯�������û����д���뱨��
class Car {
public:
	virtual void Drive() {}
};
class Benz :public Car {
public:
	virtual void Drive() override { cout << "Benz-����" << endl; }
};


//���ء�����(��д)������(�ض���)�ĶԱ�:
//���أ�����������ͬһ�������Һ�������ͬ��������ͬ��
//��д�����ǣ������������ֱ��ڻ������������������У�������������������ֵ����ͬ��Э�����⣩�����������������麯����
//�ض��壨���أ������������ֱ��ڻ������������������У���������ͬ������������������ͬ��������������д�����ض��塣

//������
//���麯���ĺ���д�� = 0 �����������Ϊ���麯�����������麯��������������ࣨҲ�нӿ��ࣩ��������
//����ʵ����������������̳к�Ҳ����ʵ����������ֻ����д���麯�������������ʵ���������󡣴�
//�麯���淶�������������д�����ⴿ�麯�������ֳ��˽ӿڼ̳С�
class Car
{
public:
	virtual void Drive() = 0;
};
class Benz :public Car
{
public:
	virtual void Drive()
	{
		cout << "Benz-����" << endl;
	}
};
class BMW :public Car
{
public:
	virtual void Drive()
	{
		cout << "BMW-�ٿ�" << endl;
	}
};
void Test()
{
	Car* pBenz = new Benz;
	pBenz->Drive();
	Car* pBMW = new BMW;
	pBMW->Drive();
}

//�ӿڼ̳к�ʵ�ּ̳�:��ͨ�����ļ̳���һ��ʵ�ּ̳У�������̳��˻��ຯ��������ʹ�ú������̳е��Ǻ�����ʵ�֡��麯����
//�̳���һ�ֽӿڼ̳У�������̳е��ǻ����麯���Ľӿڣ�Ŀ����Ϊ����д����ɶ�̬���̳е��ǽӿڡ���
//�������ʵ�ֶ�̬����Ҫ�Ѻ���������麯����
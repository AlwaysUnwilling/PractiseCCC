#include<iostream>

using namespace std;

//���������⣺
//1. ʲô�����μ̳У����μ̳е�������ʲô��
//2. ʲô����������̳У���ν����������Ͷ����Ե�
//3. �̳к���ϵ�����?ʲôʱ���ü̳У�ʲôʱ������ϣ�

//class Person
//{
//public:
//	Person(const char* name = "Peter")
//		:_name(name)
//	{
//		cout << "Person()" << endl;
//	}
//	Person(const Person& p)
//		:_name(p._name)
//	{
//		cout << "Person(const Person& p)" << endl;
//	}
//	Person& operator=(const Person& p)
//	{
//		cout << "Person& operator=(const Person& p)" << endl;
//		if (this != &p)
//		{
//			_name = p._name;
//		}
//		return *this;
//	}
//	~Person()
//	{
//		cout << "~Person()" << endl;
//	}
//protected:
//	string _name;
//};
//
////�����������Ĭ�ϳ�Ա����
//class Student :public Person
//{
//public:
//	Student(const char* name, int studid)   // ���캯��(����)
//		//:_name(name)      // ����ĳ�Ա�����ɻ���Ĺ��캯������ʼ�����������ﲻ���Լ������ʶ����
//		:Person(name)       //���������������Ҫ��ʾ�������ĳ�Ա���Ե��û���Ĺ��캯������ʾ
//		, _studid(studid)
//	{
//		cout << "Student()" << endl;
//	}
//	Student(const Student& s)   //��������
//		//:_name(s._name)      //������Ŀ������캯�����л���ĳ�Ա������Ҫ���û���Ĺ��캯����ɣ��������Լ�ȥʵ�֡�
//		:Person(s)        //������Ŀ������캯������Ҫ��ʾ����ĳ�Ա�Ŀ������졣
//		,_studid(s._studid)
//	{
//		cout << "Student(const Student& s)" << endl;
//	}
//	Student& operator=(const Student& s)   //��ֵ
//	{
//		if (this != &s)
//		{
//			//operator=(s);//���û���ĸ�ֵ  (this->operator=(s))  �������s����ֵ��Person;���ǻ����operator=()���������operator=()��ͬ������������
//			//            //�����ͬ���������������б�Ӱ���ˣ��������������Ҫ���û����ͬ��������Ҫ�ƶ������򣬷�����������ջ�����operator=(s)��������ݹ�����������operator=(s)��
//			Person::operator=(s);   //��ȷ�ĵ��û���ĸ�ֵ���� :this->Person::operator=(s)
//			_studid = s._studid;
//		}
//		cout << "Student& operator=(const Student& s)" << endl;
//		return *this;
//	}
//	~Student()
//	{
//		//Person::~Person();  //�����������������������������������濪����������ͬ����������Ҳ��ͬ���������������أ���Ϊ������������������ͳһ�����destructor(����̬�й�)
//		               //����Ҳ��Ҫָ��������
//		//�����������е�������������Ҫ���û����������������Ϊ�����������������ɺ󣬻��Զ����û����������������������Ҫ��ʾ��������������ĵ���
//		cout << "~Student()" << endl;
//	}
//protected:
//	int _studid;
//};
//int main()
//{
//	Student s1("Tom",1);
//	//Student s2(s1);
//	//Student s3("Jack",3);
//	//s1 = s3;
//	return 0;
//}

//������һ�����ܱ��̳е��ࣿ
//�ѻ���Ĺ��캯��˽�л�������������Ͳ��ܼ̳л��ࡣ��Ϊ������̳��˻���󣬻����˽�г�Ա�᲻�ɼ������ܱ�������ʹ�á��������ഴ������������û���Ĺ��캯��������Ĺ��캯��˽��
//�������಻�ܵ��ã�������Ķ���Ͳ������ɡ�
//class A
//{
//private:
//	A()
//	{}
//};
//class B:public A
//{};
//int main()
//{
//	//B b;  //�������ɶ���
//	return 0;
//}

//�̳�����Ԫ:��Ԫ��ϵ���ܼ̳У�Ҳ����˵������Ԫ���ܷ��������ࣨ���ࣩ˽�кͱ�����Ա�������Ҫ���ʣ���������������������һ����Ԫ��ϵ���ɷ���

//class Student;
//class Person
//{
//public:
//	friend void Display(const Person& p, const Student& s);
//protected:
//	string _name; // ����
//};
//class Student : public Person
//{
//	friend void Display(const Person& p, const Student& s);
//protected:
//	int _stuNum; // ѧ��
//};
//void Display(const Person& p, const Student& s) {
//	cout << p._name << endl;
//	cout << s._stuNum << endl;
//}
//void main()
//{
//	Person p;
//	Student s;
//	Display(p, s);
//}

//�̳��뾲̬��Ա:���ඨ����static��̬��Ա���������̳���ϵ����ֻ��һ�������ĳ�Ա���������������ٸ����࣬��ֻ��һ��static��Աʵ�� ��
//class Person
//{
//public:
//	Person()
//	{
//		++_count;
//	}
//	string _name;
//	static int _count;
//};
//int Person::_count = 0;
//class Student:public Person
//{
//protected:
//	int _stuNum;
//};
//int main()
//{
//	Person p;
//	Student s;
//	p._name = "jack";
//	s._name = "rose";
//
//	p._count = 1;
//	s._count = 2;
//
//	Person::_count++;
//	cout << p._name << endl;
//	cout << s._name << endl;
//	cout << p._count << endl;
//	cout << s._count << endl;
//	return 0;
//}

//********<�ص�>  ���ӵ����μ̳м�����ģ��̳� 
//���μ̳е����⣺������ݵ�����Ͷ����ԡ�����������ƶ�����ȥ���ʡ�
//���̳У�һ������ֻ��һ��ֱ�Ӹ���ʱ������̳й�ϵΪ���̳�
//��̳У�һ������������������ֱ�Ӹ���ʱ������̳й�ϵΪ��̳�
//���μ̳У����μ̳��Ƕ�̳е�һ���������
//���μ̳е����⣺������Ķ����Աģ�͹��죬���Կ������μ̳�����������Ͷ����Ե����⡣��Assistant
//�Ķ�����Person��Ա�������ݡ�
//class Person
//{
//public:
//	string _name; // ����
//};
//class Student : public Person
//{
//protected:
//	int _num; //ѧ��
//};
//class Teacher : public Person
//{
//protected:
//	int _id; // ְ�����
//};
//class Assistant : public Student, public Teacher
//{
//protected:
//	string _majorCourse; // ���޿γ�
//};
//void Test()
//{
//	// �������ж������޷���ȷ֪�����ʵ�����һ��
//	Assistant a;
//	//a._name = "peter";
//
//	// ��Ҫ��ʾָ�������ĸ�����ĳ�Ա���Խ�����������⣬�����������������޷����
//	a.Student::_name = "xxx";
//	a.Teacher::_name = "yyy";
//}
////����̳п��Խ�����μ̳еĶ����Ժ�������������⡣������ļ̳й�ϵ����Student��Teacher�ļ̳�
////Personʱʹ������̳�(virtual)�����ɽ�����⡣��Ҫע����ǣ�����̳в�Ҫ�������ط�ȥʹ�á�
//class Person
//{
//public:
//	string _name; // ����
//};
//class Student : virtual public Person
//{
//protected:
//	int _num; //ѧ��
//};
//class Teacher : virtual public Person
//{
//protected:
//	int _id; // ְ�����
//};
//class Assistant : public Student, public Teacher
//{
//protected:
//	string _majorCourse; // ���޿γ�
//};
//void Test()
//{
//	Assistant a;
//	a._name = "peter";
//}

//�����⣺c++����Щȱ�ݣ���̳о�������֮һ����̳п��ܵ������μ̳У�Ҫ������μ̳���������̳У���̳еĵײ�ṹ�Ķ���ģ�ͷǳ����ӣ�����һ����Ч����ʧ��

//��̳������ʵ�ֵ��أ�
//����ģ�ͣ��������ڴ�������ô��ģ�
//���μ̳У�
//class A
//{
//public:
//	int _a;
//};
//class B :public A
//{
//public:
//	int _b;
//};
//class C :public A
//{
//public:
//	int _c;
//};
//class D :public B, public C
//{
//public:
//	int _d;
//};
//int main()
//{
//	D d;
//	cout << sizeof(d) << endl;  //d�̳���B��C��B��C�ֱ�̳���A��A�Ĵ�С��4��B��C�Ĵ�С�ֱ���8��d�Ĵ�С����8+8+4=20;
//	d.B::_a = 1;
//	d.C::_a = 2;
//	d._b = 3;
//	d._c = 4;
//	d._d = 5;
//	return 0;
//}
//������̳У�������ͨ����B��C������ָ�룬ָ���һ�ű�������ָ��������ָ�룬��������������������д��ƫ������ͨ��ƫ���������ҵ������A��
class A
{
public:
	int _a;
};
class B :virtual public A
{
public:
	int _b;
};
class C :virtual public A
{
public:
	int _c;
};
class D :public B, public C
{
public:
	int _d;
};
int main()
{
	D d;
	cout << sizeof(d) << endl;  //����̳��У�d�̳���B��C��B��C�ֱ�̳���A������B��C��û�д洢A�г�Ա_a,���Ǵ洢��_a���������ƫ������ַ��ָ�룩��8+8+4++4=24��
	                          //��A�еĶ�����ڹ�������
	d.B::_a = 1;
	d.C::_a = 2;
	d._b = 3;
	d._c = 4;
	d._d = 5;
	return 0;
}

//�̳е��ܽ�ͷ�˼���̳к����
//1.public�̳���һ��is - a�Ĺ�ϵ��Ҳ����˵ÿ�������������һ���������
//2.�����һ��has - a�Ĺ�ϵ������B�����A��ÿ��B�����ж���һ��A����
//3.����ʹ�ö�����ϣ���������̳� ��
//4.�̳���������ݻ����ʵ���������������ʵ�֡�����ͨ������������ĸ���ͨ������Ϊ���临��
//(white - box reuse)��������䡱����Կ����Զ��ԣ��ڼ̳з�ʽ�У�������ڲ�ϸ�ڶ�����ɼ� ��
//�̳�һ���̶��ƻ��˻���ķ�װ������ĸı䣬���������кܴ��Ӱ�졣������ͻ�����������
//ϵ��ǿ����϶ȸߡ�
//5.�����������̳�֮�����һ�ָ���ѡ���µĸ����ӵĹ��ܿ���ͨ����װ����϶�������á���
//�����Ҫ����ϵĶ���������ö���Ľӿڡ����ָ��÷�񱻳�Ϊ���临��(black - box reuse)��
//��Ϊ������ڲ�ϸ���ǲ��ɼ��ġ�����ֻ�ԡ����䡱����ʽ���֡� �����֮��û�к�ǿ��������ϵ��
//��϶ȵ͡�����ʹ�ö�������������㱣��ÿ���౻��װ��
//6.ʵ�ʾ�����ȥ����ϡ���ϵ���϶ȵͣ�����ά���Ժá������̳�Ҳ������֮�صģ���Щ��ϵ����
//�ϼ̳��Ǿ��ü̳У�����Ҫʵ�ֶ�̬��Ҳ����Ҫ�̳С���֮��Ĺ�ϵ�����ü̳У���������ϣ���
//����ϡ�
 

// Car��BMW Car��Benz����is-a�Ĺ�ϵ
class Car {
protected:
	string _colour = "��ɫ"; // ��ɫ
	string _num = "��ABIT00"; // ���ƺ�
};
class BMW : public Car {
public:
	void Drive() { cout << "�ÿ�-�ٿ�" << endl; }
};

class Benz : public Car {
public:
	void Drive() { cout << "����-����" << endl; }
};

// Tire��Car����has-a�Ĺ�ϵ

class Tire {
protected:
	string _brand = "Michelin"; // Ʒ��
	size_t _size = 17; // �ߴ�

};

class Car {
protected:
	string _colour = "��ɫ"; // ��ɫ
	string _num = "��ABIT00"; // ���ƺ�
	Tire _t; // ��̥
};
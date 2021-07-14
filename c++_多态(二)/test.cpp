#include<iostream>
using namespace std;

//��̬��ԭ��
//�麯����
// ���ﳣ��һ�������⣺sizeof(Base)�Ƕ��٣�
class Base
{
public:
	virtual void Func1()
	{
		cout << "Func1()" << endl;
	}
private:
	int _b = 1;
};
//ͨ���۲�������Ƿ���b������8bytes������_b��Ա������һ��__vfptr���ڶ����ǰ��(ע����Щƽ̨���ܻ�
//	�ŵ����������棬�����ƽ̨�й�)�������е����ָ�����ǽ����麯����ָ��(v����virtual��f����
//		function)��һ�������麯�������ж����ٶ���һ���麯����ָ�룬��Ϊ�麯���ĵ�ַҪ���ŵ��麯�����У�
//	�麯����Ҳ������
// �������Ĵ��������������¸���
// 1.��������һ��������Deriveȥ�̳�Base
// 2.Derive����дFunc1
// 3.Base������һ���麯��Func2��һ����ͨ����Func3
class Base
{
public:
	virtual void Func1()
	{
		cout << "Base::Func1()" << endl;
	}
	virtual void Func2()
	{
		cout << "Base::Func2()" << endl;
	}
	void Func3()
	{
		cout << "Base::Func3()" << endl;
	}
private:
	int _b = 1;
};
class Derive : public Base
{
public:
	virtual void Func1()
	{
		cout << "Derive::Func1()" << endl;
	}
private:
	int _d = 2;
};
int main()
{
	Base b;
	Derive d;
	return 0;
}
//ͨ���۲�Ͳ��ԣ����Ƿ��������¼������⣺
//1. ���������d��Ҳ��һ�����ָ�룬d�����������ֹ��ɣ�һ�����Ǹ���̳������ĳ�Ա�����ָ��Ҳ��
//�Ǵ��ڲ��ֵ���һ�������Լ��ĳ�Ա��
//2. ����b�����������d��������ǲ�һ���ģ��������Ƿ���Func1�������д������d������д������
//д��Derive::Func1�������麯������дҲ�������ǣ����Ǿ���ָ������麯���ĸ��ǡ���д���﷨��
//�з���������ԭ���Ľз���
//3. ����Func2�̳����������麯�������ԷŽ������Func3Ҳ�̳������ˣ����ǲ����麯�������Բ���
//�Ž����
//4. �麯��������һ�����麯��ָ���ָ�����飬���������������һ��nullptr��
//5. �ܽ�һ���������������ɣ�a.�Ƚ������е�������ݿ���һ�ݵ������������ b.�����������д�˻�
//����ĳ���麯�������������Լ����麯����������л�����麯�� c.�������Լ������ӵ��麯��������
//�������е������������ӵ��������������
//6. ���ﻹ��һ��ͯЬ�Ǻ����׻��������⣺�麯�������ĵģ��������ĵģ� ���麯������������
//���ڶ����С�ע������Ļش�Ĵ�ġ����Ǻܶ�ͯЬ������������ΪȻ�ġ�ע����������麯��ָ
//�룬�����麯�����麯������ͨ����һ���ģ����Ǵ��ڴ���εģ�ֻ������ָ���ִ浽������С�����
//�����д�Ĳ��������������ָ�롣

//��̬��ԭ��:�����̬��̬�Ժ�ĺ������ã������ڱ���ʱȷ���ģ������������Ժ󵽶�����ȥ�ҵġ��������̬��������ʱ�Ǳ���ʱȷ���õġ�
class Person {
public:
	virtual void BuyTicket() { cout << "��Ʊ-ȫ��" << endl; }
};
class Student : public Person {
public:
	virtual void BuyTicket() { cout << "��Ʊ-���" << endl; }
};
void Func(Person& p) {
	p.BuyTicket();
}
int main()
{
	Person Mike;
	Func(Mike);

	Student Johnson;
	Func(Johnson);
	return 0;
}

// ��̬���뾲̬��:1. ��̬���ֳ�Ϊǰ�ڰ�(���)���ڳ�������ڼ�ȷ���˳������Ϊ��Ҳ��Ϊ��̬��̬�����磺��������
//2. ��̬���ֳƺ��ڰ�(���)�����ڳ��������ڼ䣬���ݾ����õ�������ȷ������ľ�����Ϊ������
//����ĺ�����Ҳ��Ϊ��̬��̬��

//���̳��е��麯����
class Base {
public:
	virtual void func1() { cout << "Base::func1" << endl; }
	virtual void func2() { cout << "Base::func2" << endl; }
private:
	int a;
};
class Derive :public Base {
public:
	virtual void func1() { cout << "Derive::func1" << endl; }
	virtual void func3() { cout << "Derive::func3" << endl; }
	virtual void func4() { cout << "Derive::func4" << endl; }
private:
	int b;
};


typedef void(*VFPTR) ();
void PrintVTable(VFPTR vTable[])
{
	// ����ȡ����е��麯��ָ���ӡ�����á����þͿ��Կ���������ĸ�����
	cout << " ����ַ>" << vTable << endl;
	for (int i = 0; vTable[i] != nullptr; ++i)
	{
		printf(" ��%d���麯����ַ :0X%x,->", i, vTable[i]);
		VFPTR f = vTable[i];
		f();
	}
	cout << endl;
}
int main()
{
	Base b;
	Derive d;
	// ˼·��ȡ��b��d�����ͷ4bytes����������ָ�룬ǰ������˵���麯��������һ�����麯��ָ���ָ�����飬���������������һ��nullptr
		// 1.��ȡb�ĵ�ַ��ǿת��һ��int*��ָ��
		// 2.�ٽ�����ȡֵ����ȡ����b����ͷ4bytes��ֵ�����ֵ����ָ������ָ��
		// 3.��ǿת��VFPTR*����Ϊ������һ����VFPTR����(�麯��ָ������)�����顣
		// 4.���ָ�봫�ݸ�PrintVTable���д�ӡ���
		// 5.��Ҫ˵�����������ӡ���Ĵ��뾭�����������Ϊ��������ʱ�����Ĵ����ɾ�����������û�з�nullptr������Խ�磬���Ǳ����������⡣����ֻ��Ҫ��Ŀ¼���� - ���� - �������������ٱ���ͺ��ˡ�
		VFPTR * vTableb = (VFPTR*)(*(int*)&b);
	PrintVTable(vTableb);
	VFPTR* vTabled = (VFPTR*)(*(int*)&d);
	PrintVTable(vTabled);
	return 0;
}

//��̳��е��麯����: ��̳��������ĩβд�ĺ������ڵ�һ���̳л��ಿ�ֵ��麯�����С�
class Base1 {
public:
	virtual void func1() { cout << "Base1::func1" << endl; }
	virtual void func2() { cout << "Base1::func2" << endl; }
private:
	int b1;
};
class Base2 {
public:
	virtual void func1() { cout << "Base2::func1" << endl; }
	virtual void func2() { cout << "Base2::func2" << endl; }
private:
	int b2;
};
class Derive : public Base1, public Base2 {
public:
	virtual void func1() { cout << "Derive::func1" << endl; }
	virtual void func3() { cout << "Derive::func3" << endl; }
private:
	int d1;
};
typedef void(*VFPTR) ();
void PrintVTable(VFPTR vTable[])
{
	cout << " ����ַ>" << vTable << endl;
	for (int i = 0; vTable[i] != nullptr; ++i)
	{
		printf(" ��%d���麯����ַ :0X%x,->", i, vTable[i]);
		VFPTR f = vTable[i];
		f();
	}
	cout << endl;
}
int main()
{
	Derive d;
	VFPTR* vTableb1 = (VFPTR*)(*(int*)&d);
	PrintVTable(vTableb1);
	VFPTR* vTableb2 = (VFPTR*)(*(int*)((char*)&d + sizeof(Base1)));
	PrintVTable(vTableb2);
	return 0;
}
#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
using namespace std;
//class Date
//{
//public:
//	int GetMonthDay(int year, int month)
//	{
//		static int MonthDays[13] = { 0,31,28,31,30,31,30,31,31,30,31,30,31 };
//		if (month == 2 && ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0))
//			return 29;
//		else
//		{
//			return MonthDays[month];
//		}
//	}
//	Date(int year = 0, int month = 1, int day = 1)
//	{
//		if (year >= 0 && month >= 1 && month <= 12 && day >= 1 && day <= GetMonthDay(year, month))
//		{
//			_year = year;
//			_month = month;
//			_day = day;
//		}
//		else
//		{
//			cout << "�Ƿ�����" << endl;
//		}
//
//
//	}
//	Date(const Date& d)  //����Ȩ����Сʹ��const ����d1�����
//	{
//		_year = d._year;
//		_month = d._month;
//		_day = d._day;
//	}
//	inline bool operator==(const Date& d)
//	{
//		return _year == d._year     //�����൱�� d1._year==d.year  ==>  this->_year==d.year;
//			&& _month == d._month
//			&& _day == d._day;
//	}
//	bool operator<(const Date& d)
//	{
//		if (_year < d._year) return true;
//		else if (_year == d._year && _month < d._month) return true;
//		else if (_year == d._year && _month == d._month && _day < d._day) return true;
//		else return false;
//	}
//	bool operator>(const Date& d)
//	{
//		return !(*this <= d);
//	}
//	bool operator<=(const Date& d)
//	{
//		return *this < d || *this == d;//�����������ʵ�֣�
//	}
//	bool operator>=(const Date& d)
//	{
//		return !(*this < d);
//	}
//	bool operator!=(const Date& d)
//	{
//		return !(*this == d);
//	}
//	Date operator+(int day)
//	{
//		//Date ret = d2;
//		Date ret(*this);
//		ret._day += day;    // ==> ret.operator+=(int day);
//		return ret;
//	}
//	Date& operator+=(int day)
//	{
//		if (day < 0)
//		{
//			return *this -= -day;
//		}
//		_day += day;
//		while (_day > GetMonthDay(_year, _month))
//		{
//			_day -= GetMonthDay(_year, _month);
//			_month++;
//			if (_month == 13)
//			{
//				_year++;
//				_month = 1;
//			}
//		}
//		return *this;
//	}
//	Date& operator-=(int day)   //d3-=day
//	{
//		if (day < 0)
//		{
//			return *this += -day;
//		}
//		_day -= day;
//		while (_day <= 0)
//		{
//			_month--;
//			if (_month == 0)
//			{
//				_year--;
//				_month = 12;
//			}
//			_day += GetMonthDay(_year, _month);
//		}
//		return *this;
//	}
//	Date operator-(int day)    //d3-=10
//	{
//		Date ret = *this;
//		ret._day -= day;   // ==> ret.operator-=(int day);
//		return ret;
//	}
//	Date& operator--()   //--d3    Ĭ����ǰ��--
//	{
//		* this -= 1;
//		return *this;
//	}
//	Date operator--(int)  //����--   Ϊ�˹������غ���
//	{
//		Date tmp = (*this);
//		*this -= 1;
//		return tmp;   //���ؼ�֮ǰ��
//	}
//	Date& operator++()  //++ d3  //++d3    Ĭ����ǰ��++
//	{
//		* this += 1;
//		return *this;
//	}
//	Date operator++(int)  //d3++   ����++   Ϊ�˹������غ���
//	{
//		Date tmp = (*this);
//		*this += 1;
//		return tmp;   //���ؼ�֮ǰ��
//	}
//	Date& operator=(const Date& d)  //���Զ������ʹ��κͷ���ֵʱ���ڿ��Ե�����¾���ʹ�����á����Լ��ٿ������캯���ĵ���
//	{
//		if (this != &d)  //��ֹ�Լ����Լ���ֵ  ������
//		{
//			_year = d._year;
//			_month = d._month;
//			_day = d._day;
//		}
//		return *this;
//	}
//	int operator-(const Date& d)  //���ڼ�����
//	{
//		int flag = -1;//�ж��������������������
//		int n = 0;
//		Date smaller = *this;  //��������
//		Date Greater = d;
//		if (*this > d)
//		{
//			smaller = d;    //��ֵ Date& operator=(const Date& d)
//			Greater = *this;
//			flag = 1;
//		}
//		while (smaller != Greater)
//		{
//			++smaller;
//			n++;
//		}
//		return n * flag;
//	}
//	void Print()const  //==��void Print(const Date* this)����д�֮꣬��*this�Ͳ������޸ĳ�Ա������
//	{
//		cout << _year << "-" << _month << "-" << _day << endl;
//	}
//	const Date* operator&()const
//	{
//		return this;
//	}
//	Date* operator&()
//	{
//		return this;
//	}
//private:
//	int _year;
//	int _month;
//	int _day;
//};
//void f(const Date& d)//�������const��Ա����
//{
//	d.Print();    //d.Print(const Date& d) ���ﴫ�α�const���Σ�Print(Date* this)��*this��Ȩ�ޱ��Ŵ�
//	            // �����޷����룬����*this�����صģ�����Print����Ӧ��ΪPrint()const;����const���ε�
//	            //��thisָ��Ķ���
//
//}
//int main()
//{
//	Date d(2021, 4, 18);
//	f(d);
//	return 0;
//}

//��ʼ������ ���캯���帳ֵ:�ڴ�������ʱ��������ͨ�����ù��캯�����������и�����Ա����һ�����ʵĳ�ʼֵ��
            //���캯�����е����ֻ�ܽ������Ϊ����ֵ�������ܳ�����ʼ������Ϊ��ʼ��ֻ�ܳ�ʼ��һ�Σ������캯�����ڿ��Զ�θ�ֵ��
            /* ��ʼ���б���һ��ð�ſ�ʼ��������һ���Զ��ŷָ������ݳ�Ա�б�ÿ��"��Ա����"�����һ��������
             ���еĳ�ʼֵ����ʽ��ע�⣺1. ÿ����Ա�����ڳ�ʼ���б���ֻ�ܳ���һ��(��ʼ��ֻ�ܳ�ʼ��һ��)
                                       2. ���а������³�Ա��������ڳ�ʼ���б�λ�ý��г�ʼ�������ó�Ա������const��Ա�������Զ������ͳ�Ա(����û��Ĭ�Ϲ��캯��)*/
class A
{
public:
    A(int a)
        :_a(a)
    {}
private:
    int _a;
};
class B
{
public:
    B(int a, int ref)
        :_aobj(a)
        , _ref(ref)
        , _n(10)
    {}
private:
    A _aobj; // û��Ĭ�Ϲ��캯��
    int& _ref; // ����
    const int _n; // const
};
//�ܽ᣺ 1.����ʹ�ó�ʼ���б��ʼ������Ϊ�������Ƿ�ʹ�ó�ʼ���б������Զ������ͳ�Ա������һ������ʹ
//�ó�ʼ���б��ʼ���� 2.��Ա������������������������ڳ�ʼ���б��еĳ�ʼ��˳�������ڳ�ʼ���б��е��Ⱥ�����޹أ�ֻ���Ա���������õ�˳���й�


//static��Ա
//��Ƴ�һ����A�����Լ����������ܹ������˶��ٸ�����
//˼·�������ǹ��캯�����߿������캯��������
//class A
//{
//public:
//	A()  //���캯��
//	{
//		n++;
//	}
//	A(const A& a)//�������캯��
//	{
//		n++;
//	}
//	static int GetN()//static���εĳ�Ա����û��thisָ�룬�ú����в��ܷ��ʷǾ�̬���ĳ�Ա(�磺_a)
//	{
//		//_a = 10;//����û��thisָ��  ���Բ��ܷ���
//		return n;
//	}
//private:
//	static int n;//���������ﱻstatic�����Ժ�Ͳ�����ĳ������������������ж�����������ࡣ
//	           //�����ܵ�public��privateȨ������  n�ھ�̬��
//	int _a;
//};
//int A::n = 0;//n�Ķ���
//A f1(A a) //��ֵ����  ��������
//{
//	return a;//��ֵ���� ��������һ��
//}
//int main()
//{
//	A a1;//����
//	A a2;//����
//	f1(a1);
//	f1(a2);
//	cout << a1.GetN() << endl;
//	cout << a2.GetN() << endl;
//	cout << A::GetN() << endl;
//	return 0;
//}

 //explicit  1.���캯���������Թ������ʼ�����󣬶��ڵ��������Ĺ��캯��������������ת��������
class Date
{
public:
	Date(int year) //�����ʹ��explicit��d1 = 2019;����ִ�С�ִ���߼�����ʽת������
		:_year(year)             // ������ʱDate tmp�����ù��캯����tmp��ʼ��Ϊ2019��tmp(2019) ,Ȼ��d1=tmp���п�������
	{}

	//explicit Date(int year)  //��explicit���κ���ֹd1 = 2019������ָ�ֵ����
	//	:_year(year)
	//{}
    Date(int year,int month,int day)  //��explicit���κ���ֹd1 = 2019������ָ�ֵ����
		:_year(year)
		,_month(month)
		,_day(day)
	{}

private:
	int _year;
	int _month;
	int _day;
};
void TestDate()
{
	Date d1(2018);

	// ��һ�����α������������Ͷ���ֵ
	// ʵ�ʱ������������2019����һ������������������������d1������и�ֵ
    d1 = 2019;//�ɶ��Բ�  //�����ʹ��explicit��d1 = 2019;����ִ�С�ִ���߼�����ʽת������
             // ������ʱDate tmp�����ù��캯����tmp��ʼ��Ϊ2019��tmp(2019) ,Ȼ��d1=tmp���п�������  ����Ż�Ϊ���캯��
	        // 
	const Date& d1 = 2019;//��Ϊ��ʱ�������г��ԣ������������д��Date& d1=2019�ǲ��ܱ���ģ�Ȩ�޷Ŵ󣩣����Ǽ���const���ξͿ���������
                        //���ǣ���ʱ��û���Ż����������õľ�����ʱ����tmp(2019)
	Date d2 = { 2018,4,18 }; //c++11��֧�ִ��ֲ������뵥���������캯�����ƣ��������ַ������Լ�explicit����
}
int main()
{
	TestDate();
	return 0;
}



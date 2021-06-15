#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
using namespace std;

//��������

//class Date
//{
//public:
//	Date(int year = 0, int month = 1, int day = 1)
//	{
//		_year = year;
//		_month = month;
//		_day = day;
//	}
//	Date(const Date& d)  //����Ȩ����Сʹ��const ����d1�����
//	{
//		_year = d._year;
//		_month = d._month;
//		_day = d._day;
//	}
//	//bool operator==(const Date& d1, const Date& d2) //����������thisָ�룬���²�������
//	//{
//	//	return d1._year == d2._year
//	//		&& d1._month == d2._month
//	//		&& d1._day == d2._day;
//	//}
//	bool operator==(const Date& d)
//	{
//		return _year == d._year     //�����൱�� d1._year==d.year  ==>  this->_year==d.year;
//			&& _month == d._month
//			&& _day == d._day;
//	}
//	bool operator>(const Date& d)
//	{
//		if (_year > d._year) return true;
//		else if (_year == d._year && _month > d._month) return true;
//		else if (_year == d._year && _month == d._month && _day > d._day)  return true;
//		else return false;
//	}
//private:
//	int _year;
//	int _month;
//	int _day;
//};
//int main()
//{
//	Date d1(2015,5,12);
//	Date d2(d1);   //�������� d2����d1������
//	Date d3 = d1;//��������
//	return 0;
//}

//��������أ��Զ��������ǲ���ʹ��������ģ�Ҫ�þ�Ҫʹ�����غ������Զ��������õ�ʱ��ȼ��ڵ���������غ���
//bool IsDateEqual(const Date& d1, const Date& d2)
//{
//	//...
//}
//������м�����������operator���صĺ������м�������
//bool operator==(const Date& d1, const Date& d2)
//{
//	return d1._year == d2._year
//		&& d1._month == d2._month
//		&& d1._day == d2._day;
//}
//int main()
//{
//	Date d1(2015, 5, 12);
//	Date d2(2015, 5, 13);
//	//IsDateEqual(d1, d2);  �Ƚ�������Ĵ�С
//	//d1 == d2;//����������Զ������ operator==(d1,d2);
//	//operator==(d1, d2);//ʵ���в�������д���ɶ��Բ�ǿ
//	d1 == d2;  //�����൱�� d1.operator==(d2);
//	d1 > d2;
//	cout << (d1 > d2) << endl;
//	return 0;
//}

//ʵ��һ�����Ƶ�������

class Date
{
public:
	int GetMonthDay(int year, int month)
	{
		static int MonthDays[13] = { 0,31,28,31,30,31,30,31,31,30,31,30,31 };
		if (month==2 && ((year%4==0 && year%100!=0)|| year%400==0))
			return 29;
		else
		{
			return MonthDays[month];
		}
	}
	Date(int year = 0, int month = 1, int day = 1)
	{
		if (year >= 0 && month >= 1 && month <= 12 && day >= 1 && day <= GetMonthDay(year, month))
		{
			_year = year;
			_month = month;
			_day = day;
		}
		else
		{
			cout << "�Ƿ�����" << endl;
		}
           
		
	}
	Date(const Date& d)  //����Ȩ����Сʹ��const ����d1�����
	{
		_year = d._year;
		_month = d._month;
		_day = d._day;
	}
	inline bool operator==(const Date& d)
	{
		return _year == d._year     //�����൱�� d1._year==d.year  ==>  this->_year==d.year;
			&& _month == d._month
			&& _day == d._day;
	}
	bool operator<(const Date& d)
	{
		if (_year < d._year) return true;
		else if (_year == d._year && _month < d._month) return true;
		else if (_year == d._year && _month == d._month && _day < d._day) return true;
		else return false;
	}
	//bool operator<=(const Date& d) //����ʵ���ظ���̫�� ���� �����µĳ�Ա����������Ҫ�޸ĵ���̫��
	//{
	//	if (_year < d._year) return true;
	//	else if (_year == d._year && _month < d._month) return true;
	//	else if (_year == d._year && _month == d._month && _day <= d._day) return true;
	//	else return false;
	//}
	// d1<=d2;==>d1.operator(&d1,d2);==>d1.operator(Date* this,const Date& d);
	/*bool operator>(const Date& d)
	{
		if (_year > d._year) return true;
		else if (_year == d._year && _month > d._month) return true;
		else if (_year == d._year && _month == d._month && _day > d._day)  return true;
		else return false;
	}*/
	bool operator>(const Date& d)
	{
		return !(*this <= d);
	}
	bool operator<=(const Date& d)
	{
		return *this < d || *this == d;//�����������ʵ�֣�
	}
	bool operator>=(const Date& d)
	{
		return !(*this < d);
	}
	bool operator!=(const Date& d)
	{
		return !(*this == d);
	}
	Date operator+(int day)
	{
		//Date ret = d2;
		Date ret(*this);
		ret._day += day;    // ==> ret.operator+=(int day);
		//while (ret._day > GetMonthDay(ret._year, ret._month))   //��������  ����Date& operator+=(int day)  ʵ��
		//{
		//	//������ڲ��Ϸ�����Ҫ�����Ͻ�λ
		//	ret._day -= GetMonthDay(ret._year, ret._month);
		//	ret._month++;
		//	if (ret._month == 13)
		//	{
		//		ret._year++;
		//		ret._month = 1;
		//	}
		//}
		return ret;
	}
	Date& operator+=(int day)
	{
		if (day < 0)
		{
			return *this -= -day;
		}
		_day += day;
		while (_day > GetMonthDay(_year, _month))
		{
			_day -= GetMonthDay(_year, _month);
			_month++;
			if (_month == 13)
			{
				_year++;
				_month = 1;
			}
		}
		return *this;
	}
	Date& operator-=(int day)   //d3-=day
	{
		if (day < 0)
		{
			return *this += -day;
		}
		_day -= day;
		while (_day <= 0)
		{
			_month--;
			if (_month == 0)
			{
				_year--;
				_month = 12;
			}
			_day += GetMonthDay(_year, _month);
		}
		return *this;
	}
	Date operator-(int day)    //d3-=10
	{
		Date ret = *this;
		ret._day -= day;   // ==> ret.operator-=(int day);
		/*while (ret._day <= 0)     //��������  ����Date& operator-=(int day)  ʵ��
		{
			ret._month--;
			if (ret._month == 0)
			{
				ret._year--;
				ret._month = 12;
			}
			ret._day += GetMonthDay(_year, _month);
		}*/
		return ret;
	}
	Date& operator--()   //--d3    Ĭ����ǰ��--
	{
		/*_day--;*/
	/*	while (_day <= 0)
		{
			_month--;
			if (_month == 0)
			{
				_year--;
				_month = 12;
			}
			_day += GetMonthDay(_year, _month);
		}*/
		* this -= 1;
		return *this;
	}
	Date operator--(int)  //����--   Ϊ�˹������غ���
	{
		Date tmp = (*this);
		*this -= 1;
		return tmp;   //���ؼ�֮ǰ��
	}
	Date& operator++()  //++ d3  //++d3    Ĭ����ǰ��++
	{
		/*_day++;*/
		/*while (_day > GetMonthDay(_year, _month))
		{
			_day -= GetMonthDay(_year, _month);
			_month++;
			if (_month == 12)
			{
				_year++;
				_month = 1;
			}
		}*/
		* this += 1;
		return *this;
	}
	Date operator++(int)  //d3++   ����++   Ϊ�˹������غ���
	{
		Date tmp = (*this);
		* this += 1;
		return tmp;   //���ؼ�֮ǰ��
	}
	Date& operator=(const Date& d)  //���Զ������ʹ��κͷ���ֵʱ���ڿ��Ե�����¾���ʹ�����á����Լ��ٿ������캯���ĵ���
	{
		if (this != &d)  //��ֹ�Լ����Լ���ֵ  ������
		{
			_year = d._year;
			_month = d._month;
			_day = d._day;
		}
		return *this;
	}
	int operator-(const Date& d)  //���ڼ�����
	{
		int flag = -1;//�ж��������������������
		int n = 0;
		Date smaller = *this;  //��������
		Date Greater = d;
		if (*this > d)
		{
			smaller = d;    //��ֵ Date& operator=(const Date& d)
			Greater = *this;
			flag = 1;
		}
		while (smaller != Greater)
		{
			++smaller;
			n++;
		}
		return n*flag;
	}
	void Print()
	{
		cout << _year << "-" << _month << "-" << _day << endl;
	}
private:
	int _year;
	int _month;
	int _day;
};
int main()
{
	Date d;
	d.Print();
	//Date d1(2020,2,30);
	//d1.Print();
	Date d2(2020, 3, 28);
	d2.Print();
	Date d3 = d2 + 100;
	d3.Print();
	d3 += 10;
	d3.Print();
	d3 = d2;   //Ҳ����������ֵ int i=0,j=1,k=2;  i=j=k;������ֵ�����Ǵ�������ִ�У�j=k������ʽ�Ҹ�����ֵ��j��Ȼ��j�ڸ�ֵ��i
	d3.Print();
	d3 += 100;
	d3.Print();
	d3 -= 10;
	d3.Print();
	d3 --;
	d3.Print();
	d3++;
	d3.Print();
	++d3;
	d3.Print();
	--d3;
	d3.Print();
	
	cout << (d3 - d2) << endl;
	//cout << (d1 == d2) << endl;
	//cout << (d1 > d2) << endl;
	//cout << (d1 < d2) << endl;
	//cout << (d1 != d2) << endl;
	//cout << (d1 >= d2) << endl;
	//cout << (d1 <= d2) << endl;
	return 0;
}
//******������ǲ�д���������operator=()���������Զ���������������������ֻ�����ǳ������������һ��һ���ֽڿ�����ȥ�������������￪���˶�̬�ռ䣬ֻ����ǳ����ʱ��
//      �ڽ�����������ʱ���ͬһ�鶯̬�ռ���ж���ͷţ����³������
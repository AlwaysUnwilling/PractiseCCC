#include<iostream>
using namespace std;


//������ģ�����
//template<class T,int N>    //ʵ���У������͵�ģ�����������һ�㶼��int����ЩҲ����char/short/long/long long/
//class A                   //�����Զ������Ͳ��������������͵�ģ����������ͣ�string,vector�ȣ�
//{
//public:
//
//private:
//	T _a[N];
//};
//int main()
//{
//	A<int,10> a1;
//	A<int, 100> a2;
//	
//	return 0;
//}

//ģ����ػ�
//1.����ģ����ػ�
//template<class T>
//bool IsEqual(T& left, T& right)
//{
//	return left == right;
//}
////ģ����ػ�:���ĳЩ���͵����⻯����
//template<>
//bool IsEqual<char*>(char*& left, char*& right)
//{
//	//return left == right;
//	return strcmp(left, right) == 0;
//}
////2.��ģ����ػ�
//template<class T1,class T2>
//class Data
//{
//public:
//	Data()
//	{
//		cout << "Data<T1,T2>" << endl;
//	}
//private:
//	T1 _d1;
//	T2 _d2;
//};
////��ģ���ػ�
//template<>
//class Data<int, char>   //ȫ�ػ�
//{
//public:
//	Data()
//	{
//		cout << "ȫ�ػ���Data<int,char>" << endl;
//	}
//private:
//};
//template<class T1>
//class Data<T1, int>   //ƫ�ػ�
//{
//public:
//	Data()
//	{
//		cout << "ƫ�ػ���Data<int,char>" << endl;
//	}
//private:
//};
//template<class T1,class T2>
//class Data<T1*, T2*>   //ƫ�ػ�   ָ��
//{
//public:
//	Data()
//	{
//		cout << "ƫ�ػ���Data<T1*,T2*>" << endl;
//	}
//private:
//};
//template<class T1, class T2>
//class Data<T1&, T2&>   //ƫ�ػ�   ����
//{
//public:
//	Data()
//	{
//		cout << "ƫ�ػ���Data<T1&,T2&>" << endl;
//	}
//private:
//};
//int main()
//{ 
//	int a = 0;
//	int b = 1;
//	cout << IsEqual(a, b) << endl;
//
//	const char* p1 = "hello";  //�����Ҫ�Ƚ��ַ���������������ģ�庯�����޷�ʵ����ȷ�ıȽϵģ���ΪT������char*������ʵ�ʱȽϵ���
//	const char* p2 = "world";  // ����ָ��Ĵ�С����������Ҫ���ǱȽ�ָ��ָ����ַ����Ĵ�С��
//	cout << IsEqual(p1, p2) << endl;
//
//	Data<int, double> d1;
//	Data<int, char> d2;
//	Data<string, int> d3;
//	Data<char*, int*> d4;
//	Data<int&, short&> d5;
//	return 0;
//}
//ģ��ķ������
//������룺��Ŀ������һ�뽫����������������ŵ�.h��������������Ķ���ŵ�.cpp�С�
//ΪʲôҪ������룿����鿴��ά����

#include"Func.h"

int main()
{
	Func1();//Func1()���Ա���ͨ��ִ�С�
	Func2(10);//Func2(10)�ᱨ����ʧ��
	Func2(10.11);
	return 0;
}
//ͬ���Ƿ�����룬��ͨ����/����ԣ�������ģ��/��ģ��Ϊʲô���У�
//��Ϊ������ʱFunc.o�ļ��б�û�жԺ���ģ�������T����ʵ������û��ʵ�����Ͳ�������Func2()�ĵ�ַ��Func.cpp��test.cpp������֮ǰ�ֱ��ߵ��Ǹ��Եĵ��ߣ�ֱ������ʱ�Ż�ϵ�һ�𣩡�
//Func.h         Func.cpp     test.cpp
//1��Ԥ����չ��ͷ�ļ���ģ�壩�����滻���������롢ȥ��ע��
//���ɣ�         Func.i        test.i   ��Func.h �Ѿ���չ����
//2�����룺����﷨�����ɻ�����
//���ɣ�         Func.s        test.s
//3����ࣺ��������ת���ɶ����ƻ�����
//���ɣ�         Func.o        test.o
//4�����ӣ���Ŀ���ļ��ϵ�һ�𣬱���ʱFunc1()��Func2()���������������Ա���ͨ���ˡ�����ʱҪȥFunc.o����Func1()��Func2()
//         �ĵ�ַ������Func1()�ҵ��ˣ�Func2()û���ҵ������Ա������Ӵ���
//���ɣ�a.out


// ��ν��ģ��ķ���������⣿
//1.��ʾʵ����(����Func.cpp������ģ�嶨��ĵط�):���Ƽ�ʹ�ã���׸�������㡣
template
void Func2<int>(const int& x);
template
void Func2<double>(const double& x);
//2.��Ҫ�������ģ��(�����˿�ά����)��ģ��Ķ��������������.h�ļ��С�

//�ܽ᣺ģ����ŵ㣺1.ģ�帴���˴��룬��ʡ��Դ������ĵ���������c++�ı�׼ģ��⣨STL����˶�������
//                  2.��ǿ�˴���������
//      ģ���ȱ�㣺1.ģ�����Ӵ����������⣬Ҳ����ӱ���ʱ��߳���
//                  2.����ģ��������ʱ��������Ϣ�ǳ����ң����׶�λ����
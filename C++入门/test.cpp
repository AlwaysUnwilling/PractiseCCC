#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
//using namespace std;//c++���ж������Ƿŵ�std�����ռ���
//
//int main()
//{
//	int a = 10;
//	cout << "a="<<a<< endl;
//	std:: cout << "a=" << a << std::endl;
//	return 0;
//}

//�ڹ������Ƽ�ʹ�ò���չ��ʹ��
//using std::cout;//����Ļ���
//using std::endl;
//using std::cin;//����Ļ����
//int main()
//{
//	int i=1;
//	int a = 10;
//	double d = 1.1;
//	cout << "a=" << a << endl;
//	std::cout << "a=" << a << std::endl;
//	cout << "a=" << a << endl << "d=" << d << endl;//�����Զ�ʶ������
//	cin >> i;
//	//std::cin >> i;
//	cout << "i=" << i << endl;
//	return 0;
//}

using namespace std;
//void Func(int a = 0)//ȱʡ����
//{
//	cout << a << endl;
//}
//int main()
//{
//	Func();//ȱʡ����
//	Func(1);
//	return 0;
//}

//void Func1(int a = 0, int b = 10,int c=20)//��ȱʡ���������������������ȱʡ
//{
//	cout << a <<" "<< b <<" "<< c <<endl;
//}
//void Func2(int a , int b , int c = 20)
//{
//	cout << a << " " << b << " " << c << endl;
//}
//int main()
//{
//	Func1();//ȫȱʡ
//	Func1(1);
//	Func1(1,2);
//	Func1(1,2,3);
//	Func2(7,8);//����ʱ�����Ҫ���Σ���������������δ��Σ����ܿ�ȱ
//	Func2(7,8,9);
//	return 0;
//}

//���غ���:��������ͬ��������ͬ������ or ���� or ˳��ͬ��
//�Է���ֵû��Ҫ��
//int Add(int left, int right)
//{
//	return right + left;
//}
//double Add(double left, double right)
//{
//	return right + left;
//}
//long Add(long left, long right)
//{
//	return right + left;
//}
//int Add(int left, int right,int mid)
//{
//	return left + right + mid;
//}
//double Add(int left, double right, int mid)
//{
//	return left + right + mid;
//}
//double Add(double left, int right, int mid)
//{
//	return left + right + mid;
//}
//int main()
//{
//	Add(2, 3);
//	Add(2.0, 3.1);
//	Add(2L, 3L);
//	Add(2, 3,4);
//	Add(2, 3.2,5);
//	Add(2.1, 3,6);
//	return 0;
//}
//���������������⣺1.ʲô�Ǻ������أ�2.c++�����֧�ֺ������صģ�Ϊʲôc���Բ�֧�֣�
//�ش�2.��������ʱc����������ͬ�ĺ���������������Ӧ��.o�ļ�����Ϊc�����к������ڻ������б���ľ��Ǻ�����������
//        ��c++�У��������ڻ������л��������ĺ����������������������������ᱣ�������Ĳ������͵������Ϣ�����Ӷ���������
//        ����ͬ�ĺ�������<���������ι���>

//����
//int main()
//{
//	int a = 1;
//	int& ra = a;//ra��a�����ã���a�ı�������a�ı��������Լ��ı䣬��ôa��ֵ�ͻ�ı�
//	            //�������ԣ�1.�ڶ���ʱ�����ʼ������int& ra���Ǵ���ģ�
//
//	int d = 2;
//	ra = d;  //�����ǽ�d��ֵ��ֵ��ra����ᵼ��a��ֵҲ���Ϊ2
//	return 0;
//}
int main()
{
	int a = 1;
	int& b = a;//b��������Ȼ��int
	const int c = 2;
	//int& rc = c;//����ͻ���벻ͨ������Ϊ��c��const���α����ֻ���Զ���rc��int�����ǿɶ���д�ġ�
	const int& rc = c;//�����Ϳ��Ա�����

	int d = 3;
    int& e = d;
	const int& f = d;//����Ҳ�ǿ��Եģ�c�ǿɶ���д�ģ�f��ɱ���ֻ��
	//�ܽ᣺����ȡ����ʱ��Ȩ�޿�����С�������ܷŴ�

	int i = 5;
	double db = i;//��ʿ����ת��
	//double& ri = i;//���������Ǵ����
	const double& ri = i;//�����ǿ��Եģ�����ri���õ���ʵ����i��������i��Ϊһ��double��һ����ʱ��������ʱ�������г��ԡ�
	return 0;
}
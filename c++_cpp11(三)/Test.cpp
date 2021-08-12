#include<iostream>
#include<vector>
#include<list>
#include<string>
#include<map>
#include <initializer_list>
#include <algorithm>
#include <functional>

using namespace std;
///Lambda���ʽ

template<class T>
struct Greater
{
	bool operator()(const T& x1, const T& x2)
	{
		return x1 > x2;
	}
};

bool g2(const int& x1, const int& x2)
{
	return x1 > x2;
}

int x4()
{
	int array[] = { 4, 1, 8, 5, 3, 7, 0, 9, 2, 6 };

	// Ĭ�ϰ���С�ڱȽϣ��ų������������
	std::sort(array, array + sizeof(array) / sizeof(array[0]));

	// �����Ҫ������Ҫ�ı�Ԫ�صıȽϹ���
	//std::sort(array, array + sizeof(array) / sizeof(array[0]), greater<int>());


	Greater<int> g1;
	g1(1, 2); // g1��һ������������õ�������operator()ʵ�ֵıȽ�
	g2(1, 2); // g2��һ������ָ�룬�����ǵ�����ָ��ĺ���
	// ��������ȫ��ͬ�Ķ�����������������һ���ġ�

	std::sort(array, array + sizeof(array) / sizeof(array[0]), g1);
	std::sort(array, array + sizeof(array) / sizeof(array[0]), g2);

	return 0;
}

struct Goods
{
	string _name;  // ����
	double _price; // �۸�
	int    _num;   // ����
	// ...
};

// ��ô�������ȥ����Goods��operator>/operator<�ǲ��õģ���Ϊ�㲻֪����Ҫ����һ���Աȥ�Ƚ�

struct ComparePriceGreater
{
	bool operator()(const Goods& gl, const Goods& gr)
	{
		return gl._price > gr._price;
	}
};

struct CompareNumGreater
{
	bool operator()(const Goods& gl, const Goods& gr)
	{
		return gl._num > gr._num;
	}
};

struct CompareNameGreater
{
	bool operator()(const Goods& gl, const Goods& gr)
	{
		return gl._name > gr._name;
	}
};
// ��ʵ����С�ڵģ����ڵ��ں�С�ڵ��ڣ��ᷢ������Ҫд�ܶ���º���
// ��ʵֱ��д����Ҳ���ԣ���������Ҫд�ܶ������
// ���濴������Lambda���ʽ�����õĽ������

int x5()
{
	Goods gds[] = { { "ƻ��", 2.1 , 3}, { "�ཻ", 3.0, 5}, { "����", 2.2, 9}, { "����", 1.5, 10} };
	sort(gds, gds + sizeof(gds) / sizeof(gds[0]), ComparePriceGreater());
	sort(gds, gds + sizeof(gds) / sizeof(gds[0]), CompareNumGreater());
	sort(gds, gds + sizeof(gds) / sizeof(gds[0]), CompareNameGreater());

	// Lambda
	/*auto price_greater = [](const Goods& g1, const Goods& g2){
		return g1._price > g2._price;
	};
	sort(gds, gds + sizeof(gds) / sizeof(gds[0]), price_greater);*/

	return 0;
}


// Lambda���ʽ��ʵ���庯���ڴ��������������
// 1.����Lambda���ʽд�ĸ�ʽ
// 2.Lambda���ʽ��ʹ�ó���  ���Աȷº������󡢺���ָ�룩
// 3.Lambda���ʽ��ԭ��

int add1(int a, int b)
{
	return a + b;
}

int x7()
{
	// [��׽�б�](����)->����ֵ����{������}
	int a = 0, b = 1;
	// ʵ��һ��a+b��Lambda���ʽ
	auto add1 = [](int x1, int x2)->int {return x1 + x2; };
	cout << add1(a, b) << endl;

	// ��׽�б���ǲ�׽����һ��������Ķ���
	// ��ֵ��׽ [a]��׽a  [a,b]��׽a��b  [=]��׽ͬһ�������е����ж���
	// �����ò�׽ [&a]��׽a  [&a,&b]��׽a��b  [&]��׽ͬһ�������е����ж���
	// ��ֵ����Ķ����ǲ��ܱ��ı�ġ�(����mutable�Ϳ��Ըı���)
	auto add2 = [a, b]()->int {return a + b; };
	add2();

	// ʵ��a��b����
	//auto swap = [](int& a, int& b){int c = a; a = b; b = c; };
	auto swap = [](int& x, int& y) {
		int z = x;
		x = y;
		y = z;
	};

	swap(a, b);

	/* ����ȷ���÷�
	auto swapab = [a, b]()mutable {
		int c = a;
		a = b;
		b = c;
	};
	swapab();*/

	auto swapab = [&a, &b]() {
		int c = a;
		a = b;
		b = c;
	};
	swapab();

	return 0;
}

int x8()
{
	Goods gds[] = { { "ƻ��", 2.1, 3 }, { "�ཻ", 3.0, 5 }, { "����", 2.2, 9 }, { "����", 1.5, 10 } };
	sort(gds, gds + sizeof(gds) / sizeof(gds[0]), ComparePriceGreater());
	sort(gds, gds + sizeof(gds) / sizeof(gds[0]), CompareNumGreater());
	sort(gds, gds + sizeof(gds) / sizeof(gds[0]), CompareNameGreater());

	// Lambda���ƾͻ��ô���ɶ��Ը�ǿ
	/*auto price_greater = [](const Goods& g1, const Goods& g2)->bool{return g1._price > g2._price; };
	sort(gds, gds + sizeof(gds) / sizeof(gds[0]), price_greater);
	*/
	sort(gds, gds + sizeof(gds) / sizeof(gds[0]), [](const Goods& g1, const Goods& g2)->bool {return g1._price > g2._price; });

	sort(gds, gds + sizeof(gds) / sizeof(gds[0]), [](const Goods& g1, const Goods& g2)->bool {return g1._price < g2._price; });

	sort(gds, gds + sizeof(gds) / sizeof(gds[0]), [](const Goods& g1, const Goods& g2)->bool {return g1._num > g2._num; });

	sort(gds, gds + sizeof(gds) / sizeof(gds[0]), [](const Goods& g1, const Goods& g2)->bool {return g1._num < g2._num; });

	return 0;
}

int x9()
{
	int a = 1, b = 2;
	//  ���� = �����滻���������ɵ�Lambda_uuid�º����Ķ���
	auto add = [](int x, int y)->int {return x + y; };
	add(a, b);  // call Lambda_uuid�º�����operator()

	// �ײ㻹�������º�����ʵ�֣�Ҳ����˵�㶨����һ��Lambda���ʽ��
	// ʵ���ϱ�������ȫ��������һ����Lambda_uuid�࣬�º�����operator()�Ĳ�����ʵ��
	// ��������д��Lambda���ʽ�Ĳ�����ʵ��
	/*
	00A5C8AC  mov         eax, dword ptr[b]
	00A5C8AF  push        eax
	00A5C8B0  mov         ecx, dword ptr[a]
	00A5C8B3  push        ecx
	00A5C8B4  lea         ecx, [add]
	00A5C8B7  call        <lambda_afc2b2a8543babab622761003a6aa683>::operator() (0A5AEC0h)
	*/

	auto swapab = [&a, &b]() {
		int c = a;
		a = b;
		b = c;
	};
	swapab();
	/*
	0065DA4C  lea         ecx, [swapab]
	0065DA4F  call        <lambda_574e874b35e37ce2b7269242f59eb074>::operator() (065ADC0h)
	*/

	return 0;
}

//////////////////////////////////////////////////////////////////////////
// windows �Լ���һ��API           �磺CreateThread
// Linux   ʹ��posix��pthread      �磺pthread_create
// C++98�У��������д���̵߳ĳ��򣬼�������Windows���ܣ�Ҳ������Linux����ô��ô�죿 
// ����������
/*
#ifdef _WIN32
	CreateThread(...)
#else
	pthread_create(...)
#endif
*/

// C++11 �߳̿�
// �ص㣺��ƽ̨����������װ����(ÿ���߳���һ�������)
// ʵ��ԭ����װ��ʱʹ�����������룬Ҳ����˵���ĵײ㻹�Ƿֱ�����˲���ƽ̨���߳�API


#include<thread>
#include<mutex>
#include<atomic>

// 1������ָ�����threadʹ��

//mutex mtx;
//int x = 0;
//// �����߳�ȥһ���x��n��
//
//void Add(int n)
//{
//	mtx.lock(); // ���� һ���߳������ˣ���һ���߳̽�����
//	for (int i = 0; i < n; ++i)
//	{
//		++x;
//	}
//	mtx.unlock();
//
//	// ����
//	for (int i = 0; i < n; ++i)
//	{
//		mtx.lock();  // t2���г�ȥ��t1�ͽ����ˣ����ϾͰ�t2�л���
//		++x;  // t1
//		mtx.unlock();
//	}
//
//	// ˼��:Ϊʲô���л���һЩ����Ϊ������������̫С�ˣ�ʱ�䶼�����л�������
//}
//
//int main()
//{
//	thread t1(Add, 1000000);
//	thread t2(Add, 1000000);
//
//	t1.join();
//	t2.join();
//
//	cout << x << endl;
//
//	return 0;
//}

//int x = 0;
//atomic<int> x = 0; // ֧������/�����ԭ��++��--
//// ��չѧϰ��atomic֧��CAS->������̡�
//// �����߳�ȥһ���x��n��
//
//void Add(int n)
//{
//	for (int i = 0; i < n; ++i)
//	{
//		++x;
//	}
//}
//
//int main()
//{
//	thread t1(Add, 1000000);
//	thread t2(Add, 1000000);
//
//	t1.join();
//	t2.join();
//
//	cout << x << endl;
//
//	return 0;
//}


// �º������threadʹ��
atomic<int> x = 0;

struct Add
{
	void operator()(int n)
	{
		for (int i = 0; i < n; ++i)
		{
			++x;
		}
	}
};

int y2()
{
	Add add;
	thread t1(add, 100000);
	//thread t2(add, 100000);
	thread t2(Add(), 100000);


	cout << t1.get_id() << endl;
	cout << t2.get_id() << endl;

	t1.join();
	t2.join();

	cout << x << endl;

	return 0;
}

// Lambda���ʽ���thread
int y3()
{
	atomic<int> x = 0;

	auto add = [&x](int n) {
		for (int i = 0; i < n; ++i)
		{
			++x;
		}
	};

	thread t1(add, 100000);
	thread t2(add, 100000);

	cout << t1.get_id() << endl;
	cout << t2.get_id() << endl;

	t1.join();
	t2.join();

	cout << x << endl;

	return 0;
}

int main()
{
	atomic<int> x = 0;
	// m���̶߳�x��n��
	int m, n;
	cin >> m >> n;
	/*vector<thread> vthreads;
	for (int i = 0; i < m; ++i)
	{
		vthreads.push_back(thread([&x](int count){
			for (int i = 0; i < count; ++i)
			{
				++x;
			}
		}, n));
	}*/

	// ע�����thread֧���ƶ���ֵ���ƶ���������֧������Ŀ�������Ϳ�����ֵ
	vector<thread> vthreads(m);
	for (int i = 0; i < m; ++i)
	{
		// �ƶ���ֵ
		/*thread t([&x](int count){
			for (int i = 0; i < count; ++i)
			{
				++x;
			}
		}, n);
		vthreads[i] = move(t);*/
		vthreads[i] = thread([&x](int count) {
			for (int i = 0; i < count; ++i)
			{
				++x;
			}
			}, n);
	}

	for (auto& t : vthreads)
	{
		cout << t.get_id() << ".join()" << endl;
		t.join();
	}

	cout << x << endl;

	return 0;
}
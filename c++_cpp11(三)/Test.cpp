#include<iostream>
#include<vector>
#include<list>
#include<string>
#include<map>
#include <initializer_list>
#include <algorithm>
#include <functional>

using namespace std;
///Lambda表达式

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

	// 默认按照小于比较，排出来结果是升序
	std::sort(array, array + sizeof(array) / sizeof(array[0]));

	// 如果需要降序，需要改变元素的比较规则
	//std::sort(array, array + sizeof(array) / sizeof(array[0]), greater<int>());


	Greater<int> g1;
	g1(1, 2); // g1是一个对象，这里调用的是他的operator()实现的比较
	g2(1, 2); // g2是一个函数指针，这里是调用他指向的函数
	// 他们是完全不同的对象但是他们用起来是一样的。

	std::sort(array, array + sizeof(array) / sizeof(array[0]), g1);
	std::sort(array, array + sizeof(array) / sizeof(array[0]), g2);

	return 0;
}

struct Goods
{
	string _name;  // 名字
	double _price; // 价格
	int    _num;   // 数量
	// ...
};

// 那么这里如果去重载Goods的operator>/operator<是不好的，因为你不知道需要按哪一项成员去比较

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
// 其实还有小于的，大于等于和小于等于，会发现我们要写很多个仿函数
// 其实直接写函数也可以，不过类似要写很多个函数
// 下面看我们用Lambda表达式来更好的解决问题

int x5()
{
	Goods gds[] = { { "苹果", 2.1 , 3}, { "相交", 3.0, 5}, { "橙子", 2.2, 9}, { "菠萝", 1.5, 10} };
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


// Lambda表达式其实定义函数内存的匿名函数函数
// 1.掌握Lambda表达式写的格式
// 2.Lambda表达式的使用场景  （对比仿函数对象、函数指针）
// 3.Lambda表达式的原理

int add1(int a, int b)
{
	return a + b;
}

int x7()
{
	// [捕捉列表](参数)->返回值类型{函数体}
	int a = 0, b = 1;
	// 实现一个a+b的Lambda表达式
	auto add1 = [](int x1, int x2)->int {return x1 + x2; };
	cout << add1(a, b) << endl;

	// 捕捉列表就是捕捉跟我一个作用域的对象
	// 传值捕捉 [a]捕捉a  [a,b]捕捉a，b  [=]捕捉同一作用域中的所有对象
	// 传引用捕捉 [&a]捕捉a  [&a,&b]捕捉a，b  [&]捕捉同一作用域中的所有对象
	// 传值补充的对象是不能被改变的。(加上mutable就可以改变了)
	auto add2 = [a, b]()->int {return a + b; };
	add2();

	// 实现a和b交换
	//auto swap = [](int& a, int& b){int c = a; a = b; b = c; };
	auto swap = [](int& x, int& y) {
		int z = x;
		x = y;
		y = z;
	};

	swap(a, b);

	/* 不正确的用法
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
	Goods gds[] = { { "苹果", 2.1, 3 }, { "相交", 3.0, 5 }, { "橙子", 2.2, 9 }, { "菠萝", 1.5, 10 } };
	sort(gds, gds + sizeof(gds) / sizeof(gds[0]), ComparePriceGreater());
	sort(gds, gds + sizeof(gds) / sizeof(gds[0]), CompareNumGreater());
	sort(gds, gds + sizeof(gds) / sizeof(gds[0]), CompareNameGreater());

	// Lambda优势就会让代码可读性更强
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
	//  对象 = 对象（替换编译器生成的Lambda_uuid仿函数的对象）
	auto add = [](int x, int y)->int {return x + y; };
	add(a, b);  // call Lambda_uuid仿函数的operator()

	// 底层还是依靠仿函数来实现，也就是说你定义了一个Lambda表达式，
	// 实际上编译器会全局域生成一个叫Lambda_uuid类，仿函数的operator()的参数和实现
	// 就是我们写的Lambda表达式的参数和实现
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
// windows 自己的一套API           如：CreateThread
// Linux   使用posix的pthread      如：pthread_create
// C++98中，如果你想写多线程的程序，即可以在Windows下跑，也可以在Linux，那么怎么办？ 
// 用条件编译
/*
#ifdef _WIN32
	CreateThread(...)
#else
	pthread_create(...)
#endif
*/

// C++11 线程库
// 特点：跨平台、面向对象封装的类(每个线程是一个类对象)
// 实现原理：封装库时使用了条件编译，也就是说他的底层还是分别调用了不用平台的线程API


#include<thread>
#include<mutex>
#include<atomic>

// 1、函数指针配合thread使用

//mutex mtx;
//int x = 0;
//// 两个线程去一起对x加n次
//
//void Add(int n)
//{
//	mtx.lock(); // 串行 一个线程跑完了，另一个线程接着跑
//	for (int i = 0; i < n; ++i)
//	{
//		++x;
//	}
//	mtx.unlock();
//
//	// 并行
//	for (int i = 0; i < n; ++i)
//	{
//		mtx.lock();  // t2刚切出去，t1就解锁了，马上就把t2切回来
//		++x;  // t1
//		mtx.unlock();
//	}
//
//	// 思考:为什么串行还快一些？因为这里锁的粒度太小了，时间都花到切换上下文
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
//atomic<int> x = 0; // 支持整形/浮点的原子++、--
//// 扩展学习：atomic支持CAS->无锁编程。
//// 两个线程去一起对x加n次
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


// 仿函数配合thread使用
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

// Lambda表达式配合thread
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
	// m个线程对x加n次
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

	// 注意的是thread支持移动赋值和移动拷贝，不支持深拷贝的拷贝构造和拷贝赋值
	vector<thread> vthreads(m);
	for (int i = 0; i < m; ++i)
	{
		// 移动赋值
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
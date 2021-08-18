#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
using namespace std;
#include<thread>
// ����ɾ���� -- ���˽⣩
#include<memory>
class A
{
public:
	~A()
	{
		cout << "~A()" << endl;
	}
private:
	int _a1;
	int _a2;
};

template<class T>
struct DeleteArry
{
	void operator()(T* pa)
	{
		delete[] pa;
	}
};

struct Free
{
	void operator()(void* p)
	{
		cout << "free(p)" << endl;

		free(p);
	}
};

struct Fclose
{
	void operator()(FILE* p)
	{

		cout << "fclose(p)" << endl;

		fclose(p);
	}
};

int x4()
{
	std::shared_ptr<A> sp1(new A);
	std::shared_ptr<A> sp2(new A[10], DeleteArry<A>());
	std::shared_ptr<A> sp3((A*)malloc(sizeof(A)), Free());
	std::shared_ptr<FILE> sp4(fopen("test.txt", "w"), Fclose());

	return 0;
}

// ����ָ����RAII˼���һ��Ӧ�õ�����
// ����RAII���ǽ������캯�������������������飬��Ϊ���캯���������������ص㶼���Զ�����
#include<mutex>

// ʹ��RAII˼����Ƶ�����������
template<class Lock>
class LockGuard
{
public:
	LockGuard(Lock& lock)
		:_lk(lock)
	{
		_lk.lock();
	}

	~LockGuard()
	{
		cout << "����" << endl;
		_lk.unlock();
	}

	LockGuard(LockGuard<Lock>&) = delete;
	LockGuard<Lock>& operator=(LockGuard<Lock>&) = delete;
private:
	Lock& _lk;  // ע������������
};


//void f()
//{
//	mutex mtx;
//	mtx.lock();
//
//	// func()   // ����func�����п������쳣
//
//	mtx.unlock();
//}

int div()
{
	int a, b;
	cin >> a >> b;
	if (b == 0)
		throw invalid_argument("��0����");

	return a / b;
}
void f()
{
	mutex mtx;
	LockGuard<mutex> lg(mtx);

	cout << div() << endl;   // ����div�����п������쳣
}

int x5()
{
	//try
	//{
	//	f();
	//}
	//catch (exception& e)
	//{
	//	cout << e.what() << endl;
	//}
	char* p = new char[1024 * 1024 * 1024];


	return 0;
}

// �������������ֻ���ڶ���
// ˼·��������������һ��Ҫ���ù��캯�������߿�������
class HeapOnly
{
public:
	static HeapOnly* GetObj()
	{
		return new HeapOnly;
	}

private:
	HeapOnly()
	{}

	// C++98��������������˽��
	//HeapOnly(const HeapOnly& );
public:
	// C++11 : ������delete
	HeapOnly(const HeapOnly&) = delete;
};

int x7()
{
	//HeapOnly hp;
	//HeapOnly* p = new HeapOnly;
	//HeapOnly* p = HeapOnly::GetObj();
	std::shared_ptr<HeapOnly> sp1(HeapOnly::GetObj());
	std::shared_ptr<HeapOnly> sp2(HeapOnly::GetObj());

	//HeapOnly copy(*sp1);


	return 0;
}

//class StackOnly
//{
//public:
//	static StackOnly GetObj()
//	{
//		return StackOnly();
//	}
//private:
//	StackOnly()
//	{}
//};

// ���ַ�������һ������ȱ�ݣ��޷���ֹ�����ݶ�(��̬��)��������
class StackOnly
{
public:
	void* operator new(size_t size) = delete;
};

int x8()
{
	StackOnly so;
	//StackOnly* p = new StackOnly;

	static StackOnly sso;


	return 0;
}

// ֮ǰ�Ѿ�ѧ��һЩ���ģʽ
// ������ģʽ -- �������������������֮һ�� ��װ��Ƴ����ģ���һ�����������װ�Ժ󣬲���¶�����Ľṹ������£�ͳһ�ķ�ʽ�����޸������е����ݡ�

// ������ģʽ -- ���ֵ���һ�ָ���
// ����һЩ���������ģʽ�磺����ģʽ��װ����ģʽ���۲���ģʽ������ģʽ...
// һ����ֻ����ȫ��(������)ֻ��һ��ʵ������
// ʲô������ʹ�ã�����һ����������һ���ڴ�أ������еĶ��߳���Ҫ�ڴ涼Ҫ������ڴ����ȡ����ô����ڴ�ص���Ϳ�����Ƶ���ģʽ��

// ���������������ĳ������ģ�����������ڴ�أ���ô��Ͷ����MemoryPool
#include<thread>
#include<vector>
#include<windows.h>

class Singleton
{
public:
	static Singleton* GetInstance()
	{
		::Sleep(1000);
		if (_pinst == nullptr)
		{
			_pinst = new Singleton;
		}

		return _pinst;
	}

	Singleton(const Singleton& s) = delete;

private:
	Singleton()
	{}

	static Singleton* _pinst;
};

Singleton* Singleton::_pinst = nullptr;

int main()
{
	//Singleton s1;
	//Singleton s2;
	//cout << Singleton::GetInstance() << endl;
	//cout << Singleton::GetInstance() << endl;
	//cout << Singleton::GetInstance() << endl;
	//Singleton copy(*Singleton::GetInstance());

	vector<std::thread> vthreads;
	int n = 16;
	for (int i = 0; i < n; ++i)
	{
		vthreads.push_back(std::thread([]()
			{
				//cout << std::this_thread::get_id() <<":";
				cout << Singleton::GetInstance() << endl;
			}));
	}

	for (auto& t : vthreads)
	{
		t.join();
	}

	return 0;
}
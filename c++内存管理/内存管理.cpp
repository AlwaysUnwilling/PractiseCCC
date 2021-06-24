#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>

using namespace std;

// 1. new/delete 操作内置类型
//void Test()
//{
//	//动态申请内存空间
//	int* ptr = new int;
//	//动态申请一个int类型空间并初始化为10
//	int* ptr1 = new int(10);
//	//动态申请一个int类型的数组
//	int* ptr2 = new int[10];
//	//释放动态申请的内存
//	delete ptr;
//	delete ptr1;
//	delete ptr2;
//}
//
////问题：为什么c语言中有了malloc/free，c++也可以用，但还是需要new/delete ?
////答：1.针对内置类型new和malloc都是一样的；2.针对自定义类型new除了开辟空间外，还会调用自定义类型的构造函数，delete会释放空间并调用它的析构函数。
//struct ListNode
//{
//	int val;
//	struct ListNode* next;
//};
//ListNode* BuyListNode(int x)    //
//{
//	ListNode* node = (ListNode*)malloc(sizeof(ListNode));
//	if (node == NULL)
//		exit(-1);
//	node->next = NULL;
//	node->val = x;
//	return node;
//}
//class ListNodeCPP
//{
//public:
//	ListNodeCPP(int val=0, ListNodeCPP* next=nullptr)
//		:_val(val)
//		,_next(next)
//	{
//		cout << "ListNodeCPP()" << endl;
//	}
//	~ListNodeCPP()
//	{
//		cout << "~ListNodeCPP()" << endl;
//	}
//private:
//	int _val;
//	ListNodeCPP* _next;
//};
//int main()
//{
//	ListNode* list= BuyListNode(1);//c语言开辟空间只能自己去malloc实现函数
//	free(list);//这里仅仅是释放空间
//	list = NULL;
//	ListNodeCPP* list1 = new  ListNodeCPP(2);//c++的new除了开辟了空间还调用了 ListNodeCPP的构造函数
//	delete list1;     //这里不仅释放了动态开辟的空间而且还调用了 ListNodeCPP的析构函数完成清理工作
//
//	ListNodeCPP a[10];// 调用10次构造函数，出了作用域调用10次析构函数
//	ListNodeCPP* b = new ListNodeCPP[10];//这里b是指针不是对象，出了作用域指针不会调用析构函数
//	delete[]b;//释放指针指向的空间时会调用析构函数
//	return 0;
//}
 // 2.1 operator new 和operator delete函数：new和delete是用户进行动态内存申请和释放的操作符，operator new 和operator delete是系统提供的
//全局函数，new在底层调用operator new全局函数来申请空间，delete在底层通过operator delete全局
//函数来释放空间。
/*
operator new：该函数实际通过malloc来申请空间，当malloc申请空间成功时直接返回；申请空间失败，
尝试执行空 间不足应对措施，如果改应对措施用户设置了，则继续申请，否则抛异常。
*/
//void* __CRTDECL operator new(size_t size) _THROW1(_STD bad_alloc) {
//	// try to allocate size bytes
//	void* p;
//	while ((p = malloc(size)) == 0)
//		if (_callnewh(size) == 0)
//		{
//			// report no memory
//			// 如果申请内存失败了，这里会抛出bad_alloc 类型异常
//			static const std::bad_alloc nomem;
//			_RAISE(nomem);
//		}
//	return (p);
//}
///*
//operator delete: 该函数最终是通过free来释放空间的
//*/
//void operator delete(void* pUserData) {
//	_CrtMemBlockHeader* pHead;
//	RTCCALLBACK(_RTC_Free_hook, (pUserData, 0));
//	if (pUserData == NULL)
//		return;
//	_mlock(_HEAP_LOCK); /* block other threads */
//	__TRY
//		/* get a pointer to memory block header */
//		pHead = pHdr(pUserData);
//	/* verify block type */
//	_ASSERTE(_BLOCK_TYPE_IS_VALID(pHead->nBlockUse));
//	_free_dbg(pUserData, pHead->nBlockUse);
//	__FINALLY
//		_munlock(_HEAP_LOCK); /* release other threads */
//	__END_TRY_FINALLY
//		return;
//}
///*
//free的实现
//*/
//#define free(p) _free_dbg(p,_NORMAL_BLOOK)
//通过上述两个全局函数的实现知道，operator new 实际也是通过malloc来申请空间，如果malloc申请空间
//成功就直接返回，否则执行用户提供的空间不足应对措施，如果用户提供该措施就继续申请，否则就抛异
//常。operator delete 最终是通过free来释放空间的.
 

//2.2 operator new与operator delete的类专属重载:下面代码演示了，针对链表的节点ListNode通过重载类专属 operator new/ operator delete，实现链表节
//点使用内存池申请和释放内存，提高效率。
//struct ListNode
//{
//	ListNode* _next;
//	ListNode* _prev;
//	int _data;
//	void* operator new(size_t n)
//	{
//		void* p = nullptr;
//		p = allocator<ListNode>().allocate(1);
//		cout << "memory pool allocate" << endl;
//		return p;
//	}
//	void operator delete(void* p)
//	{
//		allocator<ListNode>().deallocate((ListNode*)p, 1);
//		cout << "memory pool deallocate" << endl;
//	}
//};
//class List
//{
//public:
//	List()
//	{
//		_head = new ListNode;
//		_head->_next = _head;
//		_head->_prev = _head;
//	}
//	~List()
//	{
//		ListNode* cur = _head->_next;
//		while (cur != _head)
//		{
//			ListNode* next = cur->_next;
//			delete cur;
//			cur = next;
//		}
//		delete _head;
//		_head = nullptr;
//	}
//private:
//	ListNode* _head;
//};
//int main()
//{
//	List l;
//	return 0;
//}
class A
{
public:
	A(int a=0)
		:_a(a)
	{
		cout << "A()" << endl;
	}
	~A()
	{
		cout << "~A()" << endl;
	}
private:
	int _a;
};
//int main()
//{
//	//对于内置类都一样；
//	//对于自定义类型：
//	A* p1 = (A*)malloc(sizeof(A));
//	A* p2 = (A*)operator new(sizeof(A));
//	A* p3 = new A; //只有new会调用构造函数初始化。
//	//operator new 和malloc的区别是什么？
//	//结论：两者的使用方式一样，处理错误的方式不同：malloc申请空间失败返回空指针，而operator new申请空间失败是通过抛异常来处理
//	size_t size=2;
//	void* p4 = malloc(1024 * 1024 * 1024 * size);
//	cout << p4 << endl;//失败返回0；
//	//free(p4);
//	void* p5 = operator new(1024 * 1024 * 1021 * size);
//	cout << p5 << endl;//失败抛异常（面向对象的处理方式）
//	//operator delete (p5);
//	//抛异常的处理方式：
//	try
//	{
//		void* p5 = operator new(1024 * 1024 * 1021 * size);
//		cout << p5 << endl;
//	}
//	catch (exception& e)
//	{
//		cout << e.what() << endl;
//	}
//	return 0;
//}

//那么malloc/free  、  operator new/operator delete 、new/delete三者有什么区别？
//operator new==malloc + 申请失败抛异常；
// new == operator new  +  构造函数；
// new与malloc的不同的地方是：1.调用构造函数初始化；2.申请空间失败会抛异常（这更符合面向对象）。
//delete比起free不一样的地方：1.调用析构函数完成清理工作。
// operator delete  和free没区别，因为释放空间失败直接终止程序。
//
//3.定位new表达式(placement-new):定位new表达式是在已分配的原始内存空间中调用构造函数初始化一个对象。
//使用格式：
//new (place_address) type或者new(place_address) type(initializer - list)
//place_address必须是一个指针，initializer - list是类型的初始化列表

class Test
{
public:
	Test()
		: _data(0)
	{
		cout << "Test():" << this << endl;
	}
	~Test()
	{
		cout << "~Test():" << this << endl;
	}

private:
	int _data;
};
void Test1()
{
	// pt现在指向的只不过是与Test对象相同大小的一段空间，还不能算是一个对象，因为构造函数没有执行
	Test* pt = (Test*)malloc(sizeof(Test));

	new(pt) Test; // 注意：如果Test类的构造函数有参数时，此处需要传参
}
int main()
{
	A* p1 = new A;
	delete p1;
	//模拟实现以上行为(开空间+显示调用构造函数和析构函数)：通过定位new来实现
	A* p2 = (A*)operator new(sizeof(A));
	new(p2)A(10);

	p2->~A();
	operator delete (p2);
	return 0;
}

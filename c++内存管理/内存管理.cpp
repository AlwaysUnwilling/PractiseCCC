#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>

using namespace std;

// 1. new/delete ������������
//void Test()
//{
//	//��̬�����ڴ�ռ�
//	int* ptr = new int;
//	//��̬����һ��int���Ϳռ䲢��ʼ��Ϊ10
//	int* ptr1 = new int(10);
//	//��̬����һ��int���͵�����
//	int* ptr2 = new int[10];
//	//�ͷŶ�̬������ڴ�
//	delete ptr;
//	delete ptr1;
//	delete ptr2;
//}
//
////���⣺Ϊʲôc����������malloc/free��c++Ҳ�����ã���������Ҫnew/delete ?
////��1.�����������new��malloc����һ���ģ�2.����Զ�������new���˿��ٿռ��⣬��������Զ������͵Ĺ��캯����delete���ͷſռ䲢������������������
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
//	ListNode* list= BuyListNode(1);//c���Կ��ٿռ�ֻ���Լ�ȥmallocʵ�ֺ���
//	free(list);//����������ͷſռ�
//	list = NULL;
//	ListNodeCPP* list1 = new  ListNodeCPP(2);//c++��new���˿����˿ռ仹������ ListNodeCPP�Ĺ��캯��
//	delete list1;     //���ﲻ���ͷ��˶�̬���ٵĿռ���һ������� ListNodeCPP�������������������
//
//	ListNodeCPP a[10];// ����10�ι��캯�����������������10����������
//	ListNodeCPP* b = new ListNodeCPP[10];//����b��ָ�벻�Ƕ��󣬳���������ָ�벻�������������
//	delete[]b;//�ͷ�ָ��ָ��Ŀռ�ʱ�������������
//	return 0;
//}
 // 2.1 operator new ��operator delete������new��delete���û����ж�̬�ڴ�������ͷŵĲ�������operator new ��operator delete��ϵͳ�ṩ��
//ȫ�ֺ�����new�ڵײ����operator newȫ�ֺ���������ռ䣬delete�ڵײ�ͨ��operator deleteȫ��
//�������ͷſռ䡣
/*
operator new���ú���ʵ��ͨ��malloc������ռ䣬��malloc����ռ�ɹ�ʱֱ�ӷ��أ�����ռ�ʧ�ܣ�
����ִ�п� �䲻��Ӧ�Դ�ʩ�������Ӧ�Դ�ʩ�û������ˣ���������룬�������쳣��
*/
//void* __CRTDECL operator new(size_t size) _THROW1(_STD bad_alloc) {
//	// try to allocate size bytes
//	void* p;
//	while ((p = malloc(size)) == 0)
//		if (_callnewh(size) == 0)
//		{
//			// report no memory
//			// ��������ڴ�ʧ���ˣ�������׳�bad_alloc �����쳣
//			static const std::bad_alloc nomem;
//			_RAISE(nomem);
//		}
//	return (p);
//}
///*
//operator delete: �ú���������ͨ��free���ͷſռ��
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
//free��ʵ��
//*/
//#define free(p) _free_dbg(p,_NORMAL_BLOOK)
//ͨ����������ȫ�ֺ�����ʵ��֪����operator new ʵ��Ҳ��ͨ��malloc������ռ䣬���malloc����ռ�
//�ɹ���ֱ�ӷ��أ�����ִ���û��ṩ�Ŀռ䲻��Ӧ�Դ�ʩ������û��ṩ�ô�ʩ�ͼ������룬���������
//����operator delete ������ͨ��free���ͷſռ��.
 

//2.2 operator new��operator delete����ר������:���������ʾ�ˣ��������Ľڵ�ListNodeͨ��������ר�� operator new/ operator delete��ʵ�������
//��ʹ���ڴ��������ͷ��ڴ棬���Ч�ʡ�
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
//	//���������඼һ����
//	//�����Զ������ͣ�
//	A* p1 = (A*)malloc(sizeof(A));
//	A* p2 = (A*)operator new(sizeof(A));
//	A* p3 = new A; //ֻ��new����ù��캯����ʼ����
//	//operator new ��malloc��������ʲô��
//	//���ۣ����ߵ�ʹ�÷�ʽһ�����������ķ�ʽ��ͬ��malloc����ռ�ʧ�ܷ��ؿ�ָ�룬��operator new����ռ�ʧ����ͨ�����쳣������
//	size_t size=2;
//	void* p4 = malloc(1024 * 1024 * 1024 * size);
//	cout << p4 << endl;//ʧ�ܷ���0��
//	//free(p4);
//	void* p5 = operator new(1024 * 1024 * 1021 * size);
//	cout << p5 << endl;//ʧ�����쳣���������Ĵ���ʽ��
//	//operator delete (p5);
//	//���쳣�Ĵ���ʽ��
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

//��ômalloc/free  ��  operator new/operator delete ��new/delete������ʲô����
//operator new==malloc + ����ʧ�����쳣��
// new == operator new  +  ���캯����
// new��malloc�Ĳ�ͬ�ĵط��ǣ�1.���ù��캯����ʼ����2.����ռ�ʧ�ܻ����쳣���������������󣩡�
//delete����free��һ���ĵط���1.�����������������������
// operator delete  ��freeû������Ϊ�ͷſռ�ʧ��ֱ����ֹ����
//
//3.��λnew���ʽ(placement-new):��λnew���ʽ�����ѷ����ԭʼ�ڴ�ռ��е��ù��캯����ʼ��һ������
//ʹ�ø�ʽ��
//new (place_address) type����new(place_address) type(initializer - list)
//place_address������һ��ָ�룬initializer - list�����͵ĳ�ʼ���б�

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
	// pt����ָ���ֻ��������Test������ͬ��С��һ�οռ䣬����������һ��������Ϊ���캯��û��ִ��
	Test* pt = (Test*)malloc(sizeof(Test));

	new(pt) Test; // ע�⣺���Test��Ĺ��캯���в���ʱ���˴���Ҫ����
}
int main()
{
	A* p1 = new A;
	delete p1;
	//ģ��ʵ��������Ϊ(���ռ�+��ʾ���ù��캯������������)��ͨ����λnew��ʵ��
	A* p2 = (A*)operator new(sizeof(A));
	new(p2)A(10);

	p2->~A();
	operator delete (p2);
	return 0;
}

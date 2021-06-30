#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

void test_vector1()  //拷贝构造、赋值
{
	vector<int> v1;  //尾插数据
	v1.push_back(1);
	v1.push_back(2);
	v1.push_back(3);
	v1.push_back(4);
	for (size_t i = 0; i < v1.size(); ++i)  //遍历
	{
		cout << v1[i] << " ";
	}
	cout << endl;
	vector<int> v2(v1); //拷贝构造
	for (size_t i = 0; i < v2.size(); ++i)
	{
		cout << v2[i] << " ";
	}
	cout << endl;
	vector<int> v3;
	v3.push_back(10);
	v3.push_back(20);
	v3.push_back(30);
	v3.push_back(40);
	v1 = v3;     //赋值
	for (size_t i = 0; i < v1.size(); ++i)
	{
		cout << v1[i] << " ";
	}
	cout << endl;
}
void test_vector2()  //遍历读写
{
	vector<int> v;
	v.push_back(1);
	v.push_back(2);
	v.push_back(3);
	v.push_back(4);
	for (size_t i = 0; i < v.size(); ++i)  //写
	{
		v[i] += 1;
	}
	cout << endl;
	for (size_t i = 0; i < v.size(); ++i)  //遍历
	{
		cout << v[i] << " ";
	}
	cout << endl;
	//迭代器 vector<int>::iterator
	vector<int>::iterator it = v.begin();
	while (it != v.end())
	{
		*it += 1;
		++it;
	}
	it = v.begin();
	while (it != v.end())
	{
		cout << *it << " ";
		++it;
	}
	cout << endl;
	//范围for(auto e:v)
	for (auto& e : v)
	{
		e += 1;
	}
	for (auto e : v)
	{
		cout << e << " ";
	}
	cout << endl;
}
void print_vector(const vector<int> vt)
{
	vector<int>::const_iterator it = vt.begin();
	while (it != vt.end())
	{
		cout << *it << " ";
		++it;
	}
	cout << endl;
}
void test_vector3()  //三种类型的迭代器
{
	vector<int> v;
	v.push_back(1);
	v.push_back(2);
	v.push_back(3);
	v.push_back(4);
	//普通正向地带器  可读可写
	vector<int>::iterator it = v.begin();
	while (it != v.end())
	{
		*it += 1;
		++it;
	}
	it = v.begin();
	while (it != v.end())
	{
		cout << *it << " ";
		++it;
	}
	cout << endl;
	//const_iterator  可读  不可写
	print_vector(v);
	//逆向迭代器  可读可写（也有vector<int>::const_reverse_iterator it = vt.rbegin() 迭代器，只读）
	vector<int>::reverse_iterator rit = v.rbegin();
	while (rit != v.rend())
	{
		cout << *rit << " ";
		++rit;
	}
	cout << endl;
}
void test_vector4()
{
	vector<int> v;
	v.push_back(1);
	v.push_back(2);
	v.push_back(3);
	v.push_back(4);
	cout << v.capacity() << endl;
	cout << v.size() << endl;

	size_t sz;
	vector<int> foo;
	sz = foo.capacity();
	cout << "making foo grow:" << endl;
	for (int i = 0; i < 100; ++i)
	{
		foo.push_back(i);
		if (sz != foo.capacity())
		{
			sz = foo.capacity();
			cout << "capacity changed:" << sz << endl;
		}
	}

}
void test_vector5()
{
	vector<int> v;
	v.push_back(1);
	v.push_back(2);
	v.push_back(3);
	v.push_back(4);
	//v[4]=5;  //[]访问越界直接终止程序，assert断言实现
	v.at(4) = 5;  //at访问越界会抛异常；
}
void test_vector6()
{
	vector<int> v;
	v.push_back(1);
	v.push_back(2);
	v.push_back(3);
	v.push_back(4);
	v.insert(v.begin(), 0);   //头插    在头(v.begin())的位置插入0；
	v.insert(v.begin(), -1);
	for (auto e : v)
	{
		cout << e << " ";
	}
	cout << endl;
	v.erase(v.begin());   //头删    在头(v.begin())的位置删除数据
	for (auto e : v)
	{
		cout << e << " ";
	}
	cout << endl;
	v.insert(v.end(), -1);  //这样也可以实现尾插
	for (auto e : v)
	{
		cout << e << " ";
	}
	cout << endl;
}
void test_vector7()
{
	vector<int> v;
	v.push_back(10);
	v.push_back(20);
	v.push_back(50);
	v.push_back(7);
	v.push_back(2);
	v.push_back(7);
	v.push_back(1);
	//要求删除其中的7；
	//方法1：知道7的下标3
	v.erase(v.begin() + 3);
	for (auto e : v)
	{
		cout << e << " ";
	}
	cout << endl;
	//方法2：查找：但是vector并没有提供查找接口(find());这里可以使用算法的find();
	// #include<algorithm>  算法头文件
	vector<int>::iterator pos = find(v.begin(), v.end(), 7); //如果被查找的值有多个。find只会返回找到的第一个该值的下标
	if (pos != v.end()) 
	{
		v.erase(pos);
	}
	//其实算法（algorithm）里的find是一个函数模板，注意：find(first,last,val)中的区间必须是左闭右开（迭代器的区间必须使左闭右开，否则无法比较）
	//即[first,last);  list也可以使用该算法find()；算法中还有以快排实现的sort(v.begin(),v.end())排序函数
	for (auto e : v)
	{
		cout << e << " ";
	}
	cout << endl;
	sort(v.begin(), v.end());
	for (auto e : v)
	{
		cout << e << " ";
	}
	cout << endl;
}

//迭代器失效
void test_vector8()
{
	vector<int> v;
	v.push_back(1);
	v.push_back(2);
	v.push_back(3);
	v.push_back(4);
	v.push_back(5);
	//vector<int>::iterator it = v.begin();
	//第一种失效：push_back,insert,resize,reserve等可能会扩容的接口都会导致地带器失效。
	//即：扩容导致扩容，开辟新空间，释放了旧空间，而迭代器（指针）仍然指向旧空间，就会导致迭代器失效
	//v.push_back(6);
	/*v.push_back(7);
	v.push_back(8);*/
	//while (it != v.end())
	//{
	//	cout << *it << " ";
	//	++it;
	//}
	//cout << endl;
	//第二种迭代器失效：删除数据导致迭代器失效
	//要求:删除容器中的所有偶数
	vector<int>::iterator it = v.begin();
	while (it != v.end())
	{
		if (*it % 2 == 0)
		{
			//v.erase(it);  //这里的迭代器失效是因为：删除it之后，it的位置就失效了
			it = v.erase(it);
	    } //vs下报错了是编译器检查出来的；gcc下可能会报错或正常运行或者是会导致结果不对
	           //修正：iterator erase();erase()函数有个返回值,它的返回值是个迭代器指针指向被删除的it位置的下一个位置
		else    //所以可以用it去接受它的下一个位置即可正常运行。
	    ++it;
	}                   
	cout << endl;
	for (auto e : v)
	{
		cout << e << " ";
	}
	cout << endl;
}
int main()
{
	//test_vector1();
	//test_vector2();
	//test_vector3();
	//test_vector4();
	//test_vector5();
	//test_vector6();
	//test_vector7();
	test_vector8();
	return 0;
} 
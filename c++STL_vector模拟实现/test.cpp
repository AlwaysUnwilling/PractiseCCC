#include"vector.h"
#include<string>
using namespace std;
void test_my_vector1()
{
	my_vector::vector<int> v1;
	v1.push_back(1);
	v1.push_back(2);
	v1.push_back(3);
	v1.push_back(4);
	std::cout << v1.size() << std::endl;
	std::cout << v1.capacity() << std::endl;
	my_vector::vector_Print(v1);
	//for (size_t i = 0; i < v1.size(); ++i)
	//{
	//	std::cout << v1[i] << " ";
	//}
	//std::cout << std::endl;
	//my_vector::vector<int>::const_iterator it = v1.begin();
	//while (it != v1.end())
	//{
	//	std::cout << *it << " ";
	//	++it;
	//}
	//std::cout << std::endl;
	//for (auto e : v1)
	//{
	//	std::cout << e << " ";
	//}
	//std::cout << std::endl;
}
void test_my_vector2()
{
	my_vector::vector<int> v1;
	v1.push_back(1);
	v1.push_back(2);
	v1.push_back(3);
	v1.push_back(4);
	my_vector::vector_Print(v1);
	//v1.pop_back();
	//v1.pop_back();
	//v1.pop_back();
	//my_vector::vector_Print(v1);
	v1.insert(v1.begin(), 0);
	v1.insert(v1.begin(), -1);

	std::cout << v1.size() << std::endl;
	std::cout << v1.capacity() << std::endl;
	v1.insert(v1.end(), 5);
	v1.insert(v1.end(), 6);
	std::cout << v1.size() << std::endl;
	std::cout << v1.capacity() << std::endl;
	for (size_t i = 0; i < v1.size(); ++i)
	{
		std::cout << v1[i] << " ";
	}
	std::cout << std::endl;
	v1.erase(v1.begin());
	v1.erase(v1.end()-1);
	std::cout << v1.size() << std::endl;
	std::cout << v1.capacity() << std::endl;
	for (size_t i = 0; i < v1.size(); ++i)
	{
		std::cout << v1[i] << " ";
	}
	std::cout << std::endl;
}
void test_my_vector3()
{
	my_vector::vector<int> v1;
	v1.push_back(1);
	v1.push_back(2);
	v1.push_back(3);
	v1.push_back(4);
	my_vector::vector_Print(v1);
	v1.resize(1, 0);
	my_vector::vector_Print(v1);
	v1.resize(6, 5);
	my_vector::vector_Print(v1);
}
void test_my_vector4()
{
	my_vector::vector<int> v1;
	v1.push_back(1);
	v1.push_back(2);
	v1.push_back(3);
	v1.push_back(4);
	my_vector::vector<int> v2(v1);
	my_vector::vector_Print(v2);
	my_vector::vector<int> v3;
	v3.push_back(10);
	v3.push_back(20);
	v3.push_back(30);
	v3.push_back(40);
	v3.push_back(50);
	v3.push_back(60);
	v3.push_back(70);
	v3 = v1;
	my_vector::vector_Print(v3);
}
void test_my_vector5()
{
	my_vector::vector<string> v1;
	v1.push_back("11111111111111111111111111111111111111111111111111111111");
	v1.push_back("22222222222222222222222222222222222222222222222222222222");
	v1.push_back("33333333333333333333333333333333333333333333333333333333");
	v1.push_back("44444444444444444444444444444444444444444444444444444444");
	v1.push_back("44444444444444444444444444444444444444444444444444444444");
	v1.push_back("44444444444444444444444444444444444444444444444444444444");
	for (auto e : v1)
	{
		cout << e << " ";
	}
	cout << endl;
}
int main()
{
	//test_my_vector1();
	//test_my_vector2();
	//test_my_vector3();
	//test_my_vector4();
	test_my_vector5();
	
	return 0;
}
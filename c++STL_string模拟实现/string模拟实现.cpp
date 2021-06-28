#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
#include<string>
#include"string.h"
void test_myString1()
{
	myString::string s1("hello");
	myString::string s2(s1);
	for (size_t i=0;i<s1.size();++i)
	{
		std::cout << s1[i] << " ";
	}
	std::cout << std::endl;
	//for (size_t i = 0; i < s1.size(); ++i)
	//{
	//	s1[i] += 1;
	//	std::cout << s1[i] << " ";
	//}
	//std::cout << std::endl;
	//for (size_t i = 0; i < s2.size(); ++i)
	//{
	//	std::cout << s2[i] << " ";
	//}
	//std::cout << std::endl;
	//std::cout << s1.c_str() << std::endl;
	//std::cout << s2.c_str() << std::endl;

}
void test_myString2()
{
	//myString::string s1("hello");
	//myString::string s3("worldadadad");
	//s1 = s3;
	//std::cout << s1.c_str() << std::endl;
	//std::cout << s1;
	myString::string s4;
	std::cin >> s4;
	std::cout << s4;
}
void test_myString3()
{
	myString::string s1("hello");
	//myString::string::iterator it = s1.begin();
	//while (it != s1.end())
	//{
	//	*it += 1;
 //  		std::cout << *it << " ";
	//	++it;
	//}
	//std::cout << std::endl;
	////范围for是由迭代器支持的，也就是说这段代码最终会被编译器替换成迭代器
	////要支持范围for 必须支持iterator ,begin(),end()
	//for (auto e : s1)     
	//{
	//	std::cout << e << " ";
	//}
	//std::cout << std::endl;
	//s1.push_back('x');
	//std::cout << s1.capacity() <<" "<< s1.size();

	s1.append("ab   cd  e fg");
	std::cout << s1 << " " << s1.capacity() << " " << s1.size();
	s1 += 'P';
	std::cout << s1 << " " << s1.capacity() << " " << s1.size();
	s1 += "ABC";
	std::cout << s1 << " " << s1.capacity() << " " << s1.size();
}
void test_myString4()
{
	myString::string s1("hello");
	//s1.insert(3, 'A');
	//s1.insert(0, 'B');
	//std::cout << s1.c_str() << std::endl;
	s1.insert(5, "world");
	std::cout << s1 << std::endl;
	/*std::cout << s1 << std::endl;*/
	//std::cout << s1.capacity() << std::endl;
	//s1.resize(4, 'x');
	//std::cout << s1 << std::endl << std::endl;
	//s1.resize(18, 'a');
	//std::cout << s1 << std::endl << std::endl;
	//s1.resize(2);
	//std::cout << s1 << std::endl << std::endl;
	//s1.resize(0);
	//std::cout << s1 << std::endl << std::endl;
	//s1.erase(1, 3);
	//std::cout << s1 << std::endl;
}
void test_myString5()
{
	myString::string s1("abcdabcdef");
	std::cout << s1.find("cde") << std::endl;
	std::cout << s1.find("cdex") << std::endl;
}
void test_myString6()
{
	myString::string s1("abcdabcdef");
	myString::string s2("abcdabcdef");
	std::cout << (s1 > s2) << std::endl;
	std::cout << (s1 >= s2) << std::endl;
	std::cout << (s1 == s2) << std::endl;
	std::cout << (s1 <= s2) << std::endl;
	std::cout << (s1 < s2) << std::endl;
	std::cout << (s1 != s2) << std::endl;
}
int main()
{
	//test_myString1();
	//test_myString2(); 
	//test_myString3(); 
	test_myString4(); 
	//test_myString5(); 
	//test_myString6(); 
	return 0;
}

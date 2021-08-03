#include<iostream>
#include<string>
#include<unordered_map>
#include<unordered_set>
#include<map>
#include<set>

using namespace std;

void Test_undered_map_unordered_set()
{
	unordered_set<int> us;
	//去重，不排序 
	us.insert(6);
	us.insert(2);
	us.insert(4);
	us.insert(3);
	us.insert(5);
	us.insert(5);
	us.insert(5);
	us.insert(5);
	//不支持修改
	unordered_set<int>::iterator it = us.begin();
	while (it != us.end())
	{
		cout << *it << " ";
		++it;
	}
	cout << endl;


	unordered_map<string, string> um;
	//不排序
	um.insert(make_pair("string", "字符串"));
	um["sort"] = "排序";
	um["hello"] = "你好";
	unordered_map<string, string>::iterator umit = um.begin();
	while (umit != um.end())
	{
		cout << umit->first << ":" << umit->second << endl;
		++umit;
	}
}
int main()
{
	Test_undered_map_unordered_set();
	return 0;
}

//map / set 和 unordered_map / unordered_set 的区别和联系：
//1.他们都可以实现key和key / value的搜索场景，并且功能和使用基本一样。
//2.map / set的底层是使用红黑树实现的，遍历出来是有序的，曾删查改的时间复杂度是O(logN)。
//3.unordered_map / unordered_set 的底层是使用哈希表实现的，遍历出来是无序的，曾删查改的时间复杂度是O(1)。
//4.map / set是双向迭代器，unordered_map / unordered_set 是单向迭代器。
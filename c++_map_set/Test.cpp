#include<iostream>
#include<set>
#include<map>
#include<string>
using namespace std;

void test_set1()
{
	set<int> s;
	s.insert(3);
	s.insert(1);
	s.insert(4);
	s.insert(3);
	s.insert(7);
	//set的底层是搜索二叉树，它的遍历是 排序(搜索二叉树中序遍历是有序的)和去重。
	set<int>::iterator it = s.begin(); //迭代器访问
	while (it != s.end())
	{
		cout << *it << " ";   //不能修改  *it是常量
		++it;
	}
	cout << endl;
	//范围for
	for (auto e : s)
	{
		cout << e << " ";
	}
	cout << endl;
     //删除
	//1.传迭代器位置删除:必须判断迭代器位置是否合法
	//set<int>::iterator pos = s.find(30);  //迭代器find();
	set<int>::iterator pos = find(s.begin(),s.end(),3); //算法中的find();
	//俩种find()的区别是：1.迭代器find的效率要更优，因为迭代器的find是按搜索二叉树的性质来查找的，
	//                      比要查找的数据大就往右走，小就往左走。时间复杂度是O(logN)
	//                    2.算法find是一种从头到尾的挨个遍历。时间复杂度是O(N).
	if (pos != s.end())
	{
		s.erase(pos);
	}
	else
	{
		cout << "要删除的数据不存在！" << endl;
	}
	for (auto e : s)
	{
		cout << e << " ";
	}
	cout << endl;
	//2.传值删除:如果要删除的值不合法，不会删除。
	s.erase(4);
	for (auto e : s)
	{
		cout << e << " ";
	}
	cout << endl;
	//总结：set是对应搜索二叉树的key的模型，用来查找数据的。特点：1.快（曾删查O(logN)），但是不允许修改。
}
void test_map1()
{
	//map底层也是搜索二叉树，对应的是K/V模型   
	//map的遍历也是中序遍历，有序输出.
	map<int, int> m;
	m.insert(pair<int, int>(1, 1));
	m.insert(pair<int, int>(3, 3));
	m.insert(pair<int, int>(2, 2));  //调用的是pair的构造函数，构造一个匿名对象
	m.insert(make_pair(4, 4)); //函数模板构造一个pair对象
	//make_pair:

	//template<class T1,class T2>
	//pair<T1, T2> make_pair(T1 x, T2 y)
	//{
	//	return (pair<T1, T2>(x, y));
	//}

	//map(pair<K,V>(key,val));
	//teplate<class T1,class T2>
	//	struct pair
	//{
	// 	   typedef T1 first_type;
	// 	   typedef T2 second_type;
	//	T1 _key;
	//	T2 _val;
	// 	pair()
	// 	   :_key(T1())
	// 	   ,_val(T2())
	// 	   {}
	//	pair(const T1& key,const T2& val)
	//		:_key(key)
	//		,_val(val)
	//	{}
	//};

	map<int, int>::iterator it = m.begin();  //这里的迭代器it其实是pair类型的指针.
	while (it != m.end())
	{
		//cout << (*it).first << ":" << (*it).second << endl;
		cout << it->first << ":" << it->second << endl;  //更常用
		++it;
	}
	cout << endl;
    //范围for
	for (auto& e : m)
	{
		cout << e.first << ":" << e.second << endl;
	}
	cout << endl;
}
void test_map2()
{
	std::map<std::string, std::string> dict;
	dict.insert(pair<std::string, std::string>("sort", "排序"));
	dict.insert(pair<std::string, std::string>("hello", "你好"));
	dict.insert(pair<std::string, std::string>("world", "世界"));
	dict.insert(pair<std::string, std::string>("string", "字符串"));

	//std::map<std::string, std::string>::iterator it = dict.begin();
	auto it = dict.begin();
	while (it != dict.end())
	{
		cout << it->first << ":" << it->second << endl;
		++it;
	}
}
//统计次数
void test_map3()
{
	string strs[] = { "西瓜" ,"香瓜" ,"苹果" ,"西瓜" ,"苹果" ,"香蕉" ,"香蕉" ,"香蕉" ,"西瓜" ,"樱桃" ,"西瓜" ,"西瓜" };
	map<string, int> countMap;
	//方法一：
	//for (auto& e : strs)
	//{
	//	map<string, int>::iterator ret = countMap.find(e);
	//	if (ret != countMap.end())
	//	{ 
	//		ret->second++;
	//	}
	//	else
	//	{
	//		countMap.insert(make_pair(e, 1));
	//	}
	//}
	//for (auto& e : countMap)
	//{
	//	cout << e.first << ":" << e.second << endl;
	//}
	//方法二：operator[] :
	// 
	// 	   //mapped_type& operator[] (const key_type& k)
	// 	   //{
	// 	   //    return (*((this->insert(make_pair(k,mapped_type()))).first)).second;
	// 	   //}
	// 	   //为什么这里不用find实现呢？ 原因：假设用find，如果map中没有这个key，如何返回？
	// 	   //而这里使用insert：1.如果k不在map中，则插入pair<k,mapped_type()>,再返回映射对象的引用（mapped_type()是缺省参数，int()是0）；
	// 	   //2.如果k在map中，则插入失败，返回k所在结点中映射对象的引用。
	// 	   ***map的operator[]有三层作用：a.没有k，则插入k；b.查找k对应的映射对象；c.修改k对应映射对象（返回值是引用）。
	// 	   ***一般使用operator[]去做：1.插入+修改，2.修改；一般不会用他去做查找，因为如果k不在，会直接插入数据。
	// 
	//for (auto& e : strs)
	//{
	// 	   //1.如果水果不在map中，则operator[]会插入pair<e,0>,返回映射对象（次数）的引用进行了修改(++);注意这里的0是int()的缺省值；
	// 	   //2.如果水果在map中，则operator[]返回水果对应的映射对象（次数）的引用，对他进行修改(++);
	//	countMap[e]++;
	//}
	//for (auto& e : countMap)
	//{
	//	cout << e.first << ":" << e.second << endl;
	//}
	std::map<std::string, std::string> dict;
	dict.insert(make_pair("sort", "排序"));
	dict["string"];  //插入（一半不会这样用）
	dict["string"]="字符串";  //修改
	dict["left"]="左边";   //插入+修改   基本等同于insert
	//方法三：
	//single element(1)
	//	pair<iterator, bool> insert(const value_type & val);   //返回值是pair<迭代器，bool>
	//with hint(2)
	//	iterator insert(iterator position, const value_type & val);
	//range(3)
	//	template <class InputIterator>
	//void insert(InputIterator first, InputIterator last);
	for (auto& e : strs)
	{
		//1.如果水果没在map中，则插入成功
		//2.如果水果在map中，则插入失败。通过返回值拿到水果所在的结点的迭代器，++它的次数。
		pair<map<string,int>::iterator,bool> ret = countMap.insert(make_pair(e, 1));
		if (ret.second == false)
		{
			ret.first->second++;
		}
	}
	for (auto& e : countMap)
    {
	    cout << e.first << ":" << e.second << endl;
    }
}
int main()
{
	//test_set1();
	//test_map1();
	//test_map2();
	test_map3();
	return 0;
}

//总结map：1、曾     insert    +     operator[]
//         2、删     erase
//         3、查     find
//         4、改     operator[]
//         5、遍历   iterator   +    范围for   遍历出来的数据都是按K排序的，因为底层都是搜索树，按中序遍历的。
//需要注意的是map中存的是pair<k,v>键值对

//multiset：1. multiset是按照特定顺序存储元素的容器，其中元素是可以重复的。
 //   2. 在multiset中，元素的value也会识别它(因为multiset中本身存储的就是<value, value>组成的键值对，
	//因此value本身就是key，key就是value，类型为T).multiset元素的值不能在容器中进行修改(因为元素
	//	总是const的)，但可以从容器中插入或删除。
	//3. 在内部，multiset中的元素总是按照其内部比较规则(类型比较)所指示的特定严格弱排序准则进行排
	//序
	//4. multiset容器通过key访问单个元素的速度通常比unordered_multiset容器慢，但当使用迭代器遍历时
	//会得到一个有序序列。
	//5. multiset底层结构为二叉搜索树(红黑树)。
	//注意：
	//1. multiset中再底层中存储的是<value, value>的键值对
	//2. mtltiset的插入接口中只需要插入即可
	//3. 与set的区别是，multiset中的元素可以重复，set是中value是唯一的
	//4. 使用迭代器对multiset中的元素进行遍历，可以得到有序的序列
	//5. multiset中的元素不能修改
	//6. 在multiset中找某个元素，时间复杂度为O(logN)
	//7. multiset的作用：可以对元素进行排序

void TestSet()
{
	int array[] = { 2, 1, 3, 9, 6, 0, 5, 8, 4, 7 };

	// 注意：multiset在底层实际存储的是<int, int>的键值对
	multiset<int> s(array, array + sizeof(array) / sizeof(array[0]));
	for (auto& e : s)
		cout << e << " ";
	cout << endl;
	return ;
}

//multimap:1. Multimaps是关联式容器，它按照特定的顺序，存储由key和value映射成的键值对<key, value>，其中
//多个键值对之间的key是可以重复的。
//2. 在multimap中，通常按照key排序和惟一地标识元素，而映射的value存储与key关联的内容。key和
//value的类型可能不同，通过multimap内部的成员类型value_type组合在一起，value_type是组合key
//和value的键值对 :
//typedef pair<const Key, T> value_type;
//3. 在内部，multimap中的元素总是通过其内部比较对象，按照指定的特定严格弱排序标准对key进行排序
//的。
//4. multimap通过key访问单个元素的速度通常比unordered_multimap容器慢，但是使用迭代器直接遍历
//multimap中的元素可以得到关于key有序的序列。
//5. multimap在底层用二叉搜索树(红黑树)来实现。
//注意：multimap和map的唯一不同就是：map中的key是唯一的，而multimap中key是可以重复的。
//注意：
//1. multimap中的key是可以重复的。
//2. multimap中的元素默认将key按照小于来比较
//3. multimap中没有重载operator[]操作,因为当有多个相同的key时，不知道返回那个key对应的val。
//4. 使用时与map包含的头文件相同.
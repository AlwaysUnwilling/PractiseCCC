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
	//set�ĵײ������������������ı����� ����(������������������������)��ȥ�ء�
	set<int>::iterator it = s.begin(); //����������
	while (it != s.end())
	{
		cout << *it << " ";   //�����޸�  *it�ǳ���
		++it;
	}
	cout << endl;
	//��Χfor
	for (auto e : s)
	{
		cout << e << " ";
	}
	cout << endl;
     //ɾ��
	//1.��������λ��ɾ��:�����жϵ�����λ���Ƿ�Ϸ�
	//set<int>::iterator pos = s.find(30);  //������find();
	set<int>::iterator pos = find(s.begin(),s.end(),3); //�㷨�е�find();
	//����find()�������ǣ�1.������find��Ч��Ҫ���ţ���Ϊ��������find�ǰ����������������������ҵģ�
	//                      ��Ҫ���ҵ����ݴ�������ߣ�С�������ߡ�ʱ�临�Ӷ���O(logN)
	//                    2.�㷨find��һ�ִ�ͷ��β�İ���������ʱ�临�Ӷ���O(N).
	if (pos != s.end())
	{
		s.erase(pos);
	}
	else
	{
		cout << "Ҫɾ�������ݲ����ڣ�" << endl;
	}
	for (auto e : s)
	{
		cout << e << " ";
	}
	cout << endl;
	//2.��ֵɾ��:���Ҫɾ����ֵ���Ϸ�������ɾ����
	s.erase(4);
	for (auto e : s)
	{
		cout << e << " ";
	}
	cout << endl;
	//�ܽ᣺set�Ƕ�Ӧ������������key��ģ�ͣ������������ݵġ��ص㣺1.�죨��ɾ��O(logN)�������ǲ������޸ġ�
}
void test_map1()
{
	//map�ײ�Ҳ����������������Ӧ����K/Vģ��   
	//map�ı���Ҳ������������������.
	map<int, int> m;
	m.insert(pair<int, int>(1, 1));
	m.insert(pair<int, int>(3, 3));
	m.insert(pair<int, int>(2, 2));  //���õ���pair�Ĺ��캯��������һ����������
	m.insert(make_pair(4, 4)); //����ģ�幹��һ��pair����
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

	map<int, int>::iterator it = m.begin();  //����ĵ�����it��ʵ��pair���͵�ָ��.
	while (it != m.end())
	{
		//cout << (*it).first << ":" << (*it).second << endl;
		cout << it->first << ":" << it->second << endl;  //������
		++it;
	}
	cout << endl;
    //��Χfor
	for (auto& e : m)
	{
		cout << e.first << ":" << e.second << endl;
	}
	cout << endl;
}
void test_map2()
{
	std::map<std::string, std::string> dict;
	dict.insert(pair<std::string, std::string>("sort", "����"));
	dict.insert(pair<std::string, std::string>("hello", "���"));
	dict.insert(pair<std::string, std::string>("world", "����"));
	dict.insert(pair<std::string, std::string>("string", "�ַ���"));

	//std::map<std::string, std::string>::iterator it = dict.begin();
	auto it = dict.begin();
	while (it != dict.end())
	{
		cout << it->first << ":" << it->second << endl;
		++it;
	}
}
//ͳ�ƴ���
void test_map3()
{
	string strs[] = { "����" ,"���" ,"ƻ��" ,"����" ,"ƻ��" ,"�㽶" ,"�㽶" ,"�㽶" ,"����" ,"ӣ��" ,"����" ,"����" };
	map<string, int> countMap;
	//����һ��
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
	//��������operator[] :
	// 
	// 	   //mapped_type& operator[] (const key_type& k)
	// 	   //{
	// 	   //    return (*((this->insert(make_pair(k,mapped_type()))).first)).second;
	// 	   //}
	// 	   //Ϊʲô���ﲻ��findʵ���أ� ԭ�򣺼�����find�����map��û�����key����η��أ�
	// 	   //������ʹ��insert��1.���k����map�У������pair<k,mapped_type()>,�ٷ���ӳ���������ã�mapped_type()��ȱʡ������int()��0����
	// 	   //2.���k��map�У������ʧ�ܣ�����k���ڽ����ӳ���������á�
	// 	   ***map��operator[]���������ã�a.û��k�������k��b.����k��Ӧ��ӳ�����c.�޸�k��Ӧӳ����󣨷���ֵ�����ã���
	// 	   ***һ��ʹ��operator[]ȥ����1.����+�޸ģ�2.�޸ģ�һ�㲻������ȥ�����ң���Ϊ���k���ڣ���ֱ�Ӳ������ݡ�
	// 
	//for (auto& e : strs)
	//{
	// 	   //1.���ˮ������map�У���operator[]�����pair<e,0>,����ӳ����󣨴����������ý������޸�(++);ע�������0��int()��ȱʡֵ��
	// 	   //2.���ˮ����map�У���operator[]����ˮ����Ӧ��ӳ����󣨴����������ã����������޸�(++);
	//	countMap[e]++;
	//}
	//for (auto& e : countMap)
	//{
	//	cout << e.first << ":" << e.second << endl;
	//}
	std::map<std::string, std::string> dict;
	dict.insert(make_pair("sort", "����"));
	dict["string"];  //���루һ�벻�������ã�
	dict["string"]="�ַ���";  //�޸�
	dict["left"]="���";   //����+�޸�   ������ͬ��insert
	//��������
	//single element(1)
	//	pair<iterator, bool> insert(const value_type & val);   //����ֵ��pair<��������bool>
	//with hint(2)
	//	iterator insert(iterator position, const value_type & val);
	//range(3)
	//	template <class InputIterator>
	//void insert(InputIterator first, InputIterator last);
	for (auto& e : strs)
	{
		//1.���ˮ��û��map�У������ɹ�
		//2.���ˮ����map�У������ʧ�ܡ�ͨ������ֵ�õ�ˮ�����ڵĽ��ĵ�������++���Ĵ�����
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

//�ܽ�map��1����     insert    +     operator[]
//         2��ɾ     erase
//         3����     find
//         4����     operator[]
//         5������   iterator   +    ��Χfor   �������������ݶ��ǰ�K����ģ���Ϊ�ײ㶼��������������������ġ�
//��Ҫע�����map�д����pair<k,v>��ֵ��

//multiset��1. multiset�ǰ����ض�˳��洢Ԫ�ص�����������Ԫ���ǿ����ظ��ġ�
 //   2. ��multiset�У�Ԫ�ص�valueҲ��ʶ����(��Ϊmultiset�б���洢�ľ���<value, value>��ɵļ�ֵ�ԣ�
	//���value�������key��key����value������ΪT).multisetԪ�ص�ֵ�����������н����޸�(��ΪԪ��
	//	����const��)�������Դ������в����ɾ����
	//3. ���ڲ���multiset�е�Ԫ�����ǰ������ڲ��ȽϹ���(���ͱȽ�)��ָʾ���ض��ϸ�������׼�������
	//��
	//4. multiset����ͨ��key���ʵ���Ԫ�ص��ٶ�ͨ����unordered_multiset������������ʹ�õ���������ʱ
	//��õ�һ���������С�
	//5. multiset�ײ�ṹΪ����������(�����)��
	//ע�⣺
	//1. multiset���ٵײ��д洢����<value, value>�ļ�ֵ��
	//2. mtltiset�Ĳ���ӿ���ֻ��Ҫ���뼴��
	//3. ��set�������ǣ�multiset�е�Ԫ�ؿ����ظ���set����value��Ψһ��
	//4. ʹ�õ�������multiset�е�Ԫ�ؽ��б��������Եõ����������
	//5. multiset�е�Ԫ�ز����޸�
	//6. ��multiset����ĳ��Ԫ�أ�ʱ�临�Ӷ�ΪO(logN)
	//7. multiset�����ã����Զ�Ԫ�ؽ�������

void TestSet()
{
	int array[] = { 2, 1, 3, 9, 6, 0, 5, 8, 4, 7 };

	// ע�⣺multiset�ڵײ�ʵ�ʴ洢����<int, int>�ļ�ֵ��
	multiset<int> s(array, array + sizeof(array) / sizeof(array[0]));
	for (auto& e : s)
		cout << e << " ";
	cout << endl;
	return ;
}

//multimap:1. Multimaps�ǹ���ʽ�������������ض���˳�򣬴洢��key��valueӳ��ɵļ�ֵ��<key, value>������
//�����ֵ��֮���key�ǿ����ظ��ġ�
//2. ��multimap�У�ͨ������key�����Ωһ�ر�ʶԪ�أ���ӳ���value�洢��key���������ݡ�key��
//value�����Ϳ��ܲ�ͬ��ͨ��multimap�ڲ��ĳ�Ա����value_type�����һ��value_type�����key
//��value�ļ�ֵ�� :
//typedef pair<const Key, T> value_type;
//3. ���ڲ���multimap�е�Ԫ������ͨ�����ڲ��Ƚ϶��󣬰���ָ�����ض��ϸ��������׼��key��������
//�ġ�
//4. multimapͨ��key���ʵ���Ԫ�ص��ٶ�ͨ����unordered_multimap������������ʹ�õ�����ֱ�ӱ���
//multimap�е�Ԫ�ؿ��Եõ�����key��������С�
//5. multimap�ڵײ��ö���������(�����)��ʵ�֡�
//ע�⣺multimap��map��Ψһ��ͬ���ǣ�map�е�key��Ψһ�ģ���multimap��key�ǿ����ظ��ġ�
//ע�⣺
//1. multimap�е�key�ǿ����ظ��ġ�
//2. multimap�е�Ԫ��Ĭ�Ͻ�key����С�����Ƚ�
//3. multimap��û������operator[]����,��Ϊ���ж����ͬ��keyʱ����֪�������Ǹ�key��Ӧ��val��
//4. ʹ��ʱ��map������ͷ�ļ���ͬ.
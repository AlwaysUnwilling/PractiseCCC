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
	//ȥ�أ������� 
	us.insert(6);
	us.insert(2);
	us.insert(4);
	us.insert(3);
	us.insert(5);
	us.insert(5);
	us.insert(5);
	us.insert(5);
	//��֧���޸�
	unordered_set<int>::iterator it = us.begin();
	while (it != us.end())
	{
		cout << *it << " ";
		++it;
	}
	cout << endl;


	unordered_map<string, string> um;
	//������
	um.insert(make_pair("string", "�ַ���"));
	um["sort"] = "����";
	um["hello"] = "���";
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

//map / set �� unordered_map / unordered_set ���������ϵ��
//1.���Ƕ�����ʵ��key��key / value���������������ҹ��ܺ�ʹ�û���һ����
//2.map / set�ĵײ���ʹ�ú����ʵ�ֵģ���������������ģ���ɾ��ĵ�ʱ�临�Ӷ���O(logN)��
//3.unordered_map / unordered_set �ĵײ���ʹ�ù�ϣ��ʵ�ֵģ���������������ģ���ɾ��ĵ�ʱ�临�Ӷ���O(1)��
//4.map / set��˫���������unordered_map / unordered_set �ǵ����������
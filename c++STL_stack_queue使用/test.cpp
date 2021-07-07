#include<iostream>
#include<stack>
#include<queue>
using namespace std;
void test_stack_queue()
{
	stack<int> st;
	st.push(1);
	st.push(2);
	st.push(3);
	st.push(4);
	// 没有迭代器
	while (!st.empty())
	{
		cout << st.top() << " ";
		st.pop();
	}
	cout << endl;
	queue<int> q;
	q.push(5);
	q.push(6);
	q.push(7);
	q.push(8);
	//没有迭代器
	while (!q.empty())
	{
		cout << q.front() << " ";
		q.pop();
	}
	cout << endl;
}
int main()
{
	test_stack_queue();
	return 0;
}

#include"BTree.h"

void TestBTree()
{
	BTree<int,int,3> bt;
	int arr[] = { 53,139,75,49,145,36,101 };
	for (auto e : arr)
	{
		bt.insert({ e,e });
	}
	bt.inorder();
}
int main()
{
	TestBTree();
	return 0;
}
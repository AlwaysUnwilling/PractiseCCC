#include"UnionFindSet.h"
#include"Graph.h"
#include<string>

int main()
{
// 	const char* stu[] = {"����","����","����","����","����"};
// 	std::cout << sizeof(stu) / sizeof(stu[0]) << std::endl;
// 	UnionFindSet<const char*> ufs(stu,sizeof(stu)/sizeof(stu[0]));
	//matrix::TestGraph1();
	/*link_table::TestGraph1();*/
	//matrix::TestGraphBDFS();
	matrix::TestGraphDijkstra();
	return 0;
}
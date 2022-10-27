#include"UnionFindSet.h"
#include"Graph.h"
#include<string>

int main()
{
// 	const char* stu[] = {"张三","李四","王五","赵六","田七"};
// 	std::cout << sizeof(stu) / sizeof(stu[0]) << std::endl;
// 	UnionFindSet<const char*> ufs(stu,sizeof(stu)/sizeof(stu[0]));
	//matrix::TestGraph1();
	/*link_table::TestGraph1();*/
	//matrix::TestGraphBDFS();
	matrix::TestGraphDijkstra();
	return 0;
}
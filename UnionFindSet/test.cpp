#include"UnionFindSet.h"


//等式方程的可满足性:
//给定一个由表示变量之间关系的字符串方程组成的数组，每个字符串方程 equations[i] 的长度为 4，并采用两种不同的形式之一："a==b" 或 "a!=b"。在这里，a 和 b 是小写字母（不一定不同），表示单字母变量名。
//
//只有当可以将整数分配给变量名，以便满足所有给定的方程时才返回 true，否则返回 false。 
//
//来源：力扣（LeetCode）
//链接：https ://leetcode-cn.com/problems/satisfiability-of-equality-equations
//著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。

class Solution {
public:
    bool equationsPossible(std::vector<std::string>& equations) {
        UnionFindSet ufs(26);
        for (const auto& str : equations) {
            if (str[1] == '=') {
                ufs.Union(str[0] - 'a', str[3] - 'a');
            }
        }
        for (const auto& str : equations) {
            if (str[1] == '!' &&  ufs.FindRoot(str[0]-'a')==ufs.FindRoot(str[3]-'a')) {
                return false;
            }
        }
        return true;
    }
};

//剑指Offer II 116.朋友圈
//一个班上有n个同学，其中一些彼此是朋友，另一些不是。朋友关系是可以传递的，如果a与b直接是朋友，
//且b与c是直接朋友，那么a与c就是间接朋友。
//定义朋友圈就是一组直接或者间接朋友的同学集合。
//给定一个n* n的矩阵，isConnected表示班上的朋友关系，其中isConnected[i][j] = 1表示第i个同学
//与第j个同学是直接朋友，而isConnected[i][j]=0表示二人不是直接朋友。
//返回矩阵中的朋友圈数量。

class Solution1
{
public:
    int findCircleNum(std::vector<std::vector<int>>& isConnected) {
        UnionFindSet ufs(isConnected.size());
        for (int i = 0; i < isConnected.size(); ++i) {
            for (int j = 0; j < isConnected.size(); ++j) {
                if (isConnected[i][j] == 1) {
                    ufs.Union(i, j);
                }
            }
        }
        return ufs.SetSize();
    }
};
int main()
{
    //std::vector<std::string> vs{ {"a==b"},{"b!=a"} };
    std::vector<std::string> vs{ {"a==b"},{"b==a"},{"a==c"} };
    std::cout<<Solution().equationsPossible(vs)<<std::endl;
    std::vector<std::vector<int>> isConnected{ {1,1,0},{1,1,0},{0,0,1} };
    std::cout << Solution1().findCircleNum(isConnected) << std::endl;
    return 0;
}
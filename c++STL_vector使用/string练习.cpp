//题目： 找出字符串中第一个只出现一次的字符：
//找出字符串中第一个只出现一次的字符
//输入描述：
//输入几个非空字符串
//输出描述：
//输出第一个只出现一次的字符，如果不存在输出 - 1。
#include<iostream>
#include<string>
#include<stdio.h>
using namespace std;

int main()
{
    string s;
    int str[256] = { 0 };
    int i = 0;
    while (getline(cin, s))
    {
        for (i = 0; i < s.size(); ++i)
        {
            str[s[i]]++;
        }
        for (i = 0; i < s.size(); i++)
        {
            if (str[s[i]] == 1)
            {
                cout << s[i] << endl;
                break;
            }
        }
        if (i == s.size())
            printf("-1\n");
        fflush(stdin);
    }
    return 0;
}
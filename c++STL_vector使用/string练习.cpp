//��Ŀ�� �ҳ��ַ����е�һ��ֻ����һ�ε��ַ���
//�ҳ��ַ����е�һ��ֻ����һ�ε��ַ�
//����������
//���뼸���ǿ��ַ���
//���������
//�����һ��ֻ����һ�ε��ַ��������������� - 1��
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
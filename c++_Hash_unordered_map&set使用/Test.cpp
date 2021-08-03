#include<iostream>
#include<vector>
#include<string>

using namespace std;
class Solution {
public:
    void _letterCombinations(vector<string>& vsstr, vector<string>& result, string& tmp, string& digits, int di)
    {
        if (di >= digits.size())
        {
            result.push_back(tmp);
            return;
        }
        for (int i = 0; i < vsstr[digits[di] - '0'].size(); ++i)
        {
            tmp.push_back(vsstr[digits[di] - '0'][i]);
            _letterCombinations(vsstr, result, tmp, digits, di+1);
            tmp.pop_back();
        }
    }
    vector<string> letterCombinations(string digits) {
        vector<string> vsstr = { "","","abc","def","ghi","jkl","mno","pqrs","tuv","wxyz" };
        vector<string> result;
        string tmp;
        if (digits.size() == 0)
            return result;
        int di = 0;
        _letterCombinations(vsstr, result, tmp, digits, di);
        return result;
    }
};

int main()
{
    string digits("23");
    Solution s;
    vector<string> tmp=s.letterCombinations(digits);
    for (auto e : tmp)
    {
        cout << e << " ";
    }
    return 0;
}
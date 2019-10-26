#include <algorithm>
#include <array>
#include <bitset>
#include <chrono>
#include <iostream>
#include <limits>
#include <list>
#include <map>
#include <stack>
#include <stdarg.h>
#include <stdio.h>
#include <string>
#include <thread>
#include <vector>
using namespace std;

// https://leetcode-cn.com/problems/longest-palindromic-substring/

string Manacher(const string& s)
{
    string input;
    for (auto c : s) {
        input += '#';
        input += c;
    }
    input[0] = '~';
    input += '&';

    vector<int> dp;
    dp.resize(input.size(), 0);

    int mx = 0;
    int mid = 0;
    for (int i = 1; i < input.size() - 1; i++) {
        if (i<mx) {
            dp[i] = min(mx-i, dp[2*mid -i]);
        }
        int j=0;
        for(;input[i+dp[i]+j] == input[i-dp[i]-j];j++) {

        }
        dp[i] = j-1;
        if ((i+dp[i] ) > mx) {
            mx = i+dp[i];
            mid = i;
        }
    }

    int maxIndex = 0;
    int maxLen=0;
    for(int i=0;i<dp.size();i++) {
        if(maxLen < dp[i]) {
            maxLen = dp[i];
            maxIndex =i;
        }
    }

    string sub;
    for(int i=maxIndex;i<maxLen;i++) {
        if(input[i] != '#') {
            sub += input[i];
        }
    }
    return sub;
}

class Solution {
public:
    string longestPalindrome(string s)
    {
        return Manacher(s);
    }
};

int main()
{

    Solution sln;
    (void)sln;

    std::cout << "main exit\n";
    return 0;
}

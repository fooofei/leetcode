#include <algorithm>
#include <array>
#include <bitset>
#include <chrono>
#include <iostream>
#include <limits>
#include <list>
#include <map>
#include <stack>
#include <string>
#include <thread>
#include <vector>

using namespace std;

// 214 https://leetcode-cn.com/problems/shortest-palindrome/submissions/

class Solution {
public:
    string shortestPalindrome(string s)
    {
        if (s.size() < 2) {
            return s;
        }
        int len = s.size();
        int ans = 0;
        uint64_t seed = 233LL;
        uint64_t base = 1LL;
        uint64_t pre = 0;
        uint64_t suf = 0;
        // pre suf 是相对的 不绝对
        //
        // prefix 乘法过程
        // 1*'a' + 233*'b' + 233*233*'a'
        // 1 233 233*233

        // suffix 乘法过程
        // ((0*233 + 'a')*233 + 'b')*233 + 'c'
        // 233*233 233 1
        for (int i = 0; i < len; ++i) {
            pre += base * s[i];
            base = base * seed;
            //
            suf = suf * seed + s[i];
            if (pre == suf) {
                ans = i;
            }
        }
        string t = s.substr(ans + 1);
        reverse(t.begin(), t.end());
        return t + s;
    }
};

void test2()
{

    Solution sln;
    auto r = sln.shortestPalindrome("aacecaaa");
    if (r != "aaacecaaa") {
        printf("%s() fail\n", __func__);
    }
}

void test3()
{

    Solution sln;
    auto r = sln.shortestPalindrome("abbacd");
    if (r != "dcabbacd") {
        printf("%s() fail\n", __func__);
    }
}

void test1()
{

    Solution sln;
    auto r = sln.shortestPalindrome("aba");
    if (r != "aba") {
        printf("%s() fail\n", __func__);
    }
}

int main()
{

    test1();
    test2();
    test3();
    std::cout << "main exit\n";
    return 0;
}

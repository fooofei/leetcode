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

// 这个好难，一点也想不上来

class Solution {
public:
    string shortestPalindrome(string s)
    {
        if (s.size() < 2) {
            return s;
        }

        // 找到的是包含回文串的子串 但不是严格的就是回文串 在递归中继续寻找
        int j = 0;
        int i = s.size() - 1;
        for (; i >= 0; i--) {
            if (s[i] == s[j]) {
                j++;
            }
        }
        if (j >= s.size()) {
            return s;
        }

        string suffix = s.substr(j);
        string sub = shortestPalindrome(s.substr(0, j));
        string prefix = suffix;
        reverse(prefix.begin(), prefix.end());
        return prefix + sub + suffix;
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

void test4()
{
    Solution sln;
    auto r = sln.shortestPalindrome("aba");
    if (r != "aba") {
        printf("%s() fail\n", __func__);
    }
}

void test5()
{
    // aababababababa
    // ababababababaa
    Solution sln;
    auto r = sln.shortestPalindrome("aababababababa");
    if (r != "ababababababaababababababa") {
        printf("%s() fail\n", __func__);
    }
}

void test1()
{
    Solution sln;
    auto r = sln.shortestPalindrome("acbefghhgfebacaa");
    if (r != "aacabefghhgfebcacbefghhgfebacaa") {
        printf("%s() fail\n", __func__);
    }
}

int main()
{

    test1();
    std::cout << "main exit\n";
    return 0;
}

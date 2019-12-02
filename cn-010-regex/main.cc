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
#include <stdlib.h>
#include <string>
#include <thread>
#include <time.h>
#include <vector>

using namespace std;

// 010 https://leetcode-cn.com/problems/regular-expression-matching/

// 失败了 5 个用例，太不容易了

char GetChar(const char* p)
{
    return *p;
}

// 留下我的失败案例，写的很不好
bool MatchV1(const char* s, const char* p)
{
    if (GetChar(s) == 0) {
        if (GetChar(p) == 0) {
            return true;
        }
        // 不要急于结束，这里是要递归的
        if (GetChar(p + 1) == '*') {
            return MatchV1(s, p + 2);
        }
        return false;
    }

    if (GetChar(p) == 0) {
        return false;
    }

    if (GetChar(p + 1) == '*') {
        char c = GetChar(p);
        // 这里是要回溯的
        for (; GetChar(s) != 0; s++) {
            if (MatchV1(s, p + 2)) {
                return true;
            }
            if (!(c == '.' || GetChar(s) == c)) {
                break;
            }
        }
        return MatchV1(s, p + 2);
    }

    if (GetChar(p) == '.') {
        return MatchV1(s + 1, p + 1);
    }

    if (GetChar(p) == GetChar(s)) {
        return MatchV1(s + 1, p + 1);
    }
    return false;
}

// https://leetcode-cn.com/problems/regular-expression-matching/solution/ji-yu-guan-fang-ti-jie-gen-xiang-xi-de-jiang-jie-b/
// 这个版本代码更少，心智负担少，容易写正确，就是不容易想到
bool MatchV2(const char* s, const char* p)
{
    // 在这一步就要做对，先判断 p 而不是先判断 s
    if (GetChar(p) == 0) {
        return GetChar(s) == 0;
    }

    bool firstCharMatch = false;
    char c = GetChar(s);
    if (c != 0) {
        firstCharMatch = (GetChar(p) == '.') || (GetChar(p) == c);
    }

    if (GetChar(p + 1) == '*') {
        // 这里用递归代替 for 循环的回溯，思路简单
        if (MatchV2(s, p + 2)) {
            return true;
        }
        return firstCharMatch && MatchV2(s + 1, p);
    }
    return firstCharMatch && MatchV2(s + 1, p + 1);
}

// "动态规划的解，通俗的讲，是在分治的解上增加缓存。"
// 在上面理解的基础上，我又有了新的理解，用动态规划求解时，不要直接在递归求解上加缓存，
// 那样会离动态规划越来越远

bool MatchDP(const string& s, const string& p)
{
    if (p.size() < 1) {
        return s.size() == 0;
    }
    // row len = p len
    // col len = s len
    vector<vector<bool>> T;
    T.resize(p.size() + 1);
    for (size_t i = 0; i < T.size(); i++) {
        T[i].resize(s.size() + 1);
    }
    T[0][0] = true;
    T[1][0] = false;
    for (size_t i = 2; i < T.size(); i++) {
        // s == ""
        T[i][0] = T[i - 2][0] && p[i - 1] == '*';
    }
    for (size_t j = 1; j < T[0].size(); j++) {
        // p == ""
        T[0][j] = false;
    }

    if (T.size() > 1 && T[1].size() > 1) {
        if (p[0] == '.' || (p[0] == s[0])) {
            T[1][1] = true;
        }
    }

    for (size_t i = 2; i < T.size(); i++) {
        for (size_t j = 1; j < T[i].size(); j++) {
            if (p[i - 1] == '*') {
                if (T[i - 2][j]) {
                    T[i][j] = true;
                } else if (T[i][j - 1] && (p[i - 2] == '.' || p[i - 2] == s[j - 1])) {
                    T[i][j] = true;
                }
            } else {
                T[i][j] = T[i - 1][j - 1] && (p[i - 1] == '.' || p[i - 1] == s[j - 1]);
            }
        }
    }
    return T[p.size()][s.size()];
}

class Solution {
public:
    bool isMatch(string s, string p)
    {
        return MatchDP(s, p);
    }
};

void test2()
{
    Solution sln;

    auto r = sln.isMatch("aa", "a");
    if (r) {
        printf("%s() fail\n", __func__);
    }
}

void test3()
{
    Solution sln;

    auto r = sln.isMatch("aa", "a*");
    if (!r) {
        printf("%s() fail\n", __func__);
    }
}

void test4()
{
    Solution sln;

    auto r = sln.isMatch("aab", "c*a*b");
    if (!r) {
        printf("%s() fail\n", __func__);
    }
}

void test5()
{
    Solution sln;

    auto r = sln.isMatch("mississippi", "mis*is*p*.");
    if (r) {
        printf("%s() fail\n", __func__);
    }
}

void test6()
{
    Solution sln;

    auto r = sln.isMatch("ab", ".*");
    if (!r) {
        printf("%s() fail\n", __func__);
    }
}

void test7()
{
    Solution sln;

    auto r = sln.isMatch("ab", ".*c");
    if (r) {
        printf("%s() fail\n", __func__);
    }
}

void test8()
{
    Solution sln;

    auto r = sln.isMatch("aaa", "a*a");
    if (!r) {
        printf("%s() fail\n", __func__);
    }
}

void test9()
{
    Solution sln;

    auto r = sln.isMatch("a", "ab*");
    if (!r) {
        printf("%s() fail\n", __func__);
    }
}

void test1()
{
    Solution sln;

    auto r = sln.isMatch("", "c*c*");
    if (!r) {
        printf("%s() fail\n", __func__);
    }
}

int main()
{

    Solution sln;
    (void)sln;

    test1();
    test2();
    test3();
    test4();
    test5();
    test6();
    test7();
    test8();
    test9();

    std::cout << "main exit\n";
    return 0;
}

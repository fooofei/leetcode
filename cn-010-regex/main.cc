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

// 动态规划的解，通俗的讲，是在分治的解上增加缓存。
// 0 == not exists
// 1 == false
// 2 == true

bool DPExists(vector<int>& dp, int i, int j, int rowLen)
{
    return dp[i * rowLen + j] != 0;
}

bool DPResult(vector<int>& dp, int i, int j, int rowLen)
{
    if (dp[i * rowLen + j] == 2) {
        return true;
    }
    return false;
}

void DPSet(vector<int>& dp, int i, int j, int rowLen, bool r)
{
    if (r) {
        dp[i * rowLen + j] = 2;
    } else {
        dp[i * rowLen + j] = 1;
    }
}

bool DPMatch(const char* s, const char* p, int sOff, int pOff, int rowLen, vector<int>& dp)
{

    if (DPExists(dp, sOff, pOff, rowLen)) {
        return DPResult(dp, sOff, pOff, rowLen);
    }

    if (GetChar(p + pOff) == 0) {
        return GetChar(s + sOff) == 0;
    }

    bool firstCharMatch = false;
    char c = GetChar(s + sOff);
    if (c != 0) {
        firstCharMatch = (GetChar(p + pOff) == '.') || (GetChar(p + pOff) == c);
    }

    bool matched = false;
    if (GetChar(p + pOff + 1) == '*') {
        // 这里用递归代替 for 循环的回溯，思路简单
        if (DPMatch(s, p, sOff, pOff + 2, rowLen, dp)) {
            matched = true;
        } else {
            matched = firstCharMatch && DPMatch(s, p, sOff + 1, pOff, rowLen, dp);
        }
    } else {
        matched = firstCharMatch && DPMatch(s, p, sOff + 1, pOff + 1, rowLen, dp);
    }
    // 是保存当前 sOff pOff 的解，我理解错误，在上面也保存解，那是不对的
    DPSet(dp, sOff, pOff, rowLen, matched);
    return matched;
}

bool MatchV3(const char* s, const char* p)
{
    int sLen = strlen(s) + 1;
    int pLen = strlen(p) + 1;
    vector<int> dp;
    dp.resize(sLen * pLen);
    return DPMatch(s, p, 0, 0, pLen, dp);
}

class Solution {
public:
    bool isMatch(string s, string p)
    {
        return MatchV3(s.c_str(), p.c_str());
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

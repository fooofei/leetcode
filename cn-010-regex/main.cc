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

// https://leetcode-cn.com/problems/regular-expression-matching/

bool Match(const string& s, int sOff, const string& p, int pOff)
{
    if (sOff >= (int)s.size()) {
        return pOff >= (int)p.size();
    }

    if (pOff >= (int)p.size()) {
        return false;
    }

    if ((pOff + 1) < (int)p.size() && p[pOff + 1] == '*') {
        char c = p[pOff];

        int i;
        for (i = sOff; i < (int)s.size(); i++) {
            if (c != '.' && s[i] != c) {
                break;
            }
        }
        return Match(s, i, p, pOff + 2);
    }

    if (p[pOff] == '.') {
        return Match(s, sOff + 1, p, pOff + 1);
    }

    if (p[pOff] == s[sOff]) {
        return Match(s, sOff + 1, p, pOff + 1);
    }

    return false;
}

class Solution {
public:
    bool isMatch(string s, string p)
    {
        if (s.size() == 0) {

            return (p.size() <= 0 || p == "*");
        }

        if (p.size() == 0) {
            return false;
        }
        return Match(s, 0, p, 0);
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

void test1()
{
    Solution sln;

    auto r = sln.isMatch("aaa", "a*a");
    if (r) {
        printf("%s() fail\n", __func__);
    }
}

int main()
{

    Solution sln;
    (void)sln;

    test1();

    std::cout << "main exit\n";
    return 0;
}

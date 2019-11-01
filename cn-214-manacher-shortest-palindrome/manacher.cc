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

// 在 005 最长回文串的基础上继续做

void Manacher(const string& dummy, vector<int>& dp)
{
    int center = 0;
    int maxRight = 0;
    for (int i = 1; i < (int)dummy.size() - 1; i++) {
        int r = 0;
        if (i < maxRight) {
            int r2 = dp[2 * center - i];
            r = min(r2, maxRight - i);
        }

        r += 1;
        for (; dummy[i + r] == dummy[i - r]; r++) {
        }
        dp[i] = r - 1;
        if (dp[i] + i > maxRight) {
            maxRight = dp[i] + i;
            center = i;
        }
    }
}

struct RomePair {
    int center;
    int r;
};
typedef struct RomePair RomePair;

bool SortCmp(const RomePair& first, const RomePair& last)
{
    return first.r > last.r;
}
void ToRomePair(const string& dummy, const vector<int>& dp, vector<RomePair>& romes)
{

    for (int i = 1; i < (int)dummy.size() - 1; i++) {
        RomePair rome;
        rome.center = i;
        rome.r = dp[i];
        romes.push_back(rome);
    }

    sort(romes.begin(), romes.end(), SortCmp);
}

class Solution {
public:
    string shortestPalindrome(string s)
    {
        string dummy;
        if (s.size() < 2) {
            return s;
        }
        dummy += '~';
        for (int i = 0; i < (int)s.size(); i++) {
            dummy += '#';
            dummy += s[i];
        }
        dummy += '#';
        dummy += '@';

        vector<int> dp;
        dp.resize(dummy.size(), 0);
        Manacher(dummy, dp);
        vector<RomePair> romes;
        ToRomePair(dummy, dp, romes);
        for (auto rome : romes) {
            if (rome.center - rome.r == 1) {
                string ret;
                for (int i = dummy.size() - 2; i > rome.center + rome.r; i--) {
                    if (dummy[i] != '#') {
                        ret += dummy[i];
                    }
                }
                ret += s;
                return ret;
            }
        }

        string ret;
        for (int i = s.size() - 1; i > 0; i--) {
            ret += s[i];
        }
        ret += s;
        return ret;
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

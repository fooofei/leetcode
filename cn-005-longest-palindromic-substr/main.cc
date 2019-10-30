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

// 005 https://leetcode-cn.com/problems/longest-palindromic-substring/

// 第一次每次递归都是 2的n次方的计算量，导致无法接受
// 后来发现可以去除某些重复的区间 

// 执行用时 :
// 928 ms
// , 在所有 cpp 提交中击败了
// 5.01%
// 的用户


bool IsPalindrome(const string& s, int first, int last)
{
    int i = first;
    int j = last - 1;

    for (; i < j; i++, j--) {
        if (s[i] != s[j]) {
            return false;
        }
    }

    return true;
}

struct IndexSection {
    int first;
    int last;

    IndexSection(int first, int last)
    {
        this->first = first;
        this->last = last;
    }
};
using IndexSection = struct IndexSection;

void FindRome(const string& s, const vector<IndexSection>& sections, int subStrlen, string* maxRome)
{

    vector<IndexSection> subSections;

    for (int i = 0; i < (int)sections.size(); i++) {
        const IndexSection& sec = sections[i];
        if (IsPalindrome(s, sec.first, sec.last)) {
            *maxRome = s.substr(sec.first, sec.last - sec.first);
            return;
        }
        if (sec.first + 1 < sec.last) {
            subSections.push_back(IndexSection(sec.first, sec.last - 1));
        }
    }

    subStrlen -= 1;
    if (subStrlen > 0) {
        subSections.push_back(IndexSection(s.size() - subStrlen, s.size()));
    }

    if (subSections.size() > 0) {
        FindRome(s, subSections, subStrlen, maxRome);
    }
}

class Solution {

public:
    string longestPalindrome(string s)
    {

        vector<IndexSection> secs;
        secs.push_back(IndexSection(0, s.size()));
        string maxRome;
        FindRome(s, secs, s.size(), &maxRome);

        return maxRome;
    }
};

void test2()
{
    Solution sln;

    auto r = sln.longestPalindrome("babad");
    if (r != "bab") {
        printf("fail\n");
    }
}

void test3()
{
    Solution sln;

    auto r = sln.longestPalindrome("cbbd");
    if (r != "bb") {
        printf("fail\n");
    }
}

void test1()
{
    Solution sln;

    auto r = sln.longestPalindrome("babaddtattarrattatddetartrateedredividerb");
    if (r != "ddtattarrattatdd") {
        printf("fail\n");
    }
}

int main()
{
    Solution sln;
    (void)sln;

    test1();

    return 0;
}

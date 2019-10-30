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

// 003 https://leetcode-cn.com/problems/longest-substring-without-repeating-characters

// 我倒是想复杂了，代码量大

class UniqSubStr {
public:
    UniqSubStr()
    {
        existMap_.resize(0xFF, false);
    }
    ~UniqSubStr()
    {
    }
    bool Exist(char c)
    {
        if (indexStack_.size() > 0) {
            return existMap_[c];
        }
        return false;
    }

    int Size()
    {
        return (int)indexStack_.size();
    }

    void AdvanceUntilNotExists(const string& src, char c)
    {
        for (; Exist(c);) {
            int index = indexStack_.front();
            indexStack_.pop_front();
            existMap_[src[index]] = false;
        }
    }

    void Push(int index, char c)
    {
        indexStack_.push_back(index);
        existMap_[c] = true;
    }

private:
    list<int> indexStack_;
    vector<bool> existMap_;
};

class Solution {
public:
    int lengthOfLongestSubstring(string s)
    {

        UniqSubStr uniq;

        int maxLen = 0;

        for (int i = 0; i < (int)s.size(); i++) {
            char c = s[i];
            if (uniq.Exist(c)) {
                maxLen = max(maxLen, (int)uniq.Size());
                uniq.AdvanceUntilNotExists(s, c);
            }
            uniq.Push(i, c);
        }

        maxLen = max(maxLen, (int)uniq.Size());

        return maxLen;
    }
};

void test2()
{
    Solution sln;

    auto r = sln.lengthOfLongestSubstring("abcabcbb");
    if (r != 3) {
        printf("fail\n");
    }
}

void test3()
{
    Solution sln;

    auto r = sln.lengthOfLongestSubstring("bbbbb");
    if (r != 1) {
        printf("fail\n");
    }
}


void test1()
{
    Solution sln;

    auto r = sln.lengthOfLongestSubstring("pwwkew");
    if (r != 3) {
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

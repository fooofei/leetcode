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

// ((('a')*233+'b')*233+'b')*233 + 'c'
// 'a' + 'b'*233 + 'b'*233*233 +'c'*233*233*233

// Remove 'c'
// ((('a')*233+'b')*233+'b')
// 'a' + 'b'*233 + 'b'*233*233

// Remove 'a'
// (('b'*233)+'b')*233+'c'
// 'b'+'b'*233 + 'c'*233*233


// 执行用时 :
// 12 ms
// , 在所有 cpp 提交中击败了
// 93.98%
// 的用户

// 学习来自这里 https://blog.csdn.net/zichenzhiguang/article/details/52372988

// 误区  hash 值在移除字符时，使用除法是不正确的，乘法得到的结果除法再来一次，无法复原

// 根据一个字符串 计算三个数组
// 1 乘数因子数组
// 2 左到右方向的 hash 数组
// 3 右到左方向的 hash 数组

class StringHash {
public:
    vector<uint64_t> multipBases_;
    vector<uint64_t> lrHashs_; // left -> right
    vector<uint64_t> rlHashs_; // right -> left

    void Init(const string& str)
    {
        int len = (int)str.size();
        multipBases_.resize(len, 0);
        lrHashs_.resize(len, 0);
        rlHashs_.resize(len, 0);

        uint64_t seed = 233;
        multipBases_[0] = 1;
        for (int i = 1; i < (int)multipBases_.size(); i++) {
            multipBases_[i] = seed * multipBases_[i - 1];
        }

        lrHashs_[0] = str[0];
        for (int i = 1; i < (int)multipBases_.size(); i++) {
            lrHashs_[i] = lrHashs_[i - 1] * seed + str[i];
        }

        int off = rlHashs_.size() - 1;
        rlHashs_[off] = str[off];
        for (int i = off - 1; i >= 0; i--) {
            rlHashs_[i] = rlHashs_[i + 1] * seed + str[i];
        }
    }

    uint64_t GetLRHash(int left, int right) const
    {
        if (left == 0) {
            return lrHashs_[right - 1];
        }
        return lrHashs_[right - 1] - lrHashs_[left - 1] * multipBases_[right - left];
    }

    uint64_t GetRLHash(int left, int right) const
    {
        if (right == rlHashs_.size()) {
            return rlHashs_[left];
        }
        return rlHashs_[left] - rlHashs_[right] * multipBases_[right - left];
    }

    int Size() const
    {
        return multipBases_.size();
    }
};

// 确定了子串的长度后，即 romeLen ，根据这个长度找到所有子串中的回文串
void SearchRome(const string& str, const StringHash& hashs, int romeLen, int* outLeft)
{
    uint64_t lrhash = 0;
    uint64_t rlhash = 0;

    for (int i = 0; i < (int)hashs.Size() - romeLen; i++) {

        lrhash = hashs.GetLRHash(i, i + romeLen);
        rlhash = hashs.GetRLHash(i, i + romeLen);
        if (lrhash == rlhash) {
            // 如果需要精确匹配
            // string lrstr = str.substr(i, romeLen);
            // string rlstr = lrstr;
            // reverse(rlstr.begin(), rlstr.end());
            // if(lrstr == rlstr) {
            //     *outLeft = i;
            //     return;
            // }
            *outLeft = i;
            return;
        }
    }
}

class Solution {

public:
    string longestPalindrome(string s)
    {
        if (s.size() < 2) {
            return s;
        }

        string dummy;
        dummy += '~';
        for (auto c : s) {
            dummy += '#';
            dummy += c;
        }
        dummy += '#';
        dummy += '@';

        // 加完虚拟字符后，我们无需区分计算偶数长度还是奇数长度，最后的回文串一定是奇数
        vector<int> oddLens;
        for (int i = 1; i < (int)dummy.size(); i += 2) {
            oddLens.push_back(i);
        }

        StringHash hashs;
        hashs.Init(dummy);

        // 二分 二分为什么成立，简单说是  cabac 是回文串，那么长度更小的 aba 也是回文串
        // 但是长度更大的就很可能不是回文串
        // 满足在序列上是 true true true .... false ... 的局面，就能使用二分
        // 二分查找最后一个 true

        int maxLens = 0;
        int left = -1;
        int i = 0;
        int j = oddLens.size();

        for (; i < j;) {
            int64_t mid64 = (int64_t)i + (int64_t)j;
            int mid = (int)(mid64 / 2);

            int findLeft = -1;
            SearchRome(dummy, hashs, oddLens[mid], &findLeft);
            if (findLeft > -1) {
                if (oddLens[mid] > maxLens) {
                    maxLens = oddLens[mid];
                    left = findLeft;
                }
                i = mid + 1;
                // 为什么一定能触碰到最后一个 true 呢
                // 因为他要找第 1 个 false
            } else {
                j = mid;
            }
        }

        // 因为虚拟字符的存在 left 一定有值
        string ret;
        for (int i = left; i < left + maxLens; i++) {
            if (dummy[i] != '#') {
                ret += dummy[i];
            }
        }
        return ret;
    }
};

void test2()
{
    Solution sln;

    auto r = sln.longestPalindrome("babad");
    if (r != "bab" && r != "aba") {
        printf("%s() fail\n", __func__);
    }
}

void test3()
{
    Solution sln;

    auto r = sln.longestPalindrome("cbbd");
    if (r != "bb") {
        printf("%s() fail\n", __func__);
    }
}

void test4()
{
    Solution sln;

    auto r = sln.longestPalindrome("babaddtattarrattatddetartrateedredividerb");
    if (r != "ddtattarrattatdd") {
        printf("%s() fail\n", __func__);
    }
}

void test5()
{
    Solution sln;

    auto r = sln.longestPalindrome("ac");
    if (r != "a" && r != "c") {
        printf("%s() fail\n", __func__);
    }
}

void test1()
{
    Solution sln;

    auto r = sln.longestPalindrome("abb");
    if (r != "bb") {
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
    return 0;
}

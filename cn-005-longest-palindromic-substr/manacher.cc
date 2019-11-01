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

// Manacher's ALGORITHM: O(n)时间求字符串的最长回文子串  不指定
// https://www.felix021.com/blog/read.php?2040

// 马拉车算法结果的一个特点
// babad 扩展为
// ~#b#a#b#a#d#&
// DP数组为
// 00020301000

// 发现原本回文串长度一样的 bab aba ，在这个数组里长度不一样了
// 因此原来能发现 2 个等价结果，现在只发现 1 个结果
// 更正，这是错误发现，因为扩展字符串时，我是这样扩展的
//                 ~b#a#b#a#d&
// 其实应该写这样  ~#b#a#b#a#d#&
// 第一个两个回文串 长度不一样 b#a#b   #a#b#a#
// 第二个长度一样             #b#a#b# #a#b#a#
// 谨记：做字符串拓展的时候，不要丢弃首尾的 #

string Manacher(const string& s)
{
    if (s.size() < 2) {
        return s;
    }
    // 扩展原字符串
    string input;
    // 假设 ~ @ 都是字符串中不会出现的
    input += '~';
    for (auto c : s) {
        input += '#';
        input += c;
    }
    input += '#';
    input += '&';

    vector<int> dp;
    dp.resize(input.size(), 0);

    int mx = 0; // 能到达的最右边界
    int mid = 0; // mx 对应的中心轴
    for (int i = 1; i < (int)input.size() - 1; i++) {
        if (i < mx) {
            int i2 = 2 * mid - i; // i 关于 mid 的对称点 因为 i<mx 因此 i2 不会超过数组的界限
            // 不使用简写的形式  不好理解
            if (dp[i2] < (mx - i)) {
                dp[i] = dp[i2]; // 这种情况不需要 dp[i] 前进
            } else {
                dp[i] = mx - i; // 这种情况还需要 dp[i] 前进，继续看是否还更长
            }
        }
        // 获取 dp[i] 之后，我们都向前进，不管需不需要前进，省去 if else 区分情况
        int j = 0;
        for (; input[i + dp[i] + j] == input[i - dp[i] - j]; j++) {
        }
        dp[i] += j - 1;
        if ((i + dp[i]) > mx) {
            mx = i + dp[i];
            mid = i;
        }
    }

    int maxIndex = 0;
    int maxRad = 0;
    for (int i = 0; i < (int)dp.size(); i++) {
        if (maxRad < dp[i]) {
            maxRad = dp[i];
            maxIndex = i;
        }
    }

    // 以 maxIndex 为中心， maxRad 为半径的回文
    // 注意右边界，错误点
    string sub;
    for (int i = maxIndex - maxRad; i < maxIndex + maxRad + 1; i++) {
        if (input[i] != '#') {
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

//

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

    auto r = sln.longestPalindrome("a");
    if (r != "a") {
        printf("%s() fail\n", __func__);
    }
}

void test6()
{
    Solution sln;

    auto r = sln.longestPalindrome("bb");
    if (r != "bb") {
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
    test6();

    return 0;
}

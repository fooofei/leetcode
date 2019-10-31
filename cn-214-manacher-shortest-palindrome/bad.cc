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
    // 复杂度 O(n*n)
    // 没有通过
    string shortestPalindrome(string s)
    {

        if (s.size() < 2) {
            return s;
        }

        string sDummy;
        for (int i = 0; i < (int)s.size(); i++) {
            sDummy += '#';
            sDummy += s[i];
        }
        sDummy += '#';

        // 不 -1，sDummy 也可能是回文，题目里看不出这个意思，是从用例里得到这个信息的
        int center = sDummy.size() / 2;
        int r = 0;

        // 2*n-1
        for (; center > 1; center--) {

            int i = center - 1;
            int j = center + 1;

            for (; i >= 0 && j < (int)sDummy.size(); i--, j++) {
                if (sDummy[i] != sDummy[j]) {
                    break;
                }
            }

            if (i == -1) {
                string ret;

                for (int k = sDummy.size() - 2; k > 2 * center; k--) {
                    if (sDummy[k] != '#') {
                        ret += sDummy[k];
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

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

#include <stdarg.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

using namespace std;

// 125 https://leetcode-cn.com/problems/valid-palindrome/submissions/

bool ValidStringIsPalindrom(const string& str)
{
    int i = 0;
    int j = str.size() - 1;

    for (; i < j; i++, j--) {
        if (str[i] != str[j]) {
            return false;
        }
    }
    return true;
}

class Solution {
public:
    Solution()
    {
    }

    ~Solution()
    {
    }
    bool isPalindrome(string s)
    {
        string filtered;

        for (auto c : s) {
            if ((c >= 'A' && c <= 'Z')) {
                c = c - 'A' + 'a';
            }

            if ((c >= '0' && c <= '9') || (c >= 'a' && c <= 'z')) {
                filtered += c;
            }
        }

        if (filtered.size() <= 0) {
            return true;
        }
        return ValidStringIsPalindrom(filtered);
    }

private:
};

void test1()
{
    Solution sln;

    auto r = sln.isPalindrome("A man, a plan, a canal: Panama");

    if (!r) {
        printf("%s() fail\n", __func__);
    }
}

int main()
{
    test1();
    return 0;
}

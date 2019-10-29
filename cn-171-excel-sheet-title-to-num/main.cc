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

// 171 https://leetcode-cn.com/problems/excel-sheet-column-number/

// 执行用时 :
// 8 ms
// , 在所有 cpp 提交中击败了
// 55.38%
// 的用户

class Solution {
public:
    int titleToNumber(string s)
    {
        int num = 0;
        for (int i = 0; i < s.size(); i++) {
            num *= 26;
            num += (s[i] - 'A' + 1);
        }

        return num;
    }
};

void test1()
{
    Solution sln;

    auto r = sln.titleToNumber("A");
    if (r != 1) {
        printf("%s() fail\n", __func__);
    }
}

void test2()
{
    Solution sln;
    auto r = sln.titleToNumber("AB");
    if (r != 28) {
        printf("%s() fail\n", __func__);
    }
}

void test3()
{
    Solution sln;
    auto r = sln.titleToNumber("ZY");
    if (r != 701) {
        printf("%s() fail\n", __func__);
    }
}

int main()
{
    test1();
    test2();
    test3();
    return 0;
}

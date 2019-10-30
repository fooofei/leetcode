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

// 006 https://leetcode-cn.com/problems/zigzag-conversion/

class Solution {
public:
    string convert(string s, int numRows)
    {
        vector<string> rows;
        if (numRows == 1) {
            return s;
        }

        int rowStep;
        int rowIndex = 0;

        for (int i = 0; i < (int)s.size(); i++) {
            rows[rowIndex].push_back(s[i]);
            if (rowIndex == 0) {
                rowStep = 1;
            }
            if (rowIndex == numRows - 1) {
                rowStep = -1;
            }
            rowIndex += rowStep;
        }

        string zigzag;
        for (auto row : rows) {
            zigzag += row;
        }
        return zigzag;
    }
};

void test2()
{
    Solution sln;

    auto r = sln.convert("LEETCODEISHIRING", 3);
    if (r != "LCIRETOESIIGEDHN") {
        printf("%s() fail\n", __func__);
    }
}

void test1()
{
    Solution sln;

    auto r = sln.convert("AB", 1);
    if (r != "AB") {
        printf("%s() fail\n", __func__);
    }
}

int main()
{
    Solution sln;
    (void)sln;

    test1();
    test2();

    return 0;
}

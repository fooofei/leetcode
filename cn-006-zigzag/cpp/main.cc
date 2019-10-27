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

// https://leetcode-cn.com/problems/zigzag-conversion/

class Solution {
public:
    string convert(string s, int numRows)
    {
        vector<vector<char>> rows;

        if(numRows == 1) {
            return s;
        }
        
        for (int i = 0; i < numRows; i++) {
            rows.push_back(vector<char>());
        }

        int rowIndex = 0;
        bool up = true;

        for (int i = 0; i < (int)s.size(); i++) {
            rows[rowIndex].push_back(s[i]);

            if (up) {
                rowIndex += 1;
            } else {
                rowIndex -= 1;
            }
            if (rowIndex < 0) {
                rowIndex += 2;
                up = true;
            }
            if (rowIndex >= numRows) {
                rowIndex -= 2;
                up = false;
            }
        }

        string zigzag;
        for (auto row : rows) {
            for (auto c : row) {
                zigzag.push_back(c);
            }
        }
        return zigzag;
    }
};

void test2()
{
    Solution sln;

    auto r = sln.convert("LEETCODEISHIRING", 3);
    if(r != "LCIRETOESIIGEDHN") {
        printf("%s() fail\n", __func__);
    }
}

void test1()
{
    Solution sln;

    auto r = sln.convert("AB", 1);
    if(r != "AB") {
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

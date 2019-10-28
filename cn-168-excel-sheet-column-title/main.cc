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

// 168 https://leetcode-cn.com/problems/excel-sheet-column-title/

class Solution {
public:
    string convertToTitle(int n)
    {
        string s;
        for (; n > 0;) {
            char c = ((n-1) % 26) + 'A';
            n = (n-1) / 26;
            s.insert(s.begin(), c);
        }
        return s;
    }
};

void test1()
{
    Solution sln;
    auto r = sln.convertToTitle(26);
    if( r != "Z") {
        printf("%s() fail\n", __func__);
    }
}

void test2()
{
    Solution sln;
    auto r = sln.convertToTitle(28);

    if(r != "AB") {
        printf("%s() fail\n", __func__);
    }
}

void test3()
{
    Solution sln;
    auto r = sln.convertToTitle(701);

    if(r != "ZY") {
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

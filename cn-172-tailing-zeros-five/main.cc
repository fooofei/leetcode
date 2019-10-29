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

// 172 https://leetcode-cn.com/problems/factorial-trailing-zeroes/

// 25 是出现 2 个 5 ，我这样就少算了

// 1 2 3 4 5 6 7 8 9 10
// 11 12 13 14 15 16 17 18 19 20 
// 21 22 23 24 25 26 27 28
// ...

// 发现每隔 5 个数字，出现 1 个 5，我们称为组， 每隔 5 组，又多出 1 个 5 (比如 25 5*5*5)
// 

class Solution1 {
public:
    int trailingZeroes(int n)
    {
        if (n <= 0) {
            return 0;
        }

        string s;
        int count = 0;

        for (int i = 1; i <= n; i++) {
            if (i / 10 * 10 == i) {
                count += 1;
            } else {

                s = to_string(i);
                if (s.back() == '5') {
                    count += 1;
                }
            }
        }

        return count;
    }
};

// 使用 for loop 的还是会超时
class Solution2 {
public:
    int trailingZeroes(int n)
    {
        if (n <= 0) {
            return 0;
        }

        int count = 0;

        for (int i = 1; i <= n; i++) {
            if (i % 5 == 0) {
                int v = i;
                for (; v >= 5 && v % 5 == 0;) {
                    count += 1;
                    v = v / 5;
                }
            }
        }

        return count;
    }
};


// 看了题解才知道的
class Solution {
public:
    int trailingZeroes(int n)
    {
        if (n <= 0) {
            return 0;
        }

        int count = 0;

        for (; n >= 5;) {
            n = n / 5;
            count += n;
        }

        return count;
    }
};

void test2()
{
    Solution sln;
    auto r = sln.trailingZeroes(3);
    if (r != 0) {
        printf("%s() fail\n", __func__);
    }
}
void test1()
{
    Solution sln;
    auto r = sln.trailingZeroes(30);
    if (r != 7) {
        printf("%s() fail\n", __func__);
    }
}

int main()
{
    test1();

    return 0;
}

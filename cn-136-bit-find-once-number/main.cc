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

// 136 https://leetcode-cn.com/problems/single-number/

class Solution {
public:
    int singleNumber(vector<int>& nums)
    {
        int once = 0;
        for (auto num : nums) {
            once ^= num;
        }

        return once;
    }
};

void test1()
{
    Solution sln;

    vector<int> vec = { 2, 2, 1 };
    auto r = sln.singleNumber(vec);
    if (r != 1) {
        printf("%s() fail\n", __func__);
    }
}

int main()
{
    test1();
    return 0;
}

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

// 121 https://leetcode-cn.com/problems/best-time-to-buy-and-sell-stock/

// 单调栈的解法

// 8 ms

class Solution {
public:
    int maxProfit(vector<int>& prices)
    {
        vector<int> stk;
        int maxDiff = 0;

        if (prices.size() < 2) {
            return 0;
        }
        // 可知 正常值不会是 -1
        stk.push_back(-1);
        for (size_t i = 0; i < prices.size(); i++) {

            for (; prices[i] <= stk.back();) {
                stk.pop_back();
            }
            stk.push_back(prices[i]);
            // 栈共有 -1 min max 三个以上的值 
            if (stk.size() > 2) {
                int diff = stk.back() - stk[1];
                if (diff > maxDiff) {
                    maxDiff = diff;
                }
            }
        }
        return maxDiff;
    }
};

int main()
{

    Solution sln;
    (void)sln;

    std::cout << "main exit\n";
    return 0;
}

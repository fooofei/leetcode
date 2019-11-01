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

// 122 https://leetcode-cn.com/problems/best-time-to-buy-and-sell-stock-ii/

// 什么鸡毛题，还是先总是绕在了数学

class Solution {
public:
    int maxProfit(vector<int>& prices)
    {
        int maxDiff = 0;
        vector<int> valueStack;
        prices.push_back(-1);
        valueStack.push_back(prices[0]);
        for (int i = 1; i < prices.size(); i++) {
            if (prices[i] <= valueStack.back()) {
                // 这才算一次买入卖出
                if (valueStack.size() > 1) {
                    maxDiff += valueStack[1] - valueStack[0];
                }
                valueStack.clear();
            } else if (valueStack.size() > 1) {
                valueStack.pop_back();
            }
            valueStack.push_back(prices[i]);
        }
        return maxDiff;
    }
};

void test1()
{
    Solution sln;
    vector<int> vec = { 7, 1, 5, 3, 6, 4 };
    auto r = sln.maxProfit(vec);
}

int main()
{
    test1();

    std::cout << "main exit\n";
    return 0;
}

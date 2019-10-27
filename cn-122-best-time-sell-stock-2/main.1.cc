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

// https://leetcode-cn.com/problems/best-time-to-buy-and-sell-stock-ii/

// 超出时间限制  这个解法应该没问题，暂时没有用例是失败的，只是时间上超时

struct IndexSection {
    int inIndex;
    int outIndex;
};
using IndexSection = struct IndexSection;

// @param index 从 indexSection 开始找的那个索引
// @param minIndex indexSection[].inIndex 的最小值
void TransAction(const vector<int>& prices, const vector<IndexSection>& indexSections, 
    int index, int minInIndex, int* diff, int *maxDiff)
{
    for (int i = index; i < indexSections.size(); i++) {
        if (indexSections[i].inIndex >= minInIndex) {
            int in_ = indexSections[i].inIndex;
            int out_ = indexSections[i].outIndex;
            *diff += prices[out_] - prices[in_];
            TransAction(prices, indexSections, i + 1, indexSections[i].outIndex + 1, diff, maxDiff);
            *diff -= prices[out_] - prices[in_];
        }
    }

    *maxDiff = max(*maxDiff, *diff);
}

class Solution {
public:
    int maxProfit(vector<int>& prices)
    {
        vector<IndexSection> indexSections;
        int maxDiff = 0;

        // 所有可能的买入卖出
        vector<int> indexStack;
        indexStack.push_back(0);
        for (int i = 1; i < prices.size(); i++) {
            for (; indexStack.size() > 0 && prices[i] <= prices[indexStack.back()];) {
                indexStack.pop_back();
            }
            indexStack.push_back(i);
            for (int j = 0; j < indexStack.size() - 1; j++) {
                IndexSection sec;
                sec.inIndex = indexStack[j];
                sec.outIndex = indexStack.back();
                indexSections.push_back(sec);
            }
        }
        int diff=0;
        TransAction(prices, indexSections, 0, 0, &diff, &maxDiff);
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

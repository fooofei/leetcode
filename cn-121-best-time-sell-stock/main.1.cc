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

// https://leetcode-cn.com/problems/best-time-to-buy-and-sell-stock/
// 耗时 > 1000 ms 

typedef struct WithIndex {
    int index;
    int value;
} WithIndex;

bool sortCmp(const WithIndex& first, const WithIndex& last)
{
    return first.value < last.value;
}

class Solution {
public:
    int maxProfit(vector<int>& prices)
    {
        vector<WithIndex> withIndex;
        withIndex.reserve(prices.size());

        if (prices.size() <= 0) {
            return 0;
        }
        for (size_t i = 0; i < prices.size(); i++) {
            WithIndex a;
            a.index = i;
            a.value = prices[i];
            withIndex.push_back(a);
        }
        sort(withIndex.begin(), withIndex.end(), sortCmp);

        //  [7,1,5,3,6,4] 排序后 =>
        // 1<索引>,1  3,3,  5,4  2,5  4,6  0,7
        int maxDiff = 0;
        // 最多能到多少
        int limitDiff = withIndex[withIndex.size() - 1].value - withIndex[0].value;
        bool found = false;
        for (size_t i = 0; i < withIndex.size() - 1 && !found; i++) {
            for (size_t j = withIndex.size() - 1; j > i; j--) {
                if (withIndex[i].index < withIndex[j].index) {
                    int diff = withIndex[j].value - withIndex[i].value;
                    if (diff > maxDiff) {
                        maxDiff = diff;
                        if (maxDiff == limitDiff) {
                            found = true;
                            break;
                        }
                    }
                }
            }
        }
        return maxDiff;
    }
};

// [3,2,6,5,0,3] 排序后 =>
// 4 1 0 5 3 2
// 0 2 3 3 5 6

int main()
{

    Solution sln;
    (void)sln;

    std::cout << "main exit\n";
    return 0;
}

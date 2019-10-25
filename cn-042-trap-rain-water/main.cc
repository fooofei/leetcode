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

// https://leetcode-cn.com/problems/trapping-rain-water/submissions/

class Solution {
public:
    int trap(vector<int>& height)
    {
        if (height.size() <= 0) {
            return 0;
        }
        vector<int> valueStack;
        valueStack.push_back(height[0]);

        int waiters = 0;
        for (int i = 1; i < height.size(); i++) {
            // 右边墙呈现了洼地
            if (valueStack.size() > 0 && height[i] >= valueStack.back()) {
                // 左边墙同时有洼地就可以蓄水了
                if (valueStack.size() > 1) {
                    int minHeight = min(height[i], valueStack.front());
                    for (int j = valueStack.size() - 1; j >= 0; j--) {
                        if (valueStack[j] >= minHeight) {
                            break;
                        }
                        waiters += minHeight - valueStack[j];
                        valueStack[j] = minHeight;
                    }
                }
                // 看看是不是还有能力蓄水 左边墙是不是够高
                if (height[i] >= valueStack.front()) {
                    valueStack.clear();
                }
            }
            valueStack.push_back(height[i]);
        }
        return waiters;
    }
};

int main()
{

    Solution sln;
    (void)sln;

    std::cout << "main exit\n";
    return 0;
}

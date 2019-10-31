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

// 011 https://leetcode-cn.com/problems/container-with-most-water/

class Solution {
public:
    int maxArea(vector<int>& height)
    {
        if (height.size() < 2) {
            return 0;
        }
        int maxRet = 0;
        int i = 0;
        int j = height.size() - 1;

        for (; i < j;) {

            int area = min(height[i], height[j]) * (j - i);
            maxRet = max(maxRet, area);
            if (height[i] < height[j]) {
                i++;
            } else {
                j--;
            }
        }

        return maxRet;
    }
};

void test1()
{
    Solution sln;

    vector<int> input = { 1, 8, 6, 2, 5, 4, 8, 3, 7 };

    auto r = sln.maxArea(input);
    if (r != 49) {
        printf("fail\n");
    }
}

void test2()
{
    Solution sln;

    vector<int> input = { 1, 2, 4, 3 };

    auto r = sln.maxArea(input);
    if (r != 4) {
        printf("fail\n");
    }
}

int main()
{
    Solution sln;
    (void)sln;

    test2();

    return 0;
}

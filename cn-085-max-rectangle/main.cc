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

// 085 https://leetcode-cn.com/problems/maximal-rectangle/
// 这里有人说可以借助做过的连续最大矩形的题目
// https://leetcode-cn.com/problems/maximal-rectangle/solution/xiang-xi-tong-su-de-si-lu-fen-xi-duo-jie-fa-by-1-8/

// 借助 题目084 最大连续矩形
// 从矩形的每一层向上看，都视为矩形的高，求每一层最大连续矩形，然后 max(所有层最大连续矩形)

// 执行用时 :
// 24 ms
// , 在所有 cpp 提交中击败了
// 84.73%
// 的用户

int GetMaxArea(vector<int>& vec)
{
    vec.push_back(-1);
    vector<int> indexStack;
    indexStack.push_back(0);

    int maxArea = 0;

    for (int i = 1; i < (int)vec.size(); i++) {

        for (; indexStack.size() > 0 && vec[i] <= vec[indexStack.back()];) {

            int h = vec[indexStack.back()];
            indexStack.pop_back();
            int w = -1;
            if (indexStack.size() > 0) {
                w = indexStack.back();
            }
            w = i - w - 1;
            int area = w * h;

            maxArea = max(maxArea, area);
        }

        indexStack.push_back(i);
    }

    return maxArea;
}

int LevelsMaxArea(const vector<vector<char>>& matrix)
{
    vector<int> level;
    int maxArea = -1;

    if (matrix.size() <= 0) {
        return 0;
    }

    for (int i = 0; i < (int)matrix.size(); i++) {

        level.clear();

        for (int j = 0; j < (int)matrix[0].size(); j++) {

            int vertical = 0;
            for (int k = i; k >= 0 && matrix[k][j] == '1'; k--) {
                vertical += 1;
            }
            level.push_back(vertical);
        }
        int area = GetMaxArea(level);
        maxArea = max(maxArea, area);
    }

    return maxArea;
}

class Solution {
public:
    int maximalRectangle(vector<vector<char>>& matrix)
    {
        return LevelsMaxArea(matrix);
    }
};

void test1()
{
    Solution sln;

    vector<vector<char>> m = {
        { '1', '0', '1', '0', '0' },
        { '1', '0', '1', '1', '1' },
        { '1', '1', '1', '1', '1' },
        { '1', '0', '0', '1', '0' }
    };
    auto r = sln.maximalRectangle(m);
    if (r != 6) {
        printf("%s() fail\n", __func__);
    }
}

int main()
{
    test1();
    return 0;
}

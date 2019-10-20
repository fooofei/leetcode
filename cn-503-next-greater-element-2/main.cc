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

// https://leetcode-cn.com/problems/next-greater-element-ii/

class Solution {
public:
    vector<int> nextGreaterElements(vector<int>& nums)
    {

        vector<int> distances;
        distances.resize(nums.size(), -1);

        list<int> indexStack;
        // 正方向遍历一遍
        for (int i = 0; i < (int)nums.size(); i++) {
            for (; indexStack.size() > 0 && nums[i] > nums[indexStack.back()];) {
                distances[indexStack.back()] = nums[i];
                indexStack.pop_back();
            }
            indexStack.push_back(i);
        }

        // 剩下从大到小的排序了
        // 把最大的数字都排除在外
        if (indexStack.size() > 0) {
            int maxValue = nums[indexStack.front()];
            indexStack.pop_front();
            for (; indexStack.size() > 0 && nums[indexStack.front()] == maxValue;) {
                indexStack.pop_front();
            }
        }

        // 最大的排除了，剩下的不入栈
        for (int i = 0; indexStack.size() > 0 && i < (int)nums.size(); i++) {
            for (; indexStack.size() > 0 && nums[i] > nums[indexStack.back()];) {
                distances[indexStack.back()] = nums[i];
                indexStack.pop_back();
            }
        }
        return distances;
    }
};

int main()
{

    Solution sln;
    (void)sln;

    vector<int> nums = { 1, 2, 1 };
    vector<int> nums2 = { 1, 1, 1, 1 };
    vector<int> nums3 = { 1, 2, 3, 2, 1 };

    auto r = sln.nextGreaterElements(nums3);

    std::cout << "main exit\n";
    return 0;
}

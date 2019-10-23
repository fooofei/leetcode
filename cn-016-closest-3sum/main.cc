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

// https://leetcode-cn.com/problems/3sum-closest/

// -4 -1 1 2

class Solution {
public:
    int threeSumClosest(vector<int>& nums, int target)
    {
        sort(nums.begin(), nums.end());

        int i = 0;
        int j = 0;
        int k = 0;
        int64_t closest = INT32_MAX;


        if(nums[0] > target) {
            return nums[0] + nums[1] + nums[2];
        }

        if(nums[nums.size()-1] < target) {
            return nums[nums.size()-3] + nums[nums.size()-2] + nums[nums.size()-1]; 
        }

        for (; i < (int)nums.size() - 2; i++) {
            j = i + 1;
            k = nums.size() - 1;
            int left = 0;
            int right = 0;
            int twoSum = target - nums[i];
            for (; j < k;) {
                int sum = nums[j] + nums[k];

                if (sum < twoSum) {
                    j++;
                    left = sum;
                } else if (sum > twoSum) {
                    k--;
                    right = sum;
                } else {
                    return target;
                }
            }

            if (abs(twoSum - left) < abs(closest - target)) {
                closest = left + nums[i];
            }
            if (abs(twoSum - right) < abs(closest - target)) {
                closest = right + nums[i];
            }
        }
        return closest;
    }
};

int main()
{

    Solution sln;
    (void)sln;

    std::cout << "main exit\n";
    return 0;
}

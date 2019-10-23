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

// https://leetcode-cn.com/problems/median-of-two-sorted-arrays/

class Solution {
public:
    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2)
    {
        vector<int> nums;
        nums.resize(nums1.size() + nums2.size());

        int i = 0;
        int j = 0;
        int k = 0;

        for (; i < nums1.size() && j < nums2.size();) {
            if (nums1[i] <= nums2[j]) {
                nums[k] = nums1[i];
                k++;
                i++;
            } else {
                nums[k] = nums2[j];
                k++;
                j++;
            }
        }

        for (; i < nums1.size(); i++, k++) {
            nums[k] = nums1[i];
        }
        for (; j < nums2.size(); j++, k++) {
            nums[k] = nums2[j];
        }

        if (nums.size() % 2 == 1) {
            return nums[nums.size() / 2];
        } else {
            i = nums.size() / 2 - 1;
            j = i + 1;
            return (double(nums[i]) + double(nums[j])) / 2;
        }
    }
};

int main()
{

    Solution sln;
    (void)sln;

    std::cout << "main exit\n";
    return 0;
}

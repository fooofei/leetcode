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

// 004 https://leetcode-cn.com/problems/median-of-two-sorted-arrays/

class Solution1 {
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

double Median1(const vector<int>& nums)
{
    int i = nums.size() / 2;

    if (nums.size() % 2 == 1) {
        // 1 2 3
        return (double)nums[i];
    }
    // 1 2 3 4
    double next = nums[i]; // 2
    double prev = nums[i - 1]; // 1
    return (next + prev) / 2;
}

// 两个数组是连续的 left, right
double Median2(const vector<int>& left, const vector<int>& right)
{
    size_t len = left.size() + right.size();

    int i = len / 2;
    if (len % 2 == 1) {
        if (i < left.size()) {
            return left[i];
        } else {
            return right[i - left.size()];
        }
    }

    double prev = 0;
    double next = 0;

    if (i < left.size()) {
        next = left[i];
        prev = left[i - 1];
    } else if (i == left.size()) {
        next = right[0];
        prev = left[i - 1];
    } else {
        next = right[i - left.size()];
        prev = right[i - 1 - left.size()];
    }
    return (next + prev) / 2;
}

int Mid(int v1, int v2)
{
    int64_t v164 = v1;
    int64_t v264 = v2;
    return (int)(v164 + v264 / 2);
}

// 两个数组是交叉的 分割在两个数组中
double Median3(const vector<int>& nums1, const vector<int>& nums2)
{
    if(nums1.size() > nums2.size()) {
        return Median3(nums2, nums1);
    }

    int nums1Size = (int)nums1.size();
    int nums2Size = (int)nums2.size();
    int left = 0;
    int right = nums1Size;
    // 2 3 ｜5
    // 1 ｜4 7 9
    // k = 第 4 个数字，索引为 3   
    // 1 2 3 4 5 7 9

    // 2 3 ｜5 10
    // 1 ｜4 7 9
    // k = 第 4，5 个数字，索引为 3，4  
    // 1 2 3 4 5 7 9 10

    int topK = Mid(nums1Size, nums2Size+1);
    for(;left < right;) {
        int m = Mid(left, right);

        int num1LeftMax = nums1[m-1];
        int num1RightMin = nums1[m];
        int num2LeftMax = nums2[topK-m-1];
        
        int num2RightMin = nums2[topK-m];
    }
    
}

class Solution {
public:
    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2)
    {
        if (nums1.size() == 0) {
            if (nums2.size() == 0) {
                return 0;
            }
            return Median1(nums2);
        }
        if (nums2.size() == 0) {
            return Median1(nums1);
        }

        if (nums1.back() < nums2.front()) {
            return Median2(nums1, nums2);
        }

        if (nums2.front() < nums1.back()) {
            return Median2(nums2, nums1);
        }

        return 0;
    }
};

int main()
{

    Solution sln;
    (void)sln;

    std::cout << "main exit\n";
    return 0;
}

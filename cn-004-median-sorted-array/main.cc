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

// 004 https://leetcode-cn.com/problems/median-of-two-sorted-arrays/

// https://buptwc.com/2018/10/12/Leetcode-4-Median-of-Two-Sorted-Arrays/

int MidInt(int a, int b)
{
    int64_t a64 = a;
    int64_t b64 = b;
    return (int)((a64 + b64) / 2);
}

double MidDouble(int a, int b)
{
    double ad = a;
    double bd = b;
    return (a + b) / 2;
}

class Solution1 {
public:
    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2)
    {
        vector<int> nums;
        nums.resize(nums1.size() + nums2.size());

        int i = 0;
        int j = 0;
        int k = 0;

        for (; i < (int)nums1.size() && j < (int)nums2.size();) {
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

        for (; i < (int)nums1.size(); i++, k++) {
            nums[k] = nums1[i];
        }
        for (; j < (int)nums2.size(); j++, k++) {
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
        if (i < (int)left.size()) {
            return left[i];
        } else {
            return right[i - left.size()];
        }
    }

    double prev = 0;
    double next = 0;

    if (i < (int)left.size()) {
        next = left[i];
        prev = left[i - 1];
    } else if (i == (int)left.size()) {
        next = right[0];
        prev = left[i - 1];
    } else {
        next = right[i - left.size()];
        prev = right[i - 1 - left.size()];
    }
    return (next + prev) / 2;
}

// 两个数组是交叉的 分割在两个数组中
double Median3(const vector<int>& nums1, const vector<int>& nums2)
{
    // 调换一次顺序
    if (nums1.size() > nums2.size()) {
        return Median3(nums2, nums1);
    }

    int nums1Size = (int)nums1.size();
    int nums2Size = (int)nums2.size();

    // 2 3 | 5
    // 1 |4| 7 9
    // 1 2 3 4 5 7 9
    // left1 = 3 right1 = 5
    // left2 = 4 right2 = 4
    // mid = (4 + 4) /2
    // m+n = 7
    // 2*(m+n) = 14  // 与教程的不同点 我认为加上虚拟点不应该是 2*(m+n)+2 个
    // 再加上 INT_MIN INT_MAX 可能应该算 2*(m+n+2) 个，但是 INT_MIN 索引为 -1，因此计算 k 的个数的时候 也不能带上他
    // 当 2 3 | 5 决定的时候， 左边 4 个数 left1 = nums1'[3] c1 = 4 righ1 = nums1'[4]
    // 那应该第 2 个数组左边是 3 个数 left2 = nums2'[2] c2 = 3 righ2 = nums2'[3]

    // 2 3 | 5 10
    // 1 4 | 7 9
    // 1 2 3 4 5 7 9 10
    // left1 = 3 right1 = 5
    // left2 = 4 right2 = 7
    // mid = (4 + 5) / 2

    int left = 0;
    int right = 2 * nums1Size + 1;

    // 左边所有数的个数为 INT_MIN*2 + nums1Size + nums2Size
    int c1;
    int c2;
    int nums1LeftMax;
    int nums1RightMin;

    int nums2LeftMax;
    int nums2RightMin;

    for (; left < right;) {
        c1 = MidInt(left, right);
        // 为什么没有　+1
        c2 = nums1Size + nums2Size - c1;
        // 左边数的个数为 c1 + c2 = nums1Size + nums2Size
        // 教程有个点太模糊了， 没有虚拟点时如果 cut 在两个数中间，cut 左边是左边，右边是右边
        // cut 在数上，这个数既是左边的，又是右边的
        // 有了虚拟点以后，还是会遇到 cut 在 # 上还是数上，那计算左边应该有多少个数，右边应该有多少个数
        // 如何计算呢？
        // 也就是为什么 c1 + c2 = nums1Size + nums2Size
        // 为什么不是 c1 + c2 = nums1Size + nums2Size + 1

        // /2 是为了带上虚拟点的数对应到原数组上 这个怎么理解
        // 加上虚拟点后       # 2 # 3 # 5 #
        // 标记索引           0 0 1 1 2 2 3
        // 数值对应到原数组    2 2 3 3 5 5 INT_MAX  这么对应吗？

        nums1LeftMax = c1 <= 0 ? INT_MIN : nums1.at((c1 - 1) / 2);
        nums1RightMin = c1 >= 2 * nums1Size ? INT_MAX : nums1.at(c1 / 2);

        nums2LeftMax = c2 <= 0 ? INT_MIN : nums2.at((c2 - 1) / 2);
        nums2RightMin = c2 >= 2 * nums2Size ? INT_MAX : nums2.at(c2 / 2);

        if (nums1LeftMax > nums2RightMin) {
            right = c1;
        } else if (nums1RightMin < nums2LeftMax) {
            left = c1 + 1;
        } else {
            break;
        }
    }
    return MidDouble(max(nums1LeftMax, nums2LeftMax), min(nums1RightMin, nums2RightMin));
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

        // 包括在 Median3 里了
        // if (nums1.back() < nums2.front()) {
        //     return Median2(nums1, nums2);
        // }

        // if (nums2.back() < nums1.front()) {
        //     return Median2(nums2, nums1);
        // }

        return Median3(nums1, nums2);
    }
};

void test2()
{
    Solution sln;

    vector<int> nums1 = { 7, 8 };
    vector<int> nums2 = { 1, 2, 3, 4, 5, 6, 9 };
    auto r = sln.findMedianSortedArrays(nums1, nums2);
    printf("%s %.1f\n", __func__, r);
    if (r != 5.0) {
        printf("%s() fail\n", __func__);
    }
}

void test3()
{
    Solution sln;

    vector<int> nums1 = { 2, 3 };
    vector<int> nums2 = { 1, 4, 5, 6, 7, 8, 9 };
    auto r = sln.findMedianSortedArrays(nums1, nums2);
    printf("%s %.1f\n", __func__, r);
    if (r != 5.0) {
        printf("%s() fail\n", __func__);
    }
}

void test4()
{
    Solution sln;

    vector<int> nums1 = { 2, 3 };
    vector<int> nums2 = { 1, 4, 5, 9, 10, 11, 12 };
    auto r = sln.findMedianSortedArrays(nums1, nums2);
    printf("%s %.1f\n", __func__, r);
    if (r != 5.0) {
        printf("%s() fail\n", __func__);
    }
}

void test5()
{
    Solution sln;

    vector<int> nums1 = { 1, 2 };
    vector<int> nums2 = { 3, 4 };
    auto r = sln.findMedianSortedArrays(nums1, nums2);
    printf("%s %.1f\n", __func__, r);
    if (r != 2.5) {
        printf("%s() fail\n", __func__);
    }
}

void test1()
{
    Solution sln;

    vector<int> nums1 = { 2, 3, 5 };
    vector<int> nums2 = { 1, 4, 7, 9 };
    auto r = sln.findMedianSortedArrays(nums1, nums2);
    printf("%s %.1f\n", __func__, r);
    if (r != 4.0) {
        printf("%s() fail\n", __func__);
    }
}

int main()
{
    
    std::cout << "main exit\n";
    return 0;
}

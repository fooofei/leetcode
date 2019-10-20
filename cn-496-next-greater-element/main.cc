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

// https://leetcode-cn.com/problems/next-greater-element-i/
// 先把 nums2 排序的方法是错误的
// 因为 distance 不能是经过排序的

struct WithIndex {
    int index;
    int value;
};
using WithIndex = struct WithIndex;
bool sortCmp(const WithIndex& first, const WithIndex& last)
{
    return first.value < last.value;
}

void copy(const vector<int>& src, vector<WithIndex>& dst)
{
    for (int i = 0; i < (int)src.size(); i++) {
        WithIndex a;
        a.index = i;
        a.value = src[i];
        dst.push_back(a);
    }
}

class Solution {
public:
    vector<int> nextGreaterElement(vector<int>& nums1, vector<int>& nums2)
    {
        vector<WithIndex> withIndex;
        vector<int> nums2Distances;
        vector<WithIndex> nums1Dummy;
        vector<int> indexStack;
        nums2Distances.resize(nums2.size(), -1);

        for (int i = 0; i < (int)nums2.size(); i++) {
            for (; indexStack.size() > 0 && nums2[i] > nums2[indexStack.back()];) {
                nums2Distances[indexStack.back()] = nums2[i];
                indexStack.pop_back();
            }
            indexStack.push_back(i);
        }
        // 不需要关心栈中剩余的

        copy(nums1, nums1Dummy);
        copy(nums2, withIndex);
        sort(withIndex.begin(), withIndex.end(), sortCmp);
        sort(nums1Dummy.begin(), nums1Dummy.end(), sortCmp);

        vector<int> distances;
        distances.resize(nums1.size(), -1);

        int j = 0;
        for (int i = 0; i < (int)withIndex.size() && j < (int)nums1Dummy.size(); i++) {
            if (withIndex[i].value == nums1Dummy[j].value) {
                distances[nums1Dummy[j].index] = nums2Distances[withIndex[i].index];
                j++;
            }
        }
        return distances;
    }
};

int main()
{

    Solution sln;
    (void)sln;

    vector<int> nums1 = { 4, 1, 2 };
    vector<int> nums2 = { 1, 3, 4, 2 };

    auto r = sln.nextGreaterElement(nums1, nums2);

    std::cout << "main exit\n";
    return 0;
}

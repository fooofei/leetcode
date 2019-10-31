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

// 016 https://leetcode-cn.com/problems/3sum-closest/

class Solution {
public:
    int threeSumClosest(vector<int>& nums, int target)
    {
        // 娘啊 果然是需要排序的， 看到他好多测试用例是有序的  还以为不需要排序
        sort(nums.begin(), nums.end());

        int i = 0;
        int j = 0;
        int k = 0;
        int64_t closest = INT32_MAX;

        // 也不能得出这个结论
        // if (nums[0] > target) {
        //     return nums[0] + nums[1] + nums[2];
        // }

        // 不能得出这个结论
        // if (nums[nums.size() - 1] < target) {
        //     return nums[nums.size() - 3] + nums[nums.size() - 2] + nums[nums.size() - 1];
        // }

        for (; i < (int)nums.size() - 2; i++) {
            j = i + 1;
            k = nums.size() - 1;
            int64_t thisClosest = INT32_MAX;

            for (; j < k;) {
                int sum = nums[j] + nums[k] + nums[i];

                if (sum < target) {
                    j++;
                } else if (sum > target) {
                    k--;
                } else {
                    return target;
                }

                if (abs(sum - target) < abs(thisClosest - target)) {
                    thisClosest = sum;
                }
            }

            if (abs(thisClosest - target) < abs(closest - target)) {
                closest = thisClosest;
            }
            
            // 这个加速也要不得 不一定拿到的是最小的 不能得出结论说不用比较后面的了
            // if (new_ && closest > target) {
            //     // 没必要继续比较了
            //     return (int)closest;
            // }
        }
        return (int)closest;
    }
};

void test1()
{
    Solution sln;

    vector<int> input = { 0, 1, 2 };
    auto r = sln.threeSumClosest(input, 0);
    if (r != 3) {
        printf("fail\n");
    }
}

void test2()
{
    Solution sln;

    vector<int> input = { 1, 2, 5, 10, 11 };
    auto r = sln.threeSumClosest(input, 12);
    if (r != 13) {
        printf("fail\n");
    }
}

void test3()
{
    Solution sln;

    vector<int> input = { 1, 6, 9, 14, 16, 70 };
    auto r = sln.threeSumClosest(input, 81);

    if (r != 80) {
        printf("fail\n");
    }
}

void test4()
{
    Solution sln;

    vector<int> input = { 6, -18, -20, -7, -15, 9, 18, 10, 1, -20, -17, -19, -3, -5, -19, 10, 6, -11, 1, -17, -15, 6, 17, -18, -3, 16, 19, -20, -3, -17, -15, -3, 12, 1, -9, 4, 1, 12, -2, 14, 4, -4, 19, -20, 6, 0, -19, 18, 14, 1, -15, -5, 14, 12, -4, 0, -10, 6, 6, -6, 20, -8, -6, 5, 0, 3, 10, 7, -2, 17, 20, 12, 19, -13, -1, 10, -1, 14, 0, 7, -3, 10, 14, 14, 11, 0, -4, -15, -8, 3, 2, -5, 9, 10, 16, -4, -3, -9, -8, -14, 10, 6, 2, -12, -7, -16, -6, 10 };
    auto r = sln.threeSumClosest(input, -52);
    if (r != -52) {
        printf("fail\n");
    }
}

int main()
{

    Solution sln;
    (void)sln;

    test4();

    std::cout << "main exit\n";
    return 0;
}

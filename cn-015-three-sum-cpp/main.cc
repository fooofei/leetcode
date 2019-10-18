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

// https://leetcode-cn.com/problems/3sum/

bool sort_cmp(const int& first, const int& last)
{
    return first < last;
}

class Solution {
public:
    vector<vector<int>> threeSum(vector<int>& nums)
    {
        vector<vector<int>> result;

        sort(nums.begin(), nums.end(), sort_cmp);

        for (size_t i = 0; i + 2 < nums.size() && nums[i] <= 0;) {

            size_t j = i + 1;
            size_t k = nums.size() - 1;
            int val1 = nums[i];

            if (val1 + nums[j] + nums[j + 1] > 0) {
                i++;
                continue;
            }
            if (val1 + nums[k - 1] + nums[k] < 0) {
                i++;
                continue;
            }

            for (; j < k;) {
                int sum = val1 + nums[j] + nums[k];
                if (sum == 0) {
                    result.push_back({ val1, nums[j], nums[k] });

                    // 跳过重复的
                    size_t j1 = j + 1;
                    for (; j1 < k && nums[j1] == nums[j]; j1++) {
                    }
                    j = j1;

                    size_t k1 = k - 1;
                    for (; j < k1 && nums[k1] == nums[k]; k1--) {
                    }
                    k = k1;

                } else if (sum < 0) {
                    j++;
                } else if (sum > 0) {
                    k--;
                }
            }

            size_t i1 = i + 1;

            for (; i1 < nums.size() && nums[i1] == nums[i]; i1++) {
            }
            i = i1;
        }
        return result;
    }
};

void testf(vector<int> input, int resultCount)
{
    Solution sln;

    auto r = sln.threeSum(input);

    if (r.size() == resultCount) {
        cout << "success " << endl;
    } else {
        cout << "fail " << endl;
    }
}

int main()
{

    Solution sln;
    (void)sln;

    testf({ -1, 0, 1, 2, -1, -4 }, 2);

    testf({ -4, -1, -4, 0, 2, -2, -4, -3, 2, -3, 2, 3, 3, -4 }, 4);

    testf({ -4, -2, 1, -5, -4, -4, 4, -2, 0, 4, 0, -2, 3, 1, -5, 0 }, 6);

    std::cout << "main exit\n";
    return 0;
}

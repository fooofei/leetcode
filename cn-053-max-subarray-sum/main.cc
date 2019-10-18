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

using namespace std;

// https://leetcode-cn.com/problems/maximum-subarray/

bool sort_cmp(const int& first, const int& last)
{
    return first > last;
}

class Solution {
public:
    int maxSubArray(const vector<int>& nums)
    {
        vector<int> maxSums;

        if (nums.size() == 0) {
            return 0;
        }
        if (nums.size() == 1) {
            return nums[0];
        }

        vector<int> stk;
        int currentSum = 0;

        for (auto num : nums) {

            if (num < 0 && num + currentSum < 0) {
                if (stk.size() > 0) {
                    maxSums.push_back(currentSum);
                } else {
                    maxSums.push_back(num);
                }
                currentSum = 0;
                stk.clear();
            } else if (num < 0) {
                if (stk.size() > 0) {
                    maxSums.push_back(currentSum);
                }

                currentSum += num;
                stk.push_back(num);
            } else {
                currentSum += num;
                stk.push_back(num);
            }
        }

        if (stk.size() > 0) {
            maxSums.push_back(currentSum);
        }

        sort(maxSums.begin(), maxSums.end(), sort_cmp);

        return maxSums[0];
    }
};

void testf(const vector<int>& vec, int expect)
{
    Solution a;
    (void)a;

    auto r = a.maxSubArray(vec);

    cout << "max = " << r << " expect = " << expect << endl;
}

void test1()
{
    Solution a;
    (void)a;

    const int expect = 6;
    vector<int> vec = { -2, 1, -3, 4, -1, 2, 1, -5, 4 };
    auto r = a.maxSubArray(vec);

    cout << "max = " << r << endl;
}

int main()
{

    Solution a;
    (void)a;

    testf({ -2, 1, -3, 4, -1, 2, 1, -5, 4 }, 6);

    testf({ -2, -1 }, -1);
    // 这个测试用例证明按照极小值分割左右求值 是错误的
    testf({ 31, -41, 59, 26, -53, 58, 97, -93, -23, 84 }, 187);

    std::cout << "main exit\n";
    return 0;
}

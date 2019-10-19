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

typedef struct SumArray {
    vector<int> a_;
    int sum_;

    SumArray()
        : sum_(0)
    {
    }

    void push_back(int val)
    {
        a_.push_back(val);
        sum_ += val;
    }

    int sum()
    {
        return sum_;
    }

    void clear()
    {
        a_.clear();
        sum_ = 0;
    }

    size_t size()
    {
        return a_.size();
    }


} SumArray;

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

        SumArray stk;

        // 始终保持 sum 一定是 >= 0 
        // num < 0 && sum + num >= 0 依旧是正激励
        // num < 0 && sum + num < 0 清空栈
        // num > 0 直接入栈
        for (auto num : nums) {
            if(num < 0 && stk.size() > 0) {
                // >=0 的数 + <0的数，一定要保存快照
                maxSums.push_back(stk.sum());
            }
            if(num < 0 && num + stk.sum() < 0) {
                // 不保存当前数，清空栈 
                // 留一下当前数到 maxSums
                maxSums.push_back(num);
                stk.clear();
                continue;
            } else {
                stk.push_back(num);
            }
        }
        if (stk.size() > 0) {
            maxSums.push_back(stk.sum());
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

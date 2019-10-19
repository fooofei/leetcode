#include <algorithm>
#include <array>
#include <bitset>
#include <iostream>
#include <limits>
#include <list>
#include <map>
#include <stack>
#include <string>
#include <vector>

using namespace std;

// https://leetcode-cn.com/problems/search-insert-position/

// 就是一个二分查找
// 注意：返回值
// 题目里看不出参数是否经过升序 还是 降序

bool bs_cmp(const int& target, const int& mid)
{
    return mid >= target;
}

class Solution {
public:
    int searchInsert(vector<int>& nums, int target)
    {
        auto found = upper_bound(nums.begin(), nums.end(), target, bs_cmp);
        if (found == nums.end()) {
            return (int)nums.size();
        }
        return (int)distance(nums.begin(), found);
    }
};

int main()
{

    Solution a;
    std::cout << "main exit\n";
    return 0;
}

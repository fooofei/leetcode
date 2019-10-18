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

// https://leetcode-cn.com/problems/climbing-stairs/

// 执行用时 :
// 0 ms
// , 在所有 cpp 提交中击败了
// 100.00%
// 的用户

// f(6) = 在 f(5) 的基础上，每个结果后面 +1
//   + 在 f(4) 的基础上，每个结果后面 +2 

class Solution {

    vector<int> cache_;

public:
    Solution()
    {
        cache_.push_back(0);
        cache_.push_back(1);
        cache_.push_back(2);
    }
    int climbStairs(int n)
    {

        if (n <= 0) {
            return 0;
        }

        if (n < (int)cache_.size()) {
            return cache_[n];
        }

        auto r = climbStairs(n - 1) + climbStairs(n - 2);
        if (n == cache_.size()) {
            cache_.push_back(r);
        }
        return r;
    }
};

int main()
{

    Solution a;
    (void)a;

    auto r = a.climbStairs(2);
    r = a.climbStairs(3);
    r = a.climbStairs(4);

    std::cout << "main exit\n";
    return 0;
}

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

// 069 https://leetcode-cn.com/problems/sqrtx/

// 难点：溢出
// 用除法不用乘法

class Solution {
public:
    int mySqrt1(int x)
    {
        if (x <= 0) {
            return 0;
        }
        int i = 1;
        for (;; i++) {

            if ((x / i) >= i && (x / (i + 1)) < (i + 1)) {
                break;
            }
        }
        return i;
    }

    int mySqrt(int x)
    {
        if (x <= 0) {
            return 0;
        }
        if (x == 1) {
            return 1;
        }

        int i = 1;
        int j = x;
        for (; i < j;) {
            int mid = (int)(((uint64_t)i + (uint64_t)j) / 2);

            // 难点：确立这样一个令序列成 F F F F T T T 的表达式
            // 然后就可以使用二分查找
            bool b = (x / mid) < mid;
            if (!b) {
                i = mid + 1;
            } else {
                j = mid;
            }
        }

        return i - 1;
    }
};

int main()
{

    Solution a;
    (void)a;

    // auto r = a.mySqrt(8);
    auto r = a.mySqrt1(2147483647);
    r = a.mySqrt(2147483647);
    // auto r = a.mySqrt(4);

    std::cout << "main exit\n";
    return 0;
}

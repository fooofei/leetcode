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

// 单调栈的解法代码复杂度好高啊还不直观
// 不如前遍历一次 后遍历一次 遍历2次解题快速
class Solution {
public:
    int minBullet(vector<int>& nums)
    {
        if (nums.size() <= 0) {
            return 0;
        }
        vector<int> indexStack;
        vector<int> bullets;
        bullets.resize(nums.size());
        indexStack.push_back(0);
        for (int i = 1; i < nums.size(); i++) {
            int index = indexStack.back();
            if (nums[index] <= nums[i]) {
                int bullet = max(1, bullets[index]);
                for (; indexStack.size() > 0;) {
                    int j = indexStack.back();
                    bullets[j] = max(bullet, bullets[j]);
                    indexStack.pop_back();
                    bullet += 1;
                }
                if (nums[index] < nums[i]) {
                    bullets[i] = bullets[index] + 1;
                } else {
                    bullets[i] = max(1, bullets[i]);
                }
            }
            indexStack.push_back(i);
        }

        int bullet = max(1, bullets[indexStack.back()]);
        for (; indexStack.size() > 0;) {
            int j = indexStack.back();
            bullets[j] = max(bullet, bullets[j]);
            indexStack.pop_back();
            bullet += 1;
        }

        int sum = 0;
        for (size_t i = 0; i < bullets.size(); i++) {
            sum += bullets[i];
        }
        return sum;
    }
};

void testf(vector<int> input, int resultCount)
{
    Solution sln;

    auto r = sln.minBullet(input);

    if (r == resultCount) {
        cout << "success " << endl;
    } else {
        cout << "fail " << endl;
    }
}

int main()
{

    Solution sln;
    (void)sln;

    testf({ 1 }, 1);
    testf({ 1, 0, 5 }, 5);

    testf({ 1, 2, 2 }, 4);

    testf({ 1, 0, 5, 7, 8, 7, 6, 4, 3, 3, 1 }, 26);

    std::cout << "main exit\n";
    return 0;
}

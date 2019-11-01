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

// 066 https://leetcode-cn.com/problems/plus-one/submissions/

// 数组中每个元素是 10 进制的一个位
// 额外存储进位

class Solution {
public:
    vector<int> plusOne(vector<int>& digits)
    {
        vector<int>::reverse_iterator it = digits.rbegin();
        vector<int> result;
        int high = 0;

        if (digits.size() == 0) {
            return result;
        }
        digits[digits.size() - 1] += 1;

        for (; it != digits.rend(); it++) {
            int v = (*it) + high;
            high = v / 10;
            v = v % 10;

            result.insert(result.begin(), v);
        }
        if (high != 0) {
            result.insert(result.begin(), high);
        }
        return result;
    }
};

int main()
{

    Solution a;
    (void)a;

    vector<int> vec1 = { 1, 2, 3 };
    vector<int> vec = { 9 };
    auto r = a.plusOne(vec);

    std::cout << "main exit\n";
    return 0;
}

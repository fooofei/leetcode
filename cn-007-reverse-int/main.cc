#include <algorithm>
#include <array>
#include <iostream>
#include <limits>
#include <string>
#include <vector>

using namespace std;

// 007 https://leetcode-cn.com/problems/reverse-integer/

// 看了官方的解之后，发现官方题目的意思是仅仅让使用 int 整型，不允许使用更大的整型

class Solution {
public:
    int reverse(int x)
    {
        int64_t num = x;

        bool sign = false;
        if (num < 0) {
            sign = true;
            num = -num;
        }
        std::string s;

        s = std::to_string(num);
        std::reverse(s.begin(), s.end());

        num = std::stoll(s);
        if (sign) {
            if (-num < std::numeric_limits<int>::min()) {
                return 0;
            }
            return (int)-num;

        } else {
            if (num > std::numeric_limits<int>::max()) {
                return 0;
            }
            return (int)num;
        }
    }
};

int main()
{

    Solution a;
    a.reverse(-2147483648);
    std::cout << "main exit\n";
    return 0;
}

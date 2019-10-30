#include <algorithm>
#include <array>
#include <iostream>
#include <limits>
#include <string>
#include <vector>

using namespace std;

// 009 https://leetcode-cn.com/problems/palindrome-number/

class Solution {
public:
    bool isPalindrome(int x)
    {

        if (x < 0) {
            return false;
        }

        if (x == 0) {
            return true;
        }
        if (x % 10 == 0) {
            return false;
        }

        uint64_t n = std::abs(x);

        std::string s = std::to_string(n);
        std::string rs(s);
        std::reverse(rs.begin(), rs.end());

        return s == rs;
    }
};

int main()
{

    Solution a;
    std::cout << "main exit\n";
    return 0;
}

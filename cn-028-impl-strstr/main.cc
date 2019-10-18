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

// https://leetcode-cn.com/problems/implement-strstr/


class Solution {
public:
    int strStr(string haystack, string needle)
    {
        size_t pos = haystack.find(needle);
        if (pos == string::npos) {
            return -1;
        }
        return (int)pos;
    }
};

int main()
{

    Solution a;
    std::cout << "main exit\n";
    return 0;
}

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

// https://leetcode-cn.com/problems/length-of-last-word/

class Solution {
public:
    int lengthOfLastWord(string s)
    {

        size_t wordEnd = s.find_last_not_of(" ");
        size_t wordBegin = s.find_last_of(" ", wordEnd);

        if (wordEnd < s.size()) {
            if (wordBegin < s.size()) {
                return wordEnd - wordBegin;
            }
            return wordEnd + 1; // 错误点： 漏考虑
        }
        return 0;
    }
};

void testf(string s, int expect)
{
    Solution a;

    auto r = a.lengthOfLastWord(s);
    std::cout << "result of \"" << s << "\" = " << r << "expect = " << expect << endl;
    ;
}

int main()
{

    Solution a;
    (void)a;

    testf("Hello World", 6);
    testf("Hello World ", 6);
    testf("   ", 0);
    testf("a", 1);
    testf("a ", 1);
    std::cout << "main exit\n";
    return 0;
}

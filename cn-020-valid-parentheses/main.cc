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

// 020 https://leetcode-cn.com/problems/valid-parentheses/
// 这个题目不清楚，没有说清楚 ()  {}  [] 之间是否有优先级关系
// 是否有嵌套关系
// 发现是有嵌套没优先级

int getRight(char left)
{
    switch (left) {
    case '(':
        return ')';
    case '{':
        return '}';
    case '[':
        return ']';
    default:
        return -1;
    }
}

class Solution {
public:
    bool isValid(string s)
    {
        if (s.empty()) {
            return true;
        }

        if (s.size() % 2 != 0) {
            return false;
        }

        stack<char> sk;

        for (size_t i = 0; i < s.size(); i++) {
            if (sk.size() > 0) {
                int right = getRight(sk.top());
                if (right == s[i]) {
                    sk.pop();
                } else {
                    sk.push(s[i]);
                }
            } else {
                sk.push(s[i]);
            }
        }
        return sk.size() == 0;
    }
};

int main()
{

    Solution a;
    // a.isValid("()");
    a.isValid("{{)}");
    std::cout << "main exit\n";
    return 0;
}

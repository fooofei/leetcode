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

#include <limits.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

using namespace std;

// 151 https://leetcode-cn.com/problems/reverse-words-in-a-string/

class Solution {
public:
    string reverseWords(string s)
    {
        vector<string> ss;

        s.push_back(' ');
        int first = -1;
        for (int i = 0; i < (int)s.size(); i++) {

            if (s[i] == ' ') {
                if (first > -1) {
                    ss.push_back(s.substr(first, i - first));
                    ss.push_back(" ");
                }
                first = -1;
            } else {
                if (first == -1) {
                    first = i;
                }
            }
        }

        string r;
        for (int i = (int)ss.size() - 2; i >= 0; i--) {
            r += ss[i];
        }
        return r;
    }
};

void test1()
{
    Solution sln;

    auto r = sln.reverseWords("  hello world!  ");
    printf("%s() %s\n", __func__, r.c_str());
}

int main()
{   
    test1();
    std::cout << "main exit\n";
    return 0;
}

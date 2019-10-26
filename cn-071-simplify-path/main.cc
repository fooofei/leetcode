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

// https://leetcode-cn.com/problems/simplify-path/

class Solution {
public:
    string simplifyPath(string path)
    {
        vector<string> paths;
        string name;
        int j;
        path += '/';
        for (int i = 0; i < path.size(); i++) {
            switch (path[i]) {
            case '/':
                if (name.size() > 0) {
                    paths.push_back(name);
                }
                name.clear();
                break;
            case '.':
                for (j = i + 1; j < path.size() && path[j] == '.'; j++) {
                }
                if (j - i == 2) {
                    paths.pop_back();
                    break;
                } else if (j - i > 2) {
                    for (int k = i; k < j; k++) {
                        name.push_back('.');
                    }
                }
                i = j - 1;
                break;
            default:
                name.push_back(path[i]);
                break;
            }
        }

        string s;
        for (auto p : paths) {
            s += '/';
            s += p;
        }
        if (s.size() == 0) {
            s += '/';
        }
        return s;
    }
};

void test2()
{
    Solution sln;

    auto r = sln.simplifyPath("/../");
    printf("%s\n", r.c_str());
}

void test1()
{
    Solution sln;

    auto r = sln.simplifyPath("/...");
    printf("%s\n", r.c_str());
}

int main()
{

    Solution sln;
    (void)sln;

    test1();
    test2();

    std::cout << "main exit\n";
    return 0;
}

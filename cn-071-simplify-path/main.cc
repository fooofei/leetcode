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
#include <stdlib.h>
#include <string>
#include <thread>
#include <time.h>
#include <vector>

using namespace std;

// https://leetcode-cn.com/problems/simplify-path/
// 这个题目简直模糊的要命

// 一定要强调 ../ 才是向上 ..abc 不可以向上

class Solution {
public:
    string simplifyPath(string path)
    {
        vector<string> paths;
        vector<string> names; // `/` 分割的名字们

        string name;
        path += '/';
        for (int i = 0; i < (int)path.size(); i++) {

            if (path[i] == '/') {
                if (name.size() > 0) {
                    names.push_back(name);
                }
                name.clear();
            } else {
                name.push_back(path[i]);
            }
        }

        for (int i = 0; i < (int)names.size(); i++) {

            if (names[i] == "..") {
                if (paths.size() > 0) {
                    paths.pop_back();
                }
            } else if (names[i] == ".") {

            } else {
                paths.push_back(names[i]);
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

void test3()
{
    Solution sln;

    auto r = sln.simplifyPath("/...");
    printf("%s\n", r.c_str());
}

void test1()
{
    Solution sln;

    auto r = sln.simplifyPath("/..hidden");
    printf("%s\n", r.c_str());
}

int main()
{

    Solution sln;
    (void)sln;

    test1();

    std::cout << "main exit\n";
    return 0;
}

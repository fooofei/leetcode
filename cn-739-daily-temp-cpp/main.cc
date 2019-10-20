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

// https://leetcode-cn.com/problems/daily-temperatures/

class Solution {
public:
    vector<int> dailyTemperatures(vector<int>& T)
    {
        vector<int> indexStack;
        vector<int> days;
        days.resize(T.size());

        for (int i = 0; i < T.size(); i++) {
            for (; indexStack.size() > 0 && T[i] > T[indexStack.back()];) {
                days[indexStack.back()] = i - indexStack.back();
                indexStack.pop_back();
            }
            indexStack.push_back(i);
        }
        // 因为是 0 也可以不用再次赋值
        for (; indexStack.size() > 0;) {
            days[indexStack.back()] = 0;
            indexStack.pop_back();
        }
        return days;
    }
};

int main()
{

    Solution sln;
    (void)sln;

    std::cout << "main exit\n";
    return 0;
}

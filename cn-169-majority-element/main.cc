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

// 169  https://leetcode-cn.com/problems/majority-element/

class Solution {
public:
    int majorityElement(vector<int>& nums)
    {
        if (nums.size() <= 0) {
            return 0;
        }
        sort(nums.begin(), nums.end());

        int num = nums[0];
        int count = 1;
        for (int i = 1; i < nums.size(); i++) {
            if (nums[i] == num) {
                count++;
            } else {
                if (count > nums.size() / 2) {
                    return num;
                }
                num = nums[i];
                count = 1;
            }
        }
        if(count > nums.size()/2) {
            return num;
        }
        return 0;
    }
};

void test1()
{
    Solution sln;
    vector<int> vec = {3, 2 ,3};
    auto r = sln.majorityElement(vec);
    printf("%d\n", r);
}


int main()
{
    test1();
    std::cout << "main exit\n";
    return 0;
}

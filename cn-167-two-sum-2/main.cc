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

#include <stdarg.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

using namespace std;

// 167 https://leetcode-cn.com/problems/two-sum-ii-input-array-is-sorted/

class Solution {
public:
    vector<int> twoSum(vector<int>& numbers, int target)
    {
        vector<int> indexs;

        if(numbers.size() < 2) {
            return indexs;
        }

        int i = 0;
        int j = numbers.size()-1;

        for(;i<j;) {

            if(numbers[i] + numbers[j] > target) {
                j--;
            } else if (numbers[i] + numbers[j] < target) {
                i++;
            } else {
                indexs.push_back(i+1);
                indexs.push_back(j+1);
                return indexs;
            }

        }

        return indexs;

    }
};


void test1()
{

}

int main()
{
    test1();
    return 0;
}

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


// 409 https://leetcode-cn.com/problems/longest-palindrome/

class Solution {
public:
    int longestPalindrome(string s) {
        vector<int> counts;
        counts.resize(0x100, 0);
        for(auto c:s) {
            counts[(uint8_t)(c)] += 1;
        }
        
        int ret = 0;
        int oddMax = 0;
        
        for(auto c:counts) {
            if(c%2 == 0) {
                ret += c;
            } else {
                ret += c-1;
                oddMax = max(oddMax, c);
            }
        }
        if(oddMax >0) {
           ret += 1; 
        }
        return ret;
    }
};

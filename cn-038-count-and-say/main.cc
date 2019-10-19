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

// https://leetcode-cn.com/problems/count-and-say/

class Solution {
public:
    map<int, string> cache;

    // 递归的解法
    // :read 
    // :num 表示 在 num 时 读 read
    // :return 求 num +1 
    string say(string read, int num, int maxNum)
    {
        string s;

        int count = 1;
        char cursorNum = read[0];

        auto found = cache.find(maxNum);
        if (found != cache.end()) {
            return found->second;
        }
        for (size_t i = 1; i < read.size(); i++) {

            if (read[i] == cursorNum) {
                count += 1;
            } else {
                s.append(to_string(count));
                s.append(1, cursorNum);
                count = 1;
                cursorNum = read[i];
            }
        }
        s.append(to_string(count));
        s.append(1, cursorNum);
        num += 1;
        if (num < maxNum) {
            return say(s, num, maxNum);
        }
        cache[num] = s;
        return s;
    }

    string countAndSay(int n)
    {
        cache[1] = "1";
        return say("1", 1, n);
    }

    // 曾经写的非递归的方法
    string countAndSay1(int n)
    {
        int start = 1;
        string numString("1");
        int64_t num = 0;

        auto found = cache.find(n);
        if (found != cache.end()) {
            return found->second;
        }

        for (; start < n; start++) {

            found = cache.find(start);
            if (found != cache.end()) {
                numString = found->second;
                continue;
            }
            // not found

            int count = 1;
            char cursorNum = numString[0];
            string tmpString;

            for (size_t i = 1; i < numString.size(); i++) {

                if (numString[i] == cursorNum) {
                    count += 1;
                } else {
                    tmpString.append(to_string(count));
                    tmpString.append(1, cursorNum);
                    count = 1;
                    cursorNum = numString[i];
                }
            }

            tmpString.append(to_string(count));
            tmpString.append(1, cursorNum);
            numString = tmpString;

            cache[start] = numString;
        }

        return numString;
    }
};

int main()
{

    Solution a;
    auto r = a.countAndSay(1);
    cout << "1= " << r << endl;

    r = a.countAndSay(2);
    cout << "2= " << r << endl;

    r = a.countAndSay(3);
    cout << "3= " << r << endl;

    r = a.countAndSay(4);
    cout << "4= " << r << endl;

    r = a.countAndSay(5);
    cout << "5= " << r << endl;
    std::cout << "main exit\n";
    return 0;
}

#include <algorithm>
#include <array>
#include <bitset>
#include <iostream>
#include <limits>
#include <map>
#include <string>
#include <vector>

using namespace std;

// https://leetcode-cn.com/problems/roman-to-integer/

map<char, int> getRomanMap()
{
    map<char, int> r;
    r['I'] = 1;
    r['V'] = 5;
    r['X'] = 10;
    r['L'] = 50;
    r['C'] = 100;
    r['D'] = 500;
    r['M'] = 1000;
    return r;
}

int peek(const string& s, size_t i)
{
    if (i >= s.size()) {
        return -1;
    }
    return s[i];
}

class Solution {
public:
    int romanToInt(string s)
    {
        int value = 0;
        map<char, int> roman = getRomanMap();

        for (size_t i = 0; i < s.size();) {

            switch (s[i]) {
            case 'I':
                if (peek(s, i + 1) == 'V') {
                    value += 4;
                    i += 2;
                    break;
                } else if (peek(s, i + 1) == 'X') {
                    value += 9;
                    i += 2;
                    break;
                }
                // fall
            case 'X':
                if (peek(s, i + 1) == 'L') {
                    value += 40;
                    i += 2;
                    break;
                } else if (peek(s, i + 1) == 'C') {
                    value += 90;
                    i += 2;
                    break;
                }
                // fall
            case 'C':
                if (peek(s, i + 1) == 'D') {
                    value += 400;
                    i += 2;
                    break;
                } else if (peek(s, i + 1) == 'M') {
                    value += 900;
                    i += 2;
                    break;
                }
                // fall
            default:
                auto f = roman.find(s[i]);
                if (f != roman.end()) {
                    value += f->second;
                }
                i += 1;
            }
        }

        return value;
    }
};

int main()
{

    Solution a;
    a.romanToInt("MCMXCIV");
    std::cout << "main exit\n";
    return 0;
}

#include <algorithm>
#include <array>
#include <bitset>
#include <iostream>
#include <limits>
#include <list>
#include <map>
#include <string>
#include <vector>

using namespace std;

// 014 https://leetcode-cn.com/problems/longest-common-prefix/

class Solution {
public:
    string longestCommonPrefix(vector<string>& strs)
    {

        string prefix;

        if (strs.size() == 0) {
            return prefix;
        }

        if (strs.size() == 1) {
            return strs[0];
        }

        const string& pat = strs[0];

        for (size_t i = 0; i < pat.size(); i++) {

            for (size_t j = 1; j < strs.size(); j++) {
                if (i >= strs[j].size()) {
                    return prefix;
                }
                if (strs[j][i] != pat[i]) {
                    return prefix;
                }
            }
            prefix.append(1, pat[i]);
        }

        return prefix;
    }
};

int main()
{

    Solution a;
    vector<string> strs;
    strs.push_back("flower");
    strs.push_back("flow");
    strs.push_back("flight");
    a.longestCommonPrefix(strs);
    std::cout << "main exit\n";
    return 0;
}

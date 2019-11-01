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

// 067 https://leetcode-cn.com/problems/add-binary/

class Solution {
public:
    void largest(const string& str, string& result, int minSize, int* shift)
    {
        for (size_t i = minSize; i < str.size(); i++) {
            size_t j = str.size() - i - 1;
            int v = str[j] - '0';
            v += (*shift);
            (*shift) = v / 2;
            v = v % 2;
            result.insert(result.begin(), char(v + '0'));
        }
    }

    string addBinary(string a, string b)
    {

        size_t minSize = min(a.size(), b.size());
        int shift = 0;
        string result;

        for (size_t i = 0; i < minSize; i++) {

            int v = 0;
            // 错误点
            v += a[a.size() - i - 1] - '0';
            v += b[b.size() - i - 1] - '0';
            v += shift;

            shift = v / 2;
            v = v % 2;
            result.insert(result.begin(), char(v + '0'));
        }

        largest(a, result, minSize, &shift);
        largest(b, result, minSize, &shift);

        if (shift != 0) {
            result.insert(result.begin(), char(shift + '0'));
        }

        return result;
    }
};

int main()
{

    Solution a;
    (void)a;

    // auto r = a.addBinary("11", "1");
    // auto r = a.addBinary("1010", "1011");
    auto r = a.addBinary("100", "110010");

    std::cout << "main exit\n";
    return 0;
}

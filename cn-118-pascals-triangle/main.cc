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

// https://leetcode-cn.com/problems/pascals-triangle/

class Solution {
public:
    vector<vector<int>> generate(int numRows)
    {
        vector<vector<int>> triangle;
        triangle.reserve(numRows);

        if (numRows >= 1) {
            triangle.push_back({ 1 });
        }
        if (numRows >= 2) {
            triangle.push_back({ 1, 1 });
        }

        if (numRows > 2) {
            for (int i = 3; i <= numRows; i++) {
                vector<int> row;
                const vector<int>& prevRow = triangle[i - 1 - 1];
                row.resize(i, 1);
                for (int j = 1; j < i - 1; j++) {
                    row[j] = prevRow[j - 1] + prevRow[j];
                }
                triangle.push_back(row);
            }
        }
        return triangle;
    }
};

void test1()
{
    Solution sln;

    auto r = sln.generate(3);
}

void test2()
{
    Solution sln;
    auto r = sln.generate(4);
}

int main()
{
    test2();

    std::cout << "main exit\n";
    return 0;
}

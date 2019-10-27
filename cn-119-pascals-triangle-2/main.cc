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

// https://leetcode-cn.com/problems/pascals-triangle-ii/

class Solution {
public:
    Solution()
    {
        cache_.push_back({ 1 });
        cache_.push_back({ 1, 1 });
    }
    ~Solution()
    {
    }
    vector<int> getRow(int rowIndex)
    {
        if (rowIndex < cache_.size()) {
            return cache_[rowIndex];
        }

        vector<int> prevRow = getRow(rowIndex - 1);
        vector<int> triangle;
        triangle.resize(rowIndex + 1, 1);

        for (int i = 1; i < rowIndex + 1 - 1; i++) {
            triangle[i] = prevRow[i - 1] + prevRow[i];
        }

        if (rowIndex == cache_.size()) {
            cache_.push_back(triangle);
        }
        return triangle;
    }

private:
    vector<vector<int>> cache_;
};

void test1()
{
    Solution sln;

    auto r = sln.getRow(3);
}

int main()
{
    test1();
    std::cout << "main exit\n";
    return 0;
}


/* 

def getRow(rowIndex):
    # j行的数据, 应该由j - 1行的数据计算出来.
    # 假设j - 1行为[1,3,3,1], 那么我们前面插入一个0(j行的数据会比j-1行多一个),
    # 然后执行相加[0+1,1+3,3+3,3+1,1] = [1,4,6,4,1], 最后一个1保留即可.
    r = [1]
    for i in range(1, rowIndex + 1):
        r.insert(0, 0)
        # 因为i行的数据长度为i+1, 所以j+1不会越界, 并且最后一个1不会被修改.
        for j in range(i):
            r[j] = r[j] + r[j + 1]
    return r

print(getRow(5))

作者：leicj
链接：https://leetcode-cn.com/problems/pascals-triangle-ii/solution/python3-yang-hui-san-jiao-ii-by-leicj/
*/

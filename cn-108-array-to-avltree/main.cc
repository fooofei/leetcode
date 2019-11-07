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

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x)
        : val(x)
        , left(NULL)
        , right(NULL)
    {
    }
};

using TreeNode = struct TreeNode;

// 108 https://leetcode-cn.com/problems/convert-sorted-array-to-binary-search-tree/

// 这道题有毛病啊， 我理解的是，只要生成的二叉树 左右子树满足 高度差绝对值不超过 1 就行了
// 但是不通过
// 写一个平衡二叉树插入的算法 然后遍历数组插入，插入的时候不平衡就旋转
// 这样的解题思路，不通过，因为解有多个，求得的不一定跟测试用例预期结果一致
// 测试用例的输出结果是按照递归来做的

// 执行用时 :
// 24 ms
// , 在所有 cpp 提交中击败了
// 81.72%
// 的用户

TreeNode* build(const vector<int>& nums, int first, int last)
{

    if (first >= last) {
        return NULL;
    }

    int mid = (int)(((uint64_t)first + (uint64_t)last) / 2);
    TreeNode* n = new TreeNode(nums[mid]);

    n->left = build(nums, first, mid);
    n->right = build(nums, mid + 1, last);
    return n;
}

class Solution {
public:
    TreeNode* sortedArrayToBST(vector<int>& nums)
    {
        if (nums.size() <= 0) {
            return NULL;
        }
        return build(nums, 0, nums.size());
    }
};

int main()
{

    Solution sln;
    (void)sln;

    std::cout << "main exit\n";
    return 0;
}

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

// https://leetcode-cn.com/problems/balanced-binary-tree/


// 执行用时 :
// 16 ms
// , 在所有 cpp 提交中击败了
// 85.15%
// 的用户

int treeDepth(TreeNode* n, bool* balance)
{
    if (n == NULL) {
        return 0;
    }

    int left = treeDepth(n->left, balance);
    int right = treeDepth(n->right, balance);

    if (abs(left - right) > 1) {
        *balance = false;
    }
    return max(left, right) + 1;
}

class Solution {
public:
    bool isBalanced(TreeNode* root)
    {
        bool b = true;
        treeDepth(root, &b);
        return b;
    }
};

int main()
{

    Solution sln;
    (void)sln;

    std::cout << "main exit\n";
    return 0;
}

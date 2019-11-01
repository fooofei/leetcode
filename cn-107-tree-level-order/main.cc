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

// 107 https://leetcode-cn.com/problems/binary-tree-level-order-traversal-ii/

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

// 执行用时 :
// 4 ms
// , 在所有 cpp 提交中击败了
// 97.48%
// 的用户

void traverse(const vector<TreeNode*>& childs, vector<vector<int>>& vals)
{
    if (childs.size() <= 0) {
        return;
    }

    vector<TreeNode*> childs2;

    for (size_t i = 0; i < childs.size(); i++) {
        TreeNode* n = childs[i];
        if (n->left) {
            childs2.push_back(n->left);
        }
        if (n->right) {
            childs2.push_back(n->right);
        }
    }

    traverse(childs2, vals);

    vector<int> vals1;
    for (size_t i = 0; i < childs.size(); i++) {
        TreeNode* n = childs[i];
        vals1.push_back(n->val);
    }

    vals.push_back(vals1);
}

class Solution {
public:
    vector<vector<int>> levelOrderBottom(TreeNode* root)
    {
        vector<vector<int>> vals;

        if (root == NULL) {
            return vals;
        }

        vector<TreeNode*> childs;
        childs.push_back(root);
        traverse(childs, vals);
        return vals;
    }
};

int main()
{

    Solution sln;
    (void)sln;

    std::cout << "main exit\n";
    return 0;
}

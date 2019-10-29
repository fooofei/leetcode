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

// https://leetcode-cn.com/problems/minimum-depth-of-binary-tree/

// 执行用时 :
// 8 ms
// , 在所有 cpp 提交中击败了
// 98.58%
// 的用户

void levelTreeDepth(const vector<TreeNode*>& childs, int* depth)
{

    vector<TreeNode*> childs2;

    *depth += 1;

    for (size_t i = 0; i < childs.size(); i++) {
        TreeNode* n = childs[i];

        if (n->left == NULL && n->right == NULL) {
            return;
        }
        if (n->left) {
            childs2.push_back(n->left);
        }
        if (n->right) {
            childs2.push_back(n->right);
        }
    }

    levelTreeDepth(childs2, depth);
}

class Solution {
public:
    int minDepth(TreeNode* root)
    {

        int dep = 0;
        if (root == NULL) {
            return 0;
        }
        vector<TreeNode*> childs;
        childs.push_back(root);
        levelTreeDepth(childs, &dep);
        return dep;
    }
};

int main()
{

    Solution sln;
    (void)sln;

    std::cout << "main exit\n";
    return 0;
}

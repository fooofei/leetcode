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

// https://leetcode-cn.com/problems/path-sum-ii/

// 执行用时 :
// 16 ms
// , 在所有 cpp 提交中击败了
// 90.79%
// 的用户

void sumEqual(TreeNode* n, vector<TreeNode*>& parents, int expectVal, vector<vector<int>>& paths)
{
    if (n->left == NULL && n->right == NULL) {
        if (expectVal == n->val) {
            vector<int> vec;
            for (auto it : parents) {
                vec.push_back(it->val);
            }
            vec.push_back(n->val);
            paths.push_back(vec);
        }
        return;
    }

    parents.push_back(n);
    if (n->left) {
        sumEqual(n->left, parents, expectVal - n->val, paths);
    }
    if (n->right) {
        sumEqual(n->right, parents, expectVal - n->val, paths);
    }
    parents.pop_back();
}

class Solution {
public:
    vector<vector<int>> pathSum(TreeNode* root, int sum)
    {
        vector<vector<int>> paths;

        if (root == NULL) {
            return paths;
        }
        vector<TreeNode*> parents;
        sumEqual(root, parents, sum, paths);
        return paths;
    }
};

void test1()
{
    TreeNode* n1 = new TreeNode(1);
    TreeNode* n2 = new TreeNode(2);
    TreeNode* n40 = new TreeNode(4);
    TreeNode* n41 = new TreeNode(4);
    TreeNode* n5 = new TreeNode(5);
    TreeNode* n7 = new TreeNode(7);
    TreeNode* n8 = new TreeNode(8);
    TreeNode* n11 = new TreeNode(11);
    TreeNode* n13 = new TreeNode(13);

    n11->left = n7;
    n11->right = n2;
    n41->right = n1;

    n40->left = n11;
    n8->left = n13;
    n8->right = n41;

    n5->left = n40;
    n5->right = n8;

    Solution sln;
    (void)sln;
    sln.hasPathSum(n5, 22);
}

int main()
{

    Solution sln;
    (void)sln;

    test1();

    std::cout << "main exit\n";
    return 0;
}

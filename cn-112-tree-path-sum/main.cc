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

// 112 https://leetcode-cn.com/problems/path-sum/

// 执行用时 :
// 64 ms
// , 在所有 cpp 提交中击败了
// 7.75%
// 的用户

bool sumEqual(TreeNode* n, int parentsSum, const int expectSum)
{
    if (n->left == NULL && n->right == NULL) {
        int sum = parentsSum + n->val;
        if (sum == expectSum) {
            return true;
        }
        return false;
    }

    bool b = false;
    parentsSum += n->val;
    if (n->left) {
        b = sumEqual(n->left, parentsSum, expectSum);
    }
    if (b) {
        return b;
    }
    if (n->right) {
        b = sumEqual(n->right, parentsSum, expectSum);
    }
    parentsSum -= n->val;
    return b;
}

class Solution {
public:
    bool hasPathSum(TreeNode* root, int sum)
    {
        if (root == NULL) {
            // 错误点
            return false;
        }
        return sumEqual(root, 0, sum);
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

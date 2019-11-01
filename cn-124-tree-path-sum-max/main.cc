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

// 124 https://leetcode-cn.com/problems/binary-tree-maximum-path-sum/

// 太难想了
// 曾经想过 

string formatv(string fmt, ...)
{
    va_list ap0;
    va_list ap1;

    va_start(ap0, fmt);
    va_copy(ap1, ap0);
    int size = (int)vsnprintf(NULL, 0, fmt.c_str(), ap0);
    va_end(ap0);
    if (size <= 0) {
        return "";
    }
    size += 1;

    vector<char> vec;
    vec.resize(size);

    size = vsnprintf(&vec[0], size, fmt.c_str(), ap1);
    va_end(ap1);
    if (size <= 0) {
        return "";
    }
    return string(&vec[0], size);
}

int pathSum(TreeNode* n, int* maxSum)
{
    if (n == NULL) {
        return 0;
    }

    int left = max(0, pathSum(n->left, maxSum));
    int right = max(0, pathSum(n->right, maxSum));

    int leftAndRight = n->val + max(0, left) + max(0, right);
    int leftOrRight = n->val + max(0, max(left, right));

    *maxSum = max(*maxSum, max(leftAndRight, leftOrRight));
    return leftOrRight;
}

class Solution {
public:
    int maxPathSum(TreeNode* root)
    {
        if (root == NULL) {
            return 0;
        }
        // 难点 无法给 maxSum 一个非法值
        int maxSum = INT32_MIN;

        pathSum(root, &maxSum);
        return maxSum;
    }
};

void test1()
{
    Solution sln;

    // 我是运行了 才知道不一定要到达叶子结点 ，这个题目说的太不清晰了
    TreeNode* n2 = new TreeNode(2);

    TreeNode* n11 = new TreeNode(-1);

    n2->left = n11;

    auto r = sln.maxPathSum(n2);
    if (r != 2) {
        printf("%s fail\n", __func__);
    }
}

void test2()
{
    Solution sln;

    TreeNode* n2 = new TreeNode(2);
    TreeNode* n1 = new TreeNode(1);
    TreeNode* n3 = new TreeNode(3);

    n1->left = n2;
    n1->right = n3;

    auto r = sln.maxPathSum(n1);
    if (r != 6) {
        printf("%s fail\n", __func__);
    }
}

void test3()
{
    Solution sln;

    TreeNode* n1 = new TreeNode(-10);
    TreeNode* n2 = new TreeNode(9);
    TreeNode* n3 = new TreeNode(20);
    TreeNode* n4 = new TreeNode(15);
    TreeNode* n5 = new TreeNode(7);

    n1->left = n2;
    n1->right = n3;

    n3->left = n4;
    n3->right = n5;

    auto r = sln.maxPathSum(n1);
    if (r != 42) {
        printf("%s fail\n", __func__);
    }
}

void test4()
{
    Solution sln;

    TreeNode* n1 = new TreeNode(5);
    TreeNode* n2 = new TreeNode(4);
    TreeNode* n3 = new TreeNode(8);
    TreeNode* n4 = new TreeNode(11);
    TreeNode* n5 = new TreeNode(13);
    TreeNode* n6 = new TreeNode(4);
    TreeNode* n7 = new TreeNode(7);
    TreeNode* n8 = new TreeNode(2);
    TreeNode* n9 = new TreeNode(1);

    n1->left = n2;
    n1->right = n3;

    n2->left = n4;
    n3->left = n5;
    n3->right = n6;

    n4->left = n7;
    n4->right = n8;
    n6->left = n9;

    auto r = sln.maxPathSum(n1);
    if (r != 48) {
        printf("%s fail\n", __func__);
    }
}

int main()
{

    Solution sln;
    (void)sln;

    test4();
    

    std::cout << "main exit\n";
    return 0;
}

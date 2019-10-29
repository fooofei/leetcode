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

// https://leetcode-cn.com/problems/symmetric-tree/


// 执行用时 :
// 16 ms
// , 在所有 cpp 提交中击败了
// 14.82%
// 的用户


// 一开始的错误想法 把整个 tree 平坦化，成为 1 个数组，
// 然后找规律  [1,2,2,3,4,4,3] 按照 1 2 4 8 步进 区间内是回文数
// 发现无法排除 [1,2,2,null,3,null,3] 的情况
// 所以改进方案是必须存储 空结点，但是为了区分空结点 的值，不能定 -1，
// 那就改使用 string， 空结点是 null 好了

class Solution {

    // 左序遍历一次 右序遍历一次

    // 把二叉树存储到数组上，平坦化，广度优先
    void treeLeftToArray(TreeNode* n, vector<string>& vec)
    {
        if (n == NULL) {
            vec.push_back("null");
            return;
        }

        vec.push_back(to_string(n->val));

        treeLeftToArray(n->left, vec);
        treeLeftToArray(n->right, vec);
    }

    void treeRightToArray(TreeNode* n, vector<string>& vec)
    {
        if (n == NULL) {
            vec.push_back("null");
            return;
        }

        vec.push_back(to_string(n->val));
        treeRightToArray(n->right, vec);
        treeRightToArray(n->left, vec);
    }

public:
    bool isSymmetric(TreeNode* root)
    {
        // 先搞成数组
        vector<string> vecLeft;
        vector<string> vecRight;

        // 错误点
        if (root == NULL) {
            return true;
        }
        treeLeftToArray(root->left, vecLeft);
        treeRightToArray(root->right, vecRight);

        if (vecLeft.size() != vecRight.size()) {
            return false;
        }

        for (size_t i = 0; i < vecRight.size(); i++) {
            if (vecLeft[i] != vecRight[i]) {
                return false;
            }
        }
        return true;
    }
};

void test1()
{
    Solution sln;
    (void)sln;

    TreeNode* n1 = new TreeNode(3);
    TreeNode* n2 = new TreeNode(4);
    TreeNode* n3 = new TreeNode(4);
    TreeNode* n4 = new TreeNode(3);

    TreeNode* n5 = new TreeNode(2);
    TreeNode* n6 = new TreeNode(2);
    TreeNode* n7 = new TreeNode(1);

    n5->left = n1;
    n5->right = n2;
    n6->left = n3;
    n6->right = n4;
    n7->left = n5;
    n7->right = n6;

    sln.isSymmetric(n7);
}

void test2()
{
    Solution sln;
    (void)sln;

    TreeNode* n1 = new TreeNode(3);
    TreeNode* n4 = new TreeNode(3);

    TreeNode* n5 = new TreeNode(2);
    TreeNode* n6 = new TreeNode(2);
    TreeNode* n7 = new TreeNode(1);

    n5->right = n1;
    n6->right = n4;
    n7->left = n5;
    n7->right = n6;

    sln.isSymmetric(n7);
}

int main()
{

    Solution sln;
    (void)sln;

    test2();

    std::cout << "main exit\n";
    return 0;
}

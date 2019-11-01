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

// 104 https://leetcode-cn.com/problems/maximum-depth-of-binary-tree/

// 执行用时 :
// 20 ms
// , 在所有 cpp 提交中击败了
// 36.54%
// 的用户
// 内存消耗 :
// 19.9 MB
// , 在所有 cpp 提交中击败了
// 5.08%
// 的用户


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

void depth(const vector<TreeNode*>& childs, int* dep)
{
    if (childs.size() == 0) {
        return;
    }
    *dep += 1;

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

    depth(childs2, dep);
}

class Solution {
public:
    int maxDepth(TreeNode* root)
    {
        int dep = 0;
        vector<TreeNode*> vec;
        if (root == 0) {
            return 0;
        }
        vec.push_back(root);
        depth(vec, &dep);
        return dep;
    }
};

void test1()
{
    Solution sln;
    (void)sln;

    TreeNode* n1 = new TreeNode(3);
    TreeNode* n2 = new TreeNode(9);
    TreeNode* n3 = new TreeNode(20);
    TreeNode* n4 = new TreeNode(15);
    TreeNode* n5 = new TreeNode(7);

    n1->left = n2;
    n1->right = n3;

    n3->left = n4;
    n3->right = n5;

    sln.maxDepth(n1);
}

int main()
{

    Solution sln;
    (void)sln;

    test1();

    std::cout << "main exit\n";
    return 0;
}

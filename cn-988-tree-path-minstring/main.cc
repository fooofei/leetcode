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

// https://leetcode-cn.com/problems/smallest-string-starting-from-leaf/

string formatv(string fmt, ...)
{
    va_list ap0;
    va_list ap1;

    va_start(ap0, fmt);
    va_copy(ap1, ap0);
    int size = (int)vsnprintf(NULL, 0, fmt.c_str(), ap0);
    va_end(ap0);
    if (size <= 0) {
        va_end(ap1);
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

void enumPaths(TreeNode* n, list<TreeNode*>& parents, list<string>& pathStrs)
{
    if (n->left == NULL && n->right == NULL) {
        string s;
        for (auto it : parents) {
            char c = 'a' + it->val;
            s += c;
        }
        char c = 'a' + n->val;
        s += c;
        reverse(s.begin(), s.end());
        pathStrs.push_back(s);

        return;
    }

    parents.push_back(n);
    if (n->left != NULL) {
        enumPaths(n->left, parents, pathStrs);
    }
    if (n->right) {
        enumPaths(n->right, parents, pathStrs);
    }

    parents.pop_back();
}


class Solution {
public:
    string smallestFromLeaf(TreeNode* root)
    {
        if (root == NULL) {
            return "";
        }
        list<string> pathStrs;
        list<TreeNode*> parents;
        enumPaths(root, parents, pathStrs);

        // list 自己的排序使用字典序 std::sort 不能对 list 排序
        pathStrs.sort();
        return pathStrs.front();
    }
};

void test1()
{
    Solution sln;

    TreeNode* n1 = new TreeNode(1);
    TreeNode* n3 = new TreeNode(3);
    TreeNode* n0 = new TreeNode(0);
    TreeNode* n2 = new TreeNode(2);

    TreeNode* n11 = new TreeNode(1);
    TreeNode* n31 = new TreeNode(3);

    TreeNode* n25 = new TreeNode(25);

    n25->left = n11;
    n25->right = n31;

    n11->left = n1;
    n11->right = n3;

    n31->left = n0;
    n31->left = n2;

    sln.smallestFromLeaf(n25);
}

int main()
{

    Solution sln;
    (void)sln;

    test1();

    std::cout << "main exit\n";
    return 0;
}

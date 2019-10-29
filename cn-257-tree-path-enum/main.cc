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

// https://leetcode-cn.com/problems/binary-tree-paths/

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

void enumPaths(TreeNode* n, list<TreeNode*>& parents, vector<string>& paths)
{
    if (n->left == NULL && n->right == NULL) {
        string s;
        for (auto it : parents) {
            s += formatv("%d->", it->val);
        }
        s += formatv("%d", n->val);
        paths.push_back(s);
        return;
    }

    parents.push_back(n);

    if (n->left) {
        enumPaths(n->left, parents, paths);
    }

    if (n->right) {
        enumPaths(n->right, parents, paths);
    }

    parents.pop_back();
}

class Solution {
public:
    vector<string> binaryTreePaths(TreeNode* root)
    {

        vector<string> paths;

        if (root == NULL) {
            return paths;
        }

        list<TreeNode*> parents;

        enumPaths(root, parents, paths);
        return paths;
    }
};

int main()
{

    Solution sln;
    (void)sln;

    std::cout << "main exit\n";
    return 0;
}

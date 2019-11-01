#include <algorithm>
#include <array>
#include <bitset>
#include <chrono>
#include <iostream>
#include <limits>
#include <list>
#include <map>
#include <stack>
#include <string>
#include <thread>
#include <vector>

using namespace std;

// 100 https://leetcode-cn.com/problems/same-tree/

typedef struct TreeNode TreeNode;

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

class Solution {
public:
    bool isSameTree(TreeNode* p, TreeNode* q)
    {

        if (p == NULL && q == NULL) {
            return true;
        }
        if (p == NULL) {
            return false;
        }
        if (q == NULL) {
            return false;
        }

        if (p->val != q->val) {
            return false;
        }

        bool b;
        b = isSameTree(p->left, q->left);
        if (!b) {
            return false;
        }
        b = isSameTree(p->right, q->right);
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

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

struct Node {
    int value;
    int height;
    struct Node* left;
    struct Node* right;
    struct Node* parent;

    Node(int v)
        : value(v)
        , height(1)
        , left(NULL)
        , right(NULL)
        , parent(NULL)
    {
    }
};
using Node = struct Node;

Node* leftRotate(Node* x);
Node* rightRotate(Node* x);

void treeInsert(Node* n, Node* new_)
{
    Node* root = n;
    for (; n;) {
        if (new_->value > n->value) {
            if (n->right == NULL) {
                break;
            }
            n = n->right;
        } else if (new_->value < n->value) {
            if (n->left == NULL) {
                break;
            }
            n = n->left;
        }
    }

    if (n == NULL) {
        return;
    }

    if (new_->value >= n->value) {
        n->right = new_;
        new_->parent = n;
    } else {
        n->left = new_;
        new_->parent = n;
    }
    // 需要刷新高度
    for (; n;) {
        int left = 0;
        int right = 0;
        if (n->left) {
            left = n->left->height;
        }
        if (n->right) {
            right = n->right->height;
        }
        int height = max(left, right) + 1;
        // 不需要向上刷新了
        if (height == n->height) {
            break;
        }
        n->height = height;
        if (left > right && left - right > 1) {
            rightRotate(n);
        } else if (right > left && right - left > 1) {
            leftRotate(n);
        }
        n = n->parent;
    }

    // banlance
}

/*
	   x
	  /
	 y
	/
   z


	y
   / \
  z   x

*/

Node* rightRotate(Node* x)
{
    Node* y = x->left;
    x->left = y->right;
    y->right = x;
    return y;
}

Node* leftRotate(Node* x)
{
    Node* y = x->right;
    x->right = y->left;
    y->left = x;
    return y;
}

void levelOrderWithNull(const vector<Node*>& childs, vector<string>& vals)
{
    vector<Node*> childs2;

    bool haveChilds = false;
    for (auto it : childs) {
        vals.push_back(to_string(it->value));
        if (it->left || it->right) {
            haveChilds = true;
        }
    }

    if (haveChilds) {
        for (auto it : childs) {
            if (it->left) {
                childs2.push_back(it->left);
            } else {
                childs2.push_back(new Node(-10000));
            }

            if (it->right) {
                childs2.push_back(it->right);
            } else {
                childs2.push_back(new Node(-10000));
            }
        }
        levelOrderWithNull(childs2, vals);
    }
}

void test1()
{
    vector<int> vec = { -3, 0, 5, 9 };

    Node* root = new Node(-10);

    for (auto it : vec) {
        Node* n = new Node(it);
        treeInsert(root, n);
    }
    vector<string> vals;
    vector<Node*> childs;
    childs.push_back(root);
    levelOrderWithNull(childs, vals);

    for (auto it : vals) {
        cout << it << " ";
    }
    cout << endl;
}

int main()
{

    test1();
    std::cout << "main exit\n";
    return 0;
}

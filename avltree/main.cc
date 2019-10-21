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
};
using Node = struct Node;

void treeInsert(Node* n, Node* new_)
{
    for (; n;) {
        if (new_->value >= n->value) {
            if (n->right == NULL) {
                break;
            }
            n = n->right;
        } else {
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
    if (n->height == 0) {
        for (; n;) {
            n->height += 1;
            n = n->parent;
        }
    }

    // banlance
}

int main()
{

    std::cout << "main exit\n";
    return 0;
}

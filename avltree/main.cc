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

struct AVL {

    // :param root 不能是 NULL
    void _insert(Node* root, Node* new_)
    {
        Node* n = root;
        for (;;) {
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

        if (new_->value >= n->value) {
            n->right = new_;
            new_->parent = n;
        } else {
            n->left = new_;
            new_->parent = n;
        }
    }

    void insert(Node** pproot, Node* new_)
    {

        // 一定是高度差为 2-0 3-1 导致的不平衡
        // 也可能是 4-2 , 5-3 等
        // 所以不一定是插入 new_ 后， parent 就失去平衡，要一直向上回溯，找到不平衡的
        Node* parent = NULL;
        bool insertToLeft = true;

        _insert(*pproot, new_);
        parent = new_->parent;
        if (parent->left != new_) {
            insertToLeft = false;
        }

        for (; parent;) {
            int left = 0;
            int right = 0;
            if (parent->left) {
                left = parent->left->height;
            }
            if (parent->right) {
                right = parent->right->height;
            }
            int height = max(left, right) + 1;
            // 不需要向上刷新了
            if (height == parent->height) {
                break;
            }
            parent->height = height;
            if (left > right && left - right > 1) {
                if (insertToLeft) {
                    rightRotate(pproot, new_);
                } else {
                    leftRotate(pproot, parent->right);
                    rightRotate(pproot, parent);
                }
                break;
            } else if (right > left && right - left > 1) {
                if (insertToLeft) {
                    rightRotate(pproot, parent->left);
                    leftRotate(pproot, parent);
                } else {
                    leftRotate(pproot, parent);
                }
                break;
            }
            parent = parent->parent;
        }
    }

    // left > right
    void rightRotate(Node** pproot, Node* x)
    {
        // x not NULL
        // x->left not NULL
        // y not NULL
        Node* y = x->left;

        // parent <-> x <-> y
        y->parent = x->parent;
        if (x->parent && x->parent->left == x) {
            x->parent->left = y;
        } else if (x->parent && x->parent->right == x) {
            x->parent->right = y;
        }
        // x <-> y->right
        x->left = y->right;
        if (y->right) {
            y->right->parent = x;
        }
        // x <-> y
        y->right = x;
        x->parent = y;
        if ((*pproot) == x) {
            *pproot = y;
        }
        updateHeight(x);
        updateHeight(y);
    }

    // right > left
    void leftRotate(Node** pproot, Node* x)
    {
        // x not NULL
        // x->right not NULL
        // y not NULL
        Node* y = x->right;

        // parent <-> x <-> y
        y->parent = x->parent;
        if (x->parent && x->parent->left == x) {
            x->parent->left = y;
        } else if (x->parent && x->parent->right == x) {
            x->parent->right = y;
        }
        // x <-> y->left
        x->right = y->left;
        if (y->left) {
            y->left->parent = x;
        }
        // x <-> y
        y->left = x;
        x->parent = y;
        if (*pproot == x) {
            *pproot = y;
        }

        updateHeight(x);
        updateHeight(y);
    }

    // 更新结点的高度值，只看左右，不递归
    void updateHeight(Node* n)
    {
        int left = 0;
        int right = 0;
        if (n->left) {
            left = n->left->height;
        }
        if (n->right) {
            right = n->right->height;
        }
        n->height = max(left, right) + 1;
    }
};

//
// 自定义区域
//

string formatv(string fmt, ...);

void levelOrderWithNull(const vector<Node*>& childs, vector<string>& vals)
{
    vector<Node*> childs2;
    const int kNULL = -10000;

    bool haveChilds = false;
    for (auto it : childs) {
        string s = formatv("<height %d - %d>", it->height, it->value);
        if (it->value == kNULL) {
            s = formatv("<height %d - null>", it->height);
        }
        vals.push_back(s);
        if (it->left || it->right) {
            haveChilds = true;
        }
    }

    if (haveChilds) {
        for (auto it : childs) {
            if (it->left) {
                childs2.push_back(it->left);
            } else {
                childs2.push_back(new Node(kNULL));
            }

            if (it->right) {
                childs2.push_back(it->right);
            } else {
                childs2.push_back(new Node(kNULL));
            }
        }
        levelOrderWithNull(childs2, vals);
    }
}

void printTree(Node* root)
{
    vector<string> vals;
    vector<Node*> childs;
    childs.push_back(root);
    levelOrderWithNull(childs, vals);

    for (auto it : vals) {
        printf("%s ", it.c_str());
    }
    printf("\n");
}

void test1()
{
    vector<int> vec = { -3, 0, 5, 9 };

    Node* root = new Node(-10);
    AVL avl;

    for (auto it : vec) {
        Node* n = new Node(it);
        avl.insert(&root, n);
        printTree(root);
    }
    printTree(root);
}

int main()
{

    test1();
    std::cout << "main exit\n";
    return 0;
}

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

/*

通过这些旋转 体会如何做到  右旋 左旋
左右旋转 右左旋转 是在 右旋 左旋 基础上完成的

		 n1
		/
	   x
	  /
	 y
	/
   new

x 是不平衡点，右旋转

	  n1
	 /
	y
   / \
  new x



-----------------------------------------------


		 x
		/  \
	   y    n3
	  / \
	 n1   n2
	/
   new

x 是不平衡点，右旋转

	   y
	  / \
	 n1  x
	/   / \
   new  n2 n3


-----------------------------------------------


		 n1
		  \
		   x
			\
			 y
			/
		   new

x 是不平衡点，旋转


		 n1
		  \
		   x
			\
			 new
			  \
			   y

	  n1
		\
		new
	   / \
	  x   y

-----------------------------------------------

		 x
		/ \
	   y   n3
	  / \
	 n1   n2
	  \
	  new

x 是不平衡点，右旋转
		y
	   / \
	  /   \
	 n1    x
	  \   / \
	 new n2 n3

-----------------------------------------------

		 x
		/ \
	   y   n3
	  / \
	 n1  n2
		   \
		   new

x 是不平衡点，旋转
		x
	   / \
	  /   \
	 n2    n3
	/ \
   y  new
  /
 n1


	 n2
	/ \
   y  x
  /  / \
 n1 new n3




*/
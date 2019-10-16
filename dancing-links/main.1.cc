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

// chenshuo:谈谈数独(Sudoku) https://blog.csdn.net/Solstice/article/details/2096209
//  Dancing Links  精确覆盖算法（Exact Cover）
// https://github.com/chenshuo/muduo/blob/master/examples/sudoku/batch.cc

// 使用Muduo完成数独和八数码问题求解服务器
// https://blog.csdn.net/NK_test/article/details/51525015

struct Node {
    struct Node* left;
    struct Node* right;
    struct Node* up;
    struct Node* down;
    struct Node* columnHead;
    int x; // col
    int y; // row
    int size;
};

void insertLeft(struct Node* old, struct Node* new_)
{
    new_->left = old->left;
    new_->right = old;
    old->left = new_;
    old->left->right = new_;
}

void insertUp(struct Node* old, struct Node* new_)
{
    new_->down = old;
    new_->up = old->up;
    old->up = new_;
    old->up->down = new_;

    old->size++;
    new_->columnHead = old; // ? 怎么不是 new_->columnHead = old->columnHead ?
}

void cover(struct Node* col)
{
    col->right->left = col->left;
    col->left->right = col->right;

    for (struct Node* row = col->down; row != col; row = row->down) {
        for (struct Node* j = row->right; j != row; j = j->right) {
            j->up->down = j->down;
            j->down->up = j->up;
            j->columnHead->size--;
        }
    }
}

void uncover(struct Node* col)
{

    for (struct Node* row = col->up; row != col; row = row->up) {
        for (struct Node* j = row->left; j != row; j = j->left) {
            j->down->up = j;
            j->up->down = j;
            j->columnHead->size++;
        }
    }

    col->right->left = col;
    col->left->right = col;
}

struct Node* minColumn(struct Node* root)
{
    struct Node* col = root->right;

    int minSize = col->size;
    if (minSize > 1) {
        for (struct Node* cc = col->right; cc != root; cc = cc->right) {
            if (cc->size < minSize) {
                minSize = cc->size;
                col = cc;

                if (minSize < 2) {
                    break;
                }
            }
        }
    }
    return col;
}

class Solution {

    struct Node* root_;
    list<struct Node*> allocedNodes_;
    // struct Node* columnHeads[400]; // for what?

    struct Node* allocNode()
    {
        struct Node* n = (struct Node*)calloc(1, sizeof(struct Node));
        allocedNodes_.push_back(n);

        n->left = n;
        n->right = n;
        n->up = n;
        n->down = n;
        return n;
    }

    struct Node* newColumn(int column)
    {
        struct Node* c;
        c = allocNode();
        c->columnHead = c;
        c->column = column;
        return c;
    }

    struct Node* newRow(int column)
    {
        struct Node* r;
        r = allocNode();
        r->column = column;
    }

public:
    Solution()
    {
        root_ = NULL;
    }
    ~Solution()
    {
        for (auto it : allocedNodes_) {
            free(it);
        }
        allocedNodes_.clear();
    }

	bool solve(vector<struct Node *> & stk) 
	{

		// no rows
		if(root_->left == root_) {
			
			// get all stack
			return true;
		}


		struct Node * col = minColumn(root_);
		cover(col);

		for(struct Node * row = col->down; row != col; row= row->down) {
			stk.push_back(row);
			for(struct Node * j = row->right; j != row; j = j->right) {
				cover(j->columnHead);
			}

			if(solve(stk)) {
				return true;
			}

			stk.pop_back();
			for(struct Node * j = row->left; j != row; j= j->left) {
				uncover(j->columnHead);
			}

		}


		uncover(col);
		return false;
	}

    void solveSudoku(vector<vector<char>>& board)
    {
    }
};

int main()
{

    Solution a;
    (void)a;

    std::this_thread::sleep_for(1s);

    vector<vector<char>> b = {
        { '5', '3', '.', '.', '7', '.', '.', '.', '.' },
        { '6', '.', '.', '1', '9', '5', '.', '.', '.' },
        { '.', '9', '8', '.', '.', '.', '.', '6', '.' },
        { '8', '.', '.', '.', '6', '.', '.', '.', '3' },
        { '4', '.', '.', '8', '.', '3', '.', '.', '1' },
        { '7', '.', '.', '.', '2', '.', '.', '.', '6' },
        { '.', '6', '.', '.', '.', '.', '2', '8', '.' },
        { '.', '.', '.', '4', '1', '9', '.', '.', '5' },
        { '.', '.', '.', '.', '8', '.', '.', '7', '9' }
    };

    a.solveSudoku(b);

    vector<int> one = { 10, 11, 11, 11, 12, 12, 12 };
    auto singleNum = singleNumber(one);

    cout << "only one of " << singleNum << endl;

    std::cout << "main exit\n";
    return 0;
}

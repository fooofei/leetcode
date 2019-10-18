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

struct Node* minSizeColumn(struct Node* root)
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

void build(struct Node* root, const vector<vector<char>>& board)
{

    // max X =
    //  约束 1 每个格子必须有唯一值 9*9 +
    //  约束 2 每行必须有唯一值 9*9 +
    //  约束 3 每列必须有唯一值 9*9 +
    //  约束 4 每宫中的每格必须有值 9*9
    // = 324

    // max Y = 每个格子取值 1-9 的可能的和为 9*9*9

    int girdX = board[0].size();
    int girdY = board.size();

    vector<vector<bool>> boolX(girdX, vector<bool>(10, false));
    vector<vector<bool>> boolY(girdY, vector<bool>(10, false));
    vector<vector<bool>> boolBox(girdX, vector<bool>(10, false));

    for (size_t y = 0; y < board.size(); y++) {
        const vector<char>& vec = board[y];
        for (size_t x = 0; x < vec.size(); x++) {

            size_t boxIndex = y / 3 * 3 + x;
            int val = vec[x] - '0';
            if (vec[x] == '.') {
                val = 0;
            }
            if (boolX[x][val]) {
                printf("conflict\n");
            }
            boolX[x][val] = true;
            if (boolY[y][val]) {
                printf("conflict\n");
            }
            boolY[y][val] = true;
            if (boolBox[boxIndex][val]) {
                printf("conflict\n");
            }
            boolBox[boxIndex][val] = true;
        }
    }
}

class Solution {

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
    }
    ~Solution()
    {
        for (auto it : allocedNodes_) {
            free(it);
        }
        allocedNodes_.clear();
    }

    bool solve(vector<struct Node*>& stk)
    {

        // no rows
        if (root_->left == root_) {

            // get all stack
            return true;
        }

        struct Node* col = minColumn(root_);
        cover(col);

        for (struct Node* row = col->down; row != col; row = row->down) {
            stk.push_back(row);
            for (struct Node* j = row->right; j != row; j = j->right) {
                cover(j->columnHead);
            }

            if (solve(stk)) {
                return true;
            }

            stk.pop_back();
            for (struct Node* j = row->left; j != row; j = j->left) {
                uncover(j->columnHead);
            }
        }

        uncover(col);
        return false;
    }

    void solveSudoku(vector<vector<char>>& board)
    {
        // 是把已经填充的做结点 还是把未填充的做结点 ？
        // 应该是未填充的吧
    }
};

int main()
{

    Solution a;
    (void)a;

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

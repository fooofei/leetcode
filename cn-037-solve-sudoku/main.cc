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

// chenshuo:谈谈数独(Sudoku) https://blog.csdn.net/Solstice/article/details/2096209
//  Dancing Links  精确覆盖算法（Exact Cover）
// https://github.com/chenshuo/muduo/blob/master/examples/sudoku/batch.cc

// 使用Muduo完成数独和八数码问题求解服务器
// https://blog.csdn.net/NK_test/article/details/51525015

// https://leetcode-cn.com/problems/sudoku-solver/submissions/

// 执行用时 : 8 ms , 在所有 cpp 提交中击败了 93.54% 的用户
// 内存消耗 :
// 10.1 MB
// , 在所有 cpp 提交中击败了
// 15.19%
// 的用户

struct Node {
    struct Node* left;
    struct Node* right;
    struct Node* up;
    struct Node* down;
    struct Node* columnHead;
    int val; // 只在  columnIndex < 100 时有效
    int columnIndex;
    int size;
};

// C++ 20 have std::format, we need another name to reduce name conflict.
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

void insertLeft(struct Node* new_, struct Node* old)
{
    new_->left = old->left;
    new_->right = old;
    old->left->right = new_;
    old->left = new_;
}

void insertUp(struct Node* new_, struct Node* old)
{
    new_->down = old;
    new_->up = old->up;
    old->up->down = new_;
    old->up = new_;
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

struct Node* minSizeCol(struct Node* root)
{
    struct Node* col = root->right;

    int minSize = col->size;
    if (minSize > 1) {
        for (struct Node* cc = col->right; cc != root; cc = cc->right) {
            if (cc->size < minSize) {
                minSize = cc->size;
                col = cc;

                // 有 1 个是最小的，有了它就再也不往后看了
                if (minSize < 2) {
                    break;
                }
            }
        }
    }
    return col;
}

class Solution {

    list<struct Node*> allocedNodes_;

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

    // find solution to cells
    bool solve(struct Node* root, vector<struct Node*>& stk, vector<int>& cells)
    {

        // no rows
        if (root->left == root) {

            // get all stack

            for (size_t i = 0; i < stk.size(); i++) {

                struct Node* n = stk[i];
                for (;;) {

                    if (n->columnIndex < 100) {
                        cells[n->columnIndex] = n->val;
                        break;
                    }
                    n = n->right;
                    if (n == stk[i]) {
                        break;
                    }
                }
            }

            return true;
        }

        struct Node* col = minSizeCol(root);
        cover(col);

        for (struct Node* row = col->down; row != col; row = row->down) {
            stk.push_back(row);
            for (struct Node* j = row->right; j != row; j = j->right) {
                cover(j->columnHead);
            }

            if (solve(root, stk, cells)) {
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

    // build matrix on root
    // only support 9*9 , 每个值必须 < 9
    // :return error string
    //
    string build(struct Node* root, const vector<int>& cells, int gridSize)
    {

        // max cols =
        //  约束 1 每个格子必须有唯一值 9*9 +
        //  约束 2 每行必须有唯一值 9*9 +
        //  约束 3 每列必须有唯一值 9*9 +
        //  约束 4 每宫中的每格必须有值 9*9
        // = 324

        // max rows = 每个格子取值 1-9 的可能的和为 9*9*9

        vector<struct Node*> colHeaders;
        colHeaders.resize(4 * 100);

        // 10 代表 1-9 的数字
        // 某一列有哪些数字被使用了就 true
        vector<vector<bool>> boolCol(gridSize, vector<bool>(10, false));
        // 某一行，有哪些数字被使用了就 true
        vector<vector<bool>> boolRow(gridSize, vector<bool>(10, false));
        // 某一个宫
        vector<vector<bool>> boolBox(gridSize, vector<bool>(10, false));

        for (size_t i = 0; i < cells.size(); i++) {
            size_t col = i % gridSize;
            size_t row = i / gridSize;
            size_t box = row / 3 * 3 + col / 3;
            int val = cells[i];

            if (val > 0 && boolRow[row][val]) {
                return formatv("%d already exists in row %d", val, (int)row);
            }

            if (val > 0 && boolCol[col][val]) {
                return formatv("%d already exists in col %d", val, (int)col);
            }

            if (val > 0 && boolBox[box][val]) {
                return formatv("%d already exists in box %d", val, (int)box);
            }

            boolRow[row][val] = true;
            boolCol[col][val] = true;
            boolBox[box][val] = true;
        }

        for (size_t i = 0; i < cells.size(); i++) {
            if (cells[i] == 0) {
                newColToLeft(root, colHeaders, i);
            }            
        }

        for (size_t i = 0; i < boolRow.size(); i++) {
            for (size_t val = 1; val < 10; val++) {
                if (!boolRow[i][val]) {
                    // 第一列组 就 81 列，我们 +100 是为了算数方便
                    int name = 100 + gridSize * i + val;
                    newColToLeft(root, colHeaders, name);
                }

                if (!boolCol[i][val]) {
                    int name = 200 + gridSize * i + val;
                    newColToLeft(root, colHeaders, name);
                }

                if (!boolBox[i][val]) {
                    int name = 300 + gridSize * i + val;
                    newColToLeft(root, colHeaders, name);
                }
            }
        }

        for (size_t i = 0; i < cells.size(); i++) {
            if (cells[i] == 0) {
                size_t row = i / gridSize;
                size_t col = i % gridSize;
                size_t box = row / 3 * 3 + col / 3;

                for (int v = 1; v < 10; v++) {

                    if ((boolRow[row][v] || boolCol[col][v] || boolBox[box][v])) {
                        continue;
                    }

                    struct Node* n0 = newNodeAtCol(colHeaders, i);
                    n0->val = v;
                    struct Node* nr = newNodeAtCol(colHeaders, 100 + gridSize * row + v);
                    struct Node* nc = newNodeAtCol(colHeaders, 200 + gridSize * col + v);
                    struct Node* nb = newNodeAtCol(colHeaders, 300 + gridSize * box + v);

                    // 相同行链接起来
                    insertLeft(nr, n0);
                    insertLeft(nc, n0);
                    insertLeft(nb, n0);
                }
            }
        }

        return ""; // noerror
    }

    struct Node* newColToLeft(struct Node* root, vector<struct Node*>& colHeaders, int colIndex)
    {
        struct Node* c = allocNode();
        c->columnHead = c;
        c->columnIndex = colIndex;
        insertLeft(c, root);
        colHeaders[colIndex] = c;
        return c;
    }

    struct Node* newNodeAtCol(vector<struct Node*>& colHeaders, int colIndex)
    {
        struct Node* n = allocNode();
        struct Node* head = colHeaders[colIndex];
        n->columnHead = head;
        n->columnIndex = colIndex;
        insertUp(n, head);
        head->size++;
        return n;
    }

    // 只解决 9 x 9 规格
    void solveSudoku(vector<vector<char>>& board)
    {
        struct Node* root = allocNode();
        vector<int> cells;
        const int GRID_SIZE = 9;

        cells.resize(board.size() * board[0].size());
        vector<struct Node*> stk;

        if (board.size() != GRID_SIZE) {
            return;
        }

        for (size_t i = 0; i < board.size(); i++) {
            if (board[i].size() != GRID_SIZE) {
                return;
            }
            for (size_t j = 0; j < board[i].size(); j++) {
                char c = board[i][j];
                if (c == '.') {
                    c = '0';
                }
                cells[i * GRID_SIZE + j] = c - '0';
            }
        }

        auto err = build(root, cells, GRID_SIZE);
        if (err.size() > 0) {
            printf("err = %s\n", err.c_str());
            return;
        }

        if (solve(root, stk, cells)) {
            for (size_t i = 0; i < cells.size(); i++) {

                size_t row = i / GRID_SIZE;
                size_t col = i % GRID_SIZE;

                if (board[row][col] == '.') {
                    board[row][col] = cells[i] + '0';
                }
            }
        }
    }

    bool isValidSudoku(vector<vector<char>>& board)
    {
        int gridSize = 9;
        vector<vector<bool>> boolCol(gridSize, vector<bool>(10, false));
        vector<vector<bool>> boolRow(gridSize, vector<bool>(10, false));
        vector<vector<bool>> boolBox(gridSize, vector<bool>(10, false));

        for (size_t i = 0; i < board.size(); i++) {
            for (size_t j = 0; j < board[i].size(); j++) {
                char c = board[i][j];
                // 没有得到解不算失败
                if (c == '.' || c == '0') {
                    continue;
                }
                int val = c - '0';
                size_t box = i / 3 * 3 + j / 3;

                if (boolCol[j][val]) {
                    return false;
                }
                if (boolRow[i][val]) {
                    return false;
                }
                if (boolBox[box][val]) {
                    return false;
                }
                boolCol[j][val] = true;
                boolRow[i][val] = true;
                boolBox[box][val] = true;
            }
        }

        return true;
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
    cout << "valid " << a.isValidSudoku(b) << endl;

    std::cout << "main exit\n";
    return 0;
}

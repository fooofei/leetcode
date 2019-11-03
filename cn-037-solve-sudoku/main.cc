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

// 提供思路
// https://blog.csdn.net/WhereIsHeroFrom/article/details/79188290

// 长文，没看出来是什么意思 
// https://norvig.com/sudoku.html

// 在线玩具
// https://sudokuspoiler.azurewebsites.net/SudokuX/SudokuX16

// 列出了大矩阵
// https://www.stolaf.edu//people/hansonr/sudoku/exactcovermatrix.htm

// X 算法讲解
// https://github.com/Urinx/SomeCodes/tree/master/Python/DancingLinks

// DLX算法求解数独
// https://unordered.org/timelines/58b4831e69000000

// 037 https://leetcode-cn.com/problems/sudoku-solver/submissions/

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

// 从矩阵中移除 `col` 这一列
// 从 root-> 指针这一个链表中移除 col
// 并且把 col 挂载的列的结点触及的整个行从矩阵移除
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
	vector<struct Node*> colHeaders_;

    struct Node* allocNode()
    {
        struct Node* n = (struct Node*)calloc(1, sizeof(struct Node));
        allocedNodes_.push_back(n);

        n->left = n;
        n->right = n;
        n->up = n;
        n->down = n;
		n->val = -1;
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
	
	// X算法可以表述为
	// 约束：每一列只能有 1 个 1 每一行有多少个 1 无所谓
	// 1 选择 size 最小的列
	// 2 对于这个列中的每一行
	// 2.1 选择了这一行
	// 2.2 移除这一行包含的列
	// 2.3 移除与这一行冲突的行
	// 3 剩下的行列 递归 X 算法
	
    
	// 下面的实现是，相当于考虑加上十字链表后，如何适配 X 算法
	// 1 选择 size 最小的列(对应到数独的含义是可填入数字最少的那个 行/或者列/或者宫)
	// 2 把这一列和它挂载的行都移除掉 (相当于行列只移除了一部分，行只移除了)
	// 3 对于这个列的每一行
	// 3.1 选择了这一行
	// 3.2 把这一行的其他列以及它挂载的行都移除掉(这才算补上剩下的) 
	// 3.3 递归 直到所有行都遍历过了
	// 3.4 恢复现场
	// 4 恢复现场
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

		// 确定一个列，只要这个列没有可选的了，那么我们就求解结束了
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
		// 分 4 个读法
		// 约束1 读作 i,j 放了值，无论是几都是写1
		// 约束2 读作 i 行放了 [1,2,...9]
		// 约束3 读作 j 列放了 [1,2,...9]
		// 约束4 读作 box 宫放了 [1,2,...9]

        // max rows = 每个格子取值 1-9 的可能的和为 9*9*9 
		// 行读作 (i,j) 坐标放置了数字 n

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
            }
        }

		for (size_t i = 0; i < boolCol.size(); i++) {
			for (size_t val = 1; val < 10; val++) {
				if (!boolCol[i][val]) {
					int name = 200 + gridSize * i + val;
					newColToLeft(root, colHeaders, name);
				}
			}
		}
		for (size_t i = 0; i < boolBox.size(); i++) {
			for (size_t val = 1; val < 10; val++) {
				if (!boolBox[i][val]) {
					int name = 300 + gridSize * i + val;
					newColToLeft(root, colHeaders, name);
				}
			}
		}


		// 这是在遍历每一行 行总共是 9*9 个格子，每个格子 1-9 可能的数字 
		// 总共 9*9*9
        for (size_t i = 0; i < cells.size(); i++) {
            if (cells[i] == 0) {
                size_t row = i / gridSize;
                size_t col = i % gridSize;
                size_t box = row / 3 * 3 + col / 3;

                for (int v = 1; v < 10; v++) {

					// 这表示的意思是 4 个约束都要同时满足
					// 为什么是 4 个，因为这里看到 3 个，加上外面的大循环 if(cells[i] ==0)
					// 为什么满足 4 个约束才插入行呢
					// 我们拿矩阵来看，i 在 81 中，没有放数字，如果要放数字，他必须同时满足
					// 行不冲突 列不冲突 宫不冲突，因此是几个都要满足，如果仅仅满足部分约束，那不叫解
                    if ((boolRow[row][v] || boolCol[col][v] || boolBox[box][v])) {
                        continue;
                    }

					// 命名 rcn = row,col放数字n  rn 行上有数字 n 
                    struct Node* rcn = newNodeAtCol(colHeaders, i);
					rcn->val = v;
                    struct Node* rn = newNodeAtCol(colHeaders, 100 + gridSize * row + v);
                    struct Node* cn = newNodeAtCol(colHeaders, 200 + gridSize * col + v);
                    struct Node* bn = newNodeAtCol(colHeaders, 300 + gridSize * box + v);

					// 把结点与列头区分开来，好理解
					rn->val = 0;
					cn->val = 0;
					bn->val = 0;
                    // 相同行链接起来
                    insertLeft(rn, rcn);
                    insertLeft(cn, rcn);
                    insertLeft(bn, rcn);
                }
            }
        }

		colHeaders_ = colHeaders;
		// 到这里观察所有列都有数字 没有空列 怎么做到的 ？
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

		if (cells.size() / GRID_SIZE != GRID_SIZE) {
			return;
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


/*
X 算法推演举例
  1  2  3  4  5  6  7
A 1        4        7
B 1        4
C          4  5     7
D       3     5  6
E    2  3        6  7
F    2              7




1 选择列 1 包含行  A B

2 for 行 [A, B]

	2.1 选择 A 行 矩阵移除行列

		   2  3  5  6
		D     3  5  6


		2.1.1 这个不行， 出现了 size=0 的列，结束本次调用，需要递归回溯

	2.2 选择 B 行 矩阵移除行列

		  2  3  5  6  7
		D    3  5  6
		E 2  3     6  7
		F 2           7

		2.2.1

		继续这样递归，选择 size 最小的列 5,
		行为 D

			2.2.1.1 for [D]
				2.2.1.1.1 选择 D 行 矩阵移除行列

					  2  7
					F 2  7


				2.2.1.1.2 继续选择 size 最小的列， 2， 行就是 F，

				选择完，没有行了，说明这是 1 个解。

本文件的算法举例

  1  2  3  4  5  6  7
A 1        4        7
B 1        4
C          4  5     7
D       3     5  6
E    2  3        6  7
F    2              7


推演：
1 选择 size 最小的列 1,

2 移除这一列及列上的所有行 即 A B

	   2  3  4  5  6  7
	C        4  5     7
	D     3     5  6
	E  2  3        6  7
	F  2              7


3 for 行 [A, B]

	3.1 选择行 A
		3.1.1 for 行 A的每一列 [4, 7]
			3.1.1.1 列 4 ，移除这一列及列上的所有行

				   2  3  5  6  7
				D     3  5  6
				E  2  3     6  7
				F  2           7
			 3.1.1.2 列 7 ，移除这一列及列上的所有行

				   2  3  5  6
				D     3  5  6

		3.1.2 递归




	3.2 选择 B 行
		3.2.1 for 行 B 的每一列 [4]
			3.1.1.1 列 4 ，移除这一列及列上的所有行

				   2  3  5  6  7
				D     3  5  6
				E  2  3     6  7
				F  2           7

			3.1.1.2 递归
				3.1.1.2.1 选择 size 最小的列 5
				3.1.1.2.2 移除这一列及列上的所有行
					   2  3  6  7
					E  2  3  6  7
					F  2        7
				3.1.1.2.3 for 行 [D]
					3.1.1.2.3.1 选择行 D
						3.1.1.2.3.1.1 for 行 D 上的每一列 [3, 6]
							3.1.1.2.3.1.1.1 列 3 移除这一列及列上的所有行
								   2  6  7
								F  2     7
							3.1.1.2.3.1.1.2 列 6 移除这一列及列上的所有行 
(十字链表的移除可以处理这种情况 cover uncover 变成 cover cover uncover 也行，指针是对的，但是 size 不对)
								   2  7
								F  2  7

							3.1.1.2.3.1.1.3 递归
								省略， 选择 行 F
								再次递归就没行（列）了

*/

#include <algorithm>
#include <array>
#include <bitset>
#include <iostream>
#include <limits>
#include <list>
#include <map>
#include <stack>
#include <string>
#include <vector>

using namespace std;

// https://leetcode-cn.com/problems/valid-sudoku/

class Solution {
public:
    using array_char = vector<char>;

    bool exist(vector<bool>& existing, char c)
    {
        if (c == '.') {
            return false;
        }
        if (existing[c]) {
            return true;
        }
        existing[c] = true;
        return false;
    }

    void reset(vector<bool>& existing)
    {
        existing.clear();
        existing.resize(0xFF, false);
    }

    bool isValidSudoku(vector<vector<char>>& board)
    {

        // every row
        vector<bool> existing;

        for (size_t i = 0; i < board.size(); i++) {
            reset(existing);
            array_char& ref = board[i];

            for (size_t j = 0; j < ref.size(); j++) {
                char c = ref[j];
                if (exist(existing, c)) {
                    return false;
                }
            }
        }

        // every column
        for (size_t i = 0; i < board.size(); i++) {

            reset(existing);
            for (size_t j = 0; j < board[0].size(); j++) {
                char c = board[j][i];

                if (exist(existing, c)) {
                    return false;
                }
            }
        }

        // 每个小方框

        for (size_t i = 0; i < board.size(); i += 3) {

            for (size_t j = 0; j < board.size(); j += 3) {

                reset(existing);
                for (size_t m = 0; m < 3; m++) {
                    for (size_t n = 0; n < 3; n++) {

                        char c = board[i + m][j + n];
                        if (exist(existing, c)) {
                            return false;
                        }
                    }
                }
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

    a.isValidSudoku(b);

    std::cout << "main exit\n";
    return 0;
}

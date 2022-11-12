#include "board.h"

Board::Board(unsigned n) {
    _board = vector<vector<bool>>(n, vector<bool>(n, false));
}

void Board::toggle(unsigned row, unsigned col) {
    _board[row][col] = !_board[row][col];
}

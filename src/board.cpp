#include "board.h"
#include <stdexcept>

Board::Board(unsigned n) {
    size = n;
    _board = vector<vector<bool>>(n, vector<bool>(n, false));
}

void Board::toggle(unsigned row, unsigned col) {
    _board[row][col] = !_board[row][col];
}


friend Board operator-(const Board& lhs, const Board& rhs) {
    if (lhs.size != rhs.size) {
        throw runtime_error("wrong size");
    }
    Board toReturn(size);
    for (unsigned i = 0 ; i < size; i++) {
        for (unsigned j =0; j < size; j++) {
            if (lhs._board[i][j] != rhs._board[i][j]) {
                toReturn.toggle(i,j);
            }
        }
    }
    return toReturn;
}

Board& Board::operator=(const Board& rhs) {
    if ((*this) == rhs ) {
        return *this;
    }
    size = rhs.size;
    for (unsigned i = 0; i < size; i++) {
        for (unsigned j =0; j < size; j++) {
            _board[i][j] = rhs._board[i][j];
        }
    }
    return *this;
}

friend bool operator==(const Board& lhs, const Board& rhs) {
    if (lhs.size != rhs.size) {
        throw runtime_error("wrong size");
    }
    for (unsigned i = 0; i < size; i++) {
        for (unsigned j =0; j < size; j++) {
            if (lhs._board[i][j] != rhs._board[i][j]) {
                return false;
            }
        }
    }
    return true;
}

friend bool operator!=(const Board& lhs, const Board& rhs) [
    if (lhs.size != rhs.size) {
        throw runtime_error("wrong size");
    }
    return !(lhs == rhs);
]

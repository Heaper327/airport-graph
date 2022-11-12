#include "board.h"
#include <stdexcept>

Board::Board(unsigned n) {
    size = n;
    _board = vector<vector<bool>>(n, vector<bool>(n, false));
}

void Board::toggle(unsigned row, unsigned col) {
    assert(row < size && col < size);
    for (unsigned i = row; i < row + 3; i++) {
        for (unsigned j=  col; j < col + 3; j++) {
            _board[row][col] = !_board[row][col];
        }
    }
}

void Board::toggleOne(unsigned row, unsigned col) {
    _board[row][col] = !_board[row][col];
}

bool Board::getBulb(unsigned row, unsigned col) const {
    return _board[row][col];
}
unsigned Board::getSize() const {
    return size;
}

inline Board operator-(const Board& lhs, const Board& rhs) {
    if (lhs.size != rhs.size) {
        throw runtime_error("wrong size");
    }
    unsigned size = lhs.getSize();
    Board toReturn(size);
    for (unsigned i = 0 ; i < size; i++) {
        for (unsigned j =0; j < size; j++) {
            if (lhs.getBulb(i,j) != rhs.getBulb(i,j)) {
                toReturn.toggleOne(i,j);
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

inline bool operator==(const Board& lhs, const Board& rhs) {
    if (lhs.size != rhs.size) {
        throw runtime_error("wrong size");
    }
    unsigned size = lhs.getSize();
    for (unsigned i = 0; i < size; i++) {
        for (unsigned j =0; j < size; j++) {
            if (lhs.getBulb(i,j) != rhs.getBulb(i,j)) {
                return false;
            }
        }
    }
    return true;
}

inline bool operator!=(const Board& lhs, const Board& rhs) {

    return !(rhs == lhs);
}

#include "board.h"
#include <stdexcept>

Board::Board() : size(0), _board() {
    // do nothing
}

Board::Board(unsigned n) {
    size = n;
    _board = vector<bool>(n * n, false);
}

void Board::toggle(unsigned row, unsigned col) {
    
    if (!(row <= size - 3 && col <= size - 3 && row >= 0 && col >= 0)) {
        throw runtime_error("Area to be toggled out of bound");
    }

    for (unsigned i = row; i < row + 3 ; i++) {
        for (unsigned j= col; j < col + 3; j++) {
            setBulb(i, j, !getBulb(i, j));
        }
    }
}

std::string Board::print() const {
    string toReturn;
    for (unsigned i = 0; i < size; i++) {
        for (unsigned j =0; j < size; j++) {
            if (getBulb(i, j)) {
                toReturn.append("⚪");
            } else {
                toReturn.append("⚫");
            }
        }
        if (i != size - 1) {
            toReturn.append("\n");
        }
    }
    return toReturn;
 }

Board::Board(const Board& rhs) {
    *this = rhs;
}

Board::Board(vector<vector<bool>> board) {
    size = board.size();
    _board.resize(size * size, false);
    for (unsigned i = 0; i < size; i++) {
        for (unsigned j = 0; j < size; j++) {
            setBulb(i, j, board.at(i).at(j));
        }
    }
}

void Board::setBulb(unsigned row, unsigned col, bool value) {
    _board[row * size + col] = value;
}

bool Board::getBulb(unsigned row, unsigned col) const {
    return _board[row * size + col];
}
unsigned Board::getSize() const {
    return size;
}
Board operator-(const Board& lhs, const Board& rhs) {
    if (lhs.size != rhs.size) {
        throw runtime_error("wrong size");
    }
    unsigned size = lhs.getSize();
    Board toReturn(size);
    for (unsigned i = 0 ; i < size; i++) {
        for (unsigned j =0; j < size; j++) {
            bool diff = lhs.getBulb(i, j) ^ rhs.getBulb(i, j);
            toReturn.setBulb(i, j, diff);
        }
    }
    return toReturn;
}
Board& Board::operator=(const Board& rhs) {
    if (this == &rhs ) {
        return *this;
    }
    size = rhs.size;
    _board.resize(size * size, false);
    for (unsigned i = 0; i < size * size; i++) {
        _board.at(i) = rhs._board.at(i);
    }
    return *this;
}

bool operator==(const Board& lhs, const Board& rhs) {
    // vector's oprator== does size checking and content checking
    return lhs._board == rhs._board;
}


bool operator!=(const Board& lhs, const Board& rhs) {
    return !(rhs == lhs);
}

bool operator<(const Board& lhs, const Board& rhs) {
    return lhs._board < rhs._board;
}

PNG* Board::boardToPNG() {
    PNG* png_ = new PNG(size*11 + 1,size*11 + 1);
    unsigned png_size = size*11 + 1;
    //blacken the rows
    for (unsigned x = 0; x < png_size; x+=11) {
        for (unsigned y = 0; y < png_size ;y++) {
            HSLAPixel& pixel = png_->getPixel(x, y);
            pixel.l = 0;
        }
    }
    //blacken the columns
    for (unsigned x = 0; x < png_size; x++) {
        for (unsigned y = 0; y < png_size ;y+=11) {
            HSLAPixel& pixel = png_->getPixel(x, y);
            pixel.l = 0;
        }
    }
    HSLAPixel yellow(48, 1, 0.5);
    HSLAPixel gray(60, 0.2, 0.3);
    //now the structure of the PNG is built, time to fill in colors
    //x is in range of (b_row * 11 + 1) to (b_row+1) * 11, for example, the block in the first
    //row has a b_row = 0 and its x coordinates covers from 1 to 10
    for (unsigned b_row = 0; b_row < size; b_row++) {
        for (unsigned b_col = 0; b_col < size; b_col++) {
            for (unsigned x = b_row * 11 + 1; x < (b_row+1) * 11; x++) {
                for (unsigned y = b_col * 11 + 1; y < (b_col+1) * 11; y++) {
                    if (getBulb(b_row, b_col)) {
                        //light
                        HSLAPixel & cur_pixel = png_->getPixel(x, y);
				        cur_pixel = yellow;
                    } else {
                        //dark
                        HSLAPixel & cur_pixel = png_->getPixel(x, y);
				        cur_pixel = gray;
                    }
                }
            }
        }
    }
    return png_;
}


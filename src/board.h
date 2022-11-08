#pragma once

#include "cs225/PNG.h"
#include <vector>

using namespace std;

template<unsigned n>
class Board {
    public:
    Board();
    void toggle(unsigned row, unsigned col);

    private:
    vector<vector<bool>> _board;
};

#include "board.hpp"
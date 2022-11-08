template<unsigned n>
Board<n>::Board() {
    _board = vector<vector<bool>>(n, vector<bool>(n, false));
}

template<unsigned n>
void Board<n>::toggle(unsigned row, unsigned col) {
    _board[row][col] = !_board[row][col];
}

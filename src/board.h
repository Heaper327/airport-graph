#pragma once

#include <vector>
#include <string>

using namespace std;

/**
 * A Board represents the state of an nxn light bulb puzzle - in other words, the state of
 * an nxn grid of light bulbs
*/
class Board {
    public:
    /**
     * Default constructor that creates a 0x0 puzzle
     * Used for default instantiation of Board by containers
    */
    Board();
    /**
     * Parametrized constructor, creates a nxn puzzle where all the light bulbs are off
     * 
     * @param n the side length of the board
    */
    Board(unsigned n);
    /**
     * Parametrized constructor, initializes _board with the 2d vector given by the user
    */
    Board(vector<vector<bool>> board);
    /**
     * Copy constructor that creates a deep copy of the other board
     * 
     * @param rhs The board to copy from
    */
    Board(const Board& rhs);
    /**
     * Copy assignment operator that creates a deep copy of the other board
     * 
     * @param rhs The board to copy from
    */
    Board& operator=(const Board& rhs);
    /**
     * Default deconstructor, since we do not allocate any heap memory ourselves
    */
    ~Board() = default;
    /**
     * Toggles all light bulbs in a 3x3 square, whose **top-left corner** is located at (row, col)
     * All the light bulbs in the square that are currently off should be turned on, and vice versa.
     * 
     * If the 3x3 square located at (row, col) goes out of the bounds, an error will be thrown
     * 
     * @param row The row number of the top-left corner of the 3x3 square
     * @param col The col number of the top-left corner of the 3x3 square  
    */
    void toggle(unsigned row, unsigned col);
    /**
     * Return the side length of the board, n
     * 
     * @return The side length of the board
    */
    unsigned getSize() const;
    /**
     * Return the state of the light bulb at (row, col) in the board
     * 
     * @param row The row number of the light bulb
     * @param col The col number of the light bulb
     * 
     * @return The current state of the light bulb
    */
    bool getBulb(unsigned row, unsigned col) const;
    /**
     * Returns a string representation of the board, where off light bulbs are represented by '⚫'
     * and on light bulbs are represented by '⚪'. For example, the following represents a 3x3 board
     * with 4 light bulbs that are on
     * 
     * ⚫⚪⚫
     * ⚪⚫⚪
     * ⚫⚪⚫
     * 
     * @return The string representation of this board
    */
    string print() const;
    /**
     * Subtraction operator that returns the difference between the two boards
     * Suppose board A - B = C. C[n][m] should be true if A[n][m] != B[n][m], and false otherwise
     * e.g. If two boards are equal, then their difference should be all 0
     * 
     * @return An nxn board representing the difference between lhs and rhs
    */
    friend Board operator-(const Board& lhs, const Board& rhs);
    /**
     * Equality operator that returns true if the two boards are identical (i.e. the states of 
     * all light bulbs in the two boards are the same)
     * 
     * @return True if the lhs and rhs are identical, false otherwise
    */
    friend bool operator==(const Board& lhs, const Board& rhs);
    /**
     * Inequality operator that returns true if the two boards are not identical. See operator==
     * 
     * @return True if the lhs and rhs are different, false if they are identical
    */
    friend bool operator!=(const Board& lhs, const Board& rhs);
    /**
     * Comparison operator used by ordered containers of Board
     * 
     * @return True if lhs < rhs, false otherwise
    */
    friend bool operator<(const Board& lhs, const Board& rhs);
    /**
     * Returns the hash value of this board
    */
    size_t hash() const noexcept { return std::hash<vector<bool>>{}(_board); }
    /**
    * Sets the state of the light bulb at (row, col)
    *
    * @param row The row of the light bulb
    * @param col The column of the light bulb
    * @param value The new value of the light bulb
    */
    void setBulb(unsigned row, unsigned col, bool value);

    private:
    /**
     * This 2d vector represents the state of the nxn grid of light bulbs in row-major order
     * 
     * _board[n][m] represents the state of the light bulb at the n-th row and m-th column, where
     * row 0 is the top-most row and column 0 is the left-most column
     * 
     * A value of true means a light bulb is on, and false means a light bulb is off
    */
    unsigned size;
    vector<bool> _board;

};

struct BoardHash {
    size_t operator()(const Board& board) const noexcept { return board.hash(); };
};
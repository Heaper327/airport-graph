#pragma once

#include <fstream>
#include <string>
#include <vector>
#include <stdexcept>
#include <queue>
#include <map>
#include <algorithm>

#include "board.h"

class Solver {
    public:
    /**
     * Default constructor that creates a 5x5 game whose initial state is all off
     * and whose goal state is all on
    */
    Solver() = delete;
    /**
     * Parametrized constructor that loads a game from a formatted text file
     * The first row of the file will contain n, the size of the board
     * The next 2n rows will contain the initial board and the goal board, where
     * 0 represents an off light bulb and 1 represents an on light bulb
     * 
     * e.g.
     * 3
     * 000
     * 000
     * 000
     * 111
     * 111
     * 111
     * 
     * An exception will be thrown if n < 3, the boards are malformed (incorrect number of rows or columns),
     * or invalid characters are found
    */
    Solver(string filename);
    /**
     * Parametrized constructor that loads a game from a given initial and goal board
     * 
     * Throws an exception if the two boards are of different dimensions
    */
    Solver(const Board& intial, const Board& goal);
    /**
     * Copy constructor that creates a deep copy of another game
    */
    Solver(const Solver& other);
    /**
     * Copy assignment operator that creates a deep copy of another game
    */
    Solver& operator=(const Solver& other);
    /**
     * Default destructor
    */
    ~Solver() = default;

    /**
     * Getter method that returns the initial board
    */
    Board getInitial() const { return _initial; }
    /**
     * Getter method that returns the target board
    */
    Board getGoal() const { return _goal; }
    /**
     * Protected helper that find all neighbors of a board. That is, all boards that can be reached
     * by performing one toggle operation on the given board
     * 
     * @param board the board whose neighbors are to be found
     * @return a list of boards that are neighbors to the given board
    */
    static vector<Board> getNeighbors(const Board& board);

    /**
     * Finds a solution to the game - a finite sequence of toggles that transforms the initial board
     * to the goal board.
     * 
     * To be implemented by concrete child classes
     * 
     * @return A vector of boards, each representing a step in the solution. An empty vector if no
     * solution exists
    */
    virtual vector<Board> solve() = 0;

    protected:
    /**
     * The initial and goal board of the game
    */
    Board _initial;
    Board _goal;

    /**
     * Protected helper that converts a predecessor map produced by graph traversal to a solution to
     * the puzzle by backtracking
     * Assumes that pred does not contain cycles
     * 
     * @param pred A predecessor map of the game graph, where pred[A] = B means that ...->B->A->... is
     * part of the path from initial to goal board
     * @return A solution to the puzzle. Empty vector if no solution can be found from the predecessor graph
    */
    vector<Board> predToSolution(const map<Board, Board>& pred) const;
};

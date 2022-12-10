#pragma once

#include <fstream>
#include <string>
#include <vector>
#include <stdexcept>
#include <queue>
#include <unordered_map>
#include <algorithm>

#include "board.h"
#include "solver.h"

class Traversal {
    public:
    /**
     * Default constructor that starts at a 5x5 board whose light bulbs are all off
    */
    Traversal();
    /**
     * Parametrized constructor that starts the traversal at a given board
    */
    Traversal(const Board& initial);
    /**
     * Copy constructor that creates a deep copy of another traversal
    */
    Traversal(const Traversal& other);
    /**
     * Copy assignment operator that creates a deep copy of another traversal
    */
    Traversal& operator=(const Traversal& other);
    /**
     * Default destructor
    */
    ~Traversal() = default;

    /**
     * Getter method that returns the initial board
    */
    Board getInitial() const;
    /**
     * Deref operator that returns the current board
    */
    Board operator*() const;
    /**
     * Returns if the traversal has exhausted the graph
     * 
     * @return true if the graph has been exhausted, false otherwise
    */
    bool end() const;

    /**
     * Return the depth of the current board
    */
    unsigned getDepth() const;
    /**
     * Return the number of boards that have been visited so far
    */
    unsigned getNumVisited() const;

    /**
     * Increment operator that moves the traversal to the next board
    */
    Traversal& operator++();

    private:
    Board _initial;
    /**
     * Boards to be visited
    */
    queue<Board> _to_visit = queue<Board>();
    /**
     * Depth of the visited / to be visited boards, defined as their distance to the origin
    */
    unordered_map<Board, unsigned, BoardHash> _depth = unordered_map<Board, unsigned, BoardHash>();
    /**
     * The number of boards that have been visited so far
    */
    unsigned _num_visited = 1;
};

#pragma once

#include <unordered_map>

#include "board.h"
#include "solver.h"

using BoardMap = unordered_map<Board, unsigned, BoardHash>; 

class SolverAStar : public Solver {
    public:
    // explicitly use parent class' constructors
    using Solver::Solver;
    using Solver::operator=;
    ~SolverAStar() = default;
    /**
     * Finds a solution to the game - a finite sequence of toggles that transforms the initial board
     * to the goal board - using A* search algorithm
     * 
     * @return A vector of boards, each representing a step in the solution
    */
    vector<Board> solve() override;

    private:
    /**
     * Return the hamming distance between board and goal. The hamming distance is defined
     * As the number of light bulbs whose state differ between the two boards
     * 
     * e.g. The hamming distance between the following two boards is 2
     * 000 110
     * 111 111
     * 000 000
     * 
     * @return The estimated distance
    */
    inline unsigned hammingDist(const Board& board) const;
    /**
     * Comparator classed used by the priority queue of the A* solve method
    */
    class Compare{
        public:
        /**
         * Parametrized constructor that accepts an initial board, a goal board, a pointer
         * to an external distance map, and a pointer to an external heuristic map
         * 
         * The two maps are designed be shared between multiple Compare instances, since
         * std::priority_queue creates a shallow copy of the comparator passed to it
        */
        Compare(const Board& initial, const Board& goal, BoardMap* dist, BoardMap* heuristic);
        /**
         * Compares the priority of two boards to see which one should be explored first
         * More specifically, this function compares d(a) + h(a) with d(b) + h(b),
         * where d is the distance of a board to the initial board, and h is the heuristic of the board
         * 
         * @return true if b should be explored before a, and false otherwise
        */
        bool operator()(const Board& a, const Board& b) const;

        private:
        /**
         * Distance map and goal board must be stored in compare
         * so they can be accessed by the comparator
        */
        Board _initial;
        Board _goal;
        BoardMap* _dist;
        BoardMap* _heuristic;
    };
};

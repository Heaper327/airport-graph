#include <unordered_map>

#include "board.h"
#include "solver.h"

class SolverAStar : public Solver {
    public:
    // explicitly use parent class' constructors
    using Solver::Solver;
    using Solver::operator=;
    /**
     * Finds a solution to the game - a finite sequence of toggles that transforms the initial board
     * to the goal board - using A* search algorithm
     * 
     * @return A vector of boards, each representing a step in the solution
    */
    vector<Board> solve() override;

    private:
    // TODO: calculating heuristics takes O(n^2) time, should we memoize it instead?
    /**
     * Comparator classed used by the priority queue of the A* solve method
    */
    class Compare{
        public:
        /**
         * Parametrized constructor that accepts an initial board, a goal board, and a pointer
         * to an external distance map
         * 
         * The distance map is designed be shared between multiple Compare instances, since
         * std::priority_queue creates a shallow copy of the comparator passed to it
        */
        Compare(const Board& initial, const Board& goal, unordered_map<Board, unsigned, BoardHash>* dist_to_initial);
        /**
         * Compares the priority of two boards to see which one should be explored first
         * More specifically, this function compares d(a) + h(a) with d(b) + h(b),
         * where d is the distance of a board to the initial board, and h is the heuristic of the board
         * 
         * @return true if b should be explored before a, and false otherwise
        */
        bool operator()(const Board& a, const Board& b) const;
        /**
         * Try to update the distance to origin of to_update by going through shortcut
         * Assumes that shortcut is a neighbor of to_update
         * 
         * @param to_update The board whose distance to origin is to be updated
         * @param shortcut The board that we try to travel through to get to to_update
         * @return true if to_update's distance is reduced, false otherwise
        */
        bool updateDist(const Board& to_update, const Board& shortcut);

        private:
        /**
         * Distance map and goal board must be stored in compare
         * so they can be accessed by the comparator
        */
        Board _initial;
        Board _goal;
        unordered_map<Board, unsigned, BoardHash>* _dist_to_initial;
    };

    /**
     * Return the hamming distance between two boards a and b. The hamming distance is defined
     * As the number of light bulbs whose state differ between the two boards
     * 
     * e.g. The hamming distance between the following two boards is 2
     * 000 110
     * 111 111
     * 000 000
     * 
     * @return The estimated distance
    */
    static unsigned hammingDist(const Board& a, const Board& b);
};

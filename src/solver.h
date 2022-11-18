#include <string>
#include <list>
#include <stdexcept>
#include <queue>
#include <map>
#include <algorithm>

#include "board.h"

/**
 * TODO: Make Solver a virtual base class, implemented by children classes
 * such as A* solver, IDF solver, etc. 
*/
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
     * Finds a solution to the game - a finite sequence of toggles that transforms the initial board
     * to the goal board - using A* search algorithm
     * 
     * @return A list of boards, each representing a step in the solution
    */
    list<Board> solveAStar() const;

    private:
    /**
     * The initial and goal board of the game
    */
    Board _initial;
    Board _goal;

    // TODO: calculating heuristics takes O(n^2) time, should we memoize it instead?
    /**
     * Comparator classed used by the priority queue of the A* solve method
    */
    class Compare{
        public:
        /**
         * Parametrized constructor
        */
        Compare(const Board& initial, const Board& goal);
        /**
         * Compares the priority of two boards in regard to searching for the goal board
         * More specifically, this function compares d(a) + h(a) with d(b) + h(b),
         * where d is the distance of a board to the initial board, and h is the heuristic function
         * 
         * @return true if a should be explored before b, and false otherwise
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
        map<Board, unsigned> dist_to_initial;
        Board _initial;
        Board _goal;
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
    /**
     * Private helper that find all neighbors of a board. That is, all boards that can be reached
     * by performing one toggle operation on the given board
     * 
     * @param board the board whose neighbors are to be found
     * @return a list of boards that are neighbors to the given board
    */
    static list<Board> getNeighbors(const Board& board);
};
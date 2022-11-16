#include <string>
#include <list>
#include <stdexcept>
#include <queue>
#include <map>

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
        Solver(const Solver&);
        /**
         * Copy assignment operator that creates a deep copy of another game
        */
        Solver& operator=(const Solver&);
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

        struct Node{
            Board board;
            unsigned dist_to_initial;
            unsigned dist_to_goal;
            /**
             * Comparator used in the priority queue of the A* solve method
             * The comparator assumes that both a and b are in _dist_to_initial
             * 
             * @return true if a should be visited before b, and false otherwise
            */
            bool operator<(const Node& rhs) const;
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
        unsigned hammingDist(const Board& a, const Board& b) const;
        /**
         * Private helper that find all neighbors of a board. That is, all boards that can be reached
         * by performing one toggle operation on the given board
         * 
         * @param board the board whose neighbors are to be found
         * @return a list of boards that are neighbors to the given board
        */
        list<Board> getNeighbors(const Board& board) const;
};
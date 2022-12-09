#include <unordered_map>

#include "board.h"
#include "solver.h"

class SolverIDS : public Solver {
    public:
    // explicitly inherit constructors
    using Solver::Solver;
    using Solver::operator=;
    using Solver::animateSolution;
    /**
     * Finds a solution to the game - a finite sequence of toggles that transforms the initial board
     * to the goal board - using BFS
     * 
     * @return A list of boards, each representing a step in the solution
    */
    vector<Board> solve() override;
    /**
     * Finds a solution to the game - a finite sequence of toggles that transforms the initial board
     * to the goal board - using DFS
     * 
     * @return A list of boards, each representing a step in the solution
    */
    vector<Board> solve(int max_search_depth);
    private:
    /**
    * Helper method that performs dfs on the game graph with a maximum depth
    */
    bool limited_dfs(int max_depth, int cur_depth, const Board& cur_stat,  const Board& target_stat, unordered_map<string, int>& visited, map<Board, Board>& predecessor);
};

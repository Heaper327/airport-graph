#pragma once

#include <unordered_map>

#include "board.h"
#include "solver.h"

class SolverIDS : public Solver {
    public:
    // explicitly inherit constructors
    using Solver::Solver;
    using Solver::operator=;
    /**
     * Finds a solution to the game - a finite sequence of toggles that transforms the initial board
     * to the goal board - using DFS
     * 
     * Unlike the parametrized solve(), the search depth is practically unlimited here
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
    bool search(unsigned remaining_depth, vector<Board>& path);
};

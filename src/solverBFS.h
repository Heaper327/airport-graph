#pragma once

#include <unordered_map>
#include <unordered_set>

#include "board.h"
#include "solver.h"

class SolverBFS : public Solver {
    public:
    // explicitly inherit constructors
    using Solver::Solver;
    using Solver::operator=;
    ~SolverBFS() = default;
    /**
     * Finds a solution to the game - a finite sequence of toggles that transforms the initial board
     * to the goal board - using BFS
     * 
     * @return A list of boards, each representing a step in the solution
    */
    vector<Board> solve() override;
};

#include "solverIDS.h"
using namespace std;

vector<Board> SolverIDS::solve() {
    // The maximum depth of a reachable board is (n - 2)^2
    // Since that is the total number of possible toggles
    return solve(_initial.getSize() * _initial.getSize());
}


bool SolverIDS::search(unsigned remaining_depth, vector<Board>& path) {
    Board& cur = path.back();
    if (remaining_depth == 0) {
        // we only check if goal is reached when we exhaust our depth
        // because if goal is at a lower depth, it would have been found by previous iterations already
        if (cur == _goal) {
            return true;
        }
        return false;
    }
    for (const auto& neighbor: getNeighbors(cur)) {
        // cycle pruning
        if (find(path.begin(), path.end(), neighbor) != path.end()) {
            continue;
        }
        path.push_back(neighbor);
        if (search(remaining_depth - 1, path)) { 
            return true;
        }
        path.pop_back();
    }
    return false;  
}

vector<Board> SolverIDS::solve(int max_search_depth) { 
    for(int search_depth = 0; search_depth < max_search_depth; search_depth++) {
        vector<Board> path = {_initial};
        if (search(search_depth, path)) {
            return path;
        }
    }
    return vector<Board>{};
}
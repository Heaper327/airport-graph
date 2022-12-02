#include "solverAStar.h"
using namespace std;

vector<Board> SolverAStar::solve() {
    map<Board, unsigned> dist_to_initial;
    Compare comp = Compare(_initial, _goal, &dist_to_initial);
    priority_queue<Board, vector<Board>, Compare> frontier{comp};
    frontier.push(_initial);
    map<Board, Board> predecessor;
    while (!frontier.empty()) {
        Board cur = frontier.top();
        frontier.pop();
        if (cur == _goal) {
            break;
        }
        for (const auto& neighbor: getNeighbors(cur)) {
            // since cur is in frontier, its distance is guaranteed to be defined
            if (comp.updateDist(neighbor, cur)) {
                predecessor[neighbor] = cur;
                frontier.push(neighbor);
            }
        }
    }
    return predToSolution(predecessor);
}

SolverAStar::Compare::Compare(const Board& initial, const Board& goal, map<Board, unsigned>* dist_to_initial): 
    _initial(initial), 
    _goal(goal), 
    _dist_to_initial(dist_to_initial) 
{
    dist_to_initial->insert({initial, 0});
}

bool SolverAStar::Compare::operator()(const Board& a, const Board& b) const {
    return _dist_to_initial->at(a) + hammingDist(a, _goal) > _dist_to_initial->at(b) + hammingDist(b, _goal);
}

bool SolverAStar::Compare::updateDist(const Board& to_update, const Board& shortcut) {
    /**
     * The distance between two adjacent boards is set to 9 to make hammingDist a consistent heuristic,
     * since the hamming distance between two adjacent boards is guaranteed to be <= 9
    */
    const unsigned kAdjacentDist = 9;
    unsigned new_dist = _dist_to_initial->at(shortcut) + kAdjacentDist;
    // if to_update's distance is undefined yet
    if (_dist_to_initial->find(to_update) == _dist_to_initial->end()) {
        _dist_to_initial->insert({to_update, new_dist});
        return true;
    } else if (new_dist < _dist_to_initial->at(to_update)) {
        _dist_to_initial->at(to_update) = new_dist;
        return true;
    }
    return false;
}

unsigned SolverAStar::hammingDist(const Board& a, const Board& b) {
    unsigned dist = 0; 
    for (size_t row = 0; row < a.getSize(); row++) {
        for (size_t col = 0; col < a.getSize(); col++) {
            if (a.getBulb(row, col) != b.getBulb(row, col))
                dist++;
        }
    }
    return dist;
}

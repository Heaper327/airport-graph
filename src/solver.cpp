#include "solver.h"

Solver::Solver(const Board& initial, const Board& goal): _initial(initial), _goal(goal) {
    if (initial.getSize() != goal.getSize()) {
        throw runtime_error("Initial and goal boards have different dimensions");
    }
}

list<Board> Solver::solveAStar() const {
    Compare comp = Compare(_initial, _goal);
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
    // backtrack to find the path from _initial to _goal
    list<Board> solution;
    for (Board cur = _goal; cur != _initial; cur = predecessor.at(cur)) {
        solution.push_front(cur);
    }
    solution.push_front(_initial);
    return solution;
}

bool Solver::Compare::operator()(const Board& a, const Board& b) const {
    return dist_to_initial.at(a) + hammingDist(a, _goal) + dist_to_initial.at(b) + hammingDist(b, _goal);
}

bool Solver::Compare::updateDist(const Board& to_update, const Board& shortcut) {
    /**
     * The distance between two adjacent boards. Set to 9 to make hammingDist a consistent heuristic,
     * since the hamming distance between two adjacent boards is guaranteed to be <= 9
    */
    const unsigned kAdjacentDist = 9;
    unsigned new_dist = dist_to_initial.at(shortcut) + kAdjacentDist;
    // if to_update's distance is undefined yet
    if (find(dist_to_initial.begin(), dist_to_initial.end(), to_update) == dist_to_initial.end()) {
        dist_to_initial.insert({to_update, new_dist});
        return true;
    } else if (new_dist < dist_to_initial.at(to_update)) {
        dist_to_initial.at(to_update) = new_dist;
        return true;
    }
    return false;
}

unsigned Solver::hammingDist(const Board& a, const Board& b) {
    unsigned dist = 0; 
    for (size_t row = 0; row < a.getSize(); row++) {
        for (size_t col = 0; col < a.getSize(); col++) {
            if (a.getBulb(row, col) != b.getBulb(row, col))
                dist++;
        }
    }
    return dist;
}
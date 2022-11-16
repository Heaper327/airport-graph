#include "solver.h"

Solver::Solver(const Board& initial, const Board& goal): _initial(initial), _goal(goal) {
    if (initial.getSize() != goal.getSize()) {
        throw runtime_error("Initial and goal boards have different dimensions");
    }
}

list<Board> Solver::solveAStar() const {
    priority_queue<Node> frontier;
    frontier.emplace(_initial, 0, hammingDist(_initial, _goal));
    while (!frontier.empty()) {
        Node cur = frontier.top();
        frontier.pop();
        for (const auto& neighbor: getNeighbors(cur.board)) {
            /**
             * The distance between two adjacent boards. Set to 9 to make hammingDist a consistent heuristic,
             * since the hamming distance between two adjacent boards is guaranteed to be <= 9
            */
            const unsigned kAdjacentDist = 9;
            unsigned new_dist_to_initial = cur.dist_to_initial + kAdjacentDist;
            if (new_dist_to_initial < 0 ) {} // oh no
            /**
             * TODO: save the distance to initial board of nodes that are not in the frontier
             * Either have a separate set of explored nodes, or remove node class and add a compare class
             * That stores all known distances and does comparison for our PQ
            */
        }
    }
    return list<Board>();
}

bool Solver::Node::operator<(const Node& rhs) const {
    return dist_to_initial + dist_to_goal < rhs.dist_to_initial + rhs.dist_to_goal;
}

unsigned Solver::hammingDist(const Board& a, const Board& b) const {
    unsigned dist = 0; 
    for (size_t row = 0; row < a.getSize(); row++) {
        for (size_t col = 0; col < a.getSize(); col++) {
            if (a.getBulb(row, col) != b.getBulb(row, col))
                dist++;
        }
    }
    return dist;
}
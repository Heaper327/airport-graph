#include "solverBFS.h"
using namespace std;

vector<Board> SolverBFS::solve() {
    queue<Board> to_visit;
    to_visit.push(_initial);
    unordered_map<Board, Board, BoardHash> pred;
    unordered_set<Board, BoardHash> is_visited{_initial};

    unsigned nodes_traversed = 0;
    while (!to_visit.empty()) {
        nodes_traversed++;
        const Board& cur = to_visit.front();
        if (cur == _goal) {
            break;
        }
        for (const auto& neighbor: getNeighbors(cur)) {
            if (is_visited.find(neighbor) == is_visited.end()) {
                to_visit.push(neighbor);
                pred[neighbor] = cur;
                is_visited.insert(neighbor);
            }
        }
        to_visit.pop();
    }
    vector<Board> solution = predToSolution(pred);
    // effective branching factor = N ^ (1/d)
    // N = total #nodes searched
    // d = solution depth
    cout << "Total node traversed: " << nodes_traversed << "\n";
    cout << "Solution distance: " << solution.size() - 1 << "\n";
    return solution;
}
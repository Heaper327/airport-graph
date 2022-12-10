#include "solverBFS.h"
using namespace std;

vector<Board> SolverBFS::solve() {
    queue<Board> to_visit;
    to_visit.push(_initial);
    unordered_map<Board, Board, BoardHash> pred;
    unordered_set<Board, BoardHash> is_visited{_initial};

    while (!to_visit.empty()) {
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
    return predToSolution(pred);
}
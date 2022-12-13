#include "solverAStar.h"
using namespace std;

vector<Board> SolverAStar::solve() {
    BoardMap dist, heuristic;
    dist[_initial] = 0;
    heuristic[_initial] = hammingDist(_initial);

    Compare comp = Compare(_initial, _goal, &dist, &heuristic);
    priority_queue<Board, vector<Board>, Compare> frontier{comp};
    frontier.push(_initial);

    unordered_map<Board, Board, BoardHash> pred;
    unsigned nodes_traversed = 0;

    while (!frontier.empty()) {        
        nodes_traversed++;
        Board cur = frontier.top();
        frontier.pop();
        if (cur == _goal) {
            break;
        }
        for (const auto& neighbor: getNeighbors(cur)) {
            // since our heuristics is admissible, we will never find a shortcut to a visited node
            // thus we ignore them
            if (dist.find(neighbor) == dist.end()) {
                /**
                 * The distance between two adjacent boards is set to 9 to make hammingDist a consistent heuristic,
                 * since the hamming distance between two adjacent boards is guaranteed to be <= 9
                */
                const unsigned kEdgeLength = 9;
                dist[neighbor] = dist.at(cur) + kEdgeLength;
                heuristic[neighbor] = hammingDist(neighbor);
                frontier.push(neighbor);
                pred[neighbor] = cur;
            }
        }
    }
    vector<Board> solution = predToSolution(pred);
    std::cout << "Total node traversed: " << nodes_traversed << "\n";
    std::cout << "Solution distance: " << solution.size() - 1 << "\n";
    return solution;
}

SolverAStar::Compare::Compare(const Board& initial, const Board& goal, BoardMap* dist, BoardMap* heuristic): 
    _initial(initial), 
    _goal(goal), 
    _dist(dist),
    _heuristic(heuristic)
{
    // do nothing
}

bool SolverAStar::Compare::operator()(const Board& a, const Board& b) const {
    return _dist->at(a) + _heuristic->at(a) > _dist->at(b) + _heuristic->at(b);
}

inline unsigned SolverAStar::hammingDist(const Board& board) const {
    unsigned dist = 0;
    for (size_t row = 0; row < board.getSize(); row++) {
        for (size_t col = 0; col < board.getSize(); col++) {
            dist += board.getBulb(row, col) != _goal.getBulb(row, col);
        }
    }
    return dist;
}

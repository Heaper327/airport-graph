#include "solver.h"
using namespace std;

Solver::Solver(const Board& initial, const Board& goal): _initial(initial), _goal(goal) {
    if (initial.getSize() != goal.getSize()) {
        throw runtime_error("Initial and goal boards have different dimensions");
    }
}

vector<Board> Solver::getNeighbors(const Board& board) {
    size_t size = board.getSize();
    if (size < 3) {
        throw runtime_error("wrong size");
    }
    size_t toggle_bound = size - 2;
    vector<Board> to_return(toggle_bound * toggle_bound);
    size_t idx = 0;
    for (size_t i = 0; i < toggle_bound; i++) {
        for (size_t j = 0; j < toggle_bound ; j++ ) {
            to_return.at(idx) = board;
            to_return.at(idx).toggle(i, j);
            idx++;
        }
    }
    return to_return;
}

Solver::Solver(string filename) {
    ifstream file(filename);
    string line;
    // Read and verify size of the boards
    if (!getline(file, line))
        throw runtime_error("File does not contain the dimension of boards");
    if (stoi(line) < 3) {
        throw runtime_error("Board dimension must be at least 3");
    }
    unsigned n = stoi(line);
    _initial = Board(n);
    _goal = Board(n);
    // Read and verify the content of the boards
    for (unsigned row = 0; row < n; row++) {
        if (!getline(file, line) || line.size() != n)
            throw runtime_error("Boards are malformed");
        for (unsigned col = 0; col < n; col++) {
            char bulb = line.at(col);
            if (bulb == '0') {
                _initial.setBulb(row, col, false);
            } else if (bulb == '1') {
                _initial.setBulb(row, col, true);
            } else {
                throw runtime_error("Boards contain invalid character. Only 0 and 1 are allowed in the boards");
            }
        }
    }
    for (unsigned row = 0; row < n; row++) {
        if (!getline(file, line) || line.size() != n)
            throw runtime_error("Boards are malformed");
        for (unsigned col = 0; col < n; col++) {
            char bulb = line.at(col);
            if (bulb == '0') {
                _goal.setBulb(row, col, false);
            } else if (bulb == '1') {
                _goal.setBulb(row, col, true);
            } else {
                throw runtime_error("Boards contain invalid character. Only 0 and 1 are allowed in the boards");
            }
        }
    }
}

Solver& Solver::operator=(const Solver& other) {
    _initial = other._initial;
    _goal = other._goal;
    return *this;
}

Solver::Solver(const Solver& other) {
    _initial = other._initial;
    _goal = other._goal;
}

vector<Board> Solver::predToSolution(const map<Board, Board>& pred) const {
    vector<Board> solution;
    Board cur = _goal;
    while (pred.find(cur) != pred.end()) {  
        solution.push_back(cur);
        cur = pred.at(cur);
    }
    // verify that solution is indeed a path from initial to goal
    if (cur != _initial) {
        return vector<Board>{};
    }
    solution.push_back(_initial);
    reverse(solution.begin(), solution.end());
    return solution;
}
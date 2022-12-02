#include "solver.h"
using namespace std;

Solver::Solver(const Board& initial, const Board& goal): _initial(initial), _goal(goal) {
    if (initial.getSize() != goal.getSize()) {
        throw runtime_error("Initial and goal boards have different dimensions");
    }
}

vector<Board> Solver::getNeighbors(const Board& board) {
    vector<Board> toReturn;
    size_t size = board.getSize();
    if (size < 3) {
        throw runtime_error("wrong size");
    }
    for (size_t i =0; i <= size -3; i++) {
        for (size_t j =0; j <= size - 3 ; j++ ) {
            Board tem = board;
            tem.toggle(i, j);
            toReturn.push_back(tem);
        }
    }

    return toReturn;
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
                // do nothing
            } else if (bulb == '1') {
                _initial.toggleOne(row, col);
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
                // do nothing
            } else if (bulb == '1') {
                _goal.toggleOne(row, col);
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
    for (Board cur = _goal; pred.find(cur) != pred.end(); cur = pred.at(cur)) {  
        solution.push_back(cur);
    }
    reverse(solution.begin(), solution.end());
    // verify that solution is indeed a path from initial to goal
    if (solution.front() != _initial) {
        return vector<Board>{};
    }
    return solution;
}
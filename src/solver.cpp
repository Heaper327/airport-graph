#include "solver.h"
#include <fstream>
#include <string>
#include <iostream>
#include <list>
using namespace std;

Solver::Solver(const Board& initial, const Board& goal): _initial(initial), _goal(goal) {
    if (initial.getSize() != goal.getSize()) {
        throw runtime_error("Initial and goal boards have different dimensions");
    }
}

list<Board> Solver::getNeighbors(const Board& board) {
    list<Board> toReturn;
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
    if (dist_to_initial.find(to_update) == dist_to_initial.end()) {
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
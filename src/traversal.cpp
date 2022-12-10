#include "traversal.h"

/**
 * Default constructor that starts at a 5x5 board whose light bulbs are all off
*/
Traversal::Traversal() : _initial(Board(5)) {
    _to_visit.push(_initial);
    _depth[_initial] = 0;
}
/**
 * Parametrized constructor that starts the traversal at a given board
*/
Traversal::Traversal(const Board& initial) : _initial(initial) {
    _to_visit.push(_initial);
    _depth[_initial] = 0;
}
/**
 * Copy constructor that creates a deep copy of another traversal
*/
Traversal::Traversal(const Traversal& other) {
    *this = other;
}
/**
 * Copy assignment operator that creates a deep copy of another traversal
*/
Traversal& Traversal::operator=(const Traversal& other) {
    if (this == &other) {
        return *this;
    }
    _initial = other._initial;
    _to_visit = other._to_visit;
    return *this;
}

/**
 * Getter method that returns the initial board
*/
Board Traversal::getInitial() const {
    return _initial;
}
/**
 * Deref operator that returns the current board
*/
Board Traversal::operator*() const {
    return _to_visit.front();
}
/**
 * Returns if the traversal has exhausted the graph
 * 
 * @return true if the graph has been exhausted, false otherwise
*/
bool Traversal::end() const {
    return _to_visit.empty();
}
/**
 * Return the depth of the current board
*/
unsigned Traversal::getDepth() const {
    return _depth.at(_to_visit.front());
}
/**
 * Return the number of boards that have been visited so far
*/
unsigned Traversal::getNumVisited() const {
    return _num_visited;
}
/**
 * Increment operator that moves the traversal to the next board
*/
Traversal& Traversal::operator++() {
    if (_to_visit.empty()) {
        return *this;
    }
    const Board& cur = _to_visit.front();
    for (const auto& neighbor : Solver::getNeighbors(cur)) {
        unsigned neighbor_depth = _depth[cur] + 1;
        if (_depth.find(neighbor) == _depth.end()) {
            _to_visit.push(neighbor);
            _depth[neighbor] = neighbor_depth;
        }
    }
    _to_visit.pop();
    if (!_to_visit.empty()) {
        _num_visited++;
    }
    return *this;
}

#include <iostream>
#include "board.h"
#include "solverAStar.h"
#include "solverIDS.h"
#include "cs225/PNG.h"
#include "traversal.h"

using namespace std;

void printSolution(const vector<Board>& solution);

void analyzeGraph(unsigned size, unsigned depth);

int main()
{
    analyzeGraph(6, 100);
    // Board initial(7);
    // Board goal = initial;
    // goal.toggle(2, 2);
    // goal.toggle(0, 0);
    // goal.toggle(1, 1);
    // goal.toggle(0, 4);
    // goal.toggle(4, 2);

    // SolverIDS solver = SolverIDS{initial, goal};
    // // SolverAStar solver = SolverAStar{"../tests/4x4-simple-game.txt"};
    // auto solution = solver.solve(10);
    // printSolution(solution);
}

void printSolution(const vector<Board>& solution) {
    for (const auto& step : solution) {
        cout << "==========\n";
        cout << step.print() << "\n";
    }
    cout << "==========\n";
}

void analyzeGraph(unsigned size, unsigned depth) {
    Board initial(size);
    vector<unsigned> hist(size * size);
    Traversal trav(initial);
    for (; !trav.end(); ++trav) {
        if (trav.getDepth() > depth)
            break;
        hist[trav.getDepth()]++;
    }
    cout << "Size of game: " << size << "\n";
    for (size_t i = 0; i < hist.size(); i++) {
        if (hist[i] == 0)
            break;
        cout << "Number of nodes at depth " << i << ": " << hist[i]<< "\n";
    }
    cout << "Total number of nodes: " << trav.getNumVisited() << "\n";
}
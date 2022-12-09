#include <iostream>
#include "board.h"
#include "solverAStar.h"
#include "cs225/PNG.h"

using namespace std;

void printSolution(const vector<Board>& solution);

int main()
{
    Board initial(5);
    Board goal = initial;
    goal.toggle(0, 0);
    goal.toggle(2, 2);
    goal.toggle(0, 1);
    goal.toggle(1, 0);

    // Solver solver{initial, goal};
    SolverAStar solver = SolverAStar{"../tests/4x4-simple-game.txt"};
    auto solution = solver.solve();
    printSolution(solution);
}

void printSolution(const vector<Board>& solution) {
    for (const auto& step : solution) {
        cout << "==========\n";
        cout << step.print() << "\n";
    }
    cout << "==========\n";
}

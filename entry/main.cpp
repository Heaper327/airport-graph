#include <iostream>
#include "board.h"
#include "solver.h"
#include "cs225/PNG.h"

using namespace std;

int main()
{
    Board initial(5);
    Board goal = initial;
    goal.toggle(0, 0);

    Solver solver{initial, goal};
    auto solution = solver.solveAStar();
    for (const auto& step : solution) {
        cout << "==========\n";
        cout << step.print() << "\n";
    }
    return 0;
}

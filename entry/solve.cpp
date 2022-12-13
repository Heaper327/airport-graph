#include <iostream>
#include <string>
#include <argp.h>

#include "board.h"
#include "solverAStar.h"
#include "solverIDS.h"
#include "solverBFS.h"
#include "cs225/PNG.h"
#include "visual.h"

using namespace std;

void printSolution(const vector<Board>& solution);

int main(int argc, char* argv[])
{
    string input;
    cout << "Which solver would you like to use? (options: A*, IDS, BFS)" << endl;
    cin >> input;
    Solver* solver;
    if (input == "A*") {
        solver = new SolverAStar();
    } else if (input == "IDS") {
        solver = new SolverIDS();
    } else if (input == "BFS") {
        solver = new SolverBFS();
    } else {
        throw runtime_error("Unknown solver type, valid options: A*, IDS, BFS");
    }
    cout << "Please enter the path of the puzzle file:" << endl;;
    cin >> input;
    solver->loadFromFile(input);

    cout << "Puzzle successfully loaded\nInitial board:" << endl;;
    cout << solver->getInitial().print() << "\n";
    cout << "Goal board:" << endl;;
    cout << solver->getGoal().print() << "\n";

    cout << "Solving, please wait..." << endl;;
    vector<Board> solution = solver->solve();
    if (solution.empty()) {
        cout << "Solution does not exist: initial and goal boards not connected" << endl;;
        return 0;
    }
    cout << "Solution found:" << endl;;
    printSolution(solution);
    cout << "Would you like to save solution to an animated gif? (Y/n)" << endl;;
    cin >> input;
    if (input == "Y") {
        cout << "What path would you like to save the gif to?" << endl;;
        cin >> input;
        Animation anime = animateSolution(solution);
        anime.write(input);
    }
}

void printSolution(const vector<Board>& solution) {
    for (const auto& step : solution) {
        cout << "==========\n";
        cout << step.print() << "\n";
    }
    cout << "==========\n";
}
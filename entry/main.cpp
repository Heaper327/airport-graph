#include <iostream>
#include <bitset>
#include "board.h"
#include "solverAStar.h"
#include "solverIDS.h"
#include "solverBFS.h"
#include "cs225/PNG.h"
#include "traversal.h"
#include "visual.h"
using namespace std;

void printSolution(const vector<Board>& solution);

void analyzeGraph(unsigned size, unsigned depth);

void analyzeGroups();

void bitsetMock();

int main()
{

    // bitsetMock();
    // return 0;

    Board goal({
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 1, 1, 0, 0, 1, 1, 0},
        {0, 1, 1, 0, 0, 1, 1, 0},
        {0, 0, 0, 1, 1, 0, 0, 0},
        {0, 0, 1, 1, 1, 1, 0, 0},
        {0, 0, 1, 1, 1, 1, 0, 0},
        {0, 0, 1, 0, 0, 1, 0, 0},
    });
    Board initial = goal;
    initial.toggle(2, 1);
    initial.toggle(2, 4);
    initial.toggle(5, 1);
    initial.toggle(5, 4);
    initial.toggle(2, 3);
    // goal.toggle(4, 1);
    // goal.toggle(3, 3);
    // goal.toggle(3, 4);

    Solver* solver = new SolverBFS{"../tests/8x8-creeper-game.txt"};
    // SolverAStar solver = SolverAStar{"../tests/4x4-simple-game.txt"};
    auto solution = solver->solve();
    Animation anime = animateSolution(solution);
    anime.write("gif.gif");
    PNG start = *(boardToPNG(initial));
    PNG end = *(boardToPNG(goal));
    start.writeToFile("start.png");
    end.writeToFile("end.png");
    delete solver;
}

void bitsetMock() {
    unordered_map<bitset<36>, unsigned> map;
    for (int i = 0; i < 10000; i++) {
        bitset<36> set{(unsigned long long)rand()};
        map.insert({set, 0});
        cout << map.at(set) << endl;
    }
}

void analyzeGroups() {
    unsigned size = 6;
    Board initial(size);
    for (unsigned i = 0; i < size; i++) {
        for (unsigned j = 0; j < size; j++) {
                Board goal = initial;
                goal.setBulb(i, j, true);
                Solver* solver = new SolverBFS{initial, goal};
                auto solution = solver->solve();
                printSolution(solution);
        }
    }
    return;

    cout << initial.print() << endl;
    for (unsigned i = 0; i < size - 2; i++) {
        for (unsigned j = 0; j < size - 2; j++) {
            initial.toggle(i, j);
        }
    }
    cout << initial.print() << endl;
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
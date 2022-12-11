#include <catch2/catch_test_macros.hpp>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <stack>
#include "cs225/PNG.h"

#include "board.h"
#include "solverIDS.h"
#include "test-utils.h"

using namespace cs225;
using namespace std;

TEST_CASE("Solving 3x3 game test, IDS", "[ids]")
{
	SolverIDS solver{"../tests/3x3-game.txt"};
	vector<Board> solution = solver.solve();
	vector<Board> expected_solution = {
		Board({
			{0, 0, 0},
			{0, 0, 0},
			{0, 0, 0}
		}),
		Board({
			{1, 1, 1},
			{1, 1, 1},
			{1, 1, 1}
		}),
	};
	REQUIRE(solution == expected_solution);
}

TEST_CASE("Solving simple 4x4 game test, IDS", "[ids]")
{
	SolverIDS solver{"../tests/4x4-simple-game.txt"};
	vector<Board> solution = solver.solve();
	vector<Board> expected_solution = {
		Board({
			{0, 0, 0, 0},
			{0, 0, 0, 0},
			{0, 0, 0, 0},
			{0, 0, 0, 0},
		}),
		Board({
			{0, 1, 1, 1},
			{0, 1, 1, 1},
			{0, 1, 1, 1},
			{0, 0, 0, 0},
		}),
	};
	REQUIRE(solution == expected_solution);
}

TEST_CASE("Random 5x5 game test, IDS", "[ids]")
{
	Solver* solver = new SolverIDS();
	REQUIRE(randomSolveTest(solver, 5, 5));
	delete solver;
}

TEST_CASE("Random 6x6 game test, IDS", "[ids]")
{
	Solver* solver = new SolverIDS();
	REQUIRE(randomSolveTest(solver, 6, 4));
	delete solver;
} 

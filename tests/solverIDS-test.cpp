#include <catch2/catch_test_macros.hpp>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <stack>
#include "cs225/PNG.h"

#include "board.h"
#include "solverIDS.h"

using namespace cs225;
using namespace std;

TEST_CASE("Solving 3x3 game test, BFS", "[ids]")
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

TEST_CASE("Solving simple 4x4 game test, BFS", "[ids]")
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

 

TEST_CASE("Solving 3x3 game test, IDS", "[ids]")
{
	SolverIDS solver{"../tests/3x3-game.txt"};
	vector<Board> solution = solver.solve(100);
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
	vector<Board> solution = solver.solve(100);
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



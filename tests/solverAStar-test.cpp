#include <catch2/catch_test_macros.hpp>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <stack>
#include "cs225/PNG.h"

#include "board.h"
#include "solverAStar.h"

using namespace cs225;
using namespace std;

TEST_CASE("Board constructor test", "[astar]")
{
	Board initial = Board({{0, 0, 0}, {0, 0, 0}, {0, 0, 0}});
	Board goal = Board({{1, 1, 1}, {1, 1, 1}, {1, 1, 1}});
	SolverAStar solver{initial, goal};
	REQUIRE(solver.getInitial() == initial);
	REQUIRE(solver.getGoal() == goal);
}

TEST_CASE("Board constructor test, different size", "[astar]")
{
	Board initial = Board({{0, 0, 0}, {0, 0, 0}, {0, 0, 0}});
	Board goal = Board({{1, 1, 1, 1}, {1, 1, 1, 1}, {1, 1, 1, 1}, {1, 1, 1, 1}});
	REQUIRE_THROWS(SolverAStar{initial, goal});
}


TEST_CASE("File constructor test", "[astar]")
{
	SolverAStar solver{"../tests/3x3-game.txt"};
	Board expected_initial = Board({{0, 0, 0}, {0, 0, 0}, {0, 0, 0}});
	Board expected_goal = Board({{1, 1, 1}, {1, 1, 1}, {1, 1, 1}});
	REQUIRE(solver.getInitial() == expected_initial);
	REQUIRE(solver.getGoal() == expected_goal);
}

TEST_CASE("File constructor test, malformed board", "[astar]")
{
	REQUIRE_THROWS(SolverAStar{"../tests/4x4-malformed-game.txt"});
}

TEST_CASE("File constructor test, missing row", "[astar]")
{
	REQUIRE_THROWS(SolverAStar{"../tests/4x4-missing-row-game.txt"});
}

TEST_CASE("File constructor test, invalid char", "[astar]")
{
	REQUIRE_THROWS(SolverAStar{"../tests/4x4-invalid-char-game.txt"});
}

TEST_CASE("File constructor test, incorrect dimension", "[astar]")
{
	REQUIRE_THROWS(SolverAStar{"../tests/4x4-n-mismatch-game.txt"});
}

TEST_CASE("Solving 3x3 game test", "[astar]")
{
	SolverAStar solver{"../tests/3x3-game.txt"};
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

TEST_CASE("Solving simple 4x4 game test", "[astar]")
{
	SolverAStar solver{"../tests/4x4-simple-game.txt"};
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

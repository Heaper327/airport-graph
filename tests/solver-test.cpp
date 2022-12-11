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

/**
 * The following cases test functions implemented by Solver.cpp
 * Which are inherited by A* and not overriden
 * We cannot use instances of Solver for testing since it's abstract
*/

TEST_CASE("Board constructor test", "[solver]")
{
	Board initial = Board({{0, 0, 0}, {0, 0, 0}, {0, 0, 0}});
	Board goal = Board({{1, 1, 1}, {1, 1, 1}, {1, 1, 1}});
	SolverAStar solver{initial, goal};
	REQUIRE(solver.getInitial() == initial);
	REQUIRE(solver.getGoal() == goal);
}

TEST_CASE("Board constructor test, different size", "[solver]")
{
	Board initial = Board({{0, 0, 0}, {0, 0, 0}, {0, 0, 0}});
	Board goal = Board({{1, 1, 1, 1}, {1, 1, 1, 1}, {1, 1, 1, 1}, {1, 1, 1, 1}});
	REQUIRE_THROWS(SolverAStar{initial, goal});
}


TEST_CASE("File constructor test", "[solver]")
{
	SolverAStar solver{"../tests/3x3-game.txt"};
	Board expected_initial = Board({{0, 0, 0}, {0, 0, 0}, {0, 0, 0}});
	Board expected_goal = Board({{1, 1, 1}, {1, 1, 1}, {1, 1, 1}});
	REQUIRE(solver.getInitial() == expected_initial);
	REQUIRE(solver.getGoal() == expected_goal);
}

TEST_CASE("File constructor test, malformed board", "[solver]")
{
	REQUIRE_THROWS(SolverAStar{"../tests/4x4-malformed-game.txt"});
}

TEST_CASE("File constructor test, missing row", "[solver]")
{
	REQUIRE_THROWS(SolverAStar{"../tests/4x4-missing-row-game.txt"});
}

TEST_CASE("File constructor test, invalid char", "[solver]")
{
	REQUIRE_THROWS(SolverAStar{"../tests/4x4-invalid-char-game.txt"});
}

TEST_CASE("File constructor test, incorrect dimension", "[solver]")
{
	REQUIRE_THROWS(SolverAStar{"../tests/4x4-n-mismatch-game.txt"});
}

TEST_CASE("Board loading test", "[solver]")
{
	Board initial = Board({{0, 0, 0}, {0, 0, 0}, {0, 0, 0}});
	Board goal = Board({{1, 1, 1}, {1, 1, 1}, {1, 1, 1}});
	SolverAStar solver;
	solver.loadFromBoards(initial, goal);
	REQUIRE(solver.getInitial() == initial);
	REQUIRE(solver.getGoal() == goal);
}

TEST_CASE("Board loading test, different size", "[solver]")
{
	Board initial = Board({{0, 0, 0}, {0, 0, 0}, {0, 0, 0}});
	Board goal = Board({{1, 1, 1, 1}, {1, 1, 1, 1}, {1, 1, 1, 1}, {1, 1, 1, 1}});
	SolverAStar solver;
	REQUIRE_THROWS(solver.loadFromBoards(initial, goal));
}


TEST_CASE("File loading test", "[solver]")
{
	SolverAStar solver;
	solver.loadFromFile("../tests/3x3-game.txt");
	Board expected_initial = Board({{0, 0, 0}, {0, 0, 0}, {0, 0, 0}});
	Board expected_goal = Board({{1, 1, 1}, {1, 1, 1}, {1, 1, 1}});
	REQUIRE(solver.getInitial() == expected_initial);
	REQUIRE(solver.getGoal() == expected_goal);
}

TEST_CASE("File loading test, malformed board", "[solver]")
{
	SolverAStar solver;
	REQUIRE_THROWS(solver.loadFromFile("../tests/4x4-malformed-game.txt"));
}

TEST_CASE("File loading test, missing row", "[solver]")
{
	SolverAStar solver;
	REQUIRE_THROWS(solver.loadFromFile("../tests/4x4-missing-row-game.txt"));
}

TEST_CASE("File loading test, invalid char", "[solver]")
{
	SolverAStar solver;
	REQUIRE_THROWS(solver.loadFromFile("../tests/4x4-invalid-char-game.txt"));
}

TEST_CASE("File loading test, incorrect dimension", "[solver]")
{
	SolverAStar solver;
	REQUIRE_THROWS(solver.loadFromFile("../tests/4x4-n-mismatch-game.txt"));
}

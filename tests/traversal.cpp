#include <catch2/catch_test_macros.hpp>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <stack>
#include "cs225/PNG.h"

#include "traversal.h"
#include "board.h"
#include "solver.h"

using namespace cs225;
using namespace std;


TEST_CASE("Default constructor test", "[traversal]")
{
	Traversal traversal{};
	REQUIRE(traversal.getInitial() == Board(5));
}

TEST_CASE("Parametrized constructor test", "[traversal]")
{
	Board board({{1, 0, 1}, {1, 0, 1}, {1, 0, 1}});
	Traversal traversal(board);
	REQUIRE(traversal.getInitial() == board);
}

TEST_CASE("Copy constructor test", "[traversal]")
{
	Board board({{1, 0, 1}, {1, 0, 1}, {1, 0, 1}});
	Traversal traversal(board);
	Traversal copy(traversal);
	REQUIRE(traversal.getInitial() == copy.getInitial());
}

TEST_CASE("Copy assignment operator test", "[traversal]")
{
	Board board({{1, 0, 1}, {1, 0, 1}, {1, 0, 1}});
	Traversal traversal(board);
	Traversal copy = traversal;
	REQUIRE(traversal.getInitial() == copy.getInitial());
}

TEST_CASE("Simple traversal test", "[traversal]")
{
	Board initial({{0, 0, 0}, {0, 0, 0}, {0, 0, 0}});
	Board end({{1, 1, 1}, {1, 1, 1}, {1, 1, 1}});
	Traversal traversal(initial);
	++traversal;
	REQUIRE(*traversal == end);
}

TEST_CASE("Traversal termination test", "[traversal]")
{
	Board initial({{0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}});
	Traversal traversal(initial);
	++traversal;
	while (!traversal.end()) {
		Board cur = *traversal;
		REQUIRE(cur.getSize() == 4);
		++traversal;
	}
}

TEST_CASE("Node count test", "[traversal]")
{
	Board initial({{0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}});
	Traversal traversal(initial);
	while (!traversal.end()) {
		++traversal;
	}
	REQUIRE(traversal.getNumVisited() == 16);
}

TEST_CASE("Depth test", "[traversal]")
{
	Board initial({{0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}});
	Traversal traversal(initial);
	REQUIRE(traversal.getDepth() == 0);
	++traversal;
	REQUIRE(traversal.getDepth() == 1);
}

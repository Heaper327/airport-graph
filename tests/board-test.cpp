#include <catch2/catch_test_macros.hpp>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <stack>
#include "cs225/PNG.h"

#include "board.h"

using namespace cs225;
using namespace std;


TEST_CASE("Default constructor test", "[weight=10][part1]")
{
	Board board(5);
	REQUIRE(board.getSize() == 5);
	for (size_t row = 0; row < 5; row++) {
		for (size_t col = 0; col < 5; col++) {
			REQUIRE(board.getBulb(row, col) == false);
		}
	}
}

TEST_CASE("Parametrized constructor test", "[weight=10][part1]")
{
	vector<vector<bool>> input = {{0, 1, 0}, {1, 0, 1}, {0, 1, 0}};
	Board board(input);
	for (size_t row = 0; row < input.size(); row++) {
		for (size_t col = 0; col < input.size(); col++) {
			REQUIRE(board.getBulb(row, col) == input[row][col]);
		}
	}
}

TEST_CASE("Copy constructor test", "[weight=10][part1]")
{
	vector<vector<bool>> input = {{0, 1, 0}, {1, 0, 1}, {0, 1, 0}};
	Board board(input);
	Board board2(board);
	REQUIRE(board == board2);
}

TEST_CASE("Copy assignment operator test", "[weight=10][part1]")
{
	vector<vector<bool>> input = {{0, 1, 0}, {1, 0, 1}, {0, 1, 0}};
	Board board(input);
	Board board2(5);
	board2 = board;
	REQUIRE(board == board2);
}

TEST_CASE("Equality test", "[weight=10][part1]")
{
	vector<vector<bool>> input = {{0, 1, 0}, {1, 0, 1}, {0, 1, 0}};
	Board board(input);
	Board board2(input);
	REQUIRE(board == board2);
}

TEST_CASE("Equality test w/ toggle", "[weight=10][part1]")
{
	vector<vector<bool>> input = {{1, 1, 1}, {1, 1, 1}, {1, 1, 1}};
	Board board(input);
	Board board2(3);
	board2.toggle(0, 0);
	REQUIRE(board == board2);
}

TEST_CASE("Inequality test simple", "[weight=10][part1]")
{
	vector<vector<bool>> input = {{1, 1, 1}, {1, 1, 1}, {1, 1, 1}};
	vector<vector<bool>> input2 = {{1, 1, 1}, {1, 0, 1}, {1, 1, 1}};
	Board board(input);
	Board board2(input2);
	REQUIRE(board != board2);
}

TEST_CASE("Inequality test different size", "[weight=10][part1]")
{
	vector<vector<bool>> input = {{1, 1, 1}, {1, 1, 1}, {1, 1, 1}};
	Board board(input);
	Board board2(5);
	REQUIRE(board != board2);
}

TEST_CASE("Toggle test simple", "[weight=10][part1]")
{
	vector<vector<bool>> before = {{0, 1, 0}, {1, 0, 1}, {0, 1, 0}};
	vector<vector<bool>> after = {{1, 0, 1}, {0, 1, 0}, {1, 0, 1}};
	Board board_before(before);
	Board board_after(after);
	board_before.toggle(0, 0);
	REQUIRE(board_before == board_after);
}

TEST_CASE("Repeated toggle test", "[weight=10][part1]")
{
	vector<vector<bool>> before = {{0, 1, 0}, {1, 0, 1}, {0, 1, 0}};
	Board board_before(before);
	Board board_after(before);
	board_before.toggle(0, 0);
	board_before.toggle(0, 0);
	REQUIRE(board_before == board_after);
}

TEST_CASE("Completely out of bound toggle test", "[weight=10][part1]")
{
	vector<vector<bool>> input = {{0, 1, 0}, {1, 0, 1}, {0, 1, 0}};
	Board board(input);
	REQUIRE_THROWS(board.toggle(5, 5));
}

TEST_CASE("Partially out of bound toggle test", "[weight=10][part1]")
{
	vector<vector<bool>> input = {{0, 1, 0}, {1, 0, 1}, {0, 1, 0}};
	Board board(input);
	REQUIRE_THROWS(board.toggle(2, 2));
}

TEST_CASE("Get size test", "[weight=10][part1]")
{
	Board board(6);
	REQUIRE(board.getSize() == 6);
}

TEST_CASE("Subtraction test, identical boards", "[weight=10][part1]")
{
	vector<vector<bool>> input = {{0, 1, 0, 1}, {1, 0, 1, 0}, {0, 1, 0, 1}, {1, 0, 1, 0}};
	Board board1(input);
	Board diff(4);
	REQUIRE(board1 - board1 == diff);
}

TEST_CASE("Subtraction test, different boards", "[weight=10][part1]")
{
	vector<vector<bool>> input1 = {{0, 1, 0, 1}, {1, 0, 1, 0}, {0, 1, 0, 1}, {1, 0, 1, 0}};
	vector<vector<bool>> input2 = {{0, 0, 0, 0}, {1, 1, 1, 1}, {0, 0, 0, 0}, {1, 1, 1, 1}};
	vector<vector<bool>> input3 = {{0, 1, 0, 1}, {0, 1, 0, 1}, {0, 1, 0, 1}, {0, 1, 0, 1}};
	Board board1(input1);
	Board board2(input2);
	Board diff(input3);
	REQUIRE(board1 - board2 == diff);
}

TEST_CASE("Subtraction test, symmetry", "[weight=10][part1]")
{
	vector<vector<bool>> input1 = {{0, 1, 0, 1}, {1, 0, 1, 0}, {0, 1, 0, 1}, {1, 0, 1, 0}};
	vector<vector<bool>> input2 = {{0, 0, 0, 0}, {1, 1, 1, 1}, {0, 0, 0, 0}, {1, 1, 1, 1}};
	Board board1(input1);
	Board board2(input2);
	REQUIRE(board1 - board2 == board2 - board1);
}

TEST_CASE("Less than test, anti-reflexive", "[weight=10][part1]")
{
	vector<vector<bool>> input1 = {{0, 1, 0, 1}, {1, 0, 1, 0}, {0, 1, 0, 1}, {1, 0, 1, 0}};
	Board board1(input1);
	REQUIRE(!(board1 < board1));
}

TEST_CASE("Less than test, anti-symmetry", "[weight=10][part1]")
{
	vector<vector<bool>> input1 = {{0, 1, 0, 1}, {1, 0, 1, 0}, {0, 1, 0, 1}, {1, 0, 1, 0}};
	vector<vector<bool>> input2 = {{0, 0, 0, 0}, {1, 1, 1, 1}, {0, 0, 0, 0}, {1, 1, 1, 1}};
	Board board1(input1);
	Board board2(input2);
	REQUIRE(!(board1 < board2 && board2 < board1));
}

// TODO: Find ways to test transitivity property of operator<

TEST_CASE("Subtraction test, different size", "[weight=10][part1]")
{
	vector<vector<bool>> input1 = {{0, 1, 0, 1}, {1, 0, 1, 0}, {0, 1, 0, 1}, {1, 0, 1, 0}};
	Board board1(input1);
	Board board2(2);
	REQUIRE_THROWS(board1 - board2);
}

TEST_CASE("Print test simple", "[weight=10][part1]")
{
	Board board1(3);
	REQUIRE(board1.print() == "⚫⚫⚫\n⚫⚫⚫\n⚫⚫⚫");
}


TEST_CASE("Print test pattern", "[weight=10][part1]")
{
	vector<vector<bool>> input1 = {{0, 1, 0, 1}, {1, 0, 1, 0}, {0, 1, 0, 1}, {1, 0, 1, 0}};
	Board board1(input1);
	REQUIRE(board1.print() == "⚫⚪⚫⚪\n⚪⚫⚪⚫\n⚫⚪⚫⚪\n⚪⚫⚪⚫");
}
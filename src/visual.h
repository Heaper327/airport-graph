#include <vector>

#include "cs225/Animation.h"
#include "cs225/PNG.h"
#include "board.h"

using namespace std;
using namespace cs225;

/**
 * Animate the solution on a board
*/
Animation animateSolution(std::vector<Board> solution);

/*
* convert a board to a PNG file
*/
PNG* boardToPNG(const Board& board);


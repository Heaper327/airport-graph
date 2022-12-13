#include "visual.h"

/**
 * Animate the solution on a board
*/
Animation animateSolution(vector<Board> solution) {
    Animation animation;
    for (size_t i = 0; i < solution.size(); i++) {
        //add four frames at one time to decrease the speed of switching images.
        animation.addFrame(*(boardToPNG(solution[i])));
        animation.addFrame(*(boardToPNG(solution[i])));
        animation.addFrame(*(boardToPNG(solution[i])));
        animation.addFrame(*(boardToPNG(solution[i])));
    }
    return animation;

}

/*
* convert a board to a PNG file
*/

PNG* boardToPNG(const Board& board) {
    unsigned size = board.getSize();
    PNG* png_ = new PNG(size*11 + 1,size*11 + 1);
    unsigned png_size = size*11 + 1;
    //blacken the rows
    for (unsigned x = 0; x < png_size; x+=11) {
        for (unsigned y = 0; y < png_size ;y++) {
            HSLAPixel& pixel = png_->getPixel(x, y);
            pixel.l = 0;
        }
    }
    //blacken the columns
    for (unsigned x = 0; x < png_size; x++) {
        for (unsigned y = 0; y < png_size ;y+=11) {
            HSLAPixel& pixel = png_->getPixel(x, y);
            pixel.l = 0;
        }
    }
    HSLAPixel yellow(48, 1, 0.5);
    HSLAPixel gray(60, 0.2, 0.3);
    //now the structure of the PNG is built, time to fill in colors
    //x is in range of (b_row * 11 + 1) to (b_row+1) * 11, for example, the block in the first
    //row has a b_row = 0 and its x coordinates covers from 1 to 10
    for (unsigned b_row = 0; b_row < size; b_row++) {
        for (unsigned b_col = 0; b_col < size; b_col++) {
            for (unsigned x = b_col * 11 + 1; x < (b_col+1) * 11; x++) {
                for (unsigned y = b_row * 11 + 1; y < (b_row+1) * 11; y++) {
                    if (board.getBulb(b_row, b_col)) {
                        //light
                        HSLAPixel & cur_pixel = png_->getPixel(x, y);
				        cur_pixel = yellow;
                    } else {
                        //dark
                        HSLAPixel & cur_pixel = png_->getPixel(x, y);
				        cur_pixel = gray;
                    }
                }
            }
        }
    }
    return png_;
}



#include <iostream>
#include "board.h"
#include "cs225/PNG.h"

using namespace std;

int main()
{
    Board b(10);
    b.toggle(3, 3);
    return 0;
}

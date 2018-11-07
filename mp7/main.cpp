#include <iostream>
#include "dsets.h"
#include "maze.h"
#include "cs225/PNG.h"

using namespace std;

int main()
{
    // Write your own main here
    SquareMaze m;
    m.makeMaze(82, 42);
    PNG* unsolved = m.drawCreativeMaze();
    unsolved->writeToFile("creative.png");

    return 0;
}

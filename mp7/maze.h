/* Your code here! */
#ifndef _MAZE_H_
#define _MAZE_H_
#include<vector>
#include "cs225/PNG.h"
#include "cs225/HSLAPixel.h"
#include "dsets.h"

using namespace std;
using namespace cs225;

class SquareMaze{
  public:

    SquareMaze();
    void makeMaze(int width, int height);
    bool canTravel(int x, int y, int dir) const;
    void setWall(int x, int y, int dir, bool exists);
    vector<int> solveMaze();
    PNG* drawMaze() const;
    PNG* drawMazeWithSolution();
    PNG* drawCreativeMaze();

    private:
      struct wall{
        wall(){right_ = true; down_ = true;};
        bool right_;
        bool down_;
      };
      int width_;
      int height_;
      vector<int> cell_;
      DisjointSets cells_;
      vector<wall> walls_;
      int x_des;
      int y_des;

};

#endif

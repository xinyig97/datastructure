
#include "cs225/PNG.h"
#include "FloodFilledImage.h"
#include "Animation.h"

#include "imageTraversal/DFS.h"
#include "imageTraversal/BFS.h"

#include "colorPicker/RainbowColorPicker.h"
#include "colorPicker/GradientColorPicker.h"
#include "colorPicker/GridColorPicker.h"
#include "colorPicker/SolidColorPicker.h"
#include "colorPicker/MyColorPicker.h"

using namespace cs225;

int main() {

  // @todo [Part 3]
  // - The code below assumes you have an Animation called `animation`
  // - The code provided below produces the `myFloodFill.png` file you must
  //   submit Part 3 of this assignment -- uncomment it when you're ready.

  PNG pic;
  pic.readFromFile("tests/pacman.png");

  FloodFilledImage create(pic);
  DFS dfs(pic,Point(0,0),1.0);
  RainbowColorPicker rainbow(0.06);
  create.addFloodFill(dfs, rainbow);
  MyColorPicker mine(HSLAPixel(186,0.77,0.47),HSLAPixel(204,0.77,0.47),HSLAPixel(217,0.83,0.43),HSLAPixel(272,0.83,0.43));
  BFS bfs(pic,Point(0,0),1.0);
  create.addFloodFill(bfs,mine);
  Animation animation = create.animate(1000);
  PNG lastFrame = animation.getFrame( animation.frameCount() - 1 );
  lastFrame.writeToFile("myFloodFill.png");
  animation.write("myFloodFill.gif");



  return 0;
}

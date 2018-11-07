#include <iterator>
#include <cmath>
#include <list>
#include <queue>

#include "../cs225/PNG.h"
#include "../Point.h"

#include "ImageTraversal.h"
#include "BFS.h"

using namespace cs225;

/**
 * Initializes a breadth-first ImageTraversal on a given `png` image,
 * starting at `start`, and with a given `tolerance`.
 * @param png The image this BFS is going to traverse
 * @param start The start point of this BFS
 * @param tolerance If the current point is too different (difference larger than tolerance) with the start point,
 * it will not be included in this BFS
 */


BFS::BFS(const PNG & png, const Point & start, double tolerance) {
  /** @todo [Part 1] */
  my_png = &png;
  my_start = start;
  this->tolerance = tolerance;
  my_queue.push(start);
/*  visited = new int*[png.width()];
  for(unsigned int i = 0; i< png.height(); i++ ){
    visited[i] = new int[png.height()];
    for(unsigned int j = 0; j < png.width(); j++){
      visited[i][j] = 0;
    }
  }*/
  //visited[start.x][start.y] = 1;
}

/**
 * Returns an iterator for the traversal starting at the first point.
 */
//BFS::~BFS(){}
ImageTraversal::Iterator BFS::begin() {
  /** @todo [Part 1] */
  ImageTraversal* traversal = new BFS(*my_png, my_start, tolerance);
  return ImageTraversal::Iterator(traversal, my_start, tolerance, my_png);
}

/**
 * Returns an iterator for the traversal one past the end of the traversal.
 */
ImageTraversal::Iterator BFS::end() {
  /** @todo [Part 1] */
  return ImageTraversal::Iterator();
}

/**
 * Adds a Point for the traversal to visit at some point in the future.
 */
void BFS::add(const Point & point) {
  /** @todo [Part 1] */
  int height_ = (int)(*my_png).height();
  int width_ = (int)(*my_png).width();
  int  x = (int)point.x;
  int y = (int)point.y;

  if( x+1 < width_){
    if(fabs(calculateDelta(my_png->getPixel(x+1,y),my_png->getPixel(my_start.x,my_start.y))) <= tolerance){
    my_queue.push(Point(x+1, y));
    //visited[x+1][y] = 1;
   }
  }
  if(y+1 < height_){
    if(fabs(calculateDelta(my_png->getPixel(x,y+1),my_png->getPixel(my_start.x,my_start.y))) <= tolerance){
    my_queue.push(Point(x,y+1));
  //  visited[x][y+1] = 1;
 }
  }
  if( x-1 >0 || x-1 ==0){
  if(fabs(calculateDelta(my_png->getPixel(x-1,y),my_png->getPixel(my_start.x,my_start.y))) <= tolerance){
    my_queue.push(Point(x-1, y));
  //  visited[x-1][y] = 1;
  }
  }
  if(y-1 >0 || y-1 == 0){
if(fabs(calculateDelta(my_png->getPixel(x,y-1),my_png->getPixel(my_start.x,my_start.y))) <= tolerance){
    my_queue.push(Point(x,y-1));
  //  visited[x][y-1] = 1;
   }
  }
}

/**
 * Removes and returns the current Point in the traversal.
 */
Point BFS::pop() {
  /** @todo [Part 1] */
  if(my_queue.empty()){
    return Point(-1,-1);
  }
  else{
    Point temp = my_queue.front();
    my_queue.pop();
  /*  while(visited[temp.x][temp.y] == 1){
      my_queue.pop();
      temp = my_queue.front();
    }
    my_queue.pop();
    visited[temp.x][temp.y] =1;*/
    return temp;
  }
//  return Point(0, 0);
}

/**
 * Returns the current Point in the traversal.
 */
Point BFS::peek() const {
  /** @todo [Part 1] */
  if(my_queue.empty()){
    return Point(-1,-1);
  }
  else{
    return my_queue.front();
  }
}

/**
 * Returns true if the traversal is empty.
 */
bool BFS::empty() const {
  /** @todo [Part 1] */
  if(my_queue.empty()){
    return true;
  }
  else{
  return false;
  }
}

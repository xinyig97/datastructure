#include <iterator>
#include <cmath>
#include <list>
#include <stack>

#include "../cs225/PNG.h"
#include "../Point.h"

#include "ImageTraversal.h"
#include "DFS.h"

/**
 * Initializes a depth-first ImageTraversal on a given `png` image,
 * starting at `start`, and with a given `tolerance`.
 * @param png The image this DFS is going to traverse
 * @param start The start point of this DFS
 * @param tolerance If the current point is too different (difference larger than tolerance) with the start point,
 * it will not be included in this DFS
 */


DFS::DFS(const PNG & png, const Point & start, double tolerance) {
  /** @todo [Part 1] */
  my_png = &png;
  my_start = start;
  my_tolerance = tolerance;
  my_stack.push(start);
  //visited = new int*[png.width()];
/*  for(unsigned int i = 0; i < png.width(); i++){
    visited[i] = new int[png.height()];
    for(unsigned int j = 0; j < png.height(); j++){
      visited[i][j] = 0;
    }
  }*/
//  visited[start.x][start.y] = 1;
}
///DFS::~DFS(){}
/**
 * Returns an iterator for the traversal starting at the first point.
 */
ImageTraversal::Iterator DFS::begin() {
  /** @todo [Part 1] */
  ImageTraversal * traversal = new DFS(*my_png, my_start, my_tolerance);
  return ImageTraversal::Iterator(traversal, my_start, my_tolerance, my_png);
}

/**
 * Returns an iterator for the traversal one past the end of the traversal.
 */
ImageTraversal::Iterator DFS::end() {
  /** @todo [Part 1] */
  return ImageTraversal::Iterator();
}

/**
 * Adds a Point for the traversal to visit at some point in the future.
 */
void DFS::add(const Point & point) {
  /** @todo [Part 1] */
  int width_ = (int)(*my_png).width();
  int height_ = (int)(*my_png).height();
  int x = (int)point.x;
  int y = (int)point.y;
  if( x+1 < width_){
    if(fabs(calculateDelta(my_png->getPixel((unsigned int)x+1,(unsigned int)y),my_png->getPixel(my_start.x,my_start.y))) <= my_tolerance){
    my_stack.push(Point(x+1, y));
    }
    //visited[x+1][y] = 1;
    //}
  }
  if(y+1 < height_){
   if(fabs(calculateDelta(my_png->getPixel((unsigned int)x,(unsigned int)y+1),my_png->getPixel(my_start.x,my_start.y))) <= my_tolerance){
    my_stack.push(Point(x,y+1));
    //visited[x][y+1] = 1;
    }
  }
  if( x-1 >0 || x-1 ==0){
    if(fabs(calculateDelta(my_png->getPixel((unsigned int)x-1,(unsigned int)y),my_png->getPixel(my_start.x,my_start.y))) <= my_tolerance){
    my_stack.push(Point(x-1, y));
    //visited[x-1][y] = 1;
   }
  }
  if(y-1 >0 || y-1 == 0){
    if(fabs(calculateDelta(my_png->getPixel((unsigned int)x,(unsigned int)y-1),my_png->getPixel(my_start.x,my_start.y))) <= my_tolerance){
    my_stack.push(Point(x,y-1));
    //visited[x][y-1] = 1;
   }
  }
}

/**
 * Removes and returns the current Point in the traversal.
 */
Point DFS::pop() {
  /** @todo [Part 1] */
  if(my_stack.empty()){
    return Point(my_png->width(),my_png->height());
  }
  else{
    Point temp = my_stack.top();
    my_stack.pop();
  /*  while(visited[temp.x][temp.y] == 1){
      my_stack.pop();
      temp = my_stack.top();
    }
    my_stack.pop();
    visited[temp.x][temp.y] = 1;*/
    return temp;
  }
}

/**
 * Returns the current Point in the traversal.
 */
Point DFS::peek() const {
  /** @todo [Part 1] */
  if(my_stack.empty()){
    return Point(-1,-1);
  }
  else{
  return my_stack.top();
  }
}

/**
 * Returns true if the traversal is empty.
 */
bool DFS::empty() const {
    /** @todo [Part 1] */
    if(!my_stack.empty()){
      return false;
    }
    else{
      return true;
    }
}

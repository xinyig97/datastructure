#include <cmath>
#include <iterator>
#include <iostream>

#include "../cs225/HSLAPixel.h"
#include "../cs225/PNG.h"
#include "../Point.h"

#include "ImageTraversal.h"

/**
 * Calculates a metric for the difference between two pixels, used to
 * calculate if a pixel is within a tolerance.
 *
 * @param p1 First pixel
 * @param p2 Second pixel
 * @return the difference between two HSLAPixels
 */
double ImageTraversal::calculateDelta(const HSLAPixel & p1, const HSLAPixel & p2) {
  double h = fabs(p1.h - p2.h);
  double s = p1.s - p2.s;
  double l = p1.l - p2.l;

  // Handle the case where we found the bigger angle between two hues:
  if (h > 180) { h = 360 - h; }
  h /= 360;

  return sqrt( (h*h) + (s*s) + (l*l) );
}

/**
 * Default iterator constructor.
 */
ImageTraversal::Iterator::Iterator() {
  /** @todo [Part 1] */
  this->traversal = NULL;
}

//ImageTraversal::Iterator::~Iterator(){
  //if(traversal != NULL){delete traversal; traversal = NULL;}
//}

ImageTraversal::Iterator::Iterator(ImageTraversal* traversal, Point my_start, double tol, const PNG* my_png){
  start = my_start;
  current = traversal->peek();
  this->traversal = traversal;
  tolerance = tol;
  png = my_png;
  visited = new int*[png->width()];
  for(unsigned int i = 0; i < png->width(); i++){
    visited[i] = new int[png->height()];
    for(unsigned int j = 0; j < png->height(); j++){
      visited[i][j] = 0;
    }
  }
  //start_strd = png->getPixel(start.x,start.y);

}
/**
 * Iterator increment opreator.
 *
 * Advances the traversal of the image.
 */
ImageTraversal::Iterator & ImageTraversal::Iterator::operator++() {
  /** @todo [Part 1] */
  //if its empty. get the end iterator
  if(traversal->empty()){
    return *this;
  }
  //if it's not empty, check out its neighbors and valid points
  else{
    Point temp = traversal->pop();
    //check if visited already
    while(visited[temp.x][temp.y] == 1 /*|| (fabs(calculateDelta(png->getPixel(temp.x,temp.y),png->getPixel(start.x,start.y))) > tolerance)*/){
      //traversal->pop();
      if(traversal->empty()){
        return *this;
      }
      temp = traversal->pop();
    }

    //mark it as visited
      visited[temp.x][temp.y] = 1;

      //add its neighbors
      traversal->add(temp);
      while(!traversal->empty() && visited[traversal->peek().x][traversal->peek().y] == 1){
        traversal->pop();
      }

      current = traversal->peek();
      return *this;
    }

}

/**
 * Iterator accessor opreator.
 *
 * Accesses the current Point in the ImageTraversal.
 */
Point ImageTraversal::Iterator::operator*() {
  /** @todo [Part 1] */
  return current;
}

/**
 * Iterator inequality operator.
 *
 * Determines if two iterators are not equal.
 */
bool ImageTraversal::Iterator::operator!=(const ImageTraversal::Iterator &other) {
  /** @todo [Part 1] */
  bool thisempty = false;
  bool otherempty = false;

  if(traversal == NULL){ thisempty = true; }
  if(other.traversal == NULL){ otherempty = true; }

  if(!thisempty) { thisempty = traversal->empty();}
  if(!otherempty) { otherempty = other.traversal->empty();}

  if(thisempty && otherempty) {return false;}
  else if((!thisempty)&&(!otherempty)){
    if(current == other.current){
      return false;
    }
    else{
      return false;
    }
  }
  else{
    return true;
  }

//  return false;
}

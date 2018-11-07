/**
 * @file DFS.h
 */

#ifndef DFS_H
#define DFS_H

#include <iterator>
#include <cmath>
#include <list>
#include <stack>

#include "../cs225/PNG.h"
#include "../Point.h"

#include "ImageTraversal.h"

using namespace cs225;

/**
 * A depth-first ImageTraversal.
 * Derived from base class ImageTraversal
 */
class DFS : public ImageTraversal {
public:
  //~DFS();
  DFS(const PNG & png, const Point & start, double tolerance);
  //~DFS();
  ImageTraversal::Iterator begin();
  ImageTraversal::Iterator end();

  void add(const Point & point);
  Point pop();
  Point peek() const;
  bool empty() const;

private:
	/** @todo [Part 1] */
  stack<Point> my_stack ;
  Point my_start;
  const PNG* my_png;
  double my_tolerance;
  //int** visited;
  //vector<Point> visted;
	/** add private members here*/
};

#endif

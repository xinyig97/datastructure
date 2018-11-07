/**
 * @file FloodFilledImage.h
 * Definition for a class to do flood fill on an image
 */
#ifndef FLOODFILLEDIMAGE_H
#define FLOODFILLEDIMAGE_H

#include "cs225/PNG.h"
#include <list>
#include <iostream>

#include "colorPicker/ColorPicker.h"
#include "imageTraversal/ImageTraversal.h"

#include "Point.h"
#include "Animation.h"

using namespace cs225;
/**
 *This class is used to do flood fill on an image
 */
class FloodFilledImage {
public:
  FloodFilledImage(const PNG & png);
  void addFloodFill(ImageTraversal & traversal, ColorPicker & colorpicker);
  Animation animate(unsigned frameInterval) const;

struct Flood{
    ImageTraversal& traversal_;
    ColorPicker& colorpicker_;
    Flood(ImageTraversal& traversal, ColorPicker& colorpicker): traversal_(traversal), colorpicker_(colorpicker){}

};

private:
	/** @todo [Part 2] */
  PNG* my_png;
  list<Flood> floods_;


	/** add private members here*/

};

#endif

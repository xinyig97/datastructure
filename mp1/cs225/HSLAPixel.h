/**
 * @file HSLAPixel.h
 *
 * @author CS 225: Data Structures
 */

#ifndef CS225_HSLAPIXEL_H
#define CS225_HSLAPIXEL_H


#include <iostream>
#include <sstream>

namespace cs225 {
  //declare a class named HSLAPixel.
class HSLAPixel{
  //declare public member variables h (hue), s(saturation), l(luminance), and a(alpha).
  public:
  double h;
  double s;
  double l;
  double a;

 //declare public member constructors.
 //a defaulte consturtcor that takes no input.
  HSLAPixel();
 //constructor that takes hue, saturation, and luminance as inputs.
  HSLAPixel(double hue, double saturation, double luminance);
 //constructor that takes all parameters as inputs to customized pixel.
  HSLAPixel(double hue, double saturation, double luminance, double alpha);

};

}

#endif

/**
 * @file HSLAPixel.cpp
 * Implementation of the HSLAPixel class for use in with the PNG library.
 *
 * @author CS 225: Data Structures
 * @version 2018r1-lab1
 */

#include "HSLAPixel.h"
#include <cmath>
#include <iostream>
using namespace std;

namespace cs225 {

HSLAPixel::HSLAPixel(){
  //default constructor that takes no input but initializes parameters of HSLAPixel.
  //as required, the default constructor created a complete opaque and white pixel.
  h = 0.0;
  s = 0.0;
  a = 1.0; //when a = 1.0, it's opaque.
  l = 1.0; // when l = 1.o, it's white.
}

HSLAPixel::HSLAPixel(double hue, double saturation, double luminance){
  //constructor that takes hue, saturation, and luminance as input to define an opaque pixel.
  //initializes parameters h, s, and l as inputs suggested and set a = 1.0 as opaque.
  //if the input is within the valid range of hue, we just set h as hue.
  if(0.0<=hue && hue<=359.0){
       h = hue;
   };
   //otherwise, we assume that the user intend to get the most hue.
  if(360.0<=hue || hue<0.0){
       h = 0.0;
  };
  s = saturation;
  l = luminance;
  a = 1.0;
}

HSLAPixel::HSLAPixel(double hue, double saturation, double luminance, double alpha){
  //constructor that takes hue, saturation, luminance, and alpha as inputs to define a pixel of above characterists.
  //initializes h, s, l, and a as inputs suggested.
  if(0.0<=hue && hue<=359.0){
       h = hue;
   };
   //otherwise, we assume that the user intend to get the most hue.
  if(360.0<=hue || hue<0.0){
      h = 0.0;
  };
  s = saturation;
  l = luminance;
  a = alpha;
}

}

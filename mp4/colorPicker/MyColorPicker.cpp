#include "../cs225/HSLAPixel.h"
#include "../Point.h"

#include "ColorPicker.h"
#include "MyColorPicker.h"

using namespace cs225;

/**
 * Picks the color for pixel (x, y).
 * Using your own algorithm
 */
MyColorPicker::MyColorPicker(HSLAPixel color_1, HSLAPixel color_2, HSLAPixel color_3,HSLAPixel color_4){
  this->color_1 = color_1;
  this->color_2 = color_2;
  this->color_3 = color_3;
  this->color_4 = color_4;
//  this->increment = increment;
}


HSLAPixel MyColorPicker::getColor(unsigned x, unsigned y) {
  /* @todo [Part 3] */
  if(x%4 == 0){
    return color_1;
  }
  else if(x%4 == 1){
    return color_2;
  }
  else if(x%4 == 2){
    return color_3;
  }
  else{
    if(y%2==0){
    return color_4;
  }
  else{
    return HSLAPixel((color_1.h+color_2.h+color_3.h+color_4.h)/4,0,1);
  }
}
  //return HSLAPixel();
}

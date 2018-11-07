#ifndef MyColorPicker_H
#define MyColorPicker_H

#include "ColorPicker.h"
#include "../cs225/HSLAPixel.h"
#include "../Point.h"

using namespace cs225;

/**
 * A color picker class using your own color picking algorithm
 */
class MyColorPicker : public ColorPicker {
public:
  HSLAPixel getColor(unsigned x, unsigned y);
  MyColorPicker(HSLAPixel color_1, HSLAPixel color_2, HSLAPixel color_3, HSLAPixel color_4);
private:
   HSLAPixel color_1;
   HSLAPixel color_2;
   HSLAPixel color_3;
   HSLAPixel color_4;
//   int increment ;

};

#endif

#include "cs225/PNG.h"
#include "cs225/HSLAPixel.h"
#include <string>
#include <iostream>

using namespace cs225;


void rotate(std::string inputFile, std::string outputFile) {
  // Part 2
  //read from the inputFile
const std::string &input = inputFile;
  PNG* image = new PNG;
  //check if the input is valid and success, if not, print out warning sign
  if(image->readFromFile(input)==0){
    std::cout<<"Invalid inputFile"<<std::endl;
  }
  //rotate the image
  unsigned int width = image->width();
  unsigned int height = image->height();
  unsigned int i, j;
  HSLAPixel* cur;
  HSLAPixel* next;

  for(i = 0; i < height/2; i++){
    for(j = 0; j < width; j++){
      //get pixel form the current Pixel location and its corrresponding reversed location
      cur = image->getPixel(j,i);
      next = image->getPixel(width-1-j, height-1-i);

      //switch the two Pixels' information about hue, luminance, alpha, and saturation
      double temp = cur->h;
      cur->h = next->h;
      next->h = temp;

      temp = cur->s;
      cur->s = next->s;
      next->s = temp;

      temp = cur->l;
      cur->l = next->l;
      next->l = temp;

      temp = cur->a;
      cur->a = next->a;
      next->a = temp;
    }
  }

//if the height is an odd number, reverse the middle line
  if(height%2 ==1){
    //set up the height index as to the middle one
    i = (height-1)/2;
    //for the single line reverse, we only have to go through half of the line
    for(j = 0; j < width/2 ; j++){
      //get the pixels of the current location and its corrresponding reversed location
      cur = image->getPixel(j,i);
      next = image->getPixel(width-1-j, i);

      //switch the information of the pixels
      double temp = cur->h;
      cur->h = next->h;
      next->h = temp;

      temp = cur->s;
      cur->s = next->s;
      next->s = temp;

      temp = cur->l;
      cur->l = next->l;
      next->l = temp;

      temp = cur->a;
      cur->a = next->a;
      next->a = temp;
    }
  }

  //write to outputFile
  const std::string &output = outputFile;
  if(image->writeToFile(output) == 0){
    std::cout<<"Filed output"<<std::endl;
  }

}

PNG myArt(unsigned int width, unsigned int height) {
  PNG png(width, height);
  // Part 3
  unsigned n,m;
  //figure out the boundary of four parts accoridng to its ratio
  unsigned int flag_h = (height-1)/2;
  unsigned int flag_w = (height-1)/2;
  HSLAPixel * cur;
  //upper left part
  //it has 7 different pinks, equally occupy one horizontal stripe
  //find the appropriate distance that divide the first par equally vertically
  unsigned int temp_grad = flag_h /7;
  //pink 1
  for(m = 0; m<temp_grad ; m++){
    for(n = 0; n<flag_w ; n++){
      cur = png.getPixel(n,m);
      cur->h = 346.0;
      cur->s = 1.0;
      cur->l = 0.88;
      cur->a = 1.0;
    }
  }
  //pink 2
  for(m = temp_grad; m< temp_grad *2 ; m++){
    for(n = 0; n<flag_w; n++){
      cur = png.getPixel(n,m);
      cur->h = 350.0;
      cur->s = 1.0;
      cur->l = 0.84;
      cur->a = 1.0;
    }
  }
  //pink 3
  for(m = temp_grad*2; m< temp_grad*3; m++){
    for(n = 0; n<flag_w; n++){
      cur = png.getPixel(n,m);
      cur->h = 344.0;
      cur->s = 0.95;
      cur->l = 0.73;
      cur->a = 1.0;
    }
  }
  //pink 4
  for(m = temp_grad*3; m< temp_grad*4; m++){
    for(n = 0; n<flag_w; n++){
      cur = png.getPixel(n,m);
      cur->h = 342.0;
      cur->s = 0.75;
      cur->l = 0.59;
      cur->a = 1.0;
    }
  }
  //pink 5
  for(m = temp_grad*4; m< temp_grad*5; m++){
    for(n = 0; n<flag_w; n++){
      cur = png.getPixel(n,m);
      cur->h = 343.0;
      cur->s = 0.72;
      cur->l = 0.53;
      cur->a = 1.0;
    }
  }
  //pink 6
  for(m = temp_grad*5; m< temp_grad*6; m++){
    for(n = 0; n<flag_w; n++){
      cur = png.getPixel(n,m);
      cur->h = 337.0;
      cur->s = 0.91;
      cur->l = 0.52;
      cur->a = 1.0;
    }
  }
  //pink 7
  for(m = temp_grad*6; m< temp_grad*7; m++){
    for(n = 0; n<flag_w; n++){
      cur = png.getPixel(n,m);
      cur->h = 346.0;
      cur->s = 0.71;
      cur->l = 0.45;
      cur->a = 1.0;
    }
  }

  //for lower right part
  //it has 6 light blues that are equally ccupy vertically
  //find the distance that divide the part into 6 parts vertically equally
  temp_grad = (width-1 - flag_w)/6;
  //blue 1
  for(m = flag_w; m< flag_w + temp_grad; m++){
    for(n = flag_h; n<height; n++){
      cur = png.getPixel(m,n);
      cur->h = 183.0;
      cur->s = 1.0;
      cur->l = 0.97;
      cur->a = 1.0;
    }
  }
  //blue 2
  for(m = flag_w + temp_grad; m< flag_w + temp_grad*2; m++){
    for(n = flag_h; n<height; n++){
      cur = png.getPixel(m,n);
      cur->h = 200.0;
      cur->s = 1.0;
      cur->l = 0.83;
      cur->a = 1.0;
    }
  }
  //blue 3
  for(m = flag_w+ temp_grad*2; m< flag_w + temp_grad*3; m++){
    for(n = flag_h; n<height; n++){
      cur = png.getPixel(m,n);
      cur->h = 177.0;
      cur->s = 0.93;
      cur->l = 0.79;
      cur->a = 1.0;
    }
  }
  //blue 4
  for(m = flag_w + temp_grad*3 ; m< flag_w + temp_grad*4; m++){
    for(n = flag_h; n<height; n++){
      cur = png.getPixel(m,n);
      cur->h = 197.0;
      cur->s = 0.71;
      cur->l = 0.77;
      cur->a = 1.0;
    }
  }
  //blue 5
  for(m = flag_w+temp_grad*4; m< flag_w + temp_grad*5; m++){
    for(n = flag_h; n<height; n++){
      cur = png.getPixel(m,n);
      cur->h = 175.0;
      cur->s = 0.66;
      cur->l = 0.73;
      cur->a = 1.0;
    }
  }
  //blue 6
  for(m = flag_w + temp_grad*5; m< width; m++){
    for(n = flag_h; n<height; n++){
      cur = png.getPixel(m,n);
      cur->h = 196.0;
      cur->s = 1.0;
      cur->l = 0.46;
      cur->a = 1.0;
    }
  }

  //for lower left part
  //it has gradually changed blues vertically
  //find the appropriate graduate change of hue
  double hue_grad = (216.0-195.0)/flag_h;
  for(m = flag_h; m <height; m++){
    for(n = 0; n<flag_w; n++){
      cur = png.getPixel(n,m);
      double diff = m-flag_h;
      cur->h = 195.0 + diff*hue_grad;
      cur->s = 0.96;
      cur->l = 0.44;
      cur->a = 1.0;
    }
  }

  //for upper right part
  //it changes horizontally in purples
  //find the appropriate graduate change for hue and luminance
  hue_grad = (275.0-259.0)/flag_w;
  double l_grad = (0.68-0.33)/flag_w;
  for(m = flag_w; m<width; m++){
    for(n = 0; n<flag_h; n++){
      cur = png.getPixel(m,n);
      double diff = m-flag_w;
      cur->h = 275.0-diff*hue_grad;
      cur->s = 0.99;
      cur->l = 0.68-diff*l_grad;
      cur->a = 1.0;
    }
  }

  return png;

}

#include"Image.h"
#include"cs225/PNG.h"
#include<iostream>
#include<string>
#include "cs225/HSLAPixel.h"
#include<cmath>

using namespace cs225;

void Image::lighten(){
  //go through pixel one by one to increase its lighting level.
  for(unsigned int x = 0; x < this->height(); x++){
    for(unsigned int y = 0; y < this->width(); y++){
      HSLAPixel & cur = this->getPixel(y,x);
      double cur_l = cur.l + 0.1;
      //if the l is not legal, make it the lowest level = 0.0
      if(cur_l <= 0.0){
        cur.l = 0.0;
      }
      else if(1.0 <=cur_l){
        //if l is above the max l, make it 1.0
        cur.l = 1.0;
      }
      else{
        cur.l = cur_l;
      }
    }
  }
}

void Image::lighten(double amount){
  //go through pixels one by one to check the lighting level
  for(unsigned int x = 0; x < this->height(); x++){
    for(unsigned int y= 0; y< this->width(); y++){
      HSLAPixel & cur = this->getPixel(y,x);
      double cur_l = cur.l+amount;
      //if the resulted l is below the legal range, make it lowest level =0.0
      if (cur_l <= 0.0){
        cur.l = 0.0;
      }
      //if the resulted is above the legal range, make it highest level =1.0;
      else if(1.0 <= cur_l){
        cur.l = 1.0;
      }
      else {
        //otherwise, make it resulted.
        cur.l = cur_l;
      }
    }
  }
}

void Image::darken(){
  //go through pixels one by one to darken its light level
  for(unsigned int x = 0; x < this->height(); x++){
    for(unsigned int y = 0; y <this->width(); y++){
      HSLAPixel & cur = this->getPixel(y,x);
      double cur_l = cur.l - 0.1;
      //if the resulted light level is below the legal range, make it lowerst possibly = 0.0
      if(cur_l <= 0.0){
        cur.l = 0.0;
      }
      //if the resulted light level is above the legal range, make it highest possbly = 1.0;
      else if(1.0 <= cur_l){
        cur.l = 1.0;
      }
      //if the resulted is legal, make it the resulted.
      else{
        cur.l = cur_l;
      }
    }
  }
}

void Image::darken(double amount){
  //go through pixels one by one to darken its light level
  for(unsigned int x = 0; x < this->height(); x++){
    for(unsigned int y = 0; y < this->width(); y++){
      HSLAPixel & cur = this->getPixel(y,x);
      double cur_l = cur.l - amount;
      //if the resulted light level is below the legal range, make it lowest possible.
      if(cur_l <= 0.0){
        cur.l = 0.0;
      }
      //if the resulted light level is above the legal range, make it highest possible.
      else if(1.0 <= cur_l){
        cur.l = 1.0;
      }
     //otherwise, make it the resulted.
      else{
        cur.l =  cur_l;
      }
    }
  }
}

void Image::saturate(){
  //go through pixels one by one to change its satrateion level
  for(unsigned int x = 0; x <this->height(); x++){
    for(unsigned int y=0; y< this->width(); y++){
      HSLAPixel & cur = this->getPixel(y,x);
      double cur_s = cur.s + 0.1;
      //if the resulted saturation level is below the legal range, make it lowest possible = 0.0
      if(cur_s <= 0.0){
        cur.s = 0.0;
      }
      //if the resulted saturation level is above the legal range, make it highest possible = 1.0;
      else if(1.0 <=cur_s){
        cur.s = 1.0;
      }
      //otherwise, make it the resulted one
      else{
        cur.s = cur_s;
      }
    }
  }
}

void Image::saturate(double amount){
  //go through pixels one by one to change its stauration level according to the input
  for(unsigned int x = 0; x <this->height(); x++){
    for(unsigned int y=0; y< this->width(); y++){
      HSLAPixel & cur = this->getPixel(y,x);
      double cur_s = cur.s + amount;
      //if the resulted saturation level is below legal level, make it lowest possible = 0.0
      if(cur_s <= 0.0){
        cur.s = 0.0;
      }
      //if the resutled saturation level is above the legal level, make it highest possible =1.0;
      else if(1.0 <=cur_s){
        cur.s = 1.0;
      }
      //otherwise, make it the resulted one
      else{
        cur.s = cur_s;
      }
    }
  }
}

void Image::desaturate(){
  //go through pixels one by one to desatruration
  for(unsigned int x = 0; x <this->height(); x++){
    for(unsigned int y=0; y< this->width(); y++){
      HSLAPixel & cur = this->getPixel(y,x);
      double cur_s = cur.s - 0.1;
      //if the resulted is below legal range, make it lowest possibly = 0.0;
      if(cur_s <= 0.0){
        cur.s = 0.0;
      }
      //if the resulted is above legal range, make it highest possibly = 1.0;
      else if(1.0 <=cur_s){
        cur.s = 1.0;
      }
      //otherwise, make it the resulted level,
      else{
        cur.s = cur_s;
      }
    }
  }
}

void Image::desaturate(double amount){
  //go through pixels one by one to desaturation
  for(unsigned int x = 0; x <this->height(); x++){
    for(unsigned int y=0; y< this->width(); y++){
      HSLAPixel & cur = this->getPixel(y,x);
      double cur_s = cur.s - amount;
      //if the resulted is below legal range, make it lowest possible = 0.0;
      if(cur_s <= 0.0){
        cur.s = 0.0;
      }
      //if the resulted is above legal range, make it highest possible = 1.0;
      else if(1.0 <=cur_s){
        cur.s = 1.0;
      }
      //otherwise, make it what it suppoesed to be
      else{
        cur.s = cur_s;
      }
    }
  }
}

void Image::grayscale(){
  //go through pixels one by one to change its satraton level to make it gray
  for(unsigned int x = 0; x <this->height(); x++){
    for(unsigned int y=0; y< this->width(); y++){
      HSLAPixel & cur = this->getPixel(y,x);
      cur.s = 0.0;
    }
  }
}

void Image::rotateColor(double degrees){
  //go through pixels one by one to rotate the color
  for(unsigned int x = 0; x < this->height(); x++){
    for(unsigned int y=0; y<this->width();y++){
      HSLAPixel & cur = this->getPixel(y,x);
      cur.h += degrees;
      //if the degree is smaller than 0, take the corresponding one within the range
      if(cur.h<0.0){
        cur.h = cur.h +360.0;
      }
      //if the degree is higher than 360, make it the corresponding one within legal range
      if(cur.h > 360.0){
        cur.h = cur.h -360.0;
      }
    }
  }
}

void Image::illinify(){
  //go through pixels one by one to illinify it
  for(unsigned int x = 0; x < this->height(); x++){
    for(unsigned int y=0; y<this->width(); y++){
      HSLAPixel & cur = this->getPixel(y,x);
      //calculate the offset according to the distance between current hue to orange and blue
      unsigned int dic = (216.0-11.0)/2;
      unsigned int bound1 = 11.0 + dic;
      unsigned int bound2 = 216.0 + dic;
      //if near blue, make it blue
      if(cur.h>bound1 && cur.h < bound2){
        cur.h = 216.0;
      }
      //if near organde, make it orange
      if((bound2<=cur.h && cur.h <=360.0) || (cur.h >0.0 && cur.h<=bound1)){
        cur.h = 11.0;
      }
      //for corner case, make them to orange cuz orange is warm
      if(cur.h >360.0){
        cur.h = 11.0;
      }
      if(cur.h<0.0){
        cur.h = 11.0;
      }
    }
  }
}

void Image::scale(double factor){
  //if the input factor is negative, its invalid
if(factor <0){
  std::cout<<"invalid input"<<std::endl;
}
//create a copy of the current image, copy each pixel
PNG * temp = new PNG(this->width(),this->height());
for(unsigned int i =0; i< this->height(); i++){
  for(unsigned int j=0; j< this->width(); j++){
    HSLAPixel & cur = this->getPixel(j,i);
    HSLAPixel & tem = temp->getPixel(j,i);
    tem = cur;
  }
}
//caluclate the new width and height, call the resize function in PNG to make a new size pic.
unsigned int new_w = (unsigned)((double)this->width() * factor);
unsigned int new_h = (unsigned)((double)this->height() * factor);
this->resize(new_w,new_h);
//calculate the relative position of original pixel to the mapped pixels. copy one by one to the newly resized pic
  for(unsigned i =0; i<this->height();i++){
    for(unsigned j=0; j<this->width();j++){
      HSLAPixel & cur = this->getPixel(j,i);
      HSLAPixel tem = temp->getPixel((unsigned)((double)j/factor),(unsigned)((double)i/factor));
      cur = tem;
    }
  }
  //delete the allocated heap memory
delete temp;
return;
}

void Image::scale(unsigned w, unsigned h){
  //calculate the corresponding fatcor of height and width.
  double factor_w = w/this->width();
  double factor_h = h/this->height();
  //choose the bigger scaled factor and call the scale function
  if(factor_w>factor_h){
    this->scale(factor_w);
  }
  else{
    this->scale(factor_h);
  }
return;
}

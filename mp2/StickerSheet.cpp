#include "StickerSheet.h"
#include "Image.h"

#include<iostream>
#include<string>

//construtor of the StickSheet
StickerSheet::StickerSheet(const Image&picture, unsigned max){
  max_ = max;
  base_ = picture;
  Sticker_ = new sticker*[max];
  //initialized new array for stickers, and make them NULL
  for(unsigned i=0; i<max_; i++){
    Sticker_[i] = NULL;
  }
}

StickerSheet::~StickerSheet(){
  //if not deleted, go through each one pointer
  if(Sticker_ != NULL){
    for(unsigned i=0; i<max_; i++){
      //if the pointer is not deleted, delete and make it to NULL
      if(Sticker_[i]!=NULL){
        delete Sticker_[i];
        Sticker_[i] =NULL;
      }
    }
    //delete the double array pointer and set to NULL
  delete[] Sticker_;
  Sticker_ = NULL;
  }
 }


StickerSheet::StickerSheet(const StickerSheet & other){
  //copy max_ and base_
  max_ = other.max_;
  base_ = other.base_;
  //deep copy of the array
  Sticker_ = new sticker*[max_];
  for(unsigned i=0; i<max_ ; i++){
    if(other.Sticker_[i]!=NULL){
    Sticker_[i] = new sticker(((other.Sticker_)[i])->addr,((other.Sticker_)[i])->x_co,((other.Sticker_)[i])->y_co);
   }
   else{
     Sticker_[i] = NULL;
   }
  }
}

//private helper function of delete that being called by the assignment override
//basically the same as destrutcor of StickerSheet class.
void StickerSheet::delete_(){
  if(Sticker_ != NULL){
    for(unsigned i=0; i<max_; i++){
      if(Sticker_[i]!=NULL){
        delete Sticker_[i];
        Sticker_[i]=NULL;
     }
   }
  delete[] Sticker_;
  Sticker_ =NULL;
 }
  return;
}
//privae helper function of copy taht being called by the assignment override
//basically the same as the copy constuctor of StickerSheet class
void StickerSheet::copy_(const StickerSheet& other){
  max_ = other.max_;
  base_ = other.base_;
  Sticker_ = new sticker*[max_];
  for(unsigned i=0; i<max_ ; i++){
    if(other.Sticker_[i]!=NULL){
      Sticker_[i] = new sticker(((other.Sticker_)[i])->addr,((other.Sticker_)[i])->x_co,((other.Sticker_)[i])->y_co);
    }
    else{
     Sticker_[i] = NULL;
    }
  }
  return;
}

const StickerSheet& StickerSheet::operator=(const StickerSheet &other){
  //override assignment operator
  delete_();
  copy_(other);
  return *this;
}

void StickerSheet::changeMaxStickers(unsigned max){
  //if the new max is smaller than the previous max, free the extra allocated memeory first
  if(max < max_){
    for(unsigned i=max; i<max_; i++){
      if(Sticker_[i]!=NULL){
      delete Sticker_[i];
      }
    }
    //create a new pointer array of the length of the new max
    sticker** temp = new sticker*[max];
    for(unsigned i=0; i<max; i++){
      //if the previous pointer is not NULL, copy to the corresponding position in the new array
      if(Sticker_[i]!=NULL){
        temp[i] = Sticker_[i];
      }
      //otherwise, initialzied with NULL
      else {
        temp[i] = NULL;
      }
    }
    //update the max_
    max_ = max;
    delete[] Sticker_;
    Sticker_ = temp;
    }
  //if the new max is bigger than previous max_
  else {
    //create a new pointer array
      sticker** temp = new sticker*[max];
      for(unsigned i=0; i<max_; i++){
        //copy the old array into the new array of corresponding positions
        if(Sticker_[i]!=NULL){
        temp[i] = Sticker_[i];
        }
        else{
        temp[i]=NULL;
        }
      }
     //for extra space in new array, initialize with NULL.
      for(unsigned i = max_; i < max; i++) {
        temp[i]=NULL;
      }
      max_ = max;
      delete[] Sticker_;
      Sticker_ = temp;
    }
}

int StickerSheet::addSticker(Image &stickers, unsigned x, unsigned y){
  //if there is extra space for a new sticker, add it and return the index
  for(unsigned i=0; i<max_; i++){
    if(Sticker_[i] == NULL){
      Sticker_[i] = new sticker(&stickers, x, y);
      return i;
    }
  }
  //otherwise if the array is already FULL, return -1
  return -1;
}

bool StickerSheet::translate(unsigned index, unsigned x, unsigned y){
  //if the index does not have a valid pointer, return false.
  if(Sticker_[index] == NULL || (Sticker_[index])->addr == NULL){
    return 0;
  }
  //otherwise, change the location of copying
  (Sticker_[index])->x_co =x;
  (Sticker_[index])->y_co =y;
  return 1;
}

void StickerSheet::removeSticker(unsigned index){
  //if the index has a pointer, delete it
  if(Sticker_[index]!=NULL){
    delete Sticker_[index];
    Sticker_[index]=NULL;
    return;
  }
  //otherwise, do nothing
  return;
}

Image* StickerSheet::getSticker(const unsigned index ){
  //if the index has a sticker, return the addr of the sticker
  if(Sticker_[index]!=NULL){
    return Sticker_[index]->addr;
  }
  //otherwise return NULL
  return NULL;
}

const Image StickerSheet::render(){
  //figure out what is the final size of the pic
  unsigned int w = base_.width();
  unsigned int h = base_.height();
  if(Sticker_ !=NULL){
    for(unsigned int i=0; i<max_;i++){
      if(Sticker_[i]!=NULL && Sticker_[i]->addr!=NULL){
        unsigned temp_w = Sticker_[i]->x_co+(Sticker_[i]->addr)->width();
        unsigned temp_h = Sticker_[i]->y_co+(Sticker_[i]->addr)->height();
        if(temp_w>w){
          w = temp_w;
        }
        if(temp_h>h){
          h = temp_h;
        }
      }
    }
  }
  //resize the base_ pic
  base_.resize(w,h);
  //render stickers
  for(unsigned i=0; i<max_; i++){
    //if there is a sticker
    if(Sticker_[i]!=NULL&& Sticker_[i]->addr !=NULL){
      //get the width and height of the sticker
    unsigned width = (Sticker_[i]->addr)->width();
    unsigned height = ((Sticker_[i])->addr)->height();
    for(unsigned y= 0; y<height; y++){
      for(unsigned x= 0; x<width; x++){
        //change the corresponding pixel of the base pic to print out the sticker
        HSLAPixel &cur = base_.getPixel(x + Sticker_[i]->x_co, y + Sticker_[i]->y_co);
        HSLAPixel &tem = (Sticker_[i]->addr)->getPixel(x,y);
        if(tem.a !=0){
          cur.h = tem.h;
          cur.l = tem.l;
          cur.a = tem.a;
          cur.s = tem.s;
        }
      }
      }
    }
  }
  return base_;
}

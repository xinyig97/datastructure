#include "Image.h"
#include "StickerSheet.h"

int main() {
/* just for fun
Image background;
background.readFromFile("background.png");

Image ha;
ha.readFromFile("ha.png");
ha.scale(0.5);
for(unsigned i=0; i<ha.height(); i++){
  for(unsigned j=0; j<ha.width(); j++){
    HSLAPixel&cur = ha.getPixel(j,i);
    if(cur.a == 0.0){
      cur.a =0.2;
    }
  }
}

Image hei;
hei.readFromFile("hei.png");
hei.scale(0.5);
for(unsigned i=0; i<hei.height(); i++){
  for(unsigned j=0; j<hei.width(); j++){
    HSLAPixel&cur = hei.getPixel(j,i);
    if(cur.a == 0.0){
      cur.a =0.2;
    }
  }
}

Image xi_2;
xi_2.readFromFile("xi_2.png");
xi_2.scale(0.3);
for(unsigned i=0; i<xi_2.height(); i++){
  for(unsigned j=0; j<xi_2.width(); j++){
    HSLAPixel&cur = xi_2.getPixel(j,i);
    if(cur.a == 0.0){
      cur.a =0.2;
    }
  }
}

Image xi_4;
xi_4.readFromFile("xi_4.png");
xi_4.scale(0.5);
for(unsigned i=0; i<xi_4.height(); i++){
  for(unsigned j=0; j<xi_4.width(); j++){
    HSLAPixel&cur = xi_4.getPixel(j,i);
    if(cur.a == 0.0){
      cur.a =0.2;
    }
  }
}

Image hbd;
hbd.readFromFile("happy birthday.png");
hbd.scale(0.5);
for(unsigned i=0; i<hbd.height(); i++){
  for(unsigned j=0; j<hbd.width(); j++){
    HSLAPixel&cur = hbd.getPixel(j,i);
    if(cur.a == 0.0){
      cur.a =0.2;
    }
  }
}

Image xi_11;
xi_11.readFromFile("xi_11.png");
xi_11.scale(0.5);
for(unsigned i=0; i<xi_11.height(); i++){
  for(unsigned j=0; j<xi_11.width(); j++){
    HSLAPixel&cur = xi_11.getPixel(j,i);
    if(cur.a == 0.0){
      cur.a =0.2;
    }
  }
}

Image together;
together.readFromFile("together.png");
together.scale(0.5);
for(unsigned i=0; i<together.height(); i++){
  for(unsigned j=0; j<together.width(); j++){
    HSLAPixel&cur = together.getPixel(j,i);
    if(cur.a == 0.0){
      cur.a =0.2;
    }
  }
}

Image xi_13;
xi_13.readFromFile("xi_13.png");
xi_13.scale(0.5);
for(unsigned i=0; i<xi_13.height(); i++){
  for(unsigned j=0; j<xi_13.width(); j++){
    HSLAPixel&cur = xi_13.getPixel(j,i);
    if(cur.a == 0.0){
      cur.a =0.2;
    }
  }
}

Image xi_3;
xi_3.readFromFile("xi_3.png");
xi_3.scale(0.5);
for(unsigned i=0; i<xi_3.height(); i++){
  for(unsigned j=0; j<xi_3.width(); j++){
    HSLAPixel&cur = xi_3.getPixel(j,i);
    if(cur.a == 0.0){
      cur.a =0.2;
    }
  }
}

Image xi_5;
xi_5.readFromFile("xi_5.png");
xi_5.scale(0.5);
for(unsigned i=0; i<xi_5.height(); i++){
  for(unsigned j=0; j<xi_5.width(); j++){
    HSLAPixel&cur = xi_5.getPixel(j,i);
    if(cur.a == 0.0){
      cur.a =0.2;
    }
  }
}

Image xi_19;
xi_19.readFromFile("xi_19.png");
xi_19.scale(0.25);
for(unsigned i=0; i<xi_19.height(); i++){
  for(unsigned j=0; j<xi_19.width(); j++){
    HSLAPixel&cur = xi_19.getPixel(j,i);
    if(cur.a == 0.0){
      cur.a =0.2;
    }
  }
}

Image xi_1;
xi_1.readFromFile("xi_1.png");
xi_1.scale(0.7);
for(unsigned i=0; i<xi_1.height(); i++){
  for(unsigned j=0; j<xi_1.width(); j++){
    HSLAPixel&cur = xi_1.getPixel(j,i);
    if(cur.a == 0.0){
      cur.a =0.2;
    }
  }
}

Image cute;
cute.readFromFile("xi_21.png");
cute.scale(0.3);
for(unsigned i=0; i<cute.height(); i++){
  for(unsigned j=0; j<cute.width(); j++){
    HSLAPixel&cur = cute.getPixel(j,i);
    if(cur.a == 0.0){
      cur.a =0.2;
    }
  }
}

StickerSheet mysheet(background,13);
mysheet.addSticker(ha,0,0);
mysheet.addSticker(hei,430,0);
mysheet.addSticker(xi_2,720,0);
mysheet.addSticker(xi_4,1030,0);
mysheet.addSticker(hbd,1300,0);
mysheet.addSticker(xi_11,1300,250);
mysheet.addSticker(together,1200,540);
mysheet.addSticker(xi_13,860,440);
mysheet.addSticker(xi_3,510,750);
mysheet.addSticker(xi_5,510,530);
mysheet.addSticker(xi_19,430,290);
mysheet.addSticker(xi_1,0,550);
mysheet.addSticker(cute,715,310);

Image out = mysheet.render();
out.writeToFile("myImage.png");
*/

//read in required pics
Image background;
background.readFromFile("mp2_off.png");
background.writeToFile("myImage.png");

Image theme;
theme.readFromFile("2_7.png");
theme.scale(0.4);
//make sure the pic is available
for(unsigned i=0; i<theme.height(); i++){
  for(unsigned j=0; j<theme.width(); j++){
    HSLAPixel&cur = theme.getPixel(j,i);
    if(cur.a == 0.0){
      cur.a =0.2;
    }
  }
}
Image bless;
bless.readFromFile("mp2_12.png");
bless.scale(1.0);
for(unsigned i=0; i<bless.height(); i++){
  for(unsigned j=0; j<bless.width(); j++){
    HSLAPixel&cur = bless.getPixel(j,i);
    if(cur.a == 0.0){
      cur.a =1.0;
    }
  }
}
Image resistance;
resistance.readFromFile("mp2_13.png");
resistance.scale(0.5);
for(unsigned i=0; i<resistance.height(); i++){
  for(unsigned j=0; j<resistance.width(); j++){
    HSLAPixel&cur = resistance.getPixel(j,i);
    if(cur.a == 0.0){
      cur.a =1.0;
    }
  }
}

Image equal;
equal.readFromFile("mp2_8.png");
equal.scale(0.3);
for(unsigned i=0; i<equal.height(); i++){
  for(unsigned j=0; j<equal.width(); j++){
    HSLAPixel&cur = equal.getPixel(j,i);
    if(cur.a == 0.0){
      cur.a =1.0;
    }
  }
}
Image music;
music.readFromFile("mp2_14.png");
music.scale(0.5);
for(unsigned i=0; i<music.height(); i++){
  for(unsigned j=0; j<music.width(); j++){
    HSLAPixel&cur = music.getPixel(j,i);
    if(cur.a == 0.0){
      cur.a =1.0;
    }
  }
}

Image love;
love.readFromFile("mp2_1.png");
love.scale(0.5);
for(unsigned i=0; i<love.height();i++){
  for(unsigned j=0; j<love.width();j++){
    HSLAPixel& cur = love.getPixel(j,i);
    if(cur.a==0.0){
      cur.a = 1.0;
    }
  }
}

Image heat;
heat.readFromFile("2-13.png");
heat.scale(0.4);
for(unsigned i=0; i<love.height();i++){
  for(unsigned j=0; j<love.width();j++){
    HSLAPixel& cur = love.getPixel(j,i);
    if(cur.a==0.0){
      cur.a = 1.0;
    }
  }
}
Image moto;
moto.readFromFile("mp2_9.png");
moto.scale(0.25);
for(unsigned i=0; i<love.height();i++){
  for(unsigned j=0; j<love.width();j++){
    HSLAPixel& cur = love.getPixel(j,i);
    if(cur.a==0.0){
      cur.a = 1.0;
    }
  }
}

//start
StickerSheet mysheet(background,8);
mysheet.addSticker(theme,400,450);
mysheet.addSticker(bless,200,600);
mysheet.addSticker(resistance,0,0);
mysheet.addSticker(equal,310,0);
mysheet.addSticker(music,1100,0);
mysheet.addSticker(love,700,0);
mysheet.addSticker(heat,450,250);
mysheet.addSticker(moto,0,400);


Image out = mysheet.render();
out.writeToFile("myImage.png");

/*
Image smallgroup;
smallgroup.readFromFile("sg.png");

Image me;
me.readFromFile("me.png");
me.scale(0.4);
//start
StickerSheet mysheet(smallgroup,1);
mysheet.addSticker(me,94,600);
Image out = mysheet.render();
out.writeToFile("myImage.png");
*/
  return 0;
}

/**
 * @file StickerSheet.h
 * Contains your declaration of the interface for the StickerSheet class.
 */
#ifndef STICKERSHEET_H_
#define STICKERSHEET_H_
#include"Image.h"

class StickerSheet:public Image{
  //declaration of functions in StickerSheet class
  public:
    StickerSheet(const Image &picture, unsigned max);
    ~StickerSheet();
    StickerSheet(const StickerSheet & other);
    const StickerSheet& operator=(const StickerSheet&other);
    void changeMaxStickers(unsigned max);
    int addSticker(Image&sticker,unsigned x, unsigned y);
    bool translate(unsigned index, unsigned x, unsigned y);
    void removeSticker(unsigned index);
    Image* getSticker(const unsigned index);
    const Image render();

  private:
    //a helper class within StickerSheet that make the data strutcure much easier and clearer to use
    class sticker{
      public:
        unsigned int x_co;
        unsigned int y_co;
        Image* addr;
        sticker(){x_co = 0; y_co =0; addr = NULL;};
        sticker(Image* add, unsigned int x, unsigned int y){x_co = x; y_co =y; addr = add;};
    };
    unsigned int max_;
    Image base_;
    sticker** Sticker_;
    //a helper copy and delete function for the one for three rule.
    void delete_();
    void copy_(const StickerSheet & other);

};


#endif

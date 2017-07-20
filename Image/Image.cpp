#ifndef __INCLUDE_IMGPROCESS_CLASSEES
#define __INCLUDE_IMGPROCESS_CLASSEES
#include "Image.h"

namespace ImageProcess 
{

    Image::Image(const size_t W, const size_t H): img_H(H), img_W(W) {
        this->data = new Pix[img_H*img_W];
    }
    Image::Image(const size_t W, const size_t H, const uint8_t *img): img_H(H), img_W(W) {
        this->data = new Pix[img_H*img_W];
        for (int i=0; i<H; ++i) {
            for (int j=0; j<W; ++j) {
                this->data[i*W + j].r =     img[(i*W + j)*4 + 0];
                this->data[i*W + j].g =     img[(i*W + j)*4 + 1];
                this->data[i*W + j].b =     img[(i*W + j)*4 + 2];
                this->data[i*W + j].alpha = img[(i*W + j)*4 + 3];
            }
        }
    }
    Image::Image(const size_t W, const size_t H, Pix *input_Data): img_H(H), img_W(W) {
        using std::memcpy;
        if (input_Data==NULL) throw std::runtime_error("received NULL pointer");
        this->data = new Pix[img_H*img_W];
        memcpy(this->data, input_Data, img_H*img_W*sizeof(this->data[0]));
    }
    Image::Image(const Image &copy): img_H(copy.img_H), img_W(copy.img_W) {
        using std::memcpy;
        this->data = new Pix[img_H*img_W];
        memcpy(this->data, copy.data, img_H*img_W*sizeof(this->data[0]));
    }
    uint8_t* Image::output(void) { //dynamic alloc
        uint8_t *out = NULL;
        out = new uint8_t[img_W*img_H*4];
        for (int i=0; i<img_H; ++i) 
            for (int j=0; j<img_W; ++j) {
                out[(i*img_W+j)*4 + 0] = data[i*img_W+j].r;
                out[(i*img_W+j)*4 + 1] = data[i*img_W+j].g;
                out[(i*img_W+j)*4 + 2] = data[i*img_W+j].b;
                out[(i*img_W+j)*4 + 3] = data[i*img_W+j].alpha;
            }
        return out;
    }
    inline void Image::setPixel(const int x, const int y, const Pix &pix) {
        if(x<0||y<0||x>=img_W||y>=img_H) throw std::runtime_error("setPixel out of range");
        this->data[y*img_W+x] = pix;
    }
    inline const Pix Image::getPixel(const int x, const int y) {
        if(x<0||y<0||x>=img_W||y>=img_H) throw std::runtime_error("getPixel out of range");
        return this->data[y*img_W+x];
    }
};
#endif

#ifndef __INCLUDE_IMGPROCESS_CLASSEES
#define __INCLUDE_IMGPROCESS_CLASSEES
#include "Image.h"

namespace ImageProcess 
{
    Image::Image(const char *bmpfile_path) { 
        unsigned char *buffer=NULL;
        unsigned int width=0, height=0;
        int colored = readbmp(bmpfile_path, &width, &height, &buffer);
        int idx;
        this->img_H = height;
        this->img_W = width;
        this->data = new Pix[height*width];
        for (int i=0; i<height; ++i) {
            for (int j=0; j<width; ++j) {
                idx = i*width + j;
                if (colored) {
                    this->data[idx].r = buffer[idx*3 + 0];
                    this->data[idx].g = buffer[idx*3 + 1];
                    this->data[idx].b = buffer[idx*3 + 2];
                } else {
                    this->data[idx].r = this->data[idx].g = this->data[idx].b = buffer[idx];
                }
                this->data[idx].alpha = 255;
            }
        }
        if (buffer!=NULL) free(buffer);
    }
    void Image::writebmp(const char *bmpfile_path) {
        unsigned int img_size = this->img_H*this->img_W*3;
        unsigned char *buffer = NULL;
        buffer = (unsigned char*)malloc(sizeof(unsigned char)*img_size);
        if (buffer==NULL) exit(2);
        
        for (int i=0; i<this->img_H; ++i) {
            for (int j=0; j<this->img_W; ++j) {
                buffer[(i*this->img_W + j)*3 + 0] = this->data[i*this->img_W + j].r;
                buffer[(i*this->img_W + j)*3 + 1] = this->data[i*this->img_W + j].g;
                buffer[(i*this->img_W + j)*3 + 2] = this->data[i*this->img_W + j].b;
            }
        }
        
        ::writebmp(bmpfile_path, this->img_W, this->img_H, buffer);
        
        if (buffer!=NULL) free(buffer);
    }
    Image::Image(const size_t W, const size_t H): img_H(H), img_W(W), data(new Pix[H*W]) { }
    Image::Image(const size_t W, const size_t H, const uint8_t *img): img_H(H), img_W(W), data(new Pix[H*W]) {
        for (int i=0; i<H; ++i) {
            for (int j=0; j<W; ++j) {
                this->data[i*W + j].r =     img[(i*W + j)*4 + 0];
                this->data[i*W + j].g =     img[(i*W + j)*4 + 1];
                this->data[i*W + j].b =     img[(i*W + j)*4 + 2];
                this->data[i*W + j].alpha = img[(i*W + j)*4 + 3];
            }
        }
    }
    Image::Image(const size_t W, const size_t H, const Pix *input_Data): img_H(H), img_W(W), data(new Pix[H*W]) {
        using std::memcpy;
        if (input_Data==NULL) throw std::runtime_error("received NULL pointer");
        memcpy(this->data, input_Data, img_H*img_W*sizeof(this->data[0]));
    }
    Image::Image(const Image &copy): img_H(copy.img_H), img_W(copy.img_W), data(new Pix[copy.img_H*copy.img_W]) {
        using std::memcpy;
        memcpy(this->data, copy.data, img_H*img_W*sizeof(this->data[0]));
    }
    uint8_t* Image::output(void) const { //dynamic alloc
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
    void Image::setPixel(const int x, const int y, const Pix &pix) {
        if(x<0||y<0||x>=img_W||y>=img_H) throw std::runtime_error("setPixel out of range");
        this->data[y*img_W+x] = pix;
    }
    const Pix Image::getPixel(const int x, const int y) const {
        if(x<0||y<0||x>=img_W||y>=img_H) throw std::runtime_error("getPixel out of range");
        return this->data[y*img_W+x];
    }
};
#endif

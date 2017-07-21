#ifndef __INCLUDE_GRADIENT_CPP
#define __INCLUDE_GRADIENT_CPP
#include "utils.h"
#include "Gradient.h"
#include <cmath>

namespace ImageProcess 
{
    Pix Gradient::getGradient(int x, int y) {
        PixDouble center(simg->getPixel(x, y));
        PixDouble right = (x+1==simg->img_W)?center:PixDouble(simg->getPixel(x+1, y));
        PixDouble down = (y+1==simg->img_H)?center:PixDouble(simg->getPixel(x, y+1));
        Pix ret(((right-center) + (down-center)) / 2.0, 24);
        ret.alpha = center.alpha; // restore alpha
        return ret;
    }
    Gradient::Gradient(const Image *img) : simg(img), timg(new Image(img->img_W, img->img_H)) {}
    Image* Gradient::run(void) {
        for (int i=0; i<timg->img_H; ++i) {
            for (int j=0; j<timg->img_W; ++j) {
                Pix res(getGradient(j,i));
                timg->setPixel(j,i,res);
            }
        }
        return new Image(*(this->timg));
    }
    Gradient::~Gradient() {
        if (timg!=NULL) {
            delete timg;
        }
    }
};

#endif

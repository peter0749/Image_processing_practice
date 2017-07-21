#ifndef __INCLUDE_GRADIENT_CPP
#define __INCLUDE_GRADIENT_CPP
#include "utils.h"
#include "Gradient.h"
#include <cmath>

namespace ImageProcess 
{
    const double Gradient::xMask[3][3] = {
        {-1, 0, 1},
        {-2, 0, 2},
        {-1, 0, 1}
    };
    const double Gradient::yMask[3][3] = {
        {-1, -2, -1},
        { 0,  0,  0},
        { 1,  2,  1}
    };
    Pix Gradient::getGradient(int x, int y) {
        PixDouble sx(0,0,0,0);
        PixDouble sy(0,0,0,0);
        PixDouble O(0,0,0,0);
        for (int i=0; i<3; ++i) {
            for (int j=0; j<3; ++j) {
                PixDouble t(simg.getPixel(x+j-1,y+i-1));
                sx = sx + (t*xMask[i][j]);
                sy = sy + (t*yMask[i][j]);
            }
        }
        sx = sx - O;
        sy = sy - O;
        Pix res((sx+sy)/8.0, 24);
        res.alpha = simg.getPixel(x,y).alpha;
        return res;
    }
    Gradient::Gradient(const Image &img) : simg(img.img_W+2, img.img_H+2), timg(img.img_W, img.img_H) {
        /* paddle borders */
        for (int i=0; i<img.img_H; ++i) {
            simg.setPixel(0, i+1, img.getPixel(0, i));
            simg.setPixel(simg.img_W-1, i+1, img.getPixel(img.img_W-1, i));
            for (int j=0; j<img.img_W; ++j) {
                simg.setPixel(j+1, i+1, img.getPixel(j,i));
            }
        }
        for (int i=0; i<img.img_W; ++i) {
            simg.setPixel(i+1, 0, img.getPixel(i, 0));
            simg.setPixel(i+1, simg.img_H-1, img.getPixel(i, img.img_H-1));
        }

        /*paddle corners*/
        simg.setPixel(0,0, img.getPixel(0,0));
        simg.setPixel(0,simg.img_H-1, img.getPixel(0,img.img_H-1));
        simg.setPixel(simg.img_W-1,simg.img_H-1, img.getPixel(img.img_W-1,img.img_H-1));
        simg.setPixel(simg.img_W-1,0, img.getPixel(img.img_W-1,0));
    }
    Image* Gradient::run(void) {
        for (int i=1; i<simg.img_H-1; ++i) {
            for (int j=1; j<simg.img_W-1; ++j) {
                Pix res(getGradient(j,i));
                timg.setPixel(j-1,i-1,res);
            }
        }
        return new Image(this->timg);
    }
    Gradient::~Gradient() {}
};

#endif

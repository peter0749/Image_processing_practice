#ifndef __INCLUDE_GRADIENT_CPP
#define __INCLUDE_GRADIENT_CPP
#include "utils.h"
#include "Laplacian.h"
#include <cmath>

namespace ImageProcess 
{
    #define APPLY_LIM(X) ( X<0?0:( X>255?255:X ) )
    inline int rgb2gray(Pix p) {
        using std::round;
        int lum_int = round(p.r*0.299 + p.g*0.587 + p.b*0.114);
        return APPLY_LIM(lum_int);
    }
    inline PixDouble rgb2yiq(Pix p) {
        double Y = p.r*0.299 + p.g*0.587 + p.b*0.114;
        double I = p.r*0.596 - p.g*0.274 - p.b*0.322;
        double Q = p.r*0.211 - p.g*0.523 + p.b*0.312;
        return PixDouble(Y, I, Q, (double)p.alpha); // value range: [0, 255], unknown, unknown
    }
    inline Pix yiq2rgb(PixDouble p) {
        using std::round;
        int R = round( p.r + 0.956*p.g + 0.621*p.b );
        int G = round( p.r - 0.272*p.g - 0.647*p.b );
        int B = round( p.r - 1.106*p.g + 1.703*p.b );
        return Pix( APPLY_LIM(R), APPLY_LIM(G), APPLY_LIM(B), p.alpha );
    }
    const double Gradient::lMask[3][3] = {
        {0,  -1, 0},
        {-1,  5, -1}, // just add 1 pixel value
        {0,  -1, 0}
    };
    Pix Gradient::getGradient(int x, int y) {
        using std::round;
        double s = 0.0;
        for (int i=0; i<3; ++i) {
            for (int j=0; j<3; ++j) {
                s += rgb2gray(simg.getPixel(x+j-1,y+i-1))*lMask[i][j];
            }
        }
        PixDouble yiq = rgb2yiq(simg.getPixel(x,y));
        yiq.r = s;
        Pix res = yiq2rgb(yiq);
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

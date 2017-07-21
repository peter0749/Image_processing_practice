#ifndef __INCLUDE_ENERGYMAP_CPP
#define __INCLUDE_ENERGYMAP_CPP
#include "utils.h"
#include "EnergyMap.h"
#include <cmath>

namespace ImageProcess 
{
    const double EnergyMap::xMask[3][3] = {
        {-1, 0, 1},
        {-2, 0, 2},
        {-1, 0, 1}
    };
    const double EnergyMap::yMask[3][3] = {
        {-1, -2, -1},
        { 0,  0,  0},
        { 1,  2,  1}
    };
    double EnergyMap::getEnergyMap(int x, int y) {
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
        O  = sx + sy;
        return O.r+O.g+O.b+O.alpha;
    }
    EnergyMap::EnergyMap(const Image &img) : simg(img.img_W+2, img.img_H+2) {
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
    double* EnergyMap::run(void) {
        double *grad = NULL;
        grad = new double[(simg.img_H-2)*(simg.img_W-2)];
        for (int i=1; i<simg.img_H-1; ++i) {
            for (int j=1; j<simg.img_W-1; ++j) {
                grad[(i-1)*(simg.img_W-2) + (j-1)] = getEnergyMap(j,i);
            }
        }
        return grad;
    }
    EnergyMap::~EnergyMap() {}
};

#endif

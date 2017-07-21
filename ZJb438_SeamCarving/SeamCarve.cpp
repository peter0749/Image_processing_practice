#ifndef __INCLUDE_SEAMCARVE_CPP
#define __INCLUDE_SEAMCARVE_CPP
#include "utils.h"
#include "EnergyMap.h"
#include "SeamCarve.h"
namespace ImageProcess 
{
    void SeamCarve::dynamicCarve() {
        double *gradMap = NULL;
        gradMap = grad.run();
        for (int i=0; i<simg.img_H; ++i) 
            dp[i][0] = dp[i][simg.img_W+1] = 1e200;
        for (int i=1; i<=simg.img_W; ++i)
            dp[0][i] = gradMap[i-1];
        for (int i=1; i<simg.img_H; ++i) {
            for (int j=1; j<=simg.img_W; ++j) {
                int k=-1, minidx=-1;
                double minv=1e201;
                for (; k<=1; ++k) {
                    if (dp[i-1][j+k]<minv) {
                        minv = dp[i-1][j+k];
                        minidx = k;
                    }
                }
                dp[i][j] = minv + gradMap[(i*simg.img_W)+(j-1)];
                bt[i][j] = minidx;
            }
        }
        if (gradMap!=NULL) { delete gradMap; gradMap=NULL; }
    }
    SeamCarve::SeamCarve(const Image &img): simg(img), grad(img), timg(img.img_W-1, img.img_H) {
        dp = new double*[img.img_H];
        bt = new int*[img.img_H];
        for (int i=0; i<img.img_H; ++i) {
            dp[i] = new double[img.img_W+2];
            bt[i] = new int[img.img_W+2];
        }
    }
    SeamCarve::~SeamCarve() {
        for (int i=0; i<simg.img_H; ++i) {
            delete[] dp[i]; dp[i]=NULL;
            delete[] bt[i]; bt[i]=NULL;
        }
        delete[] dp; delete[] bt;
        dp=NULL;
        bt=NULL;
    }
    Image* SeamCarve::run(void) {
        int nInf=-1e9;
        this->dynamicCarve();
        double minval=1e300;
        int mindp=1;
        for (int i=1; i<=simg.img_W; ++i) {
            if (dp[simg.img_H-1][i]<minval) {
                minval = dp[simg.img_H-1][i];
                mindp  = i;
            }
        }
        for (int i=simg.img_H-1; i>=0; --i) {
            int last = bt[i][mindp];
            bt[i][mindp] = nInf; 
            mindp+=last;
        }
        for (int i=0; i<simg.img_H; ++i) {
            int k=0;
            for (int j=0; j<simg.img_W; ++j) {
                if (bt[i][j+1]==nInf) continue; // skip deleted pixel
                timg.setPixel(k++,i,simg.getPixel(j,i));
            }
        }
        return new Image(this->timg);
    }
};
#endif

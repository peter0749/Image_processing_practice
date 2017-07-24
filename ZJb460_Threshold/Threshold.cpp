#ifndef __INCLUDE_THRESHOLD_CPP
#define __INCLUDE_THRESHOLD_CPP
#include "Threshold.h"
namespace ImageProcess
{
#define GET_PREFIXSUM(X,a,b) (X[b]-X[a])
    Threshold::Threshold(const Image &src) : source(src), target(src.img_W,src.img_H) {}
    void Threshold::findThreshold(void) {
        int   bestV = 0;
        double maxV = 0;
        for (int i=1; i<256; ++i) { // [1,255]
            int leftW = GET_PREFIXSUM(histPrefix,0,i);
            int rightW= GET_PREFIXSUM(histPrefix,i,256);
            double leftu = GET_PREFIXSUM(weightedSum,0,i) / leftW;
            double rightu= GET_PREFIXSUM(weightedSum,i,256) / rightW;
            double Rs= leftu - rightu;
            double val=leftW*rightW*Rs*Rs;
            if (val>maxV) {
                maxV = val;
                bestV= i;
            }
        }
        this->threshold = bestV;
    }
    void Threshold::histogramPrefix(void) {
        using std::round;
        this->histPrefix[0]=0;
        this->weightedSum[0]=0;
        for (int i=0; i<this->source.img_H; ++i)
            for (int j=0; j<this->source.img_W; ++j) {
                Pix p = source.getPixel(j,i);
                int lum = (int)p.r + (int)p.g + (int)p.b;
                lum = round(lum/3.0);
                ++this->histPrefix[lum+1];
            }
        for (int i=1; i<=256; ++i) {
            this->weightedSum[i] = this->weightedSum[i-1] + this->histPrefix[i]*(i-1);
            this->histPrefix[i]+=this->histPrefix[i-1];
        }
    }
    Image* Threshold::run(void) {
        using std::memset;
        this->histPrefix = new int[300];
        this->weightedSum= new double[300];
        memset(this->histPrefix, 0x00, sizeof(int)*300);
        memset(this->weightedSum, 0x00, sizeof(double)*300);
        this->histogramPrefix();
        this->findThreshold();
        for (int i=0; i<this->source.img_H; ++i)
            for (int j=0; j<this->source.img_W; ++j) {
                Pix p = source.getPixel(j,i);
                double lum = ((uint16_t)p.r+(uint16_t)p.g+(uint16_t)p.b) / 3.0;
                p.r = p.g = p.b = (lum<(double)this->threshold?0u:255u);
                target.setPixel(j,i,p);
            }
        delete this->histPrefix;
        delete this->weightedSum;
        return new Image(target);
    }
    Image* Threshold::run(int _threshold) {
        for (int i=0; i<this->source.img_H; ++i)
            for (int j=0; j<this->source.img_W; ++j) {
                Pix p = source.getPixel(j,i);
                double lum = ((uint16_t)p.r+(uint16_t)p.g+(uint16_t)p.b) / 3.0;
                p.r = p.g = p.b = (lum<(double)_threshold?0u:255u);
                target.setPixel(j,i,p);
            }
        return new Image(target);
    }
#undef GET_PREFIXSUM
}
#endif

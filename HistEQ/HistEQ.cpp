#ifndef __INCLUDE_HISTEQ_CPP
#define __INCLUDE_HISTEQ_CPP
#include "HistEQ.h"
#include <stdio.h>
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
    HistEQ::HistEQ(const Image &src) : source(src), target(src.img_W,src.img_H) {}
    void HistEQ::histogramPrefix(void) {
        // precondition: this->histPrefix all zeros
        using std::round;
        for (int i=0; i<this->source.img_H; ++i)
            for (int j=0; j<this->source.img_W; ++j) {
                int lum = rgb2gray( source.getPixel(j,i) );
                if (lum>0) // only count non-zero entries
                    ++this->histPrefix[lum];
            }
        for (int i=2; i<=255; ++i) {
            this->histPrefix[i]+=this->histPrefix[i-1];
        }
    }
    Image* HistEQ::run(void) {
        using std::memset;
        int *cdf = NULL;
        this->histPrefix = new int[256];
        memset(this->histPrefix, 0x00, sizeof(int)*256);
        this->histogramPrefix();
        cdf = this->histPrefix+1; // ignore zeros, cdf from 1 ~ 255
        int min_cdf = 2e9;
        for (int i=0; i<255; ++i) {
            if (cdf[i]!=0) { min_cdf = cdf[i]; break; }
        }
        int denominator = cdf[254]-min_cdf;
        
        for (int i=0; i<this->source.img_H; ++i) 
            for (int j=0; j<this->source.img_W; ++j) {
                const Pix &p = source.getPixel(j,i);
                PixDouble yiq = rgb2yiq(p);
                int v = round(yiq.r); // round(Y)
                v = APPLY_LIM(v); // clip_value(round(Y), 0, 255)
                int hv = v==0?0:(round( (cdf[v-1]-min_cdf) / (double)denominator * 254.0 )+1); // new Y
                yiq.r = hv; // Y <- new Y
                Pix new_pix = yiq2rgb(yiq);
                new_pix.alpha = p.alpha;
                target.setPixel(j, i, new_pix);
            }

        cdf = NULL;
        delete this->histPrefix;
        return new Image(target);
    }
}
#endif

#ifndef __INCLUDE_HOUGH_CPP
#define __INCLUDE_HOUGH_CPP
#define PI 3.141592653589793238462643383279
#include <cmath>
#include "Hough.h"
namespace ImageProcess
{
#define of(x,y) (x*target->img_W+y)
    HoughCircle::HoughCircle(const Image &ref, double r, double e, int th) : target(new Image(ref)), radius(r), eps(e), thres(th), accumulator(new int[ref.img_W*ref.img_H]), counter(0) {
        using std::round;
        using std::memset;
        Threshold blackNWhite(*target);
        Image *temp = blackNWhite.run(); // auto-thresholding
        delete target; target = temp;
        Gradient  edgeEdtect(*target);   // simple edge-edtecting
        temp = edgeEdtect.run();
        delete target; target = temp;
        memset(accumulator,0x00,sizeof(int)*target->img_W*target->img_H);
        for (int i=0; i<target->img_H; ++i) {
            for (int j=0; j<target->img_W; ++j) {
                if (target->getPixel(j,i).r==0) continue;
                for (double k=0; k<PI*2.0; k+=eps) {
                    int x = round(cos(k)*radius)+j;
                    int y = round(sin(k)*radius)+i;
                    if (x<0||y<0||x>=target->img_W||y>=target->img_H)
                        continue;
                    ++accumulator[of(y,x)]; // 累計四周的點數
                }
            }
        }
        for (int i=0; i<target->img_H; ++i) {
            for (int j=0; j<target->img_W; ++j) {
                if (accumulator[of(i,j)]<thres)  // 小於 thres 的點數，不是圓心
                    accumulator[of(i,j)] = 0;
            }
        }
    }
    HoughCircle::~HoughCircle() {
        delete[] accumulator;
        delete target;
        accumulator=NULL;
        target=NULL;
    }
    Image* HoughCircle::HoughTempResult(void) {
        return new Image(*target);
    }
    Image* HoughCircle::out(void) {
        Image *output = new Image(*target);
        for (int i=0; i<target->img_H; ++i) {
            for (int j=0; j<target->img_W; ++j) {
                if (accumulator[of(i,j)]>0) {
                    Pix circleP = output->getPixel(j,i);
                    circleP.r=255;
                    output->setPixel(j,i,circleP);
                }
            }
        }
        return output;
    }
    int HoughCircle::count(void) {
        // pass
    }
};
#endif

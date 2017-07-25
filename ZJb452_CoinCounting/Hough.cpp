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
        using std::min;
        const int filter[3][3] = {
            1, 2, 1,
            2, 4, 2,
            1, 2, 1
        };
        for (int i=1; i<target->img_H-1; ++i) { // not process on margin, 3x3 gaussian filter
            for (int j=1; j<target->img_W-1; ++j) {
                int sumR=0, sumG=0, sumB=0;
                int alpha=target->getPixel(j,i).alpha;
                for (int k=-1; k<=1; ++k) {
                    for (int l=-1; l<=1; ++l) {
                        sumR += (int)target->getPixel(j+l,i+k).r*filter[k+1][l+1];
                        sumG += (int)target->getPixel(j+l,i+k).g*filter[k+1][l+1];
                        sumB += (int)target->getPixel(j+l,i+k).b*filter[k+1][l+1];
                    }
                }
                sumR = min(255,(int)round(sumR/16.0));
                sumG = min(255,(int)round(sumG/16.0));
                sumB = min(255,(int)round(sumB/16.0));
                target->setPixel(j,i,Pix(sumR,sumG,sumB,alpha));
            }
        }
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

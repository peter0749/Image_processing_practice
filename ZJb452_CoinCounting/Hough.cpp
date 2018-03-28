#ifndef __INCLUDE_HOUGH_CPP
#define __INCLUDE_HOUGH_CPP
// #define PI 3.141592653589793238462643383279
#define PI std::acos(-1)
#include <cmath>
#include <queue>
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
        for (int i=0; i<target->img_H*target->img_W; ++i) 
            accumulator[i] = (accumulator[i]<thres)?0:1;
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
    int HoughCircle::count(int min_component_size=16) {
        using std::queue;
        std::queue<int> que;
        int lab_cnt = 0;
        int del_lab = 0;
        int *labs = new int[target->img_W*target->img_H];
        memset(labs, 0x00, sizeof(labs[0])*target->img_W*target->img_H);
        const int dirs[4][2] = {
            {-1, 0},
            { 0, 1},
            { 1, 0},
            { 0,-1}
        };
        for (int i=0; i<target->img_H; ++i) {
            for (int j=0; j<target->img_W; ++j) {
                if (accumulator[of(i,j)]>0 && labs[of(i,j)]==0) { // has component and not labeled yet
                    ++lab_cnt;
                    int component_size = 1;
                    que.push(of(i,j));
                    labs[of(i,j)] = lab_cnt;
                    while (!que.empty()) {
                        int top=que.front(); que.pop();
                        for (int d=0; d<4; ++d) {
                            int idx = top+of(dirs[d][0], dirs[d][1]);
                            if (accumulator[idx]>0 && labs[idx]==0) { // not labeled
                                labs[idx] = lab_cnt;
                                que.push(idx);
                                ++component_size;
                            }
                        }
                    }
                    if (component_size<min_component_size) ++del_lab;
                }
            }
        }
        delete[] labs;
        return lab_cnt-del_lab;
    }
};
#endif

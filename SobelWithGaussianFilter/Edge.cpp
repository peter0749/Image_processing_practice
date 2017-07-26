#ifndef __INCLUDE_HOUGH_CPP
#define __INCLUDE_HOUGH_CPP
#include <cmath>
#include "Edge.h"
namespace ImageProcess
{
    Edge::Edge(const Image &ref) : target(new Image(ref)) {}
    Edge::~Edge() {
        delete target;
        target=NULL;
    }
    Image* Edge::run(int thres) {
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
        Threshold *blackNWhite = NULL;
        blackNWhite = new Threshold(*target);
        Image *temp = NULL;
        if (thres<1)
            temp = blackNWhite->run(); // auto-thresholding
        else
            temp = blackNWhite->run(thres); // manually
        delete blackNWhite; blackNWhite=NULL;
        delete target; target = temp;
        Gradient  edgeDetect(*target);   // simple edge-edtecting
        temp = edgeDetect.run();
        delete target; target = temp;
        return new Image(*target);
    }
};
#endif

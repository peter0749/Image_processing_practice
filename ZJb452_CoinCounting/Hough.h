#ifndef __INCLUDE_HOUGH_HEADER
#define __INCLUDE_HOUGH_HEADER
#include "utils.h"
#include "Gradient.h"
#include "Threshold.h"
namespace ImageProcess
{
    class HoughCircle {
        private:
            Image *target; // output, do not delete
            int *accumulator;
            double radius;
            double eps;
            int    thres;
            int    counter;
        public:
            HoughCircle(const Image &ref, double r, double e, int th); // : target(W,W), radius(r) , accumulator(...) ...
            ~HoughCircle();
            Image* out(void);   // points circles position
            Image* HoughTempResult(void); 
            int    count(int); // output # of circles
    };
};
#endif

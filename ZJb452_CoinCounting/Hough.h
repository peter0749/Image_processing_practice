#ifndef __INCLUDE_HOUGH_HEADER
#define __INCLUDE_HOUGH_HEADER
#include "utils.h"
#include "Gradient.h"
#include "Threshold.h"
namespace ImageProcess
{
    class HoughCircle {
        private:
            Image target;
            int *accumulator;
            double radius;
            double eps;
            int    thres;
            int    counter;
            void hough(void);
            void markCircle(void); // also count circles
        public:
            HoughCircle(const Image &ref, double r, double e, int th); // : target(W,W), radius(r) , accumulator(...) ...
            Image* out(void);   // points circles position
            int    count(void); // output # of circles
    };
};
#endif

#ifndef __INCLUDE_UTILS_HEADER
#define __INCLUDE_UTILS_HEADER
#include "utils.h"
#include <iostream>
#include <cassert>
#include <cmath>

namespace ImageProcess 
{
    /* Note: This class can only be used once. After run(), please delete it manully. */
    class Scale {
        private:
            const Image *sdata;
            Image *const tdata; // dynamic alloc
            double scaleX, scaleY;
            int mode;
            void biLinearScaling();
            void nearestScaling();
            Pix bilinear(int x, int y);
            Pix nearest(int x, int y);
        public:
            Scale(double _scaleX, double _scaleY, int mode, const Image *img);
            ~Scale();
            Image* run(void);
    };
};
#endif

#ifndef __INCLUDE_GRADIENT_HEADER
#define __INCLUDE_GRADIENT_HEADER
#include "utils.h"
#include <cmath>

namespace ImageProcess 
{
    class Gradient {
        private:
            Image simg;
            Image timg;
            Pix getGradient(int x, int y);
        public:
            Gradient(const Image &img);
            Image* run(void);
            static const double lMask[3][3];
            ~Gradient();
    };
};

#endif

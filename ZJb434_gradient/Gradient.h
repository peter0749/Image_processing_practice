#ifndef __INCLUDE_GRADIENT_HEADER
#define __INCLUDE_GRADIENT_HEADER
#include "utils.h"
#include <cmath>

namespace ImageProcess 
{
    class Gradient {
        private:
            const Image *simg;
            Image *const timg;
            Pix getGradient(int x, int y);
        public:
            Gradient(const Image *img);
            Image* run(void);
            ~Gradient();
    };
};

#endif

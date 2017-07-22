#ifndef __INCLUDE_LINEAR_GRADIENT_HEADER
#define __INCLUDE_LINEAR_GRADIENT_HEADER
#include "../utils/utils.h"
namespace ImageProcess
{
    class LinearGradient {
        private:
            Image out;
            const Pix inner, outer;
            const int mode;
            void linear(); // mode 0
            void radial(); // mode 1
            void alphaRadial(); // not implement yet
        public:
            LinearGradient(const Image &_input);
            LinearGradient(const size_t W, const size_t H, const Pix &_inner,\
                           const Pix   &_outer, int mode);
            Image* run();
    };
};

#endif

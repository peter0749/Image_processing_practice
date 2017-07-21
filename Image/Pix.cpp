#ifndef __INCLUDE_PIX_CLASS
#define __INCLUDE_PIX_CLASS
#include "Pix.h"
namespace ImageProcess
{
    Pix::Pix(uint8_t r, uint8_t g, uint8_t b, uint8_t alpha) : r(r), g(g), b(b), alpha(alpha) {}
    Pix::Pix(const Pix &copy) : r(copy.r), g(copy.g), b(copy.b), alpha(copy.alpha) {}
    Pix::Pix(const PixDouble &copy) : r((uint8_t)copy.r), g((uint8_t)copy.g), b((uint8_t)copy.b), alpha((uint8_t)copy.alpha) {}
    Pix::Pix(const PixDouble &copy, int round) : r((uint8_t)(copy.r+0.5)), g((uint8_t)(copy.g+0.5)), b((uint8_t)(copy.b+0.5)), alpha((uint8_t)(copy.alpha+0.5)) {}
    Pix::Pix() {}

    // only if you using this namespace, the operator overloadings are work.
    const Pix operator+(const Pix &left, const Pix &right) {
        Pix ret(left.r+right.r, left.g+right.g, left.b+right.b, left.alpha+right.alpha);
        return ret;
    }
    const Pix operator-(const Pix &left, const Pix &right) {
        int r = (int)left.r-(int)right.r;
        int g = (int)left.g-(int)right.g;
        int b = (int)left.b-(int)right.b;
        int a = (int)left.alpha-(int)right.alpha;

        Pix ret(r<0?0:r, g<0?0:g, b<0?0:b, a<0?0:a);
        return ret;
    }
};
#endif

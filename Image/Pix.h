#ifndef __INCLUDE_PIX_HEADER
#define __INCLUDE_PIX_HEADER
#include <cstdint>
#include <cmath>
#include "PixDouble.h"
namespace ImageProcess
{
    struct PixDouble;
    struct Pix{
        uint8_t r,g,b,alpha;
        Pix(uint8_t r, uint8_t g, uint8_t b, uint8_t alpha);
        Pix(const Pix &copy);
        Pix(const PixDouble &copy);
        Pix(const PixDouble &copy, int round);
        Pix();
    };
    // only if you using this namespace, the operator overloadings are work.

    const Pix operator+(const Pix &left, const Pix &right);
    const Pix operator-(const Pix &left, const Pix &right);
};
#endif

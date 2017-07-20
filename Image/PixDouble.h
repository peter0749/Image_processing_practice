#ifndef __INCLUDE_PIXDOUBLE_HEADER
#define __INCLUDE_PIXDOUBLE_HEADER
#include <cstdint>
#include "Pix.h"
// a double version of struct Pix
namespace ImageProcess 
{
    struct Pix;
    struct PixDouble{
        double r,g,b,alpha;
        PixDouble(double r, double g, double b, double alpha);
        PixDouble(const Pix &copy);
        PixDouble(const PixDouble &copy);
        PixDouble();
    };
    // only if you using this namespace, the operator overloadings are work.
    const PixDouble operator+(const PixDouble &left, const PixDouble &right);
    const PixDouble operator-(const PixDouble &left, const PixDouble &right);
    const PixDouble operator*(const PixDouble &left, double right);
    const PixDouble operator/(const PixDouble &left, double right);
};
#endif

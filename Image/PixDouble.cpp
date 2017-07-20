#ifndef __INCLUDE_PIXDOUBLE_CLASS
#define __INCLUDE_PIXDOUBLE_CLASS
#include "Pix.h"
// Pix.h declares Pix and PixDouble
namespace ImageProcess
{
    PixDouble::PixDouble(double r, double g, double b, double alpha) : r(r), g(g), b(b), alpha(alpha) {}
    PixDouble::PixDouble(const Pix &copy) : r((double)copy.r), g((double)copy.g), b((double)copy.b), alpha((double)copy.alpha) {}
    PixDouble::PixDouble(const PixDouble &copy) : r(copy.r), g(copy.g), b(copy.b), alpha(copy.alpha) {}
    PixDouble::PixDouble() {/*do nothing*/}

    // only if you using this namespace, the operator overloadings are work.
    const PixDouble operator+(const PixDouble &left, const PixDouble &right) {
        double r = left.r+right.r;
        double g = left.g+right.g;
        double b = left.b+right.b;
        double a = left.alpha+right.alpha;
        PixDouble ret(r,g,b,a);
        return ret;
    }
    const PixDouble operator-(const PixDouble &left, const PixDouble &right) {
        double r = left.r-right.r;
        double g = left.g-right.g;
        double b = left.b-right.b;
        double a = left.alpha-right.alpha;
        PixDouble ret(r<0.0?0.0:r, \
                      g<0.0?0.0:g, \
                      b<0.0?0.0:b, \
                      a<0.0?0.0:a  );
        return ret;
    }
    const PixDouble operator*(const PixDouble &left, double right) {
        PixDouble ret(left.r*right, left.g*right, left.b*right, left.alpha*right);
        return ret;
    }
    const PixDouble operator/(const PixDouble &left, double right) {
        PixDouble ret(left.r/right, left.g/right, left.b/right, left.alpha/right);
        return ret;
    }
};

#endif

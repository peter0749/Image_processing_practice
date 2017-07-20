#ifndef __INCLUDE_IMAGEPROCESS_HEADER
#define __INCLUDE_IMAGEPROCESS_HEADER
#include <stdexcept>
#include <cstring>

namespace ImageProcess
{
    /*
     * Image object structure:
     * some basic information: width, height, pointer to data
     */

    struct Pix {
        uint8_t r,g,b,alpha;
        Pix(uint8_t r, uint8_t g, uint8_t b, uint8_t alpha) : r(r), g(g), b(b), alpha(alpha) {}
        Pix() {/*do nothing*/}
    };

    struct Image {
        size_t img_H, img_W;
        Pix *data;
        Image(const size_t W, const size_t H);
        Image(const size_t W, const size_t H, const uint8_t *img);
        Image(const size_t W, const size_t H, Pix *input_Data);
        Image(const Image &copy);
        inline void setPixel(const int x, const int y, const Pix &pix);
        inline const Pix getPixel(const int x, const int y);
        uint8_t* output(void); //dynamic alloc
        ~Image() { delete[] data; }
    };
};
#endif

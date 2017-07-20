#ifndef __INCLUDE_IMAGEPROCESS_HEADER
#define __INCLUDE_IMAGEPROCESS_HEADER
#include <stdexcept>
#include <cstring>
#include "Pix.h"

namespace ImageProcess
{
    /*
     * Image object structure:
     * some basic information: width, height, pointer to data
     */
    struct Image {
        size_t img_H, img_W;
        Pix *const data; // for security, address of data is assigned if and only if the object is being created
        Image(const size_t W, const size_t H);
        Image(const size_t W, const size_t H, const uint8_t *img);
        Image(const size_t W, const size_t H, const Pix *input_Data);
        Image(const Image &copy);
        void setPixel(const int x, const int y, const Pix &pix);
        const Pix getPixel(const int x, const int y) const;
        uint8_t* output(void) const; //dynamic alloc
        ~Image() { delete[] data; }
    };
};
#endif

#ifndef __ERASER_HEADER_REQUIRE_ONCE
#define __ERASER_HEADER_REQUIRE_ONCE
#include "../Image/Image.h"
#include <cmath>
#include <queue>
#include <functional>
#include <stdexcept>

namespace ImageProcess 
{
    /*
     * Input:     pointer of Image object, operation mode, selected X, selected Y, pixel distance
     * Output:    A processed image
     * Mode:      0: process all data, 1: process adjacenting data
     * Exception: selected coordinate out of range, mode is not 0/1, image pointer is a NULL pointer
     */
    class Eraser {
        private:
            Image *data;
            int mode;
            int opX, opY;
            double diff;
            // Compute rgb diff between two pixels
            double pixDist(const Pix &a, const Pix &b);
            void processWholeImg();
            void processAdjacingPix();
        public:
            Eraser( Image *imgData, int mode,\
                    int selectX, int selectY, double diff);
            void run(void);
            ~Eraser() { data=NULL; }
    };
};
#endif

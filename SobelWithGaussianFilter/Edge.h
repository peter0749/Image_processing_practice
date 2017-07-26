#ifndef __INCLUDE_HOUGH_HEADER
#define __INCLUDE_HOUGH_HEADER
#include "utils.h"
#include "Gradient.h"
#include "Threshold.h"
#include <algorithm>
namespace ImageProcess
{
    class Edge {
        private:
            Image *target; 
        public:
            Edge(const Image &ref);
            ~Edge();
            Image* run(int=0); 
    };
};
#endif

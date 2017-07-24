#ifndef __INCLUDE_THRESHOLD_HEADER
#define __INCLUDE_THRESHOLD_HEADER
#include "utils.h"
#include <cmath>
namespace ImageProcess
{
    class Threshold {
        private:
            int threshold;
            const Image &source;
            int *histPrefix;
            double *weightedSum;
            Image target;
            void findThreshold(void);
            void histogramPrefix(void);
        public:
            Threshold(const Image &src);
            Image* run(void);
            Image* run(int);
    };
};
#endif

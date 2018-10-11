#ifndef __INCLUDE_HISTEQ_HEADER
#define __INCLUDE_HISTEQ_HEADER
#include "utils.h"
#include <cmath>
namespace ImageProcess
{
    class HistEQ {
        private:
            const Image &source;
            int *histPrefix;
            double *weightedSum;
            Image target;
            void histogramEqualization(void);
            void histogramPrefix(void);
        public:
            HistEQ(const Image &src);
            Image* run(void);
    };
};
#endif

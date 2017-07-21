#ifndef __INCLUDE_SEAMCURVE_HEADER
#define __INCLUDE_SEAMCURVE_HEADER
#include "utils.h"
#include "EnergyMap.h"
namespace ImageProcess
{
    class SeamCarve {
        private:
            double **dp;
            int **bt;
            EnergyMap grad; // real computation
            const Image &simg; // just a reference
            Image timg;
            void dynamicCarve();
        public:
            SeamCarve(const Image &img);
            ~SeamCarve();
            Image* run(void);
    };
};
#endif

#ifndef __INCLUDE_ENERGYMAP_HEADER
#define __INCLUDE_ENERGYMAP_HEADER
#include "utils.h"
#include <cmath>

namespace ImageProcess 
{
    class EnergyMap {
        private:
            Image simg;
            double getEnergyMap(int x, int y);
        public:
            EnergyMap(const Image &img);
            double* run(void);
            static const double xMask[3][3], yMask[3][3];
            ~EnergyMap();
    };
};

#endif

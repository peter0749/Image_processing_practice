#ifndef __INCLUDE_TEXTURE_TRNASFER_HEADER
#define __INCLUDE_TEXTURE_TRNASFER_HEADER
#include "../utils/utils.h"
#include <cstring>
#include <algorithm>
#include <cmath>
#include <climits>
namespace ImageProcess
{
    class TextureTransfer {
        private:
            const Image &srcImg;
            const Image &texture;
            int overlap; // 重疊區域
            int pattSize; // 小正方形的邊長
            Image result; // 結果圖像
            double **texSum, **srcSum;
            double regionSum(double **p, int x, int y, int w, int h) const;
            double regionErr(int tx, int ty, \
                             int sx, int sy, int w, int h) const;
            void findBest(int &bx, int &by, int sx, int sy) const;
            void composite(int x, int y, int sx, int sy);
            void montage(void);
        public:
            TextureTransfer(const Image &simg, const Image &texture, int overlap, int pattSize);
            ~TextureTransfer();
            Image* run(void);
    };
};
#endif

#ifndef __INCLUDE_UTILS_CLASS
#define __INCLUDE_UTILS_CLASS
#include "utils.h"
#include "Scale.h"

namespace ImageProcess 
{
    Scale::Scale(double _scaleX, double _scaleY, int mode, const Image *img) : \
        mode(mode), sdata(img), tdata(new Image((size_t)(_scaleX*(double)img->img_W+0.5), (size_t)(_scaleY*(double)img->img_H+0.5))) {
            if (scaleX<0||scaleY<0) throw std::runtime_error("scale ratio is negative");
            if (mode!=0 && mode!=1) throw std::runtime_error("mode is not 0/1");
            if (this->sdata==NULL) throw std::runtime_error("sdata is NULL");
            if (this->tdata==NULL) throw std::runtime_error("tdata is NULL");
            scaleX = (double)this->sdata->img_W / (double)this->tdata->img_W;
            scaleY = (double)this->sdata->img_H / (double)this->tdata->img_H;
            using std::endl;
        }
    Pix Scale::bilinear(int x, int y) {
        double midX = x*scaleX, midY = y*scaleY;
        int left = midX; int right = left+1; int up = midY; int down = up+1;
        double dl = midX-left, dr = right-midX;
        double du = midY-up, dd = down-midY;

        PixDouble upperLeft(this->sdata->getPixel(left, up));

        PixDouble upperRight = (right>=this->sdata->img_W)?upperLeft:PixDouble(this->sdata->getPixel(right,up));
        PixDouble upperMid   = upperLeft*dr + upperRight*dl;

        PixDouble downLeft = (down>=this->sdata->img_H)?upperLeft:PixDouble(this->sdata->getPixel(left,down));
        PixDouble downRight = (down>=this->sdata->img_H || right>=this->sdata->img_W)?downLeft:PixDouble(this->sdata->getPixel(right, down));
        PixDouble downMid = downLeft*dr + downRight*dl;

        PixDouble Mid = downMid*du + upperMid*dd; 

        return Pix(Mid);
    }
    Pix Scale::nearest (int x, int y) {
        using std::pair;
        using std::fabs;
        double midX = x*scaleX, midY = y*scaleY;
        int left = midX, up = midY;
        int dirs[4][2] = { 
            {0, 0},
            {1, 0},
            {0, 1},
            {1, 1}
        };
        double minDist=1e300;
        Pix ret;
        for (int i=0; i<4; ++i) {
            int nx = left+dirs[i][0];
            int ny = up+dirs[i][1];
            if (nx<0||ny<0||nx>=this->sdata->img_W||ny>=this->sdata->img_H) continue;
            double dx = midX-(double)nx;
            double dy = midY-(double)ny;
            double dist = dx*dx + dy*dy;
            if (dist<minDist) {
                minDist = dist;
                ret = this->sdata->getPixel(nx,ny);
            }
        }
        return ret;
    }
    void Scale::biLinearScaling() {
        // pass
        for (int i=0; i<tdata->img_H; ++i) {
            for (int j=0; j<tdata->img_W; ++j) {
                Pix pixel = this->bilinear(j, i);
                this->tdata->setPixel(j, i, pixel);
            }
        }
    }
    void Scale::nearestScaling() {
        // pass
        for (int i=0; i<tdata->img_H; ++i) {
            for (int j=0; j<tdata->img_W; ++j) {
                Pix pixel = this->nearest(j, i);
                this->tdata->setPixel(j, i, pixel);
            }
        }
    }

    Image* Scale::run(void) {
        switch(this->mode) {
            case 0:
                this->biLinearScaling();
                break;
            case 1:
                this->nearestScaling();
                break;
        }
        //return new Image(*(this->tdata));
        return new Image(*(this->tdata));
    }
    Scale::~Scale() {
        delete this->tdata;
    }
};

#endif

#include "utils.h"
#include <iostream>
#include <cassert>
#include <cmath>

namespace ImageProcess 
{
    /* Note: This class can only be used once. After run(), please delete it manully. */
    class Scale {
        private:
            const Image *sdata;
            Image *const tdata; // dynamic alloc
            double scaleX, scaleY;
            int mode;
            void biLinearScaling();
            void nearestScaling();
            Pix bilinear(int x, int y);
            Pix nearest(int x, int y);
        public:
            Scale(double _scaleX, double _scaleY, int mode, const Image *img);
            ~Scale();
            Image* run(void);
    };
};

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

#include <iostream>
#include <cstdint>

int main(int argc, char **argv) {
    using namespace std;
    if (argc!=6) return -1;
    // argv[1]: source, argv[2]: target
    // argv[3]: ratioX, argv[4]: ratioY
    // argv[5]: mode(0: bilinear/ 1: nearest)
    uint32_t imgWidth=0, imgHeight=0;
    uint8_t *buff = NULL;

    /* Read png32 image from disk */
    unsigned err = Lodepng::lodepng_decode32_file(&buff, &imgWidth, &imgHeight, argv[1]);
    assert(err==0);
    assert(buff!=NULL);

    /* Load raw image to my object */
    ImageProcess::Image img(imgWidth, imgHeight, buff);
    if (buff!=NULL) {
        free(buff), buff=NULL;
    }

    /* Call image processor */
    ImageProcess::Scale *scale = NULL;
    scale = new ImageProcess::Scale(atof(argv[3]), atof(argv[4]), atoi(argv[5]), &img);
    assert(scale!=NULL);
    ImageProcess::Image *img2 = NULL;
    img2 = scale->run();
    assert(img2!=NULL);
    delete scale; scale=NULL; // scale can only be used once.

    /* Output raw image from object */
    buff = img2->output();
    imgWidth = img2->img_W;
    imgHeight= img2->img_H;
    delete img2; img2=NULL;

    /* Output png image to disk */
    err = Lodepng::lodepng_encode32_file(argv[2], buff, imgWidth, imgHeight);
    assert(err==0);

    if (buff!=NULL) {
        free(buff), buff=NULL;
    }

    return 0;
}

#include <iostream>
#include <iomanip>
#include <cstdint>
#include <cstring>
#include <functional>
#include <cmath>
#include <cassert>
namespace ImageProcess
{
    struct Pix;
    struct PixDouble;
    struct Pix{
        uint8_t r,g,b,alpha;
        Pix(uint8_t r, uint8_t g, uint8_t b, uint8_t alpha) : r(r), g(g), b(b), alpha(alpha) {}
        Pix(const Pix &copy) : r(copy.r), g(copy.g), b(copy.b), alpha(copy.alpha) {}
        Pix(const PixDouble &copy);
        Pix() {};
    };
    struct PixDouble{
        double r,g,b,alpha;
        PixDouble(double r, double g, double b, double alpha) : r(r), g(g), b(b), alpha(alpha) {}
        PixDouble(const Pix &copy) : r((double)copy.r), g((double)copy.g), b((double)copy.b), alpha((double)copy.alpha) {}
        PixDouble(const PixDouble &copy);
        PixDouble(){};
    };
    Pix::Pix(const PixDouble &copy) : r((uint8_t)copy.r), g((uint8_t)copy.g), b((uint8_t)copy.b), alpha((uint8_t)copy.alpha) {}
    PixDouble::PixDouble(const PixDouble &copy) : r(copy.r), g(copy.g), b(copy.b), alpha(copy.alpha) {}
    const PixDouble operator+(const PixDouble &left, const PixDouble &right) {
        double r = left.r+right.r;
        double g = left.g+right.g;
        double b = left.b+right.b;
        double a = left.alpha+right.alpha;
        PixDouble ret(r,g,b,a);
        return ret;
    }
    const PixDouble operator*(const PixDouble &left, double right) {
        PixDouble ret(left.r*right, left.g*right, left.b*right, left.alpha*right);
        return ret;
    }
    struct Image {
        size_t img_H, img_W;
        Pix *const data; // for security, address of data is assigned if and only if the object is being created
        Image(const size_t W, const size_t H): img_H(H), img_W(W), data(new Pix[H*W]) { }
        Image(const Image &copy): img_H(copy.img_H), img_W(copy.img_W), data(new Pix[copy.img_H*copy.img_W]) {
            using std::memcpy;
            memcpy(this->data, copy.data, img_H*img_W*sizeof(this->data[0]));
        }
        void setPixel(const int x, const int y, const Pix &pix) {
            if(x<0||y<0||x>=img_W||y>=img_H) throw std::runtime_error("setPixel out of range");
            this->data[y*img_W+x] = pix;
        }
        const Pix getPixel(const int x, const int y) const {
            if(x<0||y<0||x>=img_W||y>=img_H) throw std::runtime_error("getPixel out of range");
            return this->data[y*img_W+x];
        }
        ~Image() { delete[] data; }
    };
    class Scale {
        private:
            const Image *sdata;
            Image *tdata; // dynamic alloc
            double scaleX, scaleY;
            int mode;
            Pix bilinear(int x, int y) {
                double midX = x*scaleX, midY = y*scaleY;
                int left = midX; int right = left+1; int up = midY; int down = up+1;
                double dl = midX-left, dr = right-midX;
                double du = midY-up, dd = down-midY;
                PixDouble upperLeft(this->sdata->getPixel(left, up));
                PixDouble upperRight = (right>=this->sdata->img_W)?upperLeft:PixDouble(this->sdata->getPixel(right,up));
                PixDouble upperMid   = upperLeft*dr + upperRight*dl; // interpolation on upper pixels
                if (down>=this->sdata->img_H) return Pix(upperMid);  // no lower pixels
                PixDouble downLeft(this->sdata->getPixel(left,down));
                PixDouble downRight = (right>=this->sdata->img_W)?downLeft:PixDouble(this->sdata->getPixel(right, down));
                PixDouble downMid = downLeft*dr + downRight*dl;
                PixDouble Mid = downMid*du + upperMid*dd;
                return Pix(Mid);
            }
            Pix nearest (int x, int y) {
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
            void biLinearScaling() {
                for (int i=0; i<tdata->img_H; ++i) {
                    for (int j=0; j<tdata->img_W; ++j) {
                        Pix pixel = this->bilinear(j, i);
                        this->tdata->setPixel(j, i, pixel);
                    }
                }
            }
            void nearestScaling() {
                for (int i=0; i<tdata->img_H; ++i) {
                    for (int j=0; j<tdata->img_W; ++j) {
                        Pix pixel = this->nearest(j, i);
                        this->tdata->setPixel(j, i, pixel);
                    }
                }
            }
        public:
            Scale(double _scaleX, double _scaleY, int mode, const Image *img) : \
                mode(mode), sdata(img) {
                    tdata=NULL;
                    if (_scaleX<0||_scaleY<0) throw std::runtime_error("scale ratio is negative");
                    int W = (int)((double)sdata->img_W*_scaleX+0.5);
                    int H = (int)((double)sdata->img_H*_scaleY+0.5);
                    if (W<=0||H<=0||W>256||H>256)
                        throw std::runtime_error("Online Judge!!!");
                    if (mode!=0 && mode!=1) throw std::runtime_error("mode is not 0/1");
                    tdata = new Image((size_t)W,(size_t)H); // 以上都沒 exception 發生才分配記憶體位址
                    if (this->sdata==NULL) throw std::runtime_error("sdata is NULL");
                    if (this->tdata==NULL) throw std::runtime_error("tdata is NULL");
                    scaleX = (double)this->sdata->img_W / (double)this->tdata->img_W;
                    scaleY = (double)this->sdata->img_H / (double)this->tdata->img_H;
                }
            ~Scale() {
                if (tdata!=NULL) {
                    delete this->tdata;
                    this->tdata = NULL;
                }
            }
            Image* run(void) {
                switch(this->mode) {
                    case 0:
                        this->biLinearScaling();
                        break;
                    case 1:
                        this->nearestScaling();
                        break;
                }
                return new Image(*(this->tdata));
            }
    };
};

int main(void) {
    using namespace std;
    double sx, sy;
    int w,h;
    int type;
    ImageProcess::Image *img=NULL;
    ImageProcess::Image *converted=NULL;
    ImageProcess::Scale *scaler=NULL;
    while(cin>>sx>>sy>>type) {
        cin >> w >> h;
        img = new ImageProcess::Image(w,h);
        for (int i=0; i<h; ++i) for (int j=0; j<w; ++j) {
            int r,g,b,a;
            cin >> r >> g >> b >> a;
            img->setPixel(j,i,ImageProcess::Pix((uint8_t)r,(uint8_t)g,(uint8_t)b,(uint8_t)a));
        }
        scaler=NULL;
        try {
            scaler = new ImageProcess::Scale(sx,sy,type,img);
        } catch(const std::runtime_error &e) {
            std::cerr << "error: " << e.what() << ", and pointer of scaler: " << hex << (size_t)scaler << std::endl;
            // 實驗了一下，當 constructor 失敗時，本該接收 new 到新位址的 pointer 原始值不變
            // （也就是說，在本例 scaler 仍會是 NULL）
            // 將 scaler 重新指向 NULL 即可
            
            scaler = NULL; // how to handle!?
            /*finally*/
            if (img!=NULL) {
                delete img; img = NULL;
            }
            continue;
        }
        converted = scaler->run();
        if (scaler!=NULL) {
            delete scaler; scaler=NULL;
        }
        cout << converted->img_W << ' ' << converted->img_H << '\n';
        for (int i=0; i<converted->img_H; ++i) {
            for (int j=0; j<converted->img_W; ++j) {
                if (j!=0) cout << ' ';
                ImageProcess::Pix out = converted->getPixel(j, i);
                cout << (int)out.r << ' ' << (int)out.g << ' ' << (int)out.b << ' ' << (int)out.alpha;
            }
            cout << endl;
        }
        if (img!=NULL) {
            delete img; img=NULL;
        }
    }
    return 0;
}

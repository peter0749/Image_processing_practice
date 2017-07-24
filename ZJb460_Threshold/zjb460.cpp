#pragma GCC target ("avx")
#pragma GCC optimize ("O3")
#include <bits/stdc++.h>
namespace ImageProcess
{
    struct Pix{
        uint8_t r,g,b,alpha;
        Pix(uint8_t r, uint8_t g, uint8_t b, uint8_t alpha) : r(r), g(g), b(b), alpha(alpha) {}
        Pix(const Pix &copy) : r(copy.r), g(copy.g), b(copy.b), alpha(copy.alpha) {}
        Pix(){};
    };
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
#define GET_PREFIXSUM(X,a,b) (X[b]-X[a])
    Threshold::Threshold(const Image &src) : source(src), target(src.img_W,src.img_H) {}
    void Threshold::findThreshold(void) {
        int   bestV = 0;
        double maxV = 0;
        for (int i=1; i<256; ++i) { // [1,255]
            int leftW = GET_PREFIXSUM(histPrefix,0,i);
            int rightW= GET_PREFIXSUM(histPrefix,i,256);
            double leftu = GET_PREFIXSUM(weightedSum,0,i) / leftW;
            double rightu= GET_PREFIXSUM(weightedSum,i,256) / rightW;
            double Rs= leftu - rightu;
            double val=leftW*rightW*Rs*Rs;
            if (val>maxV) {
                maxV = val;
                bestV= i;
            }
        }
        this->threshold = bestV;
    }
    void Threshold::histogramPrefix(void) {
        using std::round;
        this->histPrefix[0]=0;
        this->weightedSum[0]=0;
        for (int i=0; i<this->source.img_H; ++i)
            for (int j=0; j<this->source.img_W; ++j) {
                Pix p = source.getPixel(j,i);
                int lum = (int)p.r + (int)p.g + (int)p.b;
                lum = round(lum/3.0);
                ++this->histPrefix[lum+1];
            }
        for (int i=1; i<=256; ++i) {
            this->weightedSum[i] = this->weightedSum[i-1] + this->histPrefix[i]*(i-1);
            this->histPrefix[i]+=this->histPrefix[i-1];
        }
    }
    Image* Threshold::run(void) {
        using std::memset;
        this->histPrefix = new int[300];
        this->weightedSum= new double[300];
        memset(this->histPrefix, 0x00, sizeof(int)*300);
        memset(this->weightedSum, 0x00, sizeof(double)*300);
        this->histogramPrefix();
        this->findThreshold();
        for (int i=0; i<this->source.img_H; ++i)
            for (int j=0; j<this->source.img_W; ++j) {
                Pix p = source.getPixel(j,i);
                double lum = ((uint16_t)p.r+(uint16_t)p.g+(uint16_t)p.b) / 3.0;
                p.r = p.g = p.b = (lum<(double)this->threshold?0u:255u);
                target.setPixel(j,i,p);
            }
        delete this->histPrefix;
        delete this->weightedSum;
        return new Image(target);
    }
    Image* Threshold::run(int _threshold) {
        for (int i=0; i<this->source.img_H; ++i)
            for (int j=0; j<this->source.img_W; ++j) {
                Pix p = source.getPixel(j,i);
                double lum = ((uint16_t)p.r+(uint16_t)p.g+(uint16_t)p.b) / 3.0;
                p.r = p.g = p.b = (lum<(double)_threshold?0u:255u);
                target.setPixel(j,i,p);
            }
        return new Image(target);
    }
#undef GET_PREFIXSUM
};

int main(void) {
    using namespace std;
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int w, h;
    cin >> w >> h;
    ImageProcess::Image img(w,h);
    for (int i=0; i<h; ++i) {
        for (int j=0; j<w; ++j) {
            int r,g,b;
            cin >> r >> g >> b;
            img.setPixel(j,i,ImageProcess::Pix((uint8_t)r,(uint8_t)g,(uint8_t)b,255));
        }
    }
    ImageProcess::Threshold thres(img);
    ImageProcess::Image *img2 = NULL;
    img2 = thres.run();
    assert(img2!=NULL);
    cout << img2->img_W << ' ' << img2->img_H << endl;
    for (int i=0; i<img2->img_H; ++i) {
        for (int j=0; j<img2->img_W; ++j) {
            ImageProcess::Pix out = img2->getPixel(j,i);
            if (j!=0) cout << ' ';
            cout << (int)out.r << ' ' << (int)out.g << ' ' << (int)out.b;
        }
        cout << endl;
    }
    if (img2!=NULL) {
        delete img2; img2=NULL;
    }
    return 0;
}

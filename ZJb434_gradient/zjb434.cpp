#pragma GCC target ("avx")
#pragma GCC optimize ("O3")
#include <bits/stdc++.h>
namespace ImageProcess
{
    struct PixDouble;

    struct Pix{
        uint8_t r,g,b,alpha;
        Pix(uint8_t r, uint8_t g, uint8_t b, uint8_t alpha) : r(r), g(g), b(b), alpha(alpha) {}
        Pix(const Pix &copy) : r(copy.r), g(copy.g), b(copy.b), alpha(copy.alpha) {}
        Pix(const PixDouble &copy);
        Pix(const PixDouble &copy, int round);
        Pix(){};
    };
    struct PixDouble{
        double r,g,b,alpha;
        PixDouble(double r, double g, double b, double alpha) : r(r), g(g), b(b), alpha(alpha) {}
        PixDouble(const Pix &copy) : r((double)copy.r), g((double)copy.g), b((double)copy.b), alpha((double)copy.alpha) {}
        PixDouble(const PixDouble &copy) : r(copy.r), g(copy.g), b(copy.b), alpha(copy.alpha) {}
        PixDouble(){};
    };
    Pix::Pix(const PixDouble &copy) : r((uint8_t)copy.r), g((uint8_t)copy.g), b((uint8_t)copy.b), alpha((uint8_t)copy.alpha) {}
    Pix::Pix(const PixDouble &copy, int round) : r((uint8_t)(copy.r+0.5)), g((uint8_t)(copy.g+0.5)), b((uint8_t)(copy.b+0.5)), alpha((uint8_t)(copy.alpha+0.5)) {}

    const PixDouble operator+(const PixDouble &left, const PixDouble &right) {
        double r = left.r+right.r;
        double g = left.g+right.g;
        double b = left.b+right.b;
        double a = left.alpha+right.alpha;
        PixDouble ret(r,g,b,a);
        return ret;
    }
    const PixDouble operator-(const PixDouble &left, const PixDouble &right) {
        using std::fabs;
        double r = fabs(left.r-right.r);
        double g = fabs(left.g-right.g);
        double b = fabs(left.b-right.b);
        double a = fabs(left.alpha-right.alpha);
        PixDouble ret(r, g, b, a);
        return ret;
    }
    const PixDouble operator/(const PixDouble &left, double right) {
        PixDouble ret(left.r/right, left.g/right, left.b/right, left.alpha/right);
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
    class Gradient {
        private:
            const Image *simg;
            Image *const timg;
            Pix getGradient(int x, int y) {
                PixDouble center(simg->getPixel(x, y));
                PixDouble right = (x+1==simg->img_W)?center:PixDouble(simg->getPixel(x+1, y));
                PixDouble down = (y+1==simg->img_H)?center:PixDouble(simg->getPixel(x, y+1));
                Pix ret(((right-center) + (down-center)) / 2.0, 24);
                ret.alpha = center.alpha; // restore alpha
                return ret;
            }
        public:
            Gradient(const Image *img) : simg(img), timg(new Image(img->img_W, img->img_H)) {}
            Image* run(void) {
                for (int i=0; i<timg->img_H; ++i) {
                    for (int j=0; j<timg->img_W; ++j) {
                        Pix res(getGradient(j,i));
                        timg->setPixel(j,i,res);
                    }
                }
                return new Image(*(this->timg));
            }
            ~Gradient() {
                if (timg!=NULL) {
                    delete timg;
                }
            }
    };
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
    ImageProcess::Gradient *gradient = NULL;
    gradient = new ImageProcess::Gradient(&img);
    assert(gradient!=NULL);
    ImageProcess::Image *img2 = NULL;
    img2 = gradient->run();
    assert(img2!=NULL);
    if (gradient!=NULL) {
        delete gradient; gradient=NULL;
    }
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

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
    const PixDouble operator*(const PixDouble &left, double right) {
        PixDouble ret(left.r*right, left.g*right, left.b*right, left.alpha*right);
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
            Image simg;
            Image timg;
            Pix getGradient(int x, int y) {
                PixDouble sx(0,0,0,0);
                PixDouble sy(0,0,0,0);
                PixDouble O(0,0,0,0);
                for (int i=0; i<3; ++i) {
                    for (int j=0; j<3; ++j) {
                        PixDouble t(simg.getPixel(x+j-1,y+i-1));
                        sx = sx + (t*xMask[i][j]);
                        sy = sy + (t*yMask[i][j]);
                    }
                }
                sx = sx - O;
                sy = sy - O;
                Pix res((sx+sy)/8.0, 24);
                res.alpha = simg.getPixel(x,y).alpha;
                return res;
            }
        public:
            Gradient(const Image &img) : simg(img.img_W+2, img.img_H+2), timg(img.img_W, img.img_H) {
                /* paddle borders */
                for (int i=0; i<img.img_H; ++i) {
                    simg.setPixel(0, i+1, img.getPixel(0, i));
                    simg.setPixel(simg.img_W-1, i+1, img.getPixel(img.img_W-1, i));
                    for (int j=0; j<img.img_W; ++j) {
                        simg.setPixel(j+1, i+1, img.getPixel(j,i));
                    }
                }
                for (int i=0; i<img.img_W; ++i) {
                    simg.setPixel(i+1, 0, img.getPixel(i, 0));
                    simg.setPixel(i+1, simg.img_H-1, img.getPixel(i, img.img_H-1));
                }

                /*paddle corners*/
                simg.setPixel(0,0, img.getPixel(0,0));
                simg.setPixel(0,simg.img_H-1, img.getPixel(0,img.img_H-1));
                simg.setPixel(simg.img_W-1,simg.img_H-1, img.getPixel(img.img_W-1,img.img_H-1));
                simg.setPixel(simg.img_W-1,0, img.getPixel(img.img_W-1,0));
            }
            Image* run(void) {
                for (int i=1; i<simg.img_H-1; ++i) {
                    for (int j=1; j<simg.img_W-1; ++j) {
                        Pix res(getGradient(j,i));
                        timg.setPixel(j-1,i-1,res);
                    }
                }
                return new Image(this->timg);
            }
            static const double xMask[3][3], yMask[3][3];
            ~Gradient() {};
    };
    const double Gradient::xMask[3][3] = {
        {-1, 0, 1},
        {-2, 0, 2},
        {-1, 0, 1}
    };
    const double Gradient::yMask[3][3] = {
        {-1, -2, -1},
        { 0,  0,  0},
        { 1,  2,  1}
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
    ImageProcess::Gradient gradient(img);
    ImageProcess::Image *img2 = NULL;
    img2 = gradient.run();
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

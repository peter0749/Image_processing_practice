#include <bits/stdc++.h>
namespace IMP
{
    struct PixD;
    struct Pix;
    struct Pix{
        uint8_t r,g,b,a;
        Pix(uint8_t r, uint8_t g, uint8_t b, uint8_t a) : r(r), g(g), b(b), a(a) {}
        Pix(const Pix &copy) : r(copy.r), g(copy.g), b(copy.b), a(copy.a) {}
        Pix(const PixD &copy);
        Pix(const PixD &copy, int round);
        Pix() {};
    };
    struct PixD{
        double r,g,b,a;
        PixD(double r, double g, double b, double a) : r(r), g(g), b(b), a(a) {}
        PixD(const Pix &copy);
        PixD(const PixD &copy) : r(copy.r), g(copy.g), b(copy.b), a(copy.a) {}
        PixD() {};
    };

    Pix::Pix(const PixD &copy) : r((uint8_t)copy.r), g((uint8_t)copy.g), b((uint8_t)copy.b), a((uint8_t)copy.a) {}
    Pix::Pix(const PixD &copy, int round) : r((uint8_t)(copy.r+0.5)), g((uint8_t)(copy.g+0.5)), b((uint8_t)(copy.b+0.5)), a((uint8_t)(copy.a+0.5)) {}
    PixD::PixD(const Pix &copy) : r((double)copy.r), g((double)copy.g), b((double)copy.b), a((double)copy.a) {}

    const PixD operator+(const PixD &left, const PixD &right) {
        double r = left.r+right.r;
        double g = left.g+right.g;
        double b = left.b+right.b;
        double a = left.a+right.a;
        PixD ret(r,g,b,a);
        return ret;
    }
    const PixD operator-(const PixD &left, const PixD &right) {
        using std::fabs;
        double r = fabs(left.r-right.r);
        double g = fabs(left.g-right.g);
        double b = fabs(left.b-right.b);
        double a = fabs(left.a-right.a);
        PixD ret(r, g, b, a);
        return ret;
    }
    const PixD operator*(const PixD &left, double right) {
        PixD ret(left.r*right, left.g*right, left.b*right, left.a*right);
        return ret;
    }
    const PixD operator/(const PixD &left, double right) {
        PixD ret(left.r/right, left.g/right, left.b/right, left.a/right);
        return ret;
    }
    struct Img {
        size_t img_H, img_W;
        Pix *const data; // for security, address of data is assigned if and only if the object is being created
        Img(const size_t W, const size_t H): img_H(H), img_W(W), data(new Pix[H*W]) { }
        Img(const Img &copy): img_H(copy.img_H), img_W(copy.img_W), data(new Pix[copy.img_H*copy.img_W]) {
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
        ~Img() { delete[] data; }
    };
    class LinearGradient {
        private:
            Img out;
            Pix inner, outer;
            int mode;
            void linear() { // mode 0
                double dist = out.img_W-1.0;
                PixD left(this->inner);
                PixD right(this->outer);
                for (int i=0; i<out.img_H; ++i) {
                    for (int j=0; j<out.img_W; ++j) {
                        if (out.img_W==1) {
                            this->out.setPixel(j, i, Pix(left, 45));
                            continue;
                        }
                        double dl=j;
                        double dr=dist-dl;
                        this->out.setPixel(j, i, Pix((left*dr + right*dl)/dist, 45));
                    }
                }
            }
            void radial() { // mode 1
                using std::hypot;
#define DIST(a,b,c,d) std::sqrt( (a-c)*(a-c) + (b-d)*(b-d) )
                PixD left(this->inner);
                PixD right(this->outer);
                double midx = (double)(out.img_W-1) / 2.0;
                double midy = (double)(out.img_H-1) / 2.0;
                double radius = DIST(midx, midy, 0, 0);
                for (int i=0; i<out.img_H; ++i) {
                    for (int j=0; j<out.img_W; ++j) {
                        if (out.img_W==1) {
                            this->out.setPixel(j, i, Pix(left, 45));
                            continue;
                        }
                        double dl = DIST(j,i,midx,midy);
                        this->out.setPixel(j, i, Pix((left*(radius-dl)+right*dl) / radius ,45));
                    }
                }
            }
            //void aRadial(); // not implement yet
        public:
            LinearGradient(const size_t W, const size_t H, const Pix &_inner,\
                    const Pix   &_outer, int mode) : out(W,H), inner(_inner), outer(_outer), mode(mode) {
                if (mode!=0&&mode!=1) throw std::runtime_error("in LinearGradient constructor: mode must 0/1/2");
            }
            Img* run() {
                switch(this->mode) {
                    case 0:
                        this->linear();
                        break;
                    case 1:
                        this->radial();
                        break;
                }
                return new Img(this->out);
            }
    };
};

int main(void) {
    using namespace std;
    using namespace IMP;
    int W, H, TYPE, R1, G1, B1, A1, R2, G2, B2, A2;
    cin >> W >> H >> TYPE >> R1 >> G1 >> B1 >> A1 >> R2 >> G2 >> B2 >> A2;
    Pix p1(R1,G1,B1,A1);
    Pix p2(R2,G2,B2,A2);
    LinearGradient limg(W,H,p1,p2,TYPE);
    Img *buff = NULL;
    buff = limg.run();
    cout << W << ' ' << H << endl;
    for (int i=0; i<H; ++i) {
        for (int j=0; j<W; ++j) {
            if (j!=0) cout << ' ';
            Pix pix = buff->getPixel(j,i);
            cout << (int)pix.r << ' ' << (int)pix.g << ' ' << (int)pix.b << ' ' << (int)pix.a;
        }
        cout << endl;
    }
    delete buff; buff=NULL;
    return 0;
}

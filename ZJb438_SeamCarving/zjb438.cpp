#pragma GCC optimize ("O3")
#include <bits/stdc++.h>
namespace IPS
{
    struct _PD;
    struct _P{
        uint8_t r,g,b,alpha;
        _P(uint8_t r, uint8_t g, uint8_t b, uint8_t alpha) : r(r), g(g), b(b), alpha(alpha) {}
        _P(const _P &copy) : r(copy.r), g(copy.g), b(copy.b), alpha(copy.alpha) {}
        _P(const _PD &copy);
        _P(const _PD &copy, int round);
        _P(){};
    };
    struct _PD{
        int r,g,b,alpha;
        _PD(int r, int g, int b, int alpha) : r(r), g(g), b(b), alpha(alpha) {}
        _PD(const _P &copy) : r((int)copy.r), g((int)copy.g), b((int)copy.b), alpha((int)copy.alpha) {}
        _PD(const _PD &copy) : r(copy.r), g(copy.g), b(copy.b), alpha(copy.alpha) {}
        _PD(){};
    };
    _P::_P(const _PD &copy) : r((uint8_t)copy.r), g((uint8_t)copy.g), b((uint8_t)copy.b), alpha((uint8_t)copy.alpha) {}
    _P::_P(const _PD &copy, int round) : r((uint8_t)(copy.r+0.5)), g((uint8_t)(copy.g+0.5)), b((uint8_t)(copy.b+0.5)), alpha((uint8_t)(copy.alpha+0.5)) {}
    const _PD operator+(const _PD &left, const _PD &right) {
        int r = left.r+right.r;
        int g = left.g+right.g;
        int b = left.b+right.b;
        int a = left.alpha+right.alpha;
        _PD ret(r,g,b,a);
        return ret;
    }
    const _PD operator-(const _PD &left, const _PD &right) {
        using std::fabs;
        int r = fabs(left.r-right.r);
        int g = fabs(left.g-right.g);
        int b = fabs(left.b-right.b);
        int a = fabs(left.alpha-right.alpha);
        _PD ret(r, g, b, a);
        return ret;
    }
    const _PD operator*(const _PD &left, int right) {
        _PD ret(left.r*right, left.g*right, left.b*right, left.alpha*right);
        return ret;
    }
    const _PD operator/(const _PD &left, int right) {
        _PD ret(left.r/right, left.g/right, left.b/right, left.alpha/right);
        return ret;
    }
    struct _IG {
        size_t img_H, img_W;
        _P *const data; // for security, address of data is assigned if and only if the object is being created
        _IG(const size_t W, const size_t H): img_H(H), img_W(W), data(new _P[H*W]) { }
        _IG(const _IG &copy): img_H(copy.img_H), img_W(copy.img_W), data(new _P[copy.img_H*copy.img_W]) {
            using std::memcpy;
            memcpy(this->data, copy.data, img_H*img_W*sizeof(this->data[0]));
        }
        void set_Pel(const int x, const int y, const _P &pix) {
            if(x<0||y<0||x>=img_W||y>=img_H) throw std::runtime_error("set_Pel out of range");
            this->data[y*img_W+x] = pix;
        }
        const _P get_Pel(const int x, const int y) const {
            if(x<0||y<0||x>=img_W||y>=img_H) throw std::runtime_error("get_Pel out of range");
            return this->data[y*img_W+x];
        }
        ~_IG() { delete[] data; }
    };
    class _EM {
        private:
            _IG simg;
            int get_EM(int x, int y) {
                _PD sx(0,0,0,0);
                _PD sy(0,0,0,0);
                _PD O(0,0,0,0);
                for (int i=0; i<3; ++i) {
                    for (int j=0; j<3; ++j) {
                        _PD t(simg.get_Pel(x+j-1,y+i-1));
                        sx = sx + (t*xMask[i][j]);
                        sy = sy + (t*yMask[i][j]);
                    }
                }
                sx = sx - O;
                sy = sy - O;
                O  = sx + sy;
                return O.r+O.g+O.b+O.alpha;
            }
        public:
            _EM(const _IG &img) : simg(img.img_W+2, img.img_H+2) {
                /* paddle borders */
                for (int i=0; i<img.img_H; ++i) {
                    simg.set_Pel(0, i+1, img.get_Pel(0, i));
                    simg.set_Pel(simg.img_W-1, i+1, img.get_Pel(img.img_W-1, i));
                    for (int j=0; j<img.img_W; ++j) {
                        simg.set_Pel(j+1, i+1, img.get_Pel(j,i));
                    }
                }
                for (int i=0; i<img.img_W; ++i) {
                    simg.set_Pel(i+1, 0, img.get_Pel(i, 0));
                    simg.set_Pel(i+1, simg.img_H-1, img.get_Pel(i, img.img_H-1));
                }

                /*paddle corners*/
                simg.set_Pel(0,0, img.get_Pel(0,0));
                simg.set_Pel(0,simg.img_H-1, img.get_Pel(0,img.img_H-1));
                simg.set_Pel(simg.img_W-1,simg.img_H-1, img.get_Pel(img.img_W-1,img.img_H-1));
                simg.set_Pel(simg.img_W-1,0, img.get_Pel(img.img_W-1,0));
            }
            int* run(void) {
                int *grad = NULL;
                grad = new int[(simg.img_H-2)*(simg.img_W-2)];
                for (int i=1; i<simg.img_H-1; ++i) {
                    for (int j=1; j<simg.img_W-1; ++j) {
                        grad[(i-1)*(simg.img_W-2) + (j-1)] = get_EM(j,i);
                    }
                }
                return grad;
            }
            static const int xMask[3][3], yMask[3][3];
            ~_EM() {};
    };
    const int _EM::xMask[3][3] = {
        {-1, 0, 1},
        {-2, 0, 2},
        {-1, 0, 1}
    };
    const int _EM::yMask[3][3] = {
        {-1, -2, -1},
        { 0,  0,  0},
        { 1,  2,  1}
    };
    class _SC {
        private:
            int **dp;
            _EM grad; // real computation
            const _IG &simg; // just a reference
            _IG timg;
            void dynamicCarve() {
                using std::min;
                int *gradMap = NULL;
                gradMap = grad.run();
                for (int i=0; i<simg.img_H; ++i)
                    dp[i][0] = dp[i][simg.img_W+1] = 1e9;
                for (int i=1; i<=simg.img_W; ++i)
                    dp[0][i] = gradMap[i-1];
                for (int i=1; i<simg.img_H; ++i) {
                    for (int j=1; j<=simg.img_W; ++j) {
                        int minv=1e9-1;
                        for (int k=-1; k<=1; ++k) {
                            minv = min(minv, dp[i-1][j+k]);
                        }
                        dp[i][j] = minv + gradMap[(i*simg.img_W)+(j-1)];
                    }
                }
                int minval=1e9-1;
                int mindp=1;
                for (int i=1; i<=simg.img_W; ++i) {
                    if (dp[simg.img_H-1][i]<minval) {
                        minval = dp[simg.img_H-1][i];
                        mindp  = i;
                    }
                }
                // backtrace
                for (int i=simg.img_H-1; i>=1; --i) {
                    for (int k=-1; k<=1; ++k) {
                        if (dp[i][mindp]==dp[i-1][mindp+k]+gradMap[i*simg.img_W+mindp-1]) {
                            dp[i][mindp] = -1; // mark for delete
                            mindp += k;
                            break;
                        }
                    }
                }
                dp[0][mindp] = -1; // finally, mark first row
                if (gradMap!=NULL) { delete gradMap; gradMap=NULL; }
            }
        public:
            _SC(const _IG &img): simg(img), grad(img), timg(img.img_W-1, img.img_H) {
                dp = new int*[img.img_H];
                for (int i=0; i<img.img_H; ++i) {
                    dp[i] = new int[img.img_W+2];
                }
            }
            ~_SC() {
                for (int i=0; i<simg.img_H; ++i) {
                    delete[] dp[i]; dp[i]=NULL;
                }
                delete[] dp;
                dp=NULL;
            }
            _IG* run(void) {
                int nInf=-1e9;
                this->dynamicCarve();
                for (int i=0; i<simg.img_H; ++i) {
                    int k=0;
                    for (int j=0; j<simg.img_W; ++j) {
                        if(dp[i][j+1]<0) continue;
                        timg.set_Pel(k++,i,simg.get_Pel(j,i));
                    }
                }
                return new _IG(this->timg);
            }
    };
};

int main(void) {
    using namespace std;
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int N, w, h;
    cin >> N;
    cin >> w >> h;
    IPS::_IG *img = NULL;
    img = new IPS::_IG(w,h);
    assert(img!=NULL);
    for (int i=0; i<h; ++i) {
        for (int j=0; j<w; ++j) {
            int r,g,b;
            cin >> r >> g >> b;
            img->set_Pel(j,i,IPS::_P((uint8_t)r,(uint8_t)g,(uint8_t)b,255));
        }
    }
    IPS::_SC *seam = NULL;
    for (int i=0; i<N; ++i) {
        seam = NULL;
        seam = new IPS::_SC(*img);
        assert(seam!=NULL);
        IPS::_IG *img2 = NULL;
        img2 = seam->run();
        assert(img2!=NULL);
        if (seam!=NULL) {
            delete seam;
            seam = NULL;
        }
        if (img!=NULL) {
            delete img;
            img = NULL;
        }
        img = img2;
    }
    assert(img!=NULL);
    cout << img->img_W << ' ' << img->img_H << endl;
    for (int i=0; i<img->img_H; ++i) {
        for (int j=0; j<img->img_W; ++j) {
            IPS::_P out = img->get_Pel(j,i);
            if (j!=0) cout << ' ';
            cout << (int)out.r << ' ' << (int)out.g << ' ' << (int)out.b;
        }
        cout << endl;
    }
    if (img!=NULL) {
        delete img; img=NULL;
    }
    return 0;
}

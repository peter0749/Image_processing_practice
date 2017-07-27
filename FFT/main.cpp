#include "FFT.h"
#include "FFT.hpp"
#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>

double area[512][512];

int main(void) {
    using namespace std;
    int Ah, Aw, Bh, Bw;
    int W, H;
    vector<int> A(262144);
    vector<int> B(262144);
    vector<double> conv(262144);
    ios::sync_with_stdio(false);
    cin.tie(0);cout.tie(0);
    int T; cin >> T;
    while (T--) {
        cin >> Ah >> Aw >> Bh >> Bw;
        W = max(Aw,Bw);
        H = max(Ah,Bh);
        int n = H*W, n2base=1;
        for (n2base=1; n>n2base; n2base<<=1); // n2base==2^k , n2base>=n
        A.resize(n2base); B.resize(n2base);
        fill(A.begin(), A.end(), 0);
        fill(B.begin(), B.end(), 0);
        for (int i=0; i<Ah; ++i) {
            for (int j=0; j<Aw; ++j) {
                cin >> A.at(i*W+j);
            }
        }
        for (int i=0; i<Bh; ++i) {
            for (int j=0; j<Bw; ++j) {
                cin >> B.at(i*W+j);
            }
        }
        FFT::convolution<int>(A, B, conv);
#ifdef DEBUG
        for (int i=0; i<conv.size(); ++i) {
            int _i=i/W;
            int _j=i%W;
            if (_i+Bh>Ah||_j+Bw>Aw) continue;
            cout << "conv[" << (i/W) << "][" << (i%W) << "] = " << conv.at(i) << endl;
        }
#endif
        memset(area, 0x00, sizeof(area));
        for (int i=1; i<=Ah; ++i) {
            double sum=0.0;
            for (int j=1; j<=Aw; ++j) {
                sum += A[(i-1)*W+(j-1)]*A[(i-1)*W+(j-1)];
                area[i][j] = sum + area[i-1][j]; // 2D prefix sum
            }
        }
        double minval=1e300;
        int x=0, y=0;
        for (int i=0; i+Bh<=Ah; ++i) {
            for (int j=0; j+Bw<=Aw; ++j) {
                double diff=area[i+Bh][j+Bw] - area[i+Bh][j] - area[i][j+Bw] + area[i][j];
#ifdef DEBUG
                cout << "A2[" << i << "][" << j << "] = " << diff << endl;
#endif
                diff -= 2.0*conv[i*W+j];
                if (diff<minval) {
                    minval = diff;
                    x=j, y=i;
                }
            }
        }
        cout << y+1 << ' ' << x+1 << endl;
    }
    return 0;
}

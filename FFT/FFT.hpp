#ifndef __INCLUDE_FFT_HPP
#define __INCLUDE_FFT_HPP
#include "FFT.h"
namespace FFT
{
    template<class T>
        void convolution(const vector<T> &a, const vector<T> &b, vector<double> &ret) {
            int n = a.size();
            vector<complex<double> > s(n), d1(n), d2(n), y(n);
            for (int i = 0; i < n; ++i) {
                s[i] = complex<double>(a[i], 0);
            }
            FFT(false, s, d1);
            s[0] = complex<double>(b[0], 0);
            for (int i = 1; i < n; ++i) {
                s[i] = complex<double>(b[n - i], 0);
            }
            FFT(false, s, d2);
            for (int i = 0; i < n; ++i) {
                y[i] = d1[i] * d2[i];
            }
            FFT(true, y, s);
            ret.resize(n,0);
            for (int i = 0; i < n; ++i) {
                ret[i] = s[i].real();
            }
        }
}; //namespace FFT
#endif

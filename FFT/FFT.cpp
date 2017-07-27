#ifndef __INCLUDE_FFT_CPP
#define __INCLUDE_FFT_CPP
#include "FFT.h"
#define M_PIl 3.1415926535897932384626433832795028841971693993751058209749445923078164062862089986280348253421170679
// 預防 for(int i; ...) 的 i 跑到 scope 外面
#define for if (0); else for

namespace FFT // WARNING!!! do not reveal this namespace
{
    int NumberOfBitsNeeded(int PowerOfTwo) {
        for (int i = 0;; ++i) {
            if (PowerOfTwo & (1 << i)) {
                return i;
            }
        }
    }

    void FFT(bool InverseTransform, const vector<complex<double> >& In, vector<complex<double> >& Out) {
        // simultaneous data copy and bit-reversal ordering into outputs
        int NumSamples = In.size();
        int NumBits = NumberOfBitsNeeded(NumSamples);
        for (int i = 0; i < NumSamples; ++i) {
            Out[FastReverseBits((uint32_t)i, NumBits)] = In[i];
        }
        // the FFT process
        double angle_numerator = M_PIl * (InverseTransform ? -2 : 2);
        for (int BlockEnd = 1, BlockSize = 2; BlockSize <= NumSamples; BlockSize <<= 1) {
            double ndelta_angle = -(angle_numerator / BlockSize);
            double sin1 = sin(ndelta_angle);
            double cos1 = cos(ndelta_angle);
            double sin2 = 2*sin1*cos1;
            double cos2 = 2*cos1*cos1-1.0;
            for (int i = 0; i < NumSamples; i += BlockSize) {
                complex<double> a1(cos1, sin1), a2(cos2, sin2);
                for (int j = i, n = 0; n < BlockEnd; ++j, ++n) {
                    complex<double> a0(2 * cos1 * a1.real() - a2.real(), 2 * cos1 * a1.imag() - a2.imag());
                    a2 = a1;
                    a1 = a0;
                    complex<double> a = a0 * Out[j + BlockEnd];
                    Out[j + BlockEnd] = Out[j] - a;
                    Out[j] += a;
                }
            }
            BlockEnd = BlockSize;
        }
        // normalize if inverse transform
        if (InverseTransform) {
            for (int i = 0; i < NumSamples; ++i) {
                Out[i] /= NumSamples;
            }
        }
    }

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
}; // namespace FFT
#endif

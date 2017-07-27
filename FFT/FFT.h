#ifndef __INCLUDE_FFT_HEADER
#define __INCLUDE_FFT_HEADER
#pragma GCC optimize ("Os")
#pragma GCC optimize ("O3")
#include <iostream>
#include <algorithm>
#include <vector>
#include <complex>
#include <cmath>
#include <cstring>
#include <cstdint>
namespace FFT // WARNING!!! do not reveal this namespace
{
    using namespace std;
    int NumberOfBitsNeeded(int PowerOfTwo);
    inline uint32_t FastReverseBits(uint32_t a, int NumBits) {
        a = ( ( a & 0x55555555U ) << 1 ) | ( ( a & 0xAAAAAAAAU ) >> 1 ) ;
        a = ( ( a & 0x33333333U ) << 2 ) | ( ( a & 0xCCCCCCCCU ) >> 2 ) ;
        a = ( ( a & 0x0F0F0F0FU ) << 4 ) | ( ( a & 0xF0F0F0F0U ) >> 4 ) ;
        a = ( ( a & 0x00FF00FFU ) << 8 ) | ( ( a & 0xFF00FF00U ) >> 8 ) ;
        a = ( ( a & 0x0000FFFFU ) << 16 ) | ( ( a & 0xFFFF0000U ) >> 16 ) ;
        return a >> (32 - NumBits);
    }
    void FFT(bool, const vector<complex<double> >&, vector<complex<double> >&) __attribute__((optimize("fast-math")));
    /**
     * Given two sequences {a1, a2, a3.. an} and {b1, b2, b3... bn},
     * their repeat convolution means:
     * r1 = a1*b1 + a2*b2 + a3*b3 + ... + an*bn
     * r2 = a1*bn + a2*b1 + a3*b2 + ... + an*bn-1
     * r3 = a1*bn-1 + a2*bn + a3*b1 + ... + an*bn-2
     * ...
     * rn = a1*b2 + a2*b3 + a3*b4 + ... + an-1*bn + an*b1
     * Notice n >= 2 and n must be power of 2.
     */
    template<class T>
        void convolution(const vector<T> &a, const vector<T> &b, vector<double> &ret) __attribute__((optimize("fast-math")));
}; // namespace FFT
#endif

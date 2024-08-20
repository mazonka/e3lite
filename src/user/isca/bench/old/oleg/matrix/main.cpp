// Copyright 2022 MoMA Lab, NYU Abu Dhabi (wp.nyu.edu/momalab/)
#include <iostream>
#include <vector>

#include "e3int.h"
#include "timer.h"

#include "e3key.h"
template<class T> inline std::string de(T x) { return e3::decrypt<T>(x); }

#ifndef SZ
#define SZ 8
#endif

#define MAX_ITER 10


using namespace std;
using SecureInt  = TypeUint<SZ>;
using SecureBool = TypeBool;
using SecureMint = TypeMint;

template <class T>
void printMatrix(const vector<vector<T>> & m)
{
    for (size_t i = 0; i < m.size(); i++)
    {
        for (size_t j = 0; j < m[0].size(); j++) cout << ' ' << de(m[i][j]);
        cout << std::endl;
    }
}

template <class T>
vector<vector<T>> matrixMul(const vector<vector<T>> & a,
                            const vector<vector<T>> & b)
{
    vector<vector<T>> c (a.size(), vector<T>(b[0].size()));
    //T zero = _0_Ea;

    for ( int k = 0; k < MAX_ITER; k++ ) // do many times
    {
        for (size_t i = 0; i < a.size(); i++)
        {
            for (size_t j = 0; j < b[0].size(); j++)
            {
                for (size_t k = 0; k < b.size(); k++)
                {
                    if (k) c[i][j] += a[i][k] * b[k][j];
                    else c[i][j] = a[i][k] * b[k][j];
                }
            }
        }
    }
    return c;
}

int main(void)
{
    {
        vector<vector<SecureMint>> a = {  \
            { _1_Ea, _2_Ea, _3_Ea }, \
            { _2_Ea, _3_Ea, _4_Ea }, \
            { _3_Ea, _4_Ea, _5_Ea }
        };
        vector<vector<SecureMint>> b = {  \
            { _1_Ea, _2_Ea, _3_Ea }, \
            { _2_Ea, _3_Ea, _4_Ea }, \
            { _3_Ea, _4_Ea, _5_Ea }
        };
        Timer t;
        auto c = matrixMul<SecureMint>(a, b);
        auto r = t.get();
        printMatrix(c);
        cout << "SecureMint Runtime: " << r << " us\n";
    }


    {
        vector<vector<SecureInt>> a = {  \
            { _1_Ep, _2_Ep, _3_Ep }, \
            { _2_Ep, _3_Ep, _4_Ep }, \
            { _3_Ep, _4_Ep, _5_Ep }
        };
        vector<vector<SecureInt>> b = {  \
            { _1_Ep, _2_Ep, _3_Ep }, \
            { _2_Ep, _3_Ep, _4_Ep }, \
            { _3_Ep, _4_Ep, _5_Ep }
        };
        Timer t;
        auto c = matrixMul<SecureInt>(a, b);
        auto r = t.get();
        printMatrix(c);
        cout << "SecureInt Runtime: " << r << " us\n";
    }
}

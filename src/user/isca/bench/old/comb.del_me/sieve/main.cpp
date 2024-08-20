// Copyright 2022 MoMA Lab, NYU Abu Dhabi (wp.nyu.edu/momalab/)
#include <iostream>
#include <vector>

#include "e3int.h"
#include "timer.h"

#ifndef SZ
#define SZ 8
#endif
#define N_ELEMS 100

using namespace std;
using SecureInt  = TypeUint<SZ>;
using SecureBool = TypeBool;

template <class T>
void printVector(const vector<T> & v)
{
    for (size_t p = 2; p < v.size(); p++)
        cout << v[p] << ' ';
    cout << std::endl;
}

vector<SecureInt> sieveOfEratosthenes(size_t n)
{
    vector<SecureInt> ret (n + 1);
    vector<SecureBool> prime (n + 1, _1_Ep);
    for (int p = 2; p * p < n + 1 ; p++)
    {
        for (int i = 2 * p; i < n + 1 ; i += p) // Update all multiples of p
            prime[i] = _0_Ep;
    }
    SecureInt pe = _2_Ep;
    for (int p = 2; p < n + 1; pe++, p++)
        ret[p] = pe * prime[p];
    return ret;
}

int main(void)
{
    Timer t;
    auto v = sieveOfEratosthenes(N_ELEMS);
    auto r = t.get();
    // printVector(v);
    cout << "Runtime: " << r << " us\n";
}

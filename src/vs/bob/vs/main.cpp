// Copyright 2022 MoMA Lab, NYU Abu Dhabi (wp.nyu.edu/momalab/)
#include <iostream>
#include <string>
#include <vector>
#include <tuple>
#include <functional>

#include "e3int.h"
#include "e3key.h"

using namespace std;

template<class T> inline std::string de(T x) { return e3::decrypt<T>(x); }

struct Securo : Secure
{
    template <class T> Securo(T x) : Secure(x) {}
    e3::PaliBfvNativeCiphertext & get() { return x; }
    e3::PaliBfvNativePrivKey & getcc() { return pek->key.cc; }
};


#ifdef PALISADE_VERSION

#include "palidbg.inc"

#else

e3::PaliBfvNativeCiphertext opmul(e3::PaliBfvNativeCiphertext & x,
                                  e3::PaliBfvNativeCiphertext & y,
							 e3::PaliBfvNativePrivKey & cc, int)
{
    auto z = x.op_mul(y, cc);
    return z;
}

#endif


int main(int ac, char * av[])
try
{
    Securo ax = _2_En, ay = _3_En;
    e3::PaliBfvNativeCiphertext x = ax.get();
    auto y = ay.get();
    e3::PaliBfvNativePrivKey cc = ax.getcc();

    std::hash<string> hash;

    auto z = opmul(x, y, cc, 2); //return 0;

    for ( int i = 0; i < 3; i++ )
    {
        auto z = opmul(x, y, cc, i);
        Securo az(z);
        string saz = de(az);
        cout << hash(saz) << '\n';
    }
}
catch (string e)
{
    cout << "Error: " << e << "\n";
}
catch (const char * e)
{
    cout << "Error: " << e << "\n";
}
catch (std::exception & e)
{
    cout << "Error (std): " << e.what() << endl;
}
catch (...)
{
    cout << "exception\n";
}

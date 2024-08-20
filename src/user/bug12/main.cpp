// Copyright 2022 MoMA Lab, NYU Abu Dhabi (wp.nyu.edu/momalab/)
#include <iostream>
#include <vector>
#include <iomanip>


#define GC_USE_MACROS
#include "e3int.h"

#include "e3key.h"
template<class T> inline std::string de(T x) { return e3::decrypt<T>(x); }

#ifndef SZ
#define SZ 8
#endif

using namespace std;
using Securi  = TypeInt<SZ>;
using Securu  = TypeUint<SZ>;
using Secmod  = TypeMint;
//using SecureBool = SecireBool;

int main()
try
{
    if (0)
    {
        Secmod a(_1_M), b(_1_M);
        for (int i = 0; i < 40; i++)
        {
            cout << i << " " << de(b) << '\n';
            b *= a;
        }
    }

    Securi i1(_1_E), n1(_1_N);
    Securu u1(_1_E), u3(_3_E);
    //Secmod m1(_1_M);

    //cout << "i1=" << de(i1) << '\n';
    //cout << "u1=" << de(u1) << '\n';
    //cout << "u3=" << de(u3) << '\n';
    //cout << "m1=" << de(m1) << '\n';
    //cout << "n1=" << de(n1) << '\n';

    cout << "M c : " << de(TypeMint(_65536_M)) << '\n';
    cout << "M i1: " << de(to_TypeMint(i1)) << '\n';
    //cout << "M n1: " << de(to_SecureMod(n1)) << '\n';

    for ( int i = 0; i < 100; i++ )
    {
        cout << i << ": " << de(to_TypeMint(u1 + Securu(i))) << '\n';
    }
}
catch (const char * e)
{
    cout << "Error: " << e << "\n";
}
catch (string e)
{
    cout << "Error: " << e << "\n";
}
catch (const std::exception & e)
{
    cout << "Error (std): " << e.what() << "\n";
}
catch (...)
{
    cout << "exception ...\n";
}

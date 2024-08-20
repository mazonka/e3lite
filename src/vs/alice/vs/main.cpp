#include <iostream>
#include <vector>
#include <iomanip>


#define GC_USE_MACROS
#include "e3int.h"

#include "e3key.h"
template<class T> inline std::string de(T x) { return e3::decrypt<T>(x); }

#ifndef SZ
#define SZ 4
#endif

using namespace std;
using Securi  = SecureInt<SZ>;
using Securu  = SecureUint<SZ>;
using Secmod  = SecureMod;
//using SecureBool = SecireBool;

int main()
try
{
    if (1)
    {
        Secmod a(_1_M), b(_1_M);
        for (int i = 0; i < 2; i++)
        {
            cout << i << " " << de(b) << '\n';
            b *= a;
        }
    }

    Securi i0(_0_E), i1(_1_E), n1(_1_N);
    Securu u1(_1_E), u3(_3_E);
    Secmod m1(_1_M);

    //cout << "i0=" << de(i0) << '\n';
    //cout << "i1=" << de(i1) << '\n';
    //cout << "u1=" << de(u1) << '\n';
    //cout << "u3=" << de(u3) << '\n';
    //cout << "m1=" << de(m1) << '\n';
    //cout << "n1=" << de(n1) << '\n';

    if (0)
    {
        using Sectfhe = CtfheInt<8>;
        cout << "enc(14) = " << de(Sectfhe(_14_Et)) << '\n';
        cout << "enc(-4) = " << de(Sectfhe(_4_En)) << '\n';
    }

    //Secmod mi1(to_SecureMod(i1));//, mim1(to_Secmod(im1));
    cout << "M i1: " << de(to_SecureMod(i1)) << '\n'; //<<de(mim1)<<'\n';
    cout << "M a1: " << de(SecureMod(_65536_M)) << '\n'; //<<de(mim1)<<'\n';
    cout << "M n1: " << de(to_SecureMod(n1)) << '\n'; //<<de(mim1)<<'\n';
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

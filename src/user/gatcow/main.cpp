// Copyright 2022 MoMA Lab, NYU Abu Dhabi (wp.nyu.edu/momalab/)
#include <iostream>
#include <vector>
#include <iomanip>

///#include "e3int.h"

#define GC_USE_MACROS
#include "e3int.h"
///#include "gatcow.h"

#include "e3key.h"
template<class T> inline std::string de(T x) { return e3::decrypt<T>(x); }

#ifndef SZ
#define SZ 8
#endif
#define MAX_ITER 10

using namespace std;
using SecureInt  = TypeUint<SZ>;
using SecureBool = TypeBool;

namespace gw = e3::gatcow;

template <class T>
T fib(const SecureInt & input, int niter, const T & zero, const T & one)
{
    T f1  = zero;
    T f2  = one;
    T fi  = one;
    SecureInt  i   = _1_Ep;
    T res = zero;

    gw::PathBlock pb("fibo");
    //gc::PathBlock pb(gc::PBT::Par);
    //gc::PathBlock pb;
    ///std::cout << "AAA Summary: " << pb.sum() << '\n';
    for ( ; niter--; )
    {
        ///gc::Path share(niter);
        GC_share;
        res += (i == input) * fi;
        fi = f1 + f2;
        f1 = f2;
        f2 = fi;
        i++;
    }

    //pb.stop();

    pb.print();
    std::cout << "Summary: " << pb.sum() << '\n';

    return res;
}

template <class T>
void tmain(string name, const T & zero, const T & one)
{
    SecureInt input = _7_Ep;
    auto f = fib<T>(input, MAX_ITER, zero, one);
    cout << "Fibo: " << de(input) << " -> " << de(f) << '\n';
}


int main()
try
{
    gw::PathBlock::isvalid();
    GC_valid;

    void simple01(); simple01();
    void simple02(); simple02();
#define SIM(x)    void simple##x(); simple##x();
#define TST(x)    void test##x(); test##x();

    SIM(03)
    SIM(04)
    SIM(05)
    SIM(06)
    SIM(07)
    SIM(08)
    SIM(09)
    SIM(10)
    SIM(11)
    SIM(12)
    SIM(13)
    SIM(14)
    SIM(15)
    SIM(16)
    SIM(17)
    SIM(18)

    TST(01)
    TST(02)

#undef TST
#undef SIM

    //tmain<SecureInt> ( "SecureInt", _0_Ep, _1_Ep);
    std::ignore = _0_Ep;
    std::ignore = _1_Ep;

    gw::PathBlock::isvalid();
}
catch (const char * e)
{
    cout << "Error: " << e << "\n";
}
catch (string e)
{
    cout << "Error: " << e << "\n";
}
catch (const std::exception &e)
{
    cout << "Error (std): " << e.what() << "\n";
}
catch (...)
{
    cout << "exception ...\n";
}

using namespace e3::gatcow;


void mod(int n)
{
    SecureBool a, b;
    for ( int i = 0; i < n; i++ ) a = a && b;
}

void simple01()
{
    SecureBool a, b;

    PathBlock pb;

    for ( int i = 0; i < 2; i++ )
    {
        GC_share;
        a = a && b;
    }

    pb.print();
    cout << "(01): " << pb.sum(1, " ") << '\n';
}

void simple02()
{
    SecureBool a, b;

    PathBlock pb(PAR);

    for ( int i = 0; i < 2; i++ )
    {
        GC_share;
        a = a && b;
    }

    pb.print();
    cout << "(02): " << pb.sum(1, " ") << '\n';
}


void simple03()
{
    PathBlock pb0;

    mod(1);
    {
        PathBlock pb1;

        for ( int i = 0; i < 3; i++ )
        {
            GC_share;
            mod(3);
        }
    }
    mod(2);

    cout << "(03) 1+3.3+2 : " << pb0.sum(1, " ") << '\n';
}

void simple04()
{
    PathBlock pb0;

    mod(1);
    {
        PathBlock pb1 {gw::PAR};

        for ( int i = 0; i < 3; i++ )
        {
            GC_share;
            mod(3);
        }
    }
    mod(2);

    cout << "(04) 1+3:3+2 : " << pb0.sum(1, " ") << '\n';
}


void simple05()
{
    PathBlock pb0;

    mod(1);

    for ( int i = 0; i < 3; i++ )
    {
        GC_share;
        {
            PathBlock pb1 {gw::PAR};
            for ( int j = 0; j < 4; j++ )
            {
                Share path("mod10");
                mod(10);
            }
        }
    }

    mod(2);

    cout << "(05) 1+3.(4:10)+2 : " << pb0.sum(1, " ") << '\n';
}

void simple06()
{
    PathBlock pb0;

    mod(1);

    for ( int i = 0; i < 3; i++ )
    {
        GC_share;
        {
            PathBlock pb1 {gw::PAR};
            for ( int j = 0; j < 4; j++ )
            {
                Share path("mod10");
                mod(10);
            }
        }

        {
            PathBlock pb1 {gw::PAR};
            for ( int j = 0; j < 3; j++ )
            {
                Share path("mod10");
                mod(10);
            }
        }
    }

    mod(2);

    cout << "(06) 1+3.(4:10+3:10)+2 : " << pb0.sum(1, " ") << '\n';
}

void simple07()
{
    PathBlock pb0;

    {
        GC_share;
        {
            PathBlock pb1 {gw::PAR};
            for ( int j = 0; j < 4; j++ )
            {
                Share path("mod10");
                mod(10);
            }
            pb1.merge();
            for ( int j = 0; j < 3; j++ )
            {
                Share path("mod10");
                mod(10);
            }
        }
    }

    cout << "(07) 4:m10+3:m10 : " << pb0.sum(1, " ") << '\n';
}

void simple08()
{
    PathBlock pb0;

    {
        PathBlock pb1 {gw::PAR};
        {
            Share path("mod10");
            mod(10);
        }
        pb1.merge();
        {
            Share path("mod10");
            mod(10);
        }
    }

    cout << "(08) m10+m10 : " << pb0.sum() << '\n';
}


void simple09()
{
    PathBlock pb0;

    {
        GC_share;
        {
            PathBlock pb1 {gw::PAR};
            for ( int j = 0; j < 4; j++ )
            {
                Share path("mod10");
                mod(10);
            }
        }

        for ( int j = 0; j < 2; j++ )
        {
            Share path("mod10");
            mod(10);
        }
    }

    cout << "(09) 4:m10+2.m10 : " << pb0.sum() << '\n';
}

void simple10()
{
    PathBlock pb;

    mod(1);

    for ( int i = 0; i < 3; i++ )
    {
        GC_share;
        { Share m("m10"); mod(10); }
        mod(4);

        {
            PathBlock pb3("pb3");
            for ( int j = 0; j < 3; j++)
            {
                GC_path(j);
                mod(j + 1);
                { Share m("m10"); mod(10); }
            }
        }

        mod(5);
        { Share m("m10"); mod(10); }

    }

    mod(2);

    cout << "(10) 1+3.(m10+4+3x(i+1+m10)+5+m10)+2 : " << pb.sum() << '\n';
}

void simple11()
{
    PathBlock pb;

    PathBlock pb3("pb3");
    for ( int j = 0; j < 3; j++)
    {
        GC_path(j);
        mod(j + 1);
        //{ Share m("m10"); mod(10); }
    }
    pb3.merge();

    cout << "(11) 3x(i+1) : " << pb.sum() << '\n';
}

void simple12()
{
    PathBlock pb;

    { Share m("m10"); mod(10); }

    {
        GC_PAR;
        for ( int j = 0; j < 3; j++)
        {
            GC_share;
            { Share m("m10"); mod(10); }
        }
    }

    { Share m("m10"); mod(10); }


    cout << "(12) m10+3:(m10)+m10 : " << pb.sum() << '\n';
}

void simple13()
{
    PathBlock pb0;

    for ( int i = 0; i < 2; i++ )
    {
        {
            //GC_share;
            Share sha("sha", true);
            {
                mod(1);
                PathBlock pb1 {gw::PAR};
                for ( int j = 0; j < 1; j++ )
                {
                    Share path("m10");
                    mod(10);
                    //path.debug();
                }
                //pb1.debug("pb1");
            }
            //sha.debug();
        }
        //pb0.debug("pb0");
    }

    cout << "(13) 2.(1:10) : " << pb0.sum() << '\n';
}

void simple14()
{
    PathBlock pb0;

    {Share m("m"); mod(10);}

    {
        GC_SEQ;
        for ( int i = 0; i < 3; i++ )
        {
            GC_share;
            for ( int j = 0; j < 1; j++ )
            {
                Share m("m");
                mod(10);
            }
        }
    }

    {Share m("m"); mod(10);}

    cout << "(14) m10+3.(m10)+m10 : " << pb0.sum() << '\n';
}

void simple15()
{
    PathBlock pb0;

    {Share m("m"); mod(10);}

    {
        GC_SEQ;
        for ( int i = 0; i < 3; i++ )
        {
            Share m("m");
            mod(10);
        }
    }

    {Share m("m"); mod(10);}

    cout << "(15) m10+3.(m10)+m10 : " << pb0.sum() << '\n';
}

void simple16()
{
    PathBlock pb0;

    {Share m("m"); mod(10);}

    {
        GC_PAR;
        for ( int i = 0; i < 3; i++ )
        {
            Share m("m");
            mod(10);
        }
    }

    {Share m("m"); mod(10);}

    cout << "(16) m10+3:(m10)+m10 : " << pb0.sum() << '\n';
}

void simple17()
{
    PathBlock pb0;
    {
        GC_PAR;
        for ( int i = 0; i < 3; i++ )
        {
            Share m("m");
            mod(10);
        }
    }

    {Share m("m5"); mod(5);}

    cout << "(17) 3:(m10)+5 : " << pb0.sum() << '\n';
}

void simple18()
{
    PathBlock pb0;
    {
        GC_SEQ;
        for ( int i = 0; i < 3; i++ )
        {
            Share m("m");
            mod(10);
        }
    }

    {Share m("m5"); mod(5);}

    cout << "(18) 3.(m10)+5 : " << pb0.sum() << '\n';
}


void mod1()
{
	GC_SEQ;
	Share m("mod1");
	GC_share;
	mod(1);
}

void mod1x()
{
	GC_SEQ;
	Share m("modx");
	GC_share;
	mod1();
}

void mod1y()
{
	GC_SEQ;
	Share m("mody");
	GC_share;
	mod1();
}

void test01()
{
    PathBlock pb;
	mod1x();
	mod1x();
    cout << "(01) [2 1 2] : " << pb.sum() << '\n';
}

void test02()
{
    PathBlock pb;
	mod1x();
	mod1y();
	mod1x();
	mod1y();
    cout << "(02) [4 1 4] : " << pb.sum() << '\n';
}
